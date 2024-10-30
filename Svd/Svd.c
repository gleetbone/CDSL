/**
 @file Svd.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Singular Value Decomposition"

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

 Function definitions for the opaque Svd_t type.

*/

#include "Svd.h"

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

/**
   Note that this include file does NOT have an include guard - it may
   be included multiple times with different macro defintions.

   Defines that must be present (external to this file):

   Prefix - string used to name this container type
   Matvec_prefix - string used to name the matrix type
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
   SET_FROM                   -  sets value from another
   DISPOSE_FUNCTION           -  frees a type value

*/

/**
   Svd structure
*/

struct Svd_struct( Prefix )
{
   int32_t _type;
   int32_t _item_type;

   // rotation error
   Magnitude_type rotation_error;

   // singular value threshold
   Magnitude_type singular_value_threshold;

   // flags
   int32_t is_column_svd;
   int32_t is_svd_done;

   // input matrix
   Matvec_type( Matvec_prefix ) *input;

   // left singular values matrix
   Matvec_type( Matvec_prefix ) *matrix;

   // right singular values matrix
   Matvec_type( Matvec_prefix ) *rotation_matrix;

   // singular values vector
   Matvec_type( Matvec_prefix ) *singular_value;

   // multithread values if we include threading support
   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
svd_done_implies_matrices_not_null( Svd_type( Prefix ) *p )
{
   int32_t result = 1;

   if ( (*p).is_svd_done == 1 )
   {
      result = 0;

      if (
         ( (*p).input != NULL )
         &&
         ( (*p).matrix != NULL )
         &&
         ( (*p).rotation_matrix != NULL )
         &&
         ( (*p).singular_value != NULL )
      )
      {
         result = 1;
      }

   }

   return result;
}

static
int32_t
rotation_error_positive( Svd_type( Prefix ) *p )
{
   int32_t result = 0;

   if ( (*p).rotation_error > 0.0 )
   {
      result = 1;
   }

   return result;
}

static
int32_t
singular_value_threshold_positive( Svd_type( Prefix ) *p )
{
   int32_t result = 0;

   if ( (*p).singular_value_threshold > 0.0 )
   {
      result = 1;
   }

   return result;
}

static
void invariant( Svd_type( Prefix ) *p )
{
   assert( ( ( void ) "svd done implies matrices not null", svd_done_implies_matrices_not_null( p ) ) );
   assert( ( ( void ) "rotation error positive", rotation_error_positive( p ) ) );
   assert( ( ( void ) "singular value threshold positive", singular_value_threshold_positive( p ) ) );
   return;
}

#endif

/**
   Internal routines
*/

static void row_vector_rotate
(
   Svd_type( Prefix ) *svd,
   Matvec_type( Matvec_prefix ) *a,
   Matvec_type( Matvec_prefix ) *b,
   int32_t i1,
   int32_t i2
);

static void row_rotation
(
   Svd_type( Prefix ) *svd,
   Matvec_type( Matvec_prefix ) *a,
   int32_t i1,
   int32_t i2,
   Type c,
   Type s
);

static void row_rotation_with_swap
(
   Svd_type( Prefix ) *svd,
   Matvec_type( Matvec_prefix ) *a,
   int32_t i1,
   int32_t i2,
   Type c,
   Type s
);

static void column_vector_rotate
(
   Svd_type( Prefix ) *svd,
   Matvec_type( Matvec_prefix ) *a,
   Matvec_type( Matvec_prefix ) *b,
   int32_t i1,
   int32_t i2
);

static void column_rotation
(
   Svd_type( Prefix ) *svd,
   Matvec_type( Matvec_prefix ) *a,
   int32_t i1,
   int32_t i2,
   Type c,
   Type s
);

static void column_rotation_with_swap
(
   Svd_type( Prefix ) *svd,
   Matvec_type( Matvec_prefix ) *a,
   int32_t i1,
   int32_t i2,
   Type c,
   Type s
);

static void row_svd
(
   Svd_type( Prefix ) *svd
);

static void column_svd
(
   Svd_type( Prefix ) *svd
);

/**
   Svd_make
*/

Svd_type( Prefix ) *
Svd_make( Prefix )( void )
{
   // allocate svd struct
   Svd_type( Prefix ) * result
      = ( Svd_type( Prefix ) * ) calloc( 1, sizeof( Svd_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );
   
   // set type
   (*result)._type = SVD_TYPE;
   (*result)._item_type = Type_Code;

   // set error values
   (*result).rotation_error = 0.0000001;
   (*result).singular_value_threshold = 0.0000001;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}


/**
   Svd_dispose
*/

void
Svd_dispose( Prefix )( Svd_type( Prefix ) **svd )
{
   PRECONDITION( "svd not null", svd != NULL );
   PRECONDITION( "svd not null", *svd != NULL );
   PRECONDITION( "svd type OK", ( (**svd)._type == SVD_TYPE ) && ( (**svd)._item_type == Type_Code ) );
   LOCK( (**svd).mutex );
   INVARIANT(*svd);

   MULTITHREAD_MUTEX_DESTROY( (**svd).mutex );

   // delete svd struct
   free(*svd);

   // set to NULL
   *svd = NULL;

   return;
}

/**
   Svd_deep_dispose
*/

void
Svd_deep_dispose( Prefix )( Svd_type( Prefix ) **svd )
{
   PRECONDITION( "svd not null", svd != NULL );
   PRECONDITION( "svd not null", *svd != NULL );
   PRECONDITION( "svd type OK", ( (**svd)._type == SVD_TYPE ) && ( (**svd)._item_type == Type_Code ) );
   LOCK( (**svd).mutex );
   INVARIANT(*svd);

   // delete svd items
   if ( (**svd).input != NULL )
   {
      Matvec_deep_dispose( Matvec_prefix )( &(**svd).input );
      (**svd).input = NULL;
   }

   if ( (**svd).matrix != NULL )
   {
      Matvec_deep_dispose( Matvec_prefix )( &(**svd).matrix );
      (**svd).matrix = NULL;
   }

   if ( (**svd).rotation_matrix != NULL )
   {
      Matvec_deep_dispose( Matvec_prefix )( &(**svd).rotation_matrix );
      (**svd).rotation_matrix = NULL;
   }

   if ( (**svd).singular_value != NULL )
   {
      Matvec_deep_dispose( Matvec_prefix )( &(**svd).singular_value );
      (**svd).singular_value = NULL;
   }

   MULTITHREAD_MUTEX_DESTROY( (**svd).mutex );

   // delete svd struct
   free(*svd);

   // set to NULL
   *svd = NULL;

   return;
}

/**
   Svd_input
*/

Matvec_type( Matvec_prefix ) *
Svd_input( Prefix )( Svd_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == SVD_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Matvec_prefix ) *result = (*current).input;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Svd_singular_values
*/

Matvec_type( Matvec_prefix ) *
Svd_singular_values( Prefix )( Svd_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == SVD_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Matvec_prefix ) *result = (*current).singular_value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Svd_left_singular_vectors
*/

Matvec_type( Matvec_prefix ) *
Svd_left_singular_vectors( Prefix )( Svd_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == SVD_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Matvec_prefix ) *result = (*current).matrix;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Svd_right_singular_vectors
*/

Matvec_type( Matvec_prefix ) *
Svd_right_singular_vectors( Prefix )( Svd_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == SVD_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Matvec_prefix ) *result = (*current).rotation_matrix;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Svd_reconstructed_input
*/

Matvec_type( Matvec_prefix ) *
Svd_reconstructed_input( Prefix )( Svd_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == SVD_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Matvec_prefix ) *result = (*current).rotation_matrix;
   Matvec_type( Matvec_prefix ) *l = NULL;
   Matvec_type( Matvec_prefix ) *r = NULL;
   Matvec_type( Matvec_prefix ) *x = NULL;
   Type g = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t n = 0;

   if ( (*current).is_column_svd == 1 )
   {
      // copy lsv's and scale with singular values
      l = Matvec_copied( Matvec_prefix )( (*current).matrix );
      r = Matvec_copied( Matvec_prefix )( (*current).rotation_matrix );

      n = Matvec_columns( Matvec_prefix )( l );

      for( i = 0; i < n; i++ )
      {
         g = Matvec_vector_item( Matvec_prefix )( (*current).singular_value, i );
         Matvec_column_vector_scale( Matvec_prefix )( l, g, i );
      }

      // multiply lsv's by transpose of rsv's
      x = Matvec_hermitian_transposed( Matvec_prefix )( r );
      result = Matvec_multiplied( Matvec_prefix )( l, x );

      // dispose of temp variables
      Matvec_deep_dispose( Matvec_prefix )( &l );
      Matvec_deep_dispose( Matvec_prefix )( &r );
      Matvec_deep_dispose( Matvec_prefix )( &x );
   }
   else
   {
      // copy lsv's and scale with singular values
      l = Matvec_copied( Matvec_prefix )( (*current).matrix );
      r = Matvec_copied( Matvec_prefix )( (*current).rotation_matrix );

      n = Matvec_columns( Matvec_prefix )( l );

      for( i = 0; i < n; i++ )
      {
         g = Matvec_vector_item( Matvec_prefix )( (*current).singular_value, i );
         Matvec_row_vector_scale( Matvec_prefix )( l, g, i );
      }

      // multiply lsv's by transpose of rsv's
      x = Matvec_hermitian_transposed( Matvec_prefix )( l );
      result = Matvec_multiplied( Matvec_prefix )( x, r );

      // dispose of temp variables
      Matvec_deep_dispose( Matvec_prefix )( &l );
      Matvec_deep_dispose( Matvec_prefix )( &r );
      Matvec_deep_dispose( Matvec_prefix )( &x );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Svd_set_input
*/

void
Svd_set_input( Prefix )( Svd_type( Prefix ) *current, Matvec_type( Matvec_prefix ) *input )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == SVD_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "input not null", input != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // dispose of previous matrix, if any
   if ( (*current).input != NULL )
   {
      Matvec_dispose( Matvec_prefix )( &(*current).input );
   }

   (*current).input = input;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Svd_set_rotation_error
*/

void
Svd_set_rotation_error( Prefix )( Svd_type( Prefix ) *current, Magnitude_type rotation_error )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == SVD_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   (*current).rotation_error = rotation_error;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Svd_set_singular_value_threshold
*/

void
Svd_set_singular_value_threshold( Prefix )( Svd_type( Prefix ) *current, Magnitude_type singular_value_threshold )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == SVD_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   (*current).singular_value_threshold = singular_value_threshold;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Svd_inverse
*/

Matvec_type( Matvec_prefix ) *
Svd_inverse( Prefix )( Svd_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == SVD_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "input not null", (*current).input != NULL );
   PRECONDITION( "current is done", (*current).is_svd_done == 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Matvec_prefix ) *result = NULL;
   Matvec_type( Matvec_prefix ) *l = NULL;
   Matvec_type( Matvec_prefix ) *r = NULL;
   Matvec_type( Matvec_prefix ) *x = NULL;
   Type g = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t n = 0;
   Magnitude_type s1 = 0.0;
   Magnitude_type d = 0.0;

   if ( (*current).is_column_svd == 1 )
   {
      l = Matvec_copied( Matvec_prefix )( (*current).matrix );
      r = Matvec_copied( Matvec_prefix )( (*current).rotation_matrix );

      g = Matvec_vector_item( Matvec_prefix )( (*current).singular_value, 0 );
      s1 = sqrt( SQUARED_MAGNITUDE_FUNCTION( g ) );

      n = Matvec_columns( Matvec_prefix )( l );

      for ( i = 0; i < n; i++ )
      {
         g = Matvec_vector_item( Matvec_prefix )( (*current).singular_value, i );
         d = sqrt( SQUARED_MAGNITUDE_FUNCTION( g ) );

         if ( d > (*current).singular_value_threshold * s1 )
         {
            g = Matvec_vector_item( Matvec_prefix )( (*current).singular_value, i );
            g = INVERSE_FUNCTION( g );
         }
         else
         {
            g = DEFAULT_VALUE;
         }
         Matvec_column_vector_scale( Matvec_prefix )( l, g, i );
      }

      // multiply lsv's by transpose of rsv's
      x = Matvec_hermitian_transposed( Matvec_prefix )( l );
      result = Matvec_multiplied( Matvec_prefix )( r, x );

      // dispose of temp variables
      Matvec_deep_dispose( Matvec_prefix )( &l );
      Matvec_deep_dispose( Matvec_prefix )( &r );
      Matvec_deep_dispose( Matvec_prefix )( &x );
   }
   else
   {
      l = Matvec_copied( Matvec_prefix )( (*current).matrix );
      r = Matvec_copied( Matvec_prefix )( (*current).rotation_matrix );

      g = Matvec_vector_item( Matvec_prefix )( (*current).singular_value, 0 );
      s1 = sqrt( SQUARED_MAGNITUDE_FUNCTION( g ) );

      n = Matvec_columns( Matvec_prefix )( l );

      for ( i = 0; i < n; i++ )
      {
         g = Matvec_vector_item( Matvec_prefix )( (*current).singular_value, i );
         d = sqrt( SQUARED_MAGNITUDE_FUNCTION( g ) );

         if ( d > (*current).singular_value_threshold * s1 )
         {
            g = Matvec_vector_item( Matvec_prefix )( (*current).singular_value, i );
            g = INVERSE_FUNCTION( g );
         }
         else
         {
            g = DEFAULT_VALUE;
         }
         Matvec_row_vector_scale( Matvec_prefix )( l, g, i );
      }

      // multiply lsv's by transpose of rsv's
      x = Matvec_hermitian_transposed( Matvec_prefix )( r );
      result = Matvec_multiplied( Matvec_prefix )( x, l );

      // dispose of temp variables
      Matvec_deep_dispose( Matvec_prefix )( &l );
      Matvec_deep_dispose( Matvec_prefix )( &r );
      Matvec_deep_dispose( Matvec_prefix )( &x );
   }


   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Svd_svd
*/

void
Svd_svd( Prefix )( Svd_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == SVD_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current input not null", (*current).input != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t height = 0;
   int32_t width = 0;

   height = Matvec_rows( Matvec_prefix )( (*current).input );
   width = Matvec_columns( Matvec_prefix )( (*current).input );

   if ( height >= width )
   {
      column_svd( current );
   }
   else
   {
      row_svd( current );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   column_svd
*/

static
void
column_svd( Svd_type( Prefix ) *current )
{
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t n = 0;
   Type g = DEFAULT_VALUE;
   Magnitude_type d = 0.0;

   (*current).is_column_svd = 1;
   (*current).is_svd_done = 1;

   // dispose of previous matrices, if any
   if ( (*current).matrix != NULL )
   {
      Matvec_dispose( Matvec_prefix )( &(*current).matrix );
   }

   if ( (*current).rotation_matrix != NULL )
   {
      Matvec_dispose( Matvec_prefix )( &(*current).rotation_matrix );
   }

   if ( (*current).singular_value != NULL )
   {
      Matvec_dispose( Matvec_prefix )( &(*current).singular_value );
   }

   // get max of input width and height
   n = Matvec_columns( Matvec_prefix )( (*current).input );

   // set up matrices
   (*current).matrix = Matvec_copied( Matvec_prefix )( (*current).input );

   (*current).rotation_matrix
      =  Matvec_make( Matvec_prefix )
         (
            Matvec_columns( Matvec_prefix )( (*current).input ),
            Matvec_columns( Matvec_prefix )( (*current).input )
         );
   Matvec_set_to_one( Matvec_prefix )( (*current).rotation_matrix );

   (*current).singular_value
      =  Matvec_make_column_vector( Matvec_prefix )
         (
            Matvec_columns( Matvec_prefix )( (*current).input )
         );

   // compute svd
   for ( k = 0; k < 2; k++ )
   {
      for ( i = 0; i < n; i++ )
      {
         for ( j = i + 1; j < n; j++ )
         {
            column_vector_rotate( current, (*current).matrix, (*current).rotation_matrix, i, j );
         }
      }
   }

   // compute singular values
   for ( i = 0; i < n; i++ )
   {
      d = Matvec_column_vector_squared_magnitude( Matvec_prefix )( (*current).matrix, i );
      d = sqrt( d );
      SET_FROM( g, d );
      Matvec_vector_put( Matvec_prefix )( (*current).singular_value, g, i );
      if ( EQUAL_FUNCTION( g, DEFAULT_VALUE ) == 0 )
      {
         g = INVERSE_FUNCTION( g );
      }
      else
      {
         SET_FROM( g, DEFAULT_VALUE );
      }
      Matvec_column_vector_scale( Matvec_prefix )( (*current).matrix, g, i );
   }

   return;
}

/**
   row_svd
*/

static
void
row_svd( Svd_type( Prefix ) *current )
{
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t n = 0;
   Type g = DEFAULT_VALUE;
   Magnitude_type d = 0.0;

   (*current).is_column_svd = 0;
   (*current).is_svd_done = 1;

   // dispose of previous matrices, if any
   if ( (*current).matrix != NULL )
   {
      Matvec_dispose( Matvec_prefix )( &(*current).matrix );
   }

   if ( (*current).rotation_matrix != NULL )
   {
      Matvec_dispose( Matvec_prefix )( &(*current).rotation_matrix );
   }

   if ( (*current).singular_value != NULL )
   {
      Matvec_dispose( Matvec_prefix )( &(*current).singular_value );
   }

   // get max of input width and height
   n = Matvec_rows( Matvec_prefix )( (*current).input );

   // set up matrices
   (*current).rotation_matrix = Matvec_copied( Matvec_prefix )( (*current).input );

   (*current).matrix
      =  Matvec_make( Matvec_prefix )
         (
            Matvec_rows( Matvec_prefix )( (*current).input ),
            Matvec_rows( Matvec_prefix )( (*current).input )
         );
   Matvec_set_to_one( Matvec_prefix )( (*current).matrix );

   (*current).singular_value
      =  Matvec_make_column_vector( Matvec_prefix )
         (
            Matvec_rows( Matvec_prefix )( (*current).input )
         );

   // compute current
   for ( k = 0; k < 2; k++ )
   {
      for ( i = 0; i < n; i++ )
      {
         for ( j = i + 1; j < n; j++ )
         {
            row_vector_rotate( current, (*current).rotation_matrix, (*current).matrix, i, j );
         }
      }
   }

   // compute singular values
   for ( i = 0; i < n; i++ )
   {
      d = Matvec_row_vector_squared_magnitude( Matvec_prefix )( (*current).rotation_matrix, i );
      d = sqrt( d );
      SET_FROM( g, d );
      Matvec_vector_put( Matvec_prefix )( (*current).singular_value, g, i );
      if ( EQUAL_FUNCTION( g, DEFAULT_VALUE ) == 0 )
      {
         g = INVERSE_FUNCTION( g );
      }
      else
      {
         SET_FROM( g, DEFAULT_VALUE );
      }
      Matvec_row_vector_scale( Matvec_prefix )( (*current).rotation_matrix, g, i );
   }

   return;
}

/**
   row_vector_rotate

   interchange row vectors i1 and i2 in current

   @param current the svd instance
   @param a the input matrix
   @param b the output matrix
   @param i1 the index of the first row
   @param i2 the index of the second row
*/

static
void
row_vector_rotate
(
   Svd_type( Prefix ) *current,
   Matvec_type( Matvec_prefix ) *a,
   Matvec_type( Matvec_prefix ) *b,
   int32_t i1,
   int32_t i2
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "a not null", a != NULL );
   PRECONDITION( "b not null", b != NULL );
   PRECONDITION( "i1 OK", ( ( i1 >= 0 ) && ( i1 < Matvec_rows( Matvec_prefix )( a ) ) ) );
   PRECONDITION( "i2 OK", ( ( i2 >= 0 ) && ( i2 < Matvec_rows( Matvec_prefix )( a ) ) ) );

   Magnitude_type d = 0.0;
   Type p = DEFAULT_VALUE;
   Magnitude_type q = 0.0;
   Magnitude_type v = 0.0;
   Magnitude_type m1 = 0.0;
   Magnitude_type m2 = 0.0;
   Type g = DEFAULT_VALUE;
   Type c = DEFAULT_VALUE;
   Type s = DEFAULT_VALUE;

   p = Matvec_row_vector_dot( Matvec_prefix )( a, i1, i2 );

   q = Matvec_row_vector_squared_magnitude( Matvec_prefix )( a, i1 );
   SET_FROM( m1, q );

   v = Matvec_row_vector_squared_magnitude( Matvec_prefix )( a, i2 );
   SET_FROM( m2, v );

   SET_FROM( c, ONE_VALUE );
   SET_FROM( s, DEFAULT_VALUE );

   if ( SQUARED_MAGNITUDE_FUNCTION( p ) > (*current).rotation_error * ( q * q + v * v ) )
   {
      q = q - v;

      v = sqrt( 4.0 * SQUARED_MAGNITUDE_FUNCTION( p ) + q * q );

      if ( q >= 0.0 )
      {
         d = sqrt( ( v + q ) / ( 2.0 * v ) );
         SET_FROM( c, d );

         d = v * d;
         SET_FROM( g, d );
         g = INVERSE_FUNCTION( g );
         s = MULTIPLY_FUNCTION( p, g );

         row_rotation( current, a, i1, i2, c, s );
         row_rotation( current, b, i1, i2, c, s );
      }
      else
      {
         d = sqrt( ( v - q ) / ( 2.0 * v ) );
         SET_FROM( c, d );

         d = v * d;
         SET_FROM( g, d );
         g = INVERSE_FUNCTION( g );
         s = MULTIPLY_FUNCTION( p, g );
         s = CONJUGATE_FUNCTION( s );

         row_rotation_with_swap( current, a, i1, i2, c, s );
         row_rotation_with_swap( current, b, i1, i2, c, s );
      }
   }
   else
   {
      if ( m1 < m2 )
      {
         row_rotation_with_swap( current, a, i1, i2, c, s );
         row_rotation_with_swap( current, b, i1, i2, c, s );
      }
   }

   return;
}

/**
   row_rotation

   rotate row vectors i1 and i2 in a using c and s

   @param current the svd instance
   @param a the matrix
   @param i1 the index of the first row
   @param i2 the index of the second row
   @param c Givens rotation cosine
   @param s Givens rotation sine
*/

static
void
row_rotation
(
   Svd_type( Prefix ) *current,
   Matvec_type( Matvec_prefix ) *a,
   int32_t i1,
   int32_t i2,
   Type c,
   Type s
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "a not null", a != NULL );
   PRECONDITION( "i1 OK", ( ( i1 >= 0 ) && ( i1 < Matvec_rows( Matvec_prefix )( a ) ) ) );
   PRECONDITION( "i2 OK", ( ( i2 >= 0 ) && ( i2 < Matvec_rows( Matvec_prefix )( a ) ) ) );

   int32_t i = 0;
   int32_t n = 0;
   Type x = DEFAULT_VALUE;
   Type y = DEFAULT_VALUE;
   Type t = DEFAULT_VALUE;

   n = Matvec_columns( Matvec_prefix )( a );

   for( i = 0; i < n; i++ )
   {
      t = MULTIPLY_FUNCTION( s, Matvec_item( Matvec_prefix )( a, i2, i ) );
      x = MULTIPLY_FUNCTION( c, Matvec_item( Matvec_prefix )( a, i1, i ) );
      x = ADD_FUNCTION( x, t );

      t = NEGATE_FUNCTION( CONJUGATE_FUNCTION( s ) );
      t = MULTIPLY_FUNCTION( t, Matvec_item( Matvec_prefix )( a, i1, i ) );
      y = MULTIPLY_FUNCTION( c, Matvec_item( Matvec_prefix )( a, i2, i ) );
      y = ADD_FUNCTION( t, y );

      Matvec_put( Matvec_prefix )( a, x, i1, i );
      Matvec_put( Matvec_prefix )( a, y, i2, i );
   }

   return;
}

/**
   row_rotation_with_swap

   rotate row vectors i1 and i2 in a using c and s, and swap the rows

   @param current the svd instance
   @param a the matrix
   @param i1 the index of the first row
   @param i2 the index of the second row
   @param c Givens rotation cosine
   @param s Givens rotation sine
*/

static
void
row_rotation_with_swap
(
   Svd_type( Prefix ) *current,
   Matvec_type( Matvec_prefix ) *a,
   int32_t i1,
   int32_t i2,
   Type c,
   Type s
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "a not null", a != NULL );
   PRECONDITION( "i1 OK", ( ( i1 >= 0 ) && ( i1 < Matvec_rows( Matvec_prefix )( a ) ) ) );
   PRECONDITION( "i2 OK", ( ( i2 >= 0 ) && ( i2 < Matvec_rows( Matvec_prefix )( a ) ) ) );

   int32_t i = 0;
   int32_t n = 0;
   Type x = DEFAULT_VALUE;
   Type y = DEFAULT_VALUE;
   Type t = DEFAULT_VALUE;

   n = Matvec_columns( Matvec_prefix )( a );

   for( i = 0; i < n; i++ )
   {
      t = MULTIPLY_FUNCTION( s, Matvec_item( Matvec_prefix )( a, i1, i ) );
      x = MULTIPLY_FUNCTION( c, Matvec_item( Matvec_prefix )( a, i2, i ) );
      x = ADD_FUNCTION( x, t );

      t = NEGATE_FUNCTION( CONJUGATE_FUNCTION( s ) );
      t = MULTIPLY_FUNCTION( t, Matvec_item( Matvec_prefix )( a, i2, i ) );
      y = MULTIPLY_FUNCTION( c, Matvec_item( Matvec_prefix )( a, i1, i ) );
      y = ADD_FUNCTION( t, y );

      Matvec_put( Matvec_prefix )( a, x, i1, i );
      Matvec_put( Matvec_prefix )( a, y, i2, i );
   }

   return;
}

/**
   column_vector_rotate

   interchange colums vectors i1 and i2 in current

   @param current the svd instance
   @param a the input matrix
   @param b the output matrix
   @param i1 the index of the first column
   @param i2 the index of the second column
*/

static
void
column_vector_rotate
(
   Svd_type( Prefix ) *current,
   Matvec_type( Matvec_prefix ) *a,
   Matvec_type( Matvec_prefix ) *b,
   int32_t i1,
   int32_t i2
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "a not null", a != NULL );
   PRECONDITION( "b not null", b != NULL );
   PRECONDITION( "i1 OK", ( ( i1 >= 0 ) && ( i1 < Matvec_columns( Matvec_prefix )( a ) ) ) );
   PRECONDITION( "i2 OK", ( ( i2 >= 0 ) && ( i2 < Matvec_columns( Matvec_prefix )( a ) ) ) );

   Magnitude_type d = 0.0;
   Type p = DEFAULT_VALUE;
   Magnitude_type q = 0.0;
   Magnitude_type v = 0.0;
   Magnitude_type m1 = 0.0;
   Magnitude_type m2 = 0.0;
   Type g = DEFAULT_VALUE;
   Type c = DEFAULT_VALUE;
   Type s = DEFAULT_VALUE;

   p = Matvec_column_vector_dot( Matvec_prefix )( a, i1, i2 );

   q = Matvec_column_vector_squared_magnitude( Matvec_prefix )( a, i1 );
   SET_FROM( m1, q );

   v = Matvec_column_vector_squared_magnitude( Matvec_prefix )( a, i2 );
   SET_FROM( m2, v );

   SET_FROM( c, ONE_VALUE );
   SET_FROM( s, DEFAULT_VALUE );

   if ( SQUARED_MAGNITUDE_FUNCTION( p ) > (*current).rotation_error * ( q * q + v * v ) )
   {
      q = q - v;

      v = sqrt( 4.0 * SQUARED_MAGNITUDE_FUNCTION( p ) + q * q );

      if ( q >= 0.0 )
      {
         d = sqrt( ( v + q ) / ( 2.0 * v ) );
         SET_FROM( c, d );

         d = v * d;
         SET_FROM( g, d );
         g = INVERSE_FUNCTION( g );
         s = MULTIPLY_FUNCTION( p, g );

         column_rotation( current, a, i1, i2, c, s );
         column_rotation( current, b, i1, i2, c, s );
      }
      else
      {
         d = sqrt( ( v - q ) / ( 2.0 * v ) );
         SET_FROM( c, d );

         d = v * d;
         SET_FROM( g, d );
         g = INVERSE_FUNCTION( g );
         s = MULTIPLY_FUNCTION( p, g );
         s = CONJUGATE_FUNCTION( s );

         column_rotation_with_swap( current, a, i1, i2, c, s );
         column_rotation_with_swap( current, b, i1, i2, c, s );
      }
   }
   else
   {
      if ( m1 < m2 )
      {
         column_rotation_with_swap( current, a, i1, i2, c, s );
         column_rotation_with_swap( current, b, i1, i2, c, s );
      }
   }

   return;
}

/**
   column_rotation

   rotate column vectors i1 and i2 in a using c and s

   @param current the svd instance
   @param a the matrix
   @param i1 the index of the first column
   @param i2 the index of the second column
   @param c Givens rotation cosine
   @param s Givens rotation sine
*/

static
void
column_rotation
(
   Svd_type( Prefix ) *current,
   Matvec_type( Matvec_prefix ) *a,
   int32_t i1,
   int32_t i2,
   Type c,
   Type s
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "a not null", a != NULL );
   PRECONDITION( "i1 OK", ( ( i1 >= 0 ) && ( i1 < Matvec_columns( Matvec_prefix )( a ) ) ) );
   PRECONDITION( "i2 OK", ( ( i2 >= 0 ) && ( i2 < Matvec_columns( Matvec_prefix )( a ) ) ) );

