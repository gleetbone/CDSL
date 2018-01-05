/**
 @file Fft_test_fft.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for Fft_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Fft_make.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "f_Matvec.h"
#include "d_Matvec.h"
#include "cf_Matvec.h"
#include "cd_Matvec.h"

#include "cf_Fft.h"
#include "cd_Fft.h"

#include "Fft_utility.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_fft_1
*/

void test_fft_1( void )
{
   cf_fft_t *cffft = NULL;
   cf_matvec_t *v = NULL;
   cf_matvec_t *v1 = NULL;

   // zeros
   cffft = cf_fft_make( 256 );

   v = cf_matvec_make_column_vector( 256 );

   cf_fft_fft( cffft );

   CU_ASSERT( cffft != NULL );
   CU_ASSERT( v != NULL );
   CU_ASSERT( cf_matvec_is_approximately_equal( cf_fft_input( cffft ), v, 0.000001 ) == 1 );

   cf_fft_dispose_with_contents( cffft );
   cf_matvec_dispose( v );

   // sinusoid 4
   cffft = cf_fft_make( 4 );

   v = single_bin_sinusoid_input_f( 4, 2, 0.0 );

   cf_fft_set_input( cffft, v );
   cf_fft_fft( cffft );
   v1 = single_bin_sinusoid_output_f( 4, 2, 0.0 );

   CU_ASSERT( cffft != NULL );
   CU_ASSERT( v != NULL );
   CU_ASSERT( v1 != NULL );
   CU_ASSERT( cf_matvec_is_approximately_equal( cf_fft_output( cffft ), v1, 0.000001 ) == 1 );

   cf_fft_dispose_with_contents( cffft );
   cf_matvec_dispose( v );
   cf_matvec_dispose( v1 );

   // sinusoid 8
   cffft = cf_fft_make( 8 );

   v = single_bin_sinusoid_input_f( 8, 2, 0.0 );

   cf_fft_set_input( cffft, v );
   cf_fft_fft( cffft );
   v1 = single_bin_sinusoid_output_f( 8, 2, 0.0 );

   CU_ASSERT( cffft != NULL );
   CU_ASSERT( v != NULL );
   CU_ASSERT( v1 != NULL );
   CU_ASSERT( cf_matvec_is_approximately_equal( cf_fft_output( cffft ), v1, 0.000001 ) == 1 );

   cf_fft_dispose_with_contents( cffft );
   cf_matvec_dispose( v );
   cf_matvec_dispose( v1 );

   // sinusoid 256
   cffft = cf_fft_make( 256 );

   v = single_bin_sinusoid_input_f( 256, 8, 0.0 );

   cf_fft_set_input( cffft, v );
   cf_fft_fft( cffft );
   v1 = single_bin_sinusoid_output_f( 256, 8, 0.0 );

   CU_ASSERT( cffft != NULL );
   CU_ASSERT( v != NULL );
   CU_ASSERT( v1 != NULL );
   CU_ASSERT( cf_matvec_is_approximately_equal( cf_fft_output( cffft ), v1, 0.000001 ) == 1 );

   cf_fft_dispose_with_contents( cffft );
   cf_matvec_dispose( v );
   cf_matvec_dispose( v1 );

   // sinusoid 1024
   cffft = cf_fft_make( 1024 );

   v = single_bin_sinusoid_input_f( 1024, 8, 0.0 );

   cf_fft_set_input( cffft, v );
   cf_fft_fft( cffft );
   v1 = single_bin_sinusoid_output_f( 1024, 8, 0.0 );

   CU_ASSERT( cffft != NULL );
   CU_ASSERT( v != NULL );
   CU_ASSERT( v1 != NULL );
   CU_ASSERT( cf_matvec_is_approximately_equal( cf_fft_output( cffft ), v1, 0.000001 ) == 1 );

   cf_fft_dispose_with_contents( cffft );
   cf_matvec_dispose( v );
   cf_matvec_dispose( v1 );

   // sinusoid 1024
   cffft = cf_fft_make( 1024 );

   v = single_bin_sinusoid_input_f( 1024, 8, 0.4 );

   cf_fft_set_input( cffft, v );
   cf_fft_fft( cffft );
   v1 = single_bin_sinusoid_output_f( 1024, 8, 0.4 );

   CU_ASSERT( cffft != NULL );
   CU_ASSERT( v != NULL );
   CU_ASSERT( v1 != NULL );
   CU_ASSERT( cf_matvec_is_approximately_equal( cf_fft_output( cffft ), v1, 0.000001 ) == 1 );

   cf_fft_dispose_with_contents( cffft );
   cf_matvec_dispose( v );
   cf_matvec_dispose( v1 );

   return;
}

/**
   test_fft_2
*/

