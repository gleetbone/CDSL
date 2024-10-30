/**
 @file Heap_test_prune_and_dispose.c
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
   test_prune_and_dispose_1
*/

void test_prune_and_dispose_1( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_prune_and_dispose( heap, 0 );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_prune_and_dispose_2
*/

void test_prune_and_dispose_2( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();
   i_heap_put( heap, 1 );

   i_heap_prune_and_dispose( heap, 0 );

   CU_ASSERT( i_heap_count( heap ) == 1 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_prune_and_dispose_3
*/

void test_prune_and_dispose_3( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();
   i_heap_put( heap, 1 );

   i_heap_prune_and_dispose( heap, 1 );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_prune_and_dispose_4
*/

void test_prune_and_dispose_4( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );

   i_heap_prune_and_dispose( heap, 1 );

   CU_ASSERT( i_heap_count( heap ) == 2 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_prune_and_dispose_5
*/

void test_prune_and_dispose_5( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );

   i_heap_prune_and_dispose( heap, 2 );

   CU_ASSERT( i_heap_count( heap ) == 1 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_prune_and_dispose_6
*/

void test_prune_and_dispose_6( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );

   i_heap_prune_and_dispose( heap, 3 );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

int
add_test_prune_and_dispose( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_prune_and_dispose", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_prune_and_dispose_1
   add_test_to_suite( p_suite, test_prune_and_dispose_1, "test_prune_and_dispose_1" );

   // test_prune_and_dispose_2
   add_test_to_suite( p_suite, test_prune_and_dispose_2, "test_prune_and_dispose_2" );

   // test_prune_and_dispose_3
   add_test_to_suite( p_suite, test_prune_and_dispose_3, "test_prune_and_dispose_3" );

   // test_prune_and_dispose_4
   add_test_to_suite( p_suite, test_prune_and_dispose_4, "test_prune_and_dispose_4" );

   // test_prune_and_dispose_5
   add_test_to_suite( p_suite, test_prune_and_dispose_5, "test_prune_and_dispose_5" );

   // test_prune_and_dispose_6
   add_test_to_suite( p_suite, test_prune_and_dispose_6, "test_prune_and_dispose_6" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

