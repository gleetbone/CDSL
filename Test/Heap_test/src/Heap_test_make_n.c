/**
 @file Heap_test_make_n.c
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
   test_make_n_1
*/

void test_make_n_1( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make_n( 20 );

   CU_ASSERT( heap != NULL );
   CU_ASSERT( i_heap_count( heap ) == 0 );
   CU_ASSERT( i_heap_capacity( heap ) == 20 );
   CU_ASSERT( i_heap_is_empty( heap ) == 1 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_make_n_2
*/

void test_make_n_2( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make_n( 2 );

   CU_ASSERT( heap != NULL );
   CU_ASSERT( i_heap_count( heap ) == 0 );
   CU_ASSERT( i_heap_capacity( heap ) == 15 );
   CU_ASSERT( i_heap_is_empty( heap ) == 1 );

   i_heap_dispose( &heap );

   return;
}

int
add_test_make_n( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make_n", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_n_1
   add_test_to_suite( p_suite, test_make_n_1, "test_make_n_1" );

   // test_make_n_2
   add_test_to_suite( p_suite, test_make_n_2, "test_make_n_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