   int32_t i = 0;
   int32_t n = 0;
   Type x = DEFAULT_VALUE;
   Type y = DEFAULT_VALUE;
   Type t = DEFAULT_VALUE;

   n = Matvec_rows( Matvec_prefix )( a );

   for( i = 0; i < n; i++ )
   {
      t = MULTIPLY_FUNCTION( s, Matvec_item( Matvec_prefix )( a, i, i2 ) );
      x = MULTIPLY_FUNCTION( c, Matvec_item( Matvec_prefix )( a, i, i1 ) );
      x = ADD_FUNCTION( x, t );

      t = NEGATE_FUNCTION( CONJUGATE_FUNCTION( s ) );
      t = MULTIPLY_FUNCTION( t, Matvec_item( Matvec_prefix )( a, i, i1 ) );
      y = MULTIPLY_FUNCTION( c, Matvec_item( Matvec_prefix )( a, i, i2 ) );
      y = ADD_FUNCTION( t, y );

      Matvec_put( Matvec_prefix )( a, x, i, i1 );
      Matvec_put( Matvec_prefix )( a, y, i, i2 );
   }

   return;
}

/**
   column_rotation_with_swap

   rotate column vectors i1 and i2 in a using c and s, and swap the column

   @param current the svd instance
   @param a the matrix
   @param i1 the index of the first column
   @param i2 the index of the second column
   @param c Givens rotation cosine
   @param s Givens rotation sine
*/

