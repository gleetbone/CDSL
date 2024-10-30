/**
 @file Heap_test_prune.c
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
   test_prune_1
*/

void test_prune_1( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_prune( heap, 0 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 0 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_prune_2
*/

void test_prune_2( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();
   ii_heap_kv_put( heap, 10, 1 );

   ii_heap_kv_prune( heap, 0 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 1 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_prune_3
*/

void test_prune_3( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();
   ii_heap_kv_put( heap, 10, 1 );

   ii_heap_kv_prune( heap, 1 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 0 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_prune_4
*/

void test_prune_4( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 30, 3 );

   ii_heap_kv_prune( heap, 1 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 2 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_prune_5
*/

void test_prune_5( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 30, 3 );

   ii_heap_kv_prune( heap, 2 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 1 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_prune_6
*/

void test_prune_6( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 30, 3 );

   ii_heap_kv_prune( heap, 3 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 0 );

   ii_heap_kv_dispose( &heap );

   return;
}

int
add_test_prune( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_prune", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_prune_1
   add_test_to_suite( p_suite, test_prune_1, "test_prune_1" );

   // test_prune_2
   add_test_to_suite( p_suite, test_prune_2, "test_prune_2" );

   // test_prune_3
   add_test_to_suite( p_suite, test_prune_3, "test_prune_3" );

   // test_prune_4
   add_test_to_suite( p_suite, test_prune_4, "test_prune_4" );

   // test_prune_5
   add_test_to_suite( p_suite, test_prune_5, "test_prune_5" );

   // test_prune_6
   add_test_to_suite( p_suite, test_prune_6, "test_prune_6" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

