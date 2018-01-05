/**
 @file Fft.c
 @author Greg Lee
 @version 1.0.0
 @brief: "Fast Fourier Transform"
 
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee

 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0):
 
 1. Permission is hereby granted to use, copy, modify and/or
    distribute this package, provided that:
       * copyright notices are retained unchanged,
       * any distribution of this package, whether modified or not,
         includes this license text.
 2. Permission is hereby also granted to distribute binary programs
    which depend on this package. If the binary program depends on a
    modified version of this package, you are encouraged to publicly
    release the modified version of this package. 

 THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT WARRANTY. ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE AUTHORS BE LIABLE TO ANY PARTY FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES ARISING IN ANY WAY OUT OF THE USE OF THIS PACKAGE.
 
 @section Description

 Function definitions for the opaque Fft_t type.

*/

#include "Fft.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdlib.h>
#include <math.h>   
#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   defines
*/

#define FFT_TYPE 0xA5000B04

#define DTOR (M_PI/180.0)
#define RTOD (180.0/M_PI)

/**
   Note that this include file does NOT have an include guard - it may
   be included multiple times with different macro defintions.

   Defines that must be present (external to this file):

   Prefix - string used to name this container type
   Matvec_prefix - string used to name the vector type
   Matvec_magnitude_prefix - string used to name the magnitude vector type
   Type   - the type of the value
   Magnitude_type - the type of the magnitude or precision of Type

   Macros that must be present (external to this file):

   DEFAULT_VALUE              -  constant that is the default value for type (zero)
   ONE_VALUE                  -  constant that is the "one" value for type
   IS_INVERTIBLE              -  constant 0 if not or 1 if type is invertible
   NEGATE_FUNCTION            -  additive inverse of type value
   ADD_FUNCTION               -  adds two type values
   SQUARED_MAGNITUDE_FUNCTION -  squared magnitude of type value
   MULTIPLY_FUNCTION          -  multiplies two type values
   INVERSE_FUNCTION           -  multiplicative inverse of type value
   CONJUGATE_FUNCTION         -  complex conjugate of type value
   EQUAL_FUNCTION             -  1 if items are equal, 0 otherwise
   DUPLICATE_FUNCTION         -  makes duplicate of a type value
   WINDOW_FUNCTION            -  computes the fft window
   PHASE_FUNCTION             -  computes the phase of Type
   SET_FROM                   -  sets value from another
   DISPOSE_FUNCTION           -  frees a type value

*/

/**
   Fft structure
*/

struct Fft_struct( Prefix )
{
   int32_t type;
   
   // length
   int32_t length;
   int32_t log_length;
   
   // flags
   int32_t is_psd_done;
   int32_t is_log_psd_done;
   int32_t is_phase_done;
   int32_t is_phase_degrees_done;
   
   // input vector
   Matvec_type( Matvec_prefix ) *input;

   // output vector
   Matvec_type( Matvec_prefix ) *output;

   // power spectral density vector
   Matvec_type( Matvec_magnitude_prefix ) *psd;

   // log power spectral density vector
   Matvec_type( Matvec_magnitude_prefix ) *log_psd;

   // phase vector
   Matvec_type( Matvec_magnitude_prefix ) *phase;

   // phase degrees vector
   Matvec_type( Matvec_magnitude_prefix ) *phase_degrees;

   // bit reverse array
   int32_t *bit_reverse;

   // coefficients vector
   Matvec_type( Matvec_prefix ) *coefficients;

   // window vector
   Matvec_type( Matvec_magnitude_prefix ) *window;

