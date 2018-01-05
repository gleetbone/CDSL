/**
 @file Fft_utility.c
 @author Greg Lee
 @version 1.0.0
 @brief: "utilities for testing Fft"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Utilities for testing Fft.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "Fft_utility.h"

#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define INVARIANT_FILE DBC_YES

#include "dbc.h"

#define DTOR (M_PI/180.0)
#define RTOD (180.0/M_PI)

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

cf_matvec_t *
single_bin_sinusoid_input_f( int32_t length, int32_t i_freq, float phase_fraction )
{
   PRECONDITION( "length OK", is_power_of_two( length ) == 1 );
   PRECONDITION( "i_freq OK", ( ( i_freq > 0 ) && ( i_freq <= length/2 ) ) );
   PRECONDITION( "i_freq OK with length", ( length % i_freq )  == 0 );
   PRECONDITION( "phase_fraction OK", ( ( phase_fraction >= 0.0 ) && ( phase_fraction <= 1.0 ) ) );

   cf_matvec_t *result = NULL;
   int32_t i = 0;
   int32_t i_period = 0;
   float32_t y = 0.0;
   complex64_t c = 0.0 + 0.0*I;

   result = cf_matvec_make_column_vector( length );

   i_period = ( int32_t ) length/i_freq;

   y = ( 2.0*M_PI)/( 1.0*length );


   for ( i=0; i<length; i++ )
   {
      c = cos( i_freq*y*( i - phase_fraction*i_period ) ) + 0.0*I;
      cf_matvec_vector_put( result, c, i );
   }

   return result;
}

cf_matvec_t *
single_bin_sinusoid_output_f( int32_t length, int32_t i_freq, float phase_fraction )
{
   PRECONDITION( "length OK", is_power_of_two( length ) == 1 );
   PRECONDITION( "i_freq OK", ( ( i_freq > 0 ) && ( i_freq <= length/2 ) ) );
   PRECONDITION( "i_freq OK with length", ( length % i_freq )  == 0 );
   PRECONDITION( "phase_fraction OK", ( ( phase_fraction >= 0.0 ) && ( phase_fraction <= 1.0 ) ) );

   cf_matvec_t *result = NULL;
   int32_t i = 0;
   complex64_t c = 0.0 + 0.0*I;

   result = cf_matvec_make_column_vector( length );

   for ( i=0; i<length; i++ )
   {
      cf_matvec_vector_put( result, c, i );
   }

   c = cos( 2.0*M_PI*phase_fraction ) + sin( 2.0*M_PI*phase_fraction )*I;
   cf_matvec_vector_put( result, c, i_freq );

   c = conj( c );
   cf_matvec_vector_put( result, c, length - i_freq );

   if ( i_freq == ( length - i_freq ) )
   {
      c = (2.0 + 0.0*I)*c;
      cf_matvec_vector_put( result, c, i_freq );
   }

   return result;
}

cf_matvec_t *
single_bin_sinusoid_output_for_psd_f( int32_t length, int32_t i_freq, float phase_fraction )
{
   PRECONDITION( "length OK", is_power_of_two( length ) == 1 );
   PRECONDITION( "i_freq OK", ( ( i_freq > 0 ) && ( i_freq <= length/2 ) ) );
   PRECONDITION( "i_freq OK with length", ( length % i_freq )  == 0 );
   PRECONDITION( "phase_fraction OK", ( ( phase_fraction >= 0.0 ) && ( phase_fraction <= 1.0 ) ) );

   cf_matvec_t *result = NULL;
   int32_t i = 0;
   complex64_t c = 1.0 + 0.0*I;

   result = cf_matvec_make_column_vector( length );

   for ( i=0; i<length; i++ )
   {
      cf_matvec_vector_put( result, c, i );
   }

   return result;
}

f_matvec_t *
single_bin_sinusoid_psd_f( int32_t length, int32_t i_freq, float phase_fraction )
{
   PRECONDITION( "length OK", is_power_of_two( length ) == 1 );
   PRECONDITION( "i_freq OK", ( ( i_freq > 0 ) && ( i_freq <= length/2 ) ) );
   PRECONDITION( "i_freq OK with length", ( length % i_freq )  == 0 );
   PRECONDITION( "phase_fraction OK", ( ( phase_fraction >= 0.0 ) && ( phase_fraction <= 1.0 ) ) );

   f_matvec_t *result = NULL;

   result = f_matvec_make_column_vector( length );

   f_matvec_vector_put( result, 1.0, i_freq );

   f_matvec_vector_put( result, 1.0, length - i_freq );

   return result;
}

f_matvec_t *
single_bin_sinusoid_log_psd_f( int32_t length, int32_t i_freq, float phase_fraction )
{
   PRECONDITION( "length OK", is_power_of_two( length ) == 1 );
   PRECONDITION( "i_freq OK", ( ( i_freq > 0 ) && ( i_freq <= length/2 ) ) );
   PRECONDITION( "i_freq OK with length", ( length % i_freq )  == 0 );
   PRECONDITION( "phase_fraction OK", ( ( phase_fraction >= 0.0 ) && ( phase_fraction <= 1.0 ) ) );

   f_matvec_t *result = NULL;

   result = f_matvec_make_column_vector( length );

   return result;
}

f_matvec_t *
single_bin_sinusoid_phase_f( int32_t length, int32_t i_freq, float phase_fraction )
{
   PRECONDITION( "length OK", is_power_of_two( length ) == 1 );
   PRECONDITION( "i_freq OK", ( ( i_freq > 0 ) && ( i_freq <= length/2 ) ) );
   PRECONDITION( "i_freq OK with length", ( length % i_freq )  == 0 );
   PRECONDITION( "phase_fraction OK", ( ( phase_fraction >= 0.0 ) && ( phase_fraction <= 1.0 ) ) );

   f_matvec_t *result = NULL;
   float32_t phase = 0.0;

   result = f_matvec_make_column_vector( length );

   phase = 2.0*M_PI*phase_fraction;
   f_matvec_vector_put( result, phase, i_freq );

   f_matvec_vector_put( result, -phase, length - i_freq );

   return result;
}

f_matvec_t *
single_bin_sinusoid_phase_degrees_f( int32_t length, int32_t i_freq, float phase_fraction )
{
   PRECONDITION( "length OK", is_power_of_two( length ) == 1 );
   PRECONDITION( "i_freq OK", ( ( i_freq > 0 ) && ( i_freq <= length/2 ) ) );
   PRECONDITION( "i_freq OK with length", ( length % i_freq )  == 0 );
   PRECONDITION( "phase_fraction OK", ( ( phase_fraction >= 0.0 ) && ( phase_fraction <= 1.0 ) ) );

   f_matvec_t *result = NULL;
   float32_t phase = 0.0;

   result = f_matvec_make_column_vector( length );

   phase = RTOD*2.0*M_PI*phase_fraction;
   f_matvec_vector_put( result, phase, i_freq );

   f_matvec_vector_put( result, -phase, length - i_freq );

   return result;
}

cd_matvec_t *
single_bin_sinusoid_input_d( int32_t length, int32_t i_freq, double phase_fraction )
{
   PRECONDITION( "length OK", is_power_of_two( length ) == 1 );
   PRECONDITION( "i_freq OK", ( ( i_freq > 0 ) && ( i_freq <= length/2 ) ) );
   PRECONDITION( "i_freq OK with length", ( length % i_freq )  == 0 );
   PRECONDITION( "phase_fraction OK", ( ( phase_fraction >= 0.0 ) && ( phase_fraction <= 1.0 ) ) );

   cd_matvec_t *result = NULL;
   int32_t i = 0;
   int32_t i_period = 0;
   float32_t y = 0.0;
   complex128_t c = 0.0 + 0.0*I;

   result = cd_matvec_make_column_vector( length );

   i_period = ( int32_t ) length/i_freq;

   y = ( 2.0*M_PI)/( 1.0*length );

   for ( i=0; i<length; i++ )
   {
      c = cos( i_freq*y*( i - phase_fraction*i_period ) ) + 0.0*I;
      cd_matvec_vector_put( result, c, i );
   }

   return result;
}

cd_matvec_t *
single_bin_sinusoid_output_d( int32_t length, int32_t i_freq, double phase_fraction )
{
   PRECONDITION( "length OK", is_power_of_two( length ) == 1 );
   PRECONDITION( "i_freq OK", ( ( i_freq > 0 ) && ( i_freq <= length/2 ) ) );
   PRECONDITION( "i_freq OK with length", ( length % i_freq )  == 0 );
   PRECONDITION( "phase_fraction OK", ( ( phase_fraction >= 0.0 ) && ( phase_fraction <= 1.0 ) ) );

   cd_matvec_t *result = NULL;
   int32_t i = 0;
   complex128_t c = 0.0 + 0.0*I;

   result = cd_matvec_make_column_vector( length );

   for ( i=0; i<length; i++ )
   {
      cd_matvec_vector_put( result, c, i );
   }

   c = cos( 2.0*M_PI*phase_fraction ) + sin( 2.0*M_PI*phase_fraction )*I;
   cd_matvec_vector_put( result, c, i_freq );

   c = conj( c );
   cd_matvec_vector_put( result, c, length - i_freq );

   if ( i_freq == ( length - i_freq ) )
   {
      c = (2.0 + 0.0*I)*c;
      cd_matvec_vector_put( result, c, i_freq );
   }

   return result;
}

cd_matvec_t *
single_bin_sinusoid_output_for_psd_d( int32_t length, int32_t i_freq, double phase_fraction )
{
   PRECONDITION( "length OK", is_power_of_two( length ) == 1 );
   PRECONDITION( "i_freq OK", ( ( i_freq > 0 ) && ( i_freq <= length/2 ) ) );
   PRECONDITION( "i_freq OK with length", ( length % i_freq )  == 0 );
   PRECONDITION( "phase_fraction OK", ( ( phase_fraction >= 0.0 ) && ( phase_fraction <= 1.0 ) ) );

   cd_matvec_t *result = NULL;
   int32_t i = 0;
   complex64_t c = 1.0 + 0.0*I;

   result = cd_matvec_make_column_vector( length );

   for ( i=0; i<length; i++ )
   {
      cd_matvec_vector_put( result, c, i );
   }

   return result;
}

d_matvec_t *
single_bin_sinusoid_psd_d( int32_t length, int32_t i_freq, double phase_fraction )
{
   PRECONDITION( "length OK", is_power_of_two( length ) == 1 );
   PRECONDITION( "i_freq OK", ( ( i_freq > 0 ) && ( i_freq <= length/2 ) ) );
   PRECONDITION( "i_freq OK with length", ( length % i_freq )  == 0 );
   PRECONDITION( "phase_fraction OK", ( ( phase_fraction >= 0.0 ) && ( phase_fraction <= 1.0 ) ) );

   d_matvec_t *result = NULL;

   result = d_matvec_make_column_vector( length );

   d_matvec_vector_put( result, 1.0, i_freq );

   d_matvec_vector_put( result, 1.0, length - i_freq );

   return result;
}

d_matvec_t *
single_bin_sinusoid_log_psd_d( int32_t length, int32_t i_freq, double phase_fraction )
{
   PRECONDITION( "length OK", is_power_of_two( length ) == 1 );
   PRECONDITION( "i_freq OK", ( ( i_freq > 0 ) && ( i_freq <= length/2 ) ) );
   PRECONDITION( "i_freq OK with length", ( length % i_freq )  == 0 );
   PRECONDITION( "phase_fraction OK", ( ( phase_fraction >= 0.0 ) && ( phase_fraction <= 1.0 ) ) );

   d_matvec_t *result = NULL;

   result = d_matvec_make_column_vector( length );

   return result;
}

d_matvec_t *
single_bin_sinusoid_phase_d( int32_t length, int32_t i_freq, double phase_fraction )
{
   PRECONDITION( "length OK", is_power_of_two( length ) == 1 );
   PRECONDITION( "i_freq OK", ( ( i_freq > 0 ) && ( i_freq <= length/2 ) ) );
   PRECONDITION( "i_freq OK with length", ( length % i_freq )  == 0 );
   PRECONDITION( "phase_fraction OK", ( ( phase_fraction >= 0.0 ) && ( phase_fraction <= 1.0 ) ) );

   d_matvec_t *result = NULL;
   float64_t phase = 0.0;

   result = d_matvec_make_column_vector( length );

   phase = 2.0*M_PI*phase_fraction;
   d_matvec_vector_put( result, phase, i_freq );

   d_matvec_vector_put( result, -phase, length - i_freq );

   return result;
}

d_matvec_t *
single_bin_sinusoid_phase_degrees_d( int32_t length, int32_t i_freq, double phase_fraction )
{
   PRECONDITION( "length OK", is_power_of_two( length ) == 1 );
   PRECONDITION( "i_freq OK", ( ( i_freq > 0 ) && ( i_freq <= length/2 ) ) );
   PRECONDITION( "i_freq OK with length", ( length % i_freq )  == 0 );
   PRECONDITION( "phase_fraction OK", ( ( phase_fraction >= 0.0 ) && ( phase_fraction <= 1.0 ) ) );

   d_matvec_t *result = NULL;
   float64_t phase = 0.0;

   result = d_matvec_make_column_vector( length );

   phase = RTOD*2.0*M_PI*phase_fraction;
   d_matvec_vector_put( result, phase, i_freq );

   d_matvec_vector_put( result, -phase, length - i_freq );

   return result;
}

#ifdef __cplusplus
}
#endif

/* End of file */

