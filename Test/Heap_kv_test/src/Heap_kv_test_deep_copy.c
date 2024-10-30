/**
 @file Heap_test_deep_copy.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Heap_kv_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)

 @section Description

 Unit tests for Heap_kv_t

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_Heap_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_deep_copy_1
*/

void test_deep_copy_1( void )
{
   ii_heap_kv_t *heap = NULL;
   ii_heap_kv_t *heap1 = NULL;

   heap = ii_heap_kv_make();
   ii_heap_kv_put( heap, 130, 13 );

   heap1 = ii_heap_kv_make();
   ii_heap_kv_deep_copy( heap1, heap );

   CU_ASSERT( heap1 != NULL );
   CU_ASSERT( ii_heap_kv_count( heap1 ) == 1 );
   CU_ASSERT( ii_heap_kv_has( heap1, 13 ) == 1 );

   ii_heap_kv_dispose( &heap );
   ii_heap_kv_dispose( &heap1 );

   return;
}

/**
   test_deep_copy_2
*/

void test_deep_copy_2( void )
{
   ii_heap_kv_t *heap = NULL;
   ii_heap_kv_t *heap1 = NULL;

   heap = ii_heap_kv_make_n( 20 );
   ii_heap_kv_put( heap, 130, 13 );

   heap1 = ii_heap_kv_make();
   ii_heap_kv_put( heap1, 230, 23 );
   ii_heap_kv_deep_copy( heap1, heap );

   CU_ASSERT( heap1 != NULL );
   CU_ASSERT( ii_heap_kv_count( heap1 ) == 1 );
   CU_ASSERT( ii_heap_kv_has( heap1, 13 ) == 1 );

   ii_heap_kv_dispose( &heap );
   ii_heap_kv_dispose( &heap1 );

   return;
}

int
add_test_deep_copy( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_deep_copy", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_deep_copy_1
   add_test_to_suite( p_suite, test_deep_copy_1, "test_deep_copy_1" );

   // test_deep_copy_2
   add_test_to_suite( p_suite, test_deep_copy_2, "test_deep_copy_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

