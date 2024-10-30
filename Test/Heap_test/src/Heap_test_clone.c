/**
 @file Heap_test_clone.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Heap_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)

 @section Description

 Unit tests for Heap_t

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_Heap.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_clone_1
*/

void test_clone_1( void )
{
   i_heap_t *heap = NULL;
   i_heap_t *heap1 = NULL;

   heap = i_heap_make();
   i_heap_put( heap, 13 );

   heap1 = i_heap_clone( heap );

   CU_ASSERT( heap1 != NULL );
   CU_ASSERT( i_heap_count( heap1 ) == 1 );
   CU_ASSERT( i_heap_has( heap1, 13 ) == 1 );

   i_heap_dispose( &heap );
   i_heap_dispose( &heap1 );

   return;
}

int
add_test_clone( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_clone", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_clone_1
   add_test_to_suite( p_suite, test_clone_1, "test_clone_1" );
   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

