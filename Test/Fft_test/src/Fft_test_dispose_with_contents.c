/**
 @file Fft_test_deep_dispose.c
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
   test_deep_dispose_1
*/

void test_deep_dispose_1( void )
{
   cf_fft_t *cffft = NULL;

   cffft = cf_fft_make( 16 );

   CU_ASSERT( cffft != NULL );

   cf_fft_deep_dispose( &cffft );

   return;
}

/**
   test_deep_dispose_2
*/

void test_deep_dispose_2( void )
{
   cd_fft_t *cdfft = NULL;

   cdfft = cd_fft_make( 16 );

   CU_ASSERT( cdfft != NULL );

   cd_fft_deep_dispose( &cdfft );

   return;
}

int
add_test_deep_dispose( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_deep_dispose", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_deep_dispose_1
   add_test_to_suite( p_suite, test_deep_dispose_1, "test_deep_dispose_1" );

   // test_deep_dispose_2
   add_test_to_suite( p_suite, test_deep_dispose_2, "test_deep_dispose_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

