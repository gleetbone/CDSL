/**
 @file Rng_isaac_gaussian_test_dispose.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Rng_isaac_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Rng_isaac_make.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "Rng_Isaac_gaussian.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_dispose_1
*/

void gaussian_test_dispose_1( void )
{
   rng_isaac_gaussian_t *rng = NULL;

   rng = rng_isaac_gaussian_make();

   CU_ASSERT( rng != NULL );

   rng_isaac_gaussian_dispose( &rng );

   return;
}

/**
   test_dispose_2
*/

void gaussian_test_dispose_2( void )
{
   rng_isaac_gaussian_t *rng = NULL;

   rng = rng_isaac_gaussian_make_with_seed( 0x1234567812345678LL );

   CU_ASSERT( rng != NULL );

   rng_isaac_gaussian_dispose( &rng );

   return;
}

int
add_gaussian_test_dispose( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_dispose", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_dispose_1
   add_test_to_suite( p_suite, gaussian_test_dispose_1, "gaussian_test_dispose_1" );

   // test_dispose_2
   add_test_to_suite( p_suite, gaussian_test_dispose_2, "gaussian_test_dispose_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

