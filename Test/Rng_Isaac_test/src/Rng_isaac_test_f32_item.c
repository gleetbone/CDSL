/**
 @file Rng_isaac_test_f32_item.c
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

#include "Rng_Isaac.h"

#define UNION_CAST(x, destType) \
 (((union {__typeof__(x) a; destType b;})x).b)

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_f32_item_1
*/

void test_f32_item_1( void )
{
   rng_isaac_t *rng = NULL;
   uint64_t u = 0;
   int32_t i = 0;
   float32_t f1 = 0;
   float32_t f2 = 0;

   rng = rng_isaac_make();

   CU_ASSERT( rng != NULL );

   for ( i=0; i<512; i++ )
   {
      u = rng_isaac_u64_item( rng );
      f1 = rng_isaac_f32_item( rng );
      rng_isaac_forth( rng );

      f2 = ( float32_t ) 1.0*u/UINT64_MAX;

      CU_ASSERT( f1 == f2 );
   }

   rng_isaac_dispose( &rng );

   return;
}

int
add_test_f32_item( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_f32_item", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_f32_item_1
   add_test_to_suite( p_suite, test_f32_item_1, "test_f32_item_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

