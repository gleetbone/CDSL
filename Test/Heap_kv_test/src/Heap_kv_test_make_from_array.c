/**
 @file Heap_test_make_from_array.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Heap_kv_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)

 @section Description

 Unit tests for Heap_kv_t.

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
   test_make_from_array_1
*/

void test_make_from_array_1( void )
{
   ii_heap_kv_t *heap = NULL;
   int32_t key_array[3] = { 13, 0, 0 };
   int32_t value_array[3] = { 130, 0, 0 };

   heap = ii_heap_kv_make_from_array( key_array, value_array, 1 );

   CU_ASSERT( heap != NULL );
   CU_ASSERT( ii_heap_kv_count( heap ) == 1 );
   CU_ASSERT( ii_heap_kv_has( heap, 13 ) == 1 );

   ii_heap_kv_dispose( &heap );

   return;
}

int
add_test_make_from_array( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make_from_array", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_from_array_1
   add_test_to_suite( p_suite, test_make_from_array_1, "test_make_from_array_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