   // multithread values if we include threading support
   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
fft_done_implies_matrices_not_null( Fft_type( Prefix ) *p )
{
   int32_t result = 0;

   if (
         ( (*p).input != NULL )
         &&
         ( (*p).output != NULL )
         &&
         ( (*p).psd != NULL )
         &&
         ( (*p).log_psd != NULL )
         &&
         ( (*p).phase != NULL )
         &&
         ( (*p).phase_degrees != NULL )
         &&
         ( (*p).bit_reverse != NULL )
         &&
         ( (*p).coefficients != NULL )
         &&
         ( (*p).window != NULL )
      )
   {
      result = 1;
   }
   
   return result;
}

static
int32_t
length_positive( Fft_type( Prefix ) *p )
{
   int32_t result = 0;

   if ( ( (*p).log_length > 0 ) && ( (*p).length > 0 ) )
   {
      result = 1;
   }

   return result;
}

static
void invariant( Fft_type( Prefix ) *p )
{
   assert(((void) "fft done implies matrices not null", fft_done_implies_matrices_not_null( p ) ));
   assert(((void) "length positive", length_positive( p ) ));
   return;
}

#else

static
void invariant( p )
{
   return;
}

#endif

/**
   Internal routines
*/

static void set_psd
( 
   Fft_type( Prefix ) *fft
);

static void set_log_psd
( 
   Fft_type( Prefix ) *fft
);

static void set_phase
( 
   Fft_type( Prefix ) *fft
);

static void set_phase_degrees
( 
   Fft_type( Prefix ) *fft
);

static void set_window
( 
   Fft_type( Prefix ) *fft
);

static void set_bit_reverse
( 
   Fft_type( Prefix ) *fft
);

static void set_coefficients
( 
   Fft_type( Prefix ) *fft
);

static void bit_reverse
( 
   Fft_type( Prefix ) *fft,
   Matvec_type( Matvec_prefix ) *v
);

static int32_t is_power_of_two
( 
   int32_t length
);

static int32_t log_2i
( 
   int32_t length
);

/**
   Fft_make
*/

Fft_type( Prefix ) *
Fft_make( Prefix )( int32_t length )
{
   PRECONDITION( "length", is_power_of_two( length ) == 1 );
   
   // allocate fft struct
   Fft_type( Prefix ) * fft
      = ( Fft_type( Prefix ) * ) calloc( 1, sizeof( Fft_type( Prefix ) ) );

   // set type code
   (*fft).type = FFT_TYPE;
   
   // set length, log length
   (*fft).length = length;
   (*fft).log_length = log_2i( length );

   // set flags
   (*fft).is_psd_done = 0;
   (*fft).is_log_psd_done = 0;
   (*fft).is_phase_done = 0;
   (*fft).is_phase_degrees_done = 0;
   
   // allocate vectors, array
   (*fft).input = Matvec_make_column_vector( Matvec_prefix )( length );
   (*fft).output = Matvec_make_column_vector( Matvec_prefix )( length );
   (*fft).psd = Matvec_make_column_vector( Matvec_magnitude_prefix )( length );
   (*fft).log_psd = Matvec_make_column_vector( Matvec_magnitude_prefix )( length );
   (*fft).phase = Matvec_make_column_vector( Matvec_magnitude_prefix )( length );
   (*fft).phase_degrees = Matvec_make_column_vector( Matvec_magnitude_prefix )( length );
   (*fft).bit_reverse = ( int32_t * ) calloc( length, sizeof( int32_t ) );
   (*fft).coefficients = Matvec_make_column_vector( Matvec_prefix )( length );
   (*fft).window = Matvec_make_column_vector( Matvec_magnitude_prefix )( length );
   
   // set bit reverse, window, coefficients
   set_bit_reverse( fft );
   set_window( fft );
   set_coefficients( fft );
   
   MULTITHREAD_MUTEX_INIT( (*fft).mutex );

   INVARIANT( fft );

   return fft;
}


/**
   Fft_dispose
*/

void
Fft_dispose( Prefix )( Fft_type( Prefix ) *fft )
{
   PRECONDITION( "fft not null", fft != NULL );
   PRECONDITION( "fft type ok", (*fft).type == FFT_TYPE );  
   LOCK( (*fft).mutex );
   INVARIANT( fft );

   // dispose of internal only vectors and array
   free( (*fft).bit_reverse );
   Matvec_dispose_with_contents( Matvec_prefix )( (*fft).coefficients );
   Matvec_dispose_with_contents( Matvec_magnitude_prefix )( (*fft).window );
   
   MULTITHREAD_MUTEX_DESTROY( (*fft).mutex );

   // delete fft struct
   free( fft );

   return;
}

/**
   Fft_dispose_with_contents
*/

void
Fft_dispose_with_contents( Prefix )( Fft_type( Prefix ) *fft )
{
   PRECONDITION( "fft not null", fft != NULL );
   PRECONDITION( "fft type ok", (*fft).type == FFT_TYPE );  
   LOCK( (*fft).mutex );
   INVARIANT( fft );

   // dispose of vectors and array
   Matvec_dispose_with_contents( Matvec_prefix )( (*fft).input );
   Matvec_dispose_with_contents( Matvec_prefix )( (*fft).output );
   Matvec_dispose_with_contents( Matvec_magnitude_prefix )( (*fft).psd );
   Matvec_dispose_with_contents( Matvec_magnitude_prefix )( (*fft).log_psd );
   Matvec_dispose_with_contents( Matvec_magnitude_prefix )( (*fft).phase );
   Matvec_dispose_with_contents( Matvec_magnitude_prefix )( (*fft).phase_degrees );
   free( (*fft).bit_reverse );
   Matvec_dispose_with_contents( Matvec_prefix )( (*fft).coefficients );
   Matvec_dispose_with_contents( Matvec_magnitude_prefix )( (*fft).window );
   
   MULTITHREAD_MUTEX_DESTROY( (*fft).mutex );
   
   // delete fft struct
   free( fft );

   return;
}

/**
   Fft_input
*/

Matvec_type( Matvec_prefix ) *
Fft_input( Prefix )( Fft_type( Prefix ) *fft )
{
   PRECONDITION( "fft not null", fft != NULL );
   PRECONDITION( "fft type ok", (*fft).type == FFT_TYPE );  
   LOCK( (*fft).mutex );
   INVARIANT( fft );

   Matvec_type( Matvec_prefix ) *result = (*fft).input;

   INVARIANT( fft );
   UNLOCK( (*fft).mutex );

   return result;
}

/**
   Fft_output
*/

Matvec_type( Matvec_prefix ) *
Fft_output( Prefix )( Fft_type( Prefix ) *fft )
{
   PRECONDITION( "fft not null", fft != NULL );
   PRECONDITION( "fft type ok", (*fft).type == FFT_TYPE );  
   LOCK( (*fft).mutex );
   INVARIANT( fft );

   Matvec_type( Matvec_prefix ) *result = (*fft).output;

   INVARIANT( fft );
   UNLOCK( (*fft).mutex );

   return result;
}

/**
   Fft_psd
*/

Matvec_type( Matvec_magnitude_prefix ) *
Fft_psd( Prefix )( Fft_type( Prefix ) *fft )
{
   PRECONDITION( "fft not null", fft != NULL );
   PRECONDITION( "fft type ok", (*fft).type == FFT_TYPE );  
   LOCK( (*fft).mutex );
   INVARIANT( fft );

   if ( (*fft).is_psd_done == 0 )
   {
      set_psd( fft );
   }
   
   Matvec_type( Matvec_magnitude_prefix ) *result = (*fft).psd;

   INVARIANT( fft );
   UNLOCK( (*fft).mutex );

   return result;
}

/**
   Fft_log_psd
*/

Matvec_type( Matvec_magnitude_prefix ) *
Fft_log_psd( Prefix )( Fft_type( Prefix ) *fft )
{
   PRECONDITION( "fft not null", fft != NULL );
   PRECONDITION( "fft type ok", (*fft).type == FFT_TYPE );  
   LOCK( (*fft).mutex );
   INVARIANT( fft );

   if ( (*fft).is_log_psd_done == 0 )
   {
      set_log_psd( fft );
   }
   
   Matvec_type( Matvec_magnitude_prefix ) *result = (*fft).log_psd;

   INVARIANT( fft );
   UNLOCK( (*fft).mutex );

   return result;
}

/**
   Fft_phase
*/

Matvec_type( Matvec_magnitude_prefix ) *
Fft_phase( Prefix )( Fft_type( Prefix ) *fft )
{
   PRECONDITION( "fft not null", fft != NULL );
   PRECONDITION( "fft type ok", (*fft).type == FFT_TYPE );  
   LOCK( (*fft).mutex );
   INVARIANT( fft );

   if ( (*fft).is_phase_done == 0 )
   {
      set_phase( fft );
   }
   
   Matvec_type( Matvec_magnitude_prefix ) *result = (*fft).phase;

   INVARIANT( fft );
   UNLOCK( (*fft).mutex );

   return result;
}

/**
   Fft_phase_degrees
*/

Matvec_type( Matvec_magnitude_prefix ) *
Fft_phase_degrees( Prefix )( Fft_type( Prefix ) *fft )
{
   PRECONDITION( "fft not null", fft != NULL );
   PRECONDITION( "fft type ok", (*fft).type == FFT_TYPE );  
   LOCK( (*fft).mutex );
   INVARIANT( fft );

   if ( (*fft).is_phase_degrees_done == 0 )
   {
      set_phase_degrees( fft );
   }
   
   Matvec_type( Matvec_magnitude_prefix ) *result = (*fft).phase_degrees;

   INVARIANT( fft );
   UNLOCK( (*fft).mutex );

   return result;
}

/**
   Fft_set_input
*/

void
Fft_set_input( Prefix )( Fft_type( Prefix ) *fft, Matvec_type( Matvec_prefix ) *input )
{
   PRECONDITION( "fft not null", fft != NULL );
   PRECONDITION( "fft type ok", (*fft).type == FFT_TYPE );  
   PRECONDITION( "input right size", Matvec_vector_length( Matvec_prefix )( input ) == (*fft).length );
   LOCK( (*fft).mutex );
   INVARIANT( fft );

   Matvec_set_from( Matvec_prefix )( (*fft).input, input );

   (*fft).is_psd_done = 0;
   (*fft).is_log_psd_done = 0;
   (*fft).is_phase_done = 0;
   (*fft).is_phase_degrees_done = 0;
   
   INVARIANT( fft );
   UNLOCK( (*fft).mutex );

   return;
}

/**
   Fft_set_output
*/

void
Fft_set_output( Prefix )( Fft_type( Prefix ) *fft, Matvec_type( Matvec_prefix ) *output )
{
   PRECONDITION( "fft not null", fft != NULL );
   PRECONDITION( "fft type ok", (*fft).type == FFT_TYPE );  
   PRECONDITION( "output right size", Matvec_vector_length( Matvec_prefix )( output ) == (*fft).length );
   LOCK( (*fft).mutex );
   INVARIANT( fft );

   Matvec_set_from( Matvec_prefix )( (*fft).output, output );

   (*fft).is_psd_done = 0;
   (*fft).is_log_psd_done = 0;
   (*fft).is_phase_done = 0;
   (*fft).is_phase_degrees_done = 0;
   
   INVARIANT( fft );
   UNLOCK( (*fft).mutex );

   return;
}

/**
   Fft_fft
*/

void
Fft_fft( Prefix )( Fft_type( Prefix ) *fft )
{
   PRECONDITION( "fft not null", fft != NULL );
   PRECONDITION( "fft type ok", (*fft).type == FFT_TYPE );  
   LOCK( (*fft).mutex );
   INVARIANT( fft );

   int32_t i = 0;
   int32_t j = 0;
   int32_t jrv = 0;
   int32_t k = 0;
   int32_t l = 0;
   int32_t n = 0;
   int32_t log_length = 0;
   int32_t n2 = 0;
   int32_t ibrv = 0;
   Type cis = DEFAULT_VALUE;
   Type g = DEFAULT_VALUE;
   Type g1 = DEFAULT_VALUE;
   Type g2 = DEFAULT_VALUE;
   Magnitude_type d = 0.0;
   Matvec_type( Matvec_prefix ) *v1 = NULL;
   Matvec_type( Matvec_prefix ) *v2 = NULL;
   Matvec_type( Matvec_magnitude_prefix ) *mv = NULL;
   int32_t *ia = NULL;
   
   n = (*fft).length;
   log_length = (*fft).log_length;
   
   v1 = (*fft).input;
   v2 = (*fft).output;
   mv = (*fft).window;
   
   // put windowed input into output
   for ( i=0; i<n; i++ )
   {
      SET_FROM( g, MULTIPLY_FUNCTION( Matvec_vector_item( Matvec_magnitude_prefix )( mv, i ), Matvec_vector_item( Matvec_prefix )( v1, i ) ) );
      Matvec_vector_put( Matvec_prefix )( v2, g, i );         
   }

   ia = (*fft).bit_reverse;
   v1 = (*fft).output;
   v2 = (*fft).coefficients;
   
   // perform the fft butterflies
   for ( i=0, j=0, l=log_length-1, n2=n/2; i<log_length; i++ )
   {
      for ( ; j<n; )
      {
         for ( k=0; k<n2; k++ )
         {
            jrv = j >> l;
            ibrv = ia[jrv];
            cis = Matvec_vector_item( Matvec_prefix )( v2, ibrv );
            SET_FROM( g, MULTIPLY_FUNCTION( Matvec_vector_item( Matvec_prefix )( v1, j+n2 ), cis ) ); 
            SET_FROM( g1, NEGATE_FUNCTION( g ) );
            SET_FROM( g1, ADD_FUNCTION( Matvec_vector_item( Matvec_prefix )( v1, j ), g1 ) );
            SET_FROM( g2, ADD_FUNCTION( Matvec_vector_item( Matvec_prefix )( v1, j ), g ) );
            Matvec_vector_put( Matvec_prefix )( v1, g1, j+n2 );
            Matvec_vector_put( Matvec_prefix )( v1, g2, j );
            
            j = j + 1;
         }
         j = j + n2;
      }
      
      // update offsets
      j = 0;
      l = l - 1;
      n2 = n2/2;
      
   }
   
   // scale and bit reverse output
   d = 2.0/n;
   SET_FROM( g, d );
   Matvec_scale( Matvec_prefix )( v1, g );
   
   bit_reverse( fft, (*fft).output );
   
   (*fft).is_psd_done = 0;
   (*fft).is_log_psd_done = 0;
   (*fft).is_phase_done = 0;
   (*fft).is_phase_degrees_done = 0;
   
   INVARIANT( fft );
   UNLOCK( (*fft).mutex );

   return;
}

/**
   Fft_inverse_fft
*/

void
Fft_inverse_fft( Prefix )( Fft_type( Prefix ) *fft )
{
   PRECONDITION( "fft not null", fft != NULL );
   PRECONDITION( "fft type ok", (*fft).type == FFT_TYPE );  
   LOCK( (*fft).mutex );
   INVARIANT( fft );

   int32_t i = 0;
   int32_t j = 0;
   int32_t jrv = 0;
   int32_t k = 0;
   int32_t l = 0;
   int32_t n = 0;
   int32_t log_length = 0;
   int32_t n2 = 0;
   int32_t ibrv = 0;
   Type cis = DEFAULT_VALUE;
   Type g = DEFAULT_VALUE;
   Type g1 = DEFAULT_VALUE;
   Type g2 = DEFAULT_VALUE;
   Magnitude_type d = 0.0;
   Matvec_type( Matvec_prefix ) *v1 = NULL;
   Matvec_type( Matvec_prefix ) *v2 = NULL;
   int32_t *ia = NULL;
   
   n = (*fft).length;
   log_length = (*fft).log_length;
   
   v1 = (*fft).input;
   v2 = (*fft).output;
   
   // put output into input
   for ( i=0; i<n; i++ )
   {
      SET_FROM( g, Matvec_vector_item( Matvec_prefix )( v2, i ) );
      Matvec_vector_put( Matvec_prefix )( v1, g, i );         
   }

   ia = (*fft).bit_reverse;
   v1 = (*fft).input;
   v2 = (*fft).coefficients;
   
   // perform the fft butterflies
   for ( i=0, j=0, l=log_length-1, n2=n/2; i<log_length; i++ )
   {
      for ( ; j<n; )
      {
         for ( k=0; k<n2; k++ )
         {
            jrv = j >> l;
            ibrv = ia[jrv];
            cis = Matvec_vector_item( Matvec_prefix )( v2, ibrv );
            SET_FROM( g, MULTIPLY_FUNCTION( Matvec_vector_item( Matvec_prefix )( v1, j+n2 ), CONJUGATE_FUNCTION( cis ) ) ); 
            SET_FROM( g1, NEGATE_FUNCTION( g ) );
            SET_FROM( g1, ADD_FUNCTION( Matvec_vector_item( Matvec_prefix )( v1, j ), g1 ) );
            SET_FROM( g2, ADD_FUNCTION( Matvec_vector_item( Matvec_prefix )( v1, j ), g ) );
            Matvec_vector_put( Matvec_prefix )( v1, g1, j+n2 );
            Matvec_vector_put( Matvec_prefix )( v1, g2, j );
            
            j = j + 1;
         }
         j = j + n2;
      }
      
      // update offsets
      j = 0;
      l = l - 1;
      n2 = n2/2;
      
   }
   
   // scale and bit reverse output
   d = 0.5;
   SET_FROM( g, d );
   Matvec_scale( Matvec_prefix )( v1, g );
   
   bit_reverse( fft, (*fft).input );
   
   (*fft).is_psd_done = 0;
   (*fft).is_log_psd_done = 0;
   (*fft).is_phase_done = 0;
   (*fft).is_phase_degrees_done = 0;
   
   INVARIANT( fft );
   UNLOCK( (*fft).mutex );

   return;
}

/**
   set_psd
*/

static 
void set_psd
( 
   Fft_type( Prefix ) *fft
)
{
   int32_t i = 0;
   int32_t n = 0;
   Magnitude_type d = 0.0;
   Matvec_type( Matvec_prefix ) *v = NULL;
   Matvec_type( Matvec_magnitude_prefix ) *psd = NULL;
   
   if ( (*fft).is_psd_done == 0 )
   {
      n = (*fft).length;
      v = (*fft).output;
      psd = (*fft).psd;
         
      for ( i=0; i<n; i++ )
      {
         d = sqrt( SQUARED_MAGNITUDE_FUNCTION( Matvec_vector_item( Matvec_prefix )( v, i ) ) ); 
         Matvec_vector_put( Matvec_magnitude_prefix )( psd, d, i );
      }
      (*fft).is_psd_done = 1;
   }

   return;
}

/**
   set_log_psd
*/

static 
void set_log_psd
( 
   Fft_type( Prefix ) *fft
)
{
   int32_t i = 0;
   int32_t n = 0;
   Magnitude_type d = 0.0;
   Matvec_type( Matvec_prefix ) *v = NULL;
   Matvec_type( Matvec_magnitude_prefix ) *log_psd = NULL;
   
   if ( (*fft).is_log_psd_done == 0 )
   {
      n = (*fft).length;
      v = (*fft).output;
      log_psd = (*fft).log_psd;
         
      for ( i=0; i<n; i++ )
      {
         d = 10.0*log10( SQUARED_MAGNITUDE_FUNCTION( Matvec_vector_item( Matvec_prefix )( v, i ) ) ); 
         Matvec_vector_put( Matvec_magnitude_prefix )( log_psd, d, i );
      }
      (*fft).is_log_psd_done = 1;
   }
   
   return;
}

/**
   set_phase
*/

static 
void set_phase
( 
   Fft_type( Prefix ) *fft
)
{
   int32_t i = 0;
   int32_t n = 0;
   Magnitude_type d = 0.0;
   Matvec_type( Matvec_prefix ) *v = NULL;
   Matvec_type( Matvec_magnitude_prefix ) *phase = NULL;
   
   if ( (*fft).is_phase_done == 0 )
   {
      n = (*fft).length;
      v = (*fft).output;
      phase = (*fft).phase;
         
      for ( i=0; i<n; i++ )
      {
         d = PHASE_FUNCTION( Matvec_vector_item( Matvec_prefix )( v, i ) ); 
         Matvec_vector_put( Matvec_magnitude_prefix )( phase, d, i );
      }
      (*fft).is_phase_done = 1;
   }

   return;
}

/**
   set_phase_degrees
*/

static 
void set_phase_degrees
( 
   Fft_type( Prefix ) *fft
)
{
   int32_t i = 0;
   int32_t n = 0;
   Magnitude_type d = 0.0;
   Matvec_type( Matvec_prefix ) *v = NULL;
   Matvec_type( Matvec_magnitude_prefix ) *phase_degrees = NULL;
   
   if ( (*fft).is_phase_degrees_done == 0 )
   {
      n = (*fft).length;
      v = (*fft).output;
      phase_degrees = (*fft).phase_degrees;
         
      for ( i=0; i<n; i++ )
      {
         d = RTOD*PHASE_FUNCTION( Matvec_vector_item( Matvec_prefix )( v, i ) ); 
         Matvec_vector_put( Matvec_magnitude_prefix )( phase_degrees, d, i );
      }
      (*fft).is_phase_degrees_done = 1;
   }

   return;
}

/**
   set_bit_reverse
*/

static 
void set_bit_reverse
( 
   Fft_type( Prefix ) *fft
)
{
   int32_t i = 0;
   int32_t j = 0;
   int32_t ui = 0;
   int32_t uj = 0;
   int32_t n = 0;
   int32_t log_length = 0;
   int32_t *bit_reverse = NULL;
   
   n = (*fft).length;
   log_length = (*fft).log_length;
   bit_reverse = (*fft).bit_reverse;
      
   for ( i=0; i<n; i++ )
   {
      ui = 0;
      uj = i;
      
      for( j=0; j<log_length; j++ )
      {
         ui = 2*ui;
         if ( uj % 2 == 1 )
         {
            ui = ui + 1;
         }
         uj = uj/2;
      }
      bit_reverse[i] = ui; 
   }

   return;
}

/**
   set_coefficients
*/

static 
void set_coefficients
( 
   Fft_type( Prefix ) *fft
)
{
   int32_t i = 0;
   int32_t n = 0;
   Type g = DEFAULT_VALUE;
   Magnitude_type x = 0.0;
   Magnitude_type y = 0.0;
   Matvec_type( Matvec_prefix ) *coefficients = NULL;
   
   n = (*fft).length;
   coefficients = (*fft).coefficients;
      
   y = 2.0*M_PI/( 1.0*n );
   
   for ( i=0; i<n; i++ )
   {
      x = y*i;
      SET_FROM( g, ( Type ) ( cos(x) + sin(x)*I ) ); 
      Matvec_vector_put( Matvec_prefix )( coefficients, g, i );
   }

   return;
}

/**
   set_window
*/

static 
void set_window
( 
   Fft_type( Prefix ) *fft
)
{
   int32_t i = 0;
   int32_t n = 0;
   Magnitude_type x = 0.0;
   Magnitude_type y = 0.0;
   Magnitude_type d = 0.0;
   Matvec_type( Matvec_magnitude_prefix ) *window = NULL;
   
   n = (*fft).length;
   window = (*fft).window;
      
   y = 2.0*M_PI/( 1.0*n );
   
   for ( i=0; i<n; i++ )
   {
      x = y*i;
      d =  WINDOW_FUNCTION( i, n, x ); 
      Matvec_vector_put( Matvec_magnitude_prefix )( window, d, i );
   }

   return;
}

static 
void bit_reverse
( 
   Fft_type( Prefix ) *fft,
   Matvec_type( Matvec_prefix ) *v
)
{
   int32_t i = 0;
   int32_t n = 0;
   int32_t ibrv = 0;
   Type g1 = DEFAULT_VALUE;
   Type g2 = DEFAULT_VALUE;
   int32_t *brv = NULL;
   
   n = (*fft).length;
   brv = (*fft).bit_reverse;
   
   for( i=0; i<n; i++ )
   {
      ibrv = brv[i];
      
      if ( ibrv > i )
      {
         g1 = Matvec_vector_item( Matvec_prefix ) ( v, i );
         g2 = Matvec_vector_item( Matvec_prefix ) ( v, ibrv );
         
         Matvec_vector_put( Matvec_prefix )( v, g2, i );
         Matvec_vector_put( Matvec_prefix )( v, g1, ibrv );
      }
   }
   
   return;
}

/**
   is_power_of_two
*/

static 
int32_t is_power_of_two
( 
   int32_t length
)
{
   int32_t result = 0;
   int32_t i = 0;
   int32_t m = 0;
   
   m = 1;
   for ( i=1; i<65537; i++ )
   {
      m = 2*m;
      
      if ( m == length )
      {
         result = 1;
         break;
      }
   }
   
   return result;
}

/**
   log_2i
*/

static 
int32_t log_2i
( 
   int32_t length
)
{
   int32_t result = 0;
   Magnitude_type d = 0.0;

   d = log( 1.0*length )/log( 2.0 );
      
   result = ( int32_t ) floor( ( d + 0.5 ) );   
   
   return result;
}

/* End of file */

