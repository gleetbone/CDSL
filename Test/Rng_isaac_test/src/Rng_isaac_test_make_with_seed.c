/**
 @file Rng_isaac_test_make_with_seed.c
 @author Greg Lee
 @version 1.0.0
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

#include "Rng_Isaac.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_make_with_seed_1
*/

void test_make_with_seed_1( void )
{
   rng_isaac_t *rng = NULL;

   rng = rng_isaac_make_with_seed( 0x1234567812345678LL );

   CU_ASSERT( rng != NULL );

   rng_isaac_dispose( rng );

   return;
}

int
add_test_make_with_seed( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make_with_seed", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_with_seed_1
   add_test_to_suite( p_suite, test_make_with_seed_1, "test_make_with_seed_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

