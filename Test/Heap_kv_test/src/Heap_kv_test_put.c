/**
 @file Heap_test_put.c
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
   test_put_1
*/

void test_put_1( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 10, 1 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 1 );
   CU_ASSERT( ii_heap_kv_is_empty( heap ) == 0 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_put_2
*/

void test_put_2( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 30, 3 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 3 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_put_3
*/

void test_put_3( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 30, 3 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 10, 1 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 3 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_put_4
*/

void test_put_4( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 30, 3 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 3 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_put_5
*/

void test_put_5( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 40, 4 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 60, 6 );
   ii_heap_kv_put( heap, 10, 1 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 4 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_put_6
*/

void test_put_6( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 40, 4 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 60, 6 );
   ii_heap_kv_put( heap, 30, 3 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 4 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_put_7
*/

void test_put_7( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 40, 4 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 60, 6 );
   ii_heap_kv_put( heap, 50, 5 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 4 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_put_8
*/

void test_put_8( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 40, 4 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 60, 6 );
   ii_heap_kv_put( heap, 70, 7 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 4 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_put_9
*/

void test_put_9( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 40, 40 );
   ii_heap_kv_put( heap, 20, 20 );
   ii_heap_kv_put( heap, 60, 60 );
   ii_heap_kv_put( heap, 70, 70 );
   ii_heap_kv_put( heap, 70, 71 );
   ii_heap_kv_put( heap, 71, 72 );
   ii_heap_kv_put( heap, 72, 73 );
   ii_heap_kv_put( heap, 73, 74 );
   ii_heap_kv_put( heap, 74, 75 );
   ii_heap_kv_put( heap, 75, 76 );
   ii_heap_kv_put( heap, 76, 77 );
   ii_heap_kv_put( heap, 77, 78 );
   ii_heap_kv_put( heap, 78, 79 );
   ii_heap_kv_put( heap, 79, 80 );
   ii_heap_kv_put( heap, 80, 81 );
   ii_heap_kv_put( heap, 81, 82 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 16 );

   ii_heap_kv_dispose( &heap );

   return;
}

int
add_test_put( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_put", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_put_1
   add_test_to_suite( p_suite, test_put_1, "test_put_1" );

   // test_put_2
   add_test_to_suite( p_suite, test_put_2, "test_put_2" );

   // test_put_3
   add_test_to_suite( p_suite, test_put_3, "test_put_3" );

   // test_put_4
   add_test_to_suite( p_suite, test_put_4, "test_put_4" );

   // test_put_5
   add_test_to_suite( p_suite, test_put_5, "test_put_5" );

   // test_put_6
   add_test_to_suite( p_suite, test_put_6, "test_put_6" );

   // test_put_7
   add_test_to_suite( p_suite, test_put_7, "test_put_7" );

   // test_put_8
   add_test_to_suite( p_suite, test_put_8, "test_put_8" );

   // test_put_9
   add_test_to_suite( p_suite, test_put_9, "test_put_9" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