static
void
column_rotation_with_swap
(
   Svd_type( Prefix ) *svd,
   Matvec_type( Matvec_prefix ) *a,
   int32_t i1,
   int32_t i2,
   Type c,
   Type s
)
{
   PRECONDITION( "svd not null", svd != NULL );
   PRECONDITION( "a not null", a != NULL );
   PRECONDITION( "i1 OK", ( ( i1 >= 0 ) && ( i1 < Matvec_columns( Matvec_prefix )( a ) ) ) );
   PRECONDITION( "i2 OK", ( ( i2 >= 0 ) && ( i2 < Matvec_columns( Matvec_prefix )( a ) ) ) );

   int32_t i = 0;
   int32_t n = 0;
   Type x = DEFAULT_VALUE;
   Type y = DEFAULT_VALUE;
   Type t = DEFAULT_VALUE;

   n = Matvec_rows( Matvec_prefix )( a );

   for( i = 0; i < n; i++ )
   {
      t = MULTIPLY_FUNCTION( s, Matvec_item( Matvec_prefix )( a, i, i1 ) );
      x = MULTIPLY_FUNCTION( c, Matvec_item( Matvec_prefix )( a, i, i2 ) );
      x = ADD_FUNCTION( x, t );

      t = NEGATE_FUNCTION( CONJUGATE_FUNCTION( s ) );
      t = MULTIPLY_FUNCTION( t, Matvec_item( Matvec_prefix )( a, i, i2 ) );
      y = MULTIPLY_FUNCTION( c, Matvec_item( Matvec_prefix )( a, i, i1 ) );
      y = ADD_FUNCTION( t, y );

      Matvec_put( Matvec_prefix )( a, x, i, i1 );
      Matvec_put( Matvec_prefix )( a, y, i, i2 );
   }

   return;
}

/* End of file */

