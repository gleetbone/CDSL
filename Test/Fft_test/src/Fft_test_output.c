/**
 @file Fft_test_output.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Fft_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Fft_t

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

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_output_1
*/

void test_output_1( void )
{
   cf_fft_t *cffft = NULL;
   cf_matvec_t *v = NULL;

   cffft = cf_fft_make( 2 );

   v = cf_matvec_make_from_args( 2, 1, 2, 1.0 + 0.0*I, 2.0 + 1.0*I );
   cf_fft_set_output( cffft, v );

   CU_ASSERT( cffft != NULL );
   CU_ASSERT( v != NULL );
   CU_ASSERT( cf_matvec_is_approximately_equal( cf_fft_output( cffft ), v, 0.000001 ) == 1 );

   cf_fft_deep_dispose( &cffft );
   cf_matvec_dispose( &v );

   return;
}

/**
   test_output_2
*/

void test_output_2( void )
{
   cd_fft_t *cdfft = NULL;
   cd_matvec_t *v = NULL;

   cdfft = cd_fft_make( 2 );

   v = cd_matvec_make_from_args( 2, 1, 2, 1.0 + 0.0*I, 2.0 + 1.0*I );
   cd_fft_set_output( cdfft, v );

   CU_ASSERT( cdfft != NULL );
   CU_ASSERT( v != NULL );
   CU_ASSERT( cd_matvec_is_approximately_equal( cd_fft_output( cdfft ), v, 0.000001 ) == 1 );

   cd_fft_deep_dispose( &cdfft );
   cd_matvec_dispose( &v );

   return;
}

int
add_test_output( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_output", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_output_1
   add_test_to_suite( p_suite, test_output_1, "test_output_1" );

   // test_output_2
   add_test_to_suite( p_suite, test_output_2, "test_output_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