void test_fft_2( void )
{
	   cd_fft_t *cdfft = NULL;
	   cd_matvec_t *v = NULL;
	   cd_matvec_t *v1 = NULL;

	   // zeros
	   cdfft = cd_fft_make( 256 );

	   v = cd_matvec_make_column_vector( 256 );

	   cd_fft_fft( cdfft );

	   CU_ASSERT( cdfft != NULL );
	   CU_ASSERT( v != NULL );
	   CU_ASSERT( cd_matvec_is_approximately_equal( cd_fft_input( cdfft ), v, 0.000001 ) == 1 );

	   cd_fft_dispose_with_contents( cdfft );
	   cd_matvec_dispose( v );

	   // sinusoid 4
	   cdfft = cd_fft_make( 4 );

	   v = single_bin_sinusoid_input_d( 4, 2, 0.0 );

	   cd_fft_set_input( cdfft, v );
	   cd_fft_fft( cdfft );
	   v1 = single_bin_sinusoid_output_d( 4, 2, 0.0 );

	   CU_ASSERT( cdfft != NULL );
	   CU_ASSERT( v != NULL );
	   CU_ASSERT( v1 != NULL );
	   CU_ASSERT( cd_matvec_is_approximately_equal( cd_fft_output( cdfft ), v1, 0.000001 ) == 1 );

	   cd_fft_dispose_with_contents( cdfft );
	   cd_matvec_dispose( v );
	   cd_matvec_dispose( v1 );

	   // sinusoid 8
	   cdfft = cd_fft_make( 8 );

	   v = single_bin_sinusoid_input_d( 8, 2, 0.0 );

	   cd_fft_set_input( cdfft, v );
	   cd_fft_fft( cdfft );
	   v1 = single_bin_sinusoid_output_d( 8, 2, 0.0 );

	   CU_ASSERT( cdfft != NULL );
	   CU_ASSERT( v != NULL );
	   CU_ASSERT( v1 != NULL );
	   CU_ASSERT( cd_matvec_is_approximately_equal( cd_fft_output( cdfft ), v1, 0.000001 ) == 1 );

	   cd_fft_dispose_with_contents( cdfft );
	   cd_matvec_dispose( v );
	   cd_matvec_dispose( v1 );

	   // sinusoid 256
	   cdfft = cd_fft_make( 256 );

	   v = single_bin_sinusoid_input_d( 256, 8, 0.0 );

	   cd_fft_set_input( cdfft, v );
	   cd_fft_fft( cdfft );
	   v1 = single_bin_sinusoid_output_d( 256, 8, 0.0 );

	   CU_ASSERT( cdfft != NULL );
	   CU_ASSERT( v != NULL );
	   CU_ASSERT( v1 != NULL );
	   CU_ASSERT( cd_matvec_is_approximately_equal( cd_fft_output( cdfft ), v1, 0.000001 ) == 1 );

	   cd_fft_dispose_with_contents( cdfft );
	   cd_matvec_dispose( v );
	   cd_matvec_dispose( v1 );

	   // sinusoid 1024
	   cdfft = cd_fft_make( 1024 );

	   v = single_bin_sinusoid_input_d( 1024, 8, 0.0 );

	   cd_fft_set_input( cdfft, v );
	   cd_fft_fft( cdfft );
	   v1 = single_bin_sinusoid_output_d( 1024, 8, 0.0 );

	   CU_ASSERT( cdfft != NULL );
	   CU_ASSERT( v != NULL );
	   CU_ASSERT( v1 != NULL );
	   CU_ASSERT( cd_matvec_is_approximately_equal( cd_fft_output( cdfft ), v1, 0.000001 ) == 1 );

	   cd_fft_dispose_with_contents( cdfft );
	   cd_matvec_dispose( v );
	   cd_matvec_dispose( v1 );

	   // sinusoid 1024
	   cdfft = cd_fft_make( 1024 );

	   v = single_bin_sinusoid_input_d( 1024, 8, 0.4 );

	   cd_fft_set_input( cdfft, v );
	   cd_fft_fft( cdfft );
	   v1 = single_bin_sinusoid_output_d( 1024, 8, 0.4 );

	   CU_ASSERT( cdfft != NULL );
	   CU_ASSERT( v != NULL );
	   CU_ASSERT( v1 != NULL );
	   CU_ASSERT( cd_matvec_is_approximately_equal( cd_fft_output( cdfft ), v1, 0.000001 ) == 1 );

	   cd_fft_dispose_with_contents( cdfft );
	   cd_matvec_dispose( v );
	   cd_matvec_dispose( v1 );

	   return;
}

int
add_test_fft( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_fft", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_fft_1
   add_test_to_suite( p_suite, test_fft_1, "test_fft_1" );

   // test_fft_2
   add_test_to_suite( p_suite, test_fft_2, "test_fft_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

