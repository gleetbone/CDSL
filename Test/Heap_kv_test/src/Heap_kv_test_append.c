/**
 @file Heap_test_append.c
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
   test_append_1
*/

void test_append_1( void )
{
   ii_heap_kv_t *heap = NULL;
   ii_heap_kv_t *heap1 = NULL;

   heap = ii_heap_kv_make();

   heap1 = ii_heap_kv_make();

   ii_heap_kv_append( heap, heap1 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 0 );

   ii_heap_kv_dispose( &heap );
   ii_heap_kv_dispose( &heap1 );

   return;
}

/**
   test_append_2
*/

void test_append_2( void )
{
   ii_heap_kv_t *heap = NULL;
   ii_heap_kv_t *heap1 = NULL;

   heap = ii_heap_kv_make();
   ii_heap_kv_put( heap, 10, 1 );

   heap1 = ii_heap_kv_make();

   ii_heap_kv_append( heap, heap1 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 1 );
   CU_ASSERT( ii_heap_kv_key( heap ) == 1 );
   CU_ASSERT( ii_heap_kv_item( heap ) == 10 );

   ii_heap_kv_dispose( &heap );
   ii_heap_kv_dispose( &heap1 );

   return;
}

/**
   test_append_3
*/

void test_append_3( void )
{
   ii_heap_kv_t *heap = NULL;
   ii_heap_kv_t *heap1 = NULL;

   heap = ii_heap_kv_make();

   heap1 = ii_heap_kv_make();
   ii_heap_kv_put( heap1, 20, 2 );

   ii_heap_kv_append( heap, heap1 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 1 );
   CU_ASSERT( ii_heap_kv_key( heap ) == 2 );
   CU_ASSERT( ii_heap_kv_item( heap ) == 20 );

   ii_heap_kv_dispose( &heap );
   ii_heap_kv_dispose( &heap1 );

   return;
}

/**
   test_append_4
*/

void test_append_4( void )
{
   ii_heap_kv_t *heap = NULL;
   ii_heap_kv_t *heap1 = NULL;

   heap = ii_heap_kv_make();
   ii_heap_kv_put( heap, 10, 1 );

   heap1 = ii_heap_kv_make();
   ii_heap_kv_put( heap1, 20, 2 );

   ii_heap_kv_append( heap, heap1 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 2 );
   CU_ASSERT( ii_heap_kv_key( heap ) == 1 );
   CU_ASSERT( ii_heap_kv_item( heap ) == 10 );

   ii_heap_kv_dispose( &heap );
   ii_heap_kv_dispose( &heap1 );

   return;
}

/**
   test_append_5
*/

void test_append_5( void )
{
   ii_heap_kv_t *heap = NULL;
   ii_heap_kv_t *heap1 = NULL;

   heap = ii_heap_kv_make();
   ii_heap_kv_put( heap, 20, 2 );

   heap1 = ii_heap_kv_make();
   ii_heap_kv_put( heap1, 10, 1 );

   ii_heap_kv_append( heap, heap1 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 2 );
   CU_ASSERT( ii_heap_kv_key( heap ) == 1 );
   CU_ASSERT( ii_heap_kv_item( heap ) == 10 );

   ii_heap_kv_dispose( &heap );
   ii_heap_kv_dispose( &heap1 );

   return;
}

/**
   test_append_6
*/

void test_append_6( void )
{
   ii_heap_kv_t *heap = NULL;
   ii_heap_kv_t *heap1 = NULL;

   heap = ii_heap_kv_make();
   ii_heap_kv_put( heap, 10, 1 );

   heap1 = ii_heap_kv_make();
   ii_heap_kv_put( heap1, 10, 1 );

   ii_heap_kv_append( heap, heap1 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 1 );
   CU_ASSERT( ii_heap_kv_key( heap ) == 1 );
   CU_ASSERT( ii_heap_kv_item( heap ) == 10 );

   ii_heap_kv_dispose( &heap );
   ii_heap_kv_dispose( &heap1 );

   return;
}

int
add_test_append( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_append", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_append_1
   add_test_to_suite( p_suite, test_append_1, "test_append_1" );

   // test_append_2
   add_test_to_suite( p_suite, test_append_2, "test_append_2" );

   // test_append_3
   add_test_to_suite( p_suite, test_append_3, "test_append_3" );

   // test_append_4
   add_test_to_suite( p_suite, test_append_4, "test_append_4" );

   // test_append_5
   add_test_to_suite( p_suite, test_append_5, "test_append_5" );

   // test_append_6
   add_test_to_suite( p_suite, test_append_6, "test_append_6" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

