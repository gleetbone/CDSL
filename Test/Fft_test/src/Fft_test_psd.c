/**
 @file Fft_test_psd.c
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
   test_psd_1
*/

void test_psd_1( void )
{
   cf_fft_t *cffft = NULL;
   cf_matvec_t *v = NULL;
   f_matvec_t *v1 = NULL;
   f_matvec_t *v2 = NULL;

   cffft = cf_fft_make( 1024 );

   v = single_bin_sinusoid_output_f( 1024, 8, 0.0 );
   cf_fft_set_output( cffft, v );
   v1 = cf_fft_psd( cffft );
   v2 = single_bin_sinusoid_psd_f( 1024, 8, 0.0 );

   CU_ASSERT( cffft != NULL );
   CU_ASSERT( v != NULL );
   CU_ASSERT( v1 != NULL );
   CU_ASSERT( v2 != NULL );
   CU_ASSERT( f_matvec_is_approximately_equal( v1, v2, 0.000001 ) == 1 );

   cf_fft_dispose_with_contents( cffft );
   cf_matvec_dispose( v );
   f_matvec_dispose( v2 );

   return;
}

/**
   test_psd_2
*/

void test_psd_2( void )
{
   cd_fft_t *cdfft = NULL;
   cd_matvec_t *v = NULL;
   d_matvec_t *v1 = NULL;
   d_matvec_t *v2 = NULL;

   cdfft = cd_fft_make( 1024 );

   v = single_bin_sinusoid_output_d( 1024, 8, 0.0 );
   cd_fft_set_output( cdfft, v );
   v1 = cd_fft_psd( cdfft );
   v2 = single_bin_sinusoid_psd_d( 1024, 8, 0.0 );

   CU_ASSERT( cdfft != NULL );
   CU_ASSERT( v != NULL );
   CU_ASSERT( v1 != NULL );
   CU_ASSERT( v2 != NULL );
   CU_ASSERT( d_matvec_is_approximately_equal( v1, v2, 0.000001 ) == 1 );

   cd_fft_dispose_with_contents( cdfft );
   cd_matvec_dispose( v );
   d_matvec_dispose( v2 );

   return;
}

int
add_test_psd( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_psd", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_psd_1
   add_test_to_suite( p_suite, test_psd_1, "test_psd_1" );

   // test_psd_2
   add_test_to_suite( p_suite, test_psd_2, "test_psd_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

