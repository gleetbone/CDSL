/**
 @file Heap_test_put_and_dispose.c
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
   test_put_and_dispose_1
*/

void test_put_and_dispose_1( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put_and_dispose( heap, 1 );

   CU_ASSERT( i_heap_count( heap ) == 1 );
   CU_ASSERT( i_heap_is_empty( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_put_and_dispose_2
*/

void test_put_and_dispose_2( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put_and_dispose( heap, 2 );
   i_heap_put_and_dispose( heap, 1 );
   i_heap_put_and_dispose( heap, 3 );

   CU_ASSERT( i_heap_count( heap ) == 3 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_put_and_dispose_3
*/

void test_put_and_dispose_3( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put_and_dispose( heap, 3 );
   i_heap_put_and_dispose( heap, 2 );
   i_heap_put_and_dispose( heap, 1 );

   CU_ASSERT( i_heap_count( heap ) == 3 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_put_and_dispose_4
*/

void test_put_and_dispose_4( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put_and_dispose( heap, 1 );
   i_heap_put_and_dispose( heap, 2 );
   i_heap_put_and_dispose( heap, 3 );

   CU_ASSERT( i_heap_count( heap ) == 3 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_put_and_dispose_5
*/

void test_put_and_dispose_5( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put_and_dispose( heap, 4 );
   i_heap_put_and_dispose( heap, 2 );
   i_heap_put_and_dispose( heap, 6 );
   i_heap_put_and_dispose( heap, 1 );

   CU_ASSERT( i_heap_count( heap ) == 4 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_put_and_dispose_6
*/

void test_put_and_dispose_6( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put_and_dispose( heap, 4 );
   i_heap_put_and_dispose( heap, 2 );
   i_heap_put_and_dispose( heap, 6 );
   i_heap_put_and_dispose( heap, 3 );

   CU_ASSERT( i_heap_count( heap ) == 4 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_put_and_dispose_7
*/

void test_put_and_dispose_7( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put_and_dispose( heap, 4 );
   i_heap_put_and_dispose( heap, 2 );
   i_heap_put_and_dispose( heap, 6 );
   i_heap_put_and_dispose( heap, 5 );

   CU_ASSERT( i_heap_count( heap ) == 4 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_put_and_dispose_8
*/

void test_put_and_dispose_8( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put_and_dispose( heap, 4 );
   i_heap_put_and_dispose( heap, 2 );
   i_heap_put_and_dispose( heap, 6 );
   i_heap_put_and_dispose( heap, 7 );

   CU_ASSERT( i_heap_count( heap ) == 4 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_put_9
*/

void test_put_and_dispose_9( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put_and_dispose( heap,  1 );
   i_heap_put_and_dispose( heap,  2 );
   i_heap_put_and_dispose( heap,  3 );
   i_heap_put_and_dispose( heap,  4 );
   i_heap_put_and_dispose( heap,  5 );
   i_heap_put_and_dispose( heap,  6 );
   i_heap_put_and_dispose( heap,  7 );
   i_heap_put_and_dispose( heap,  8 );
   i_heap_put_and_dispose( heap,  9 );
   i_heap_put_and_dispose( heap, 10 );
   i_heap_put_and_dispose( heap, 11 );
   i_heap_put_and_dispose( heap, 12 );
   i_heap_put_and_dispose( heap, 13 );
   i_heap_put_and_dispose( heap, 14 );
   i_heap_put_and_dispose( heap, 15 );
   i_heap_put_and_dispose( heap, 16 );
   i_heap_put_and_dispose( heap, 17 );

   CU_ASSERT( i_heap_count( heap ) == 17 );

   i_heap_dispose( &heap );

   return;
}

int
add_test_put_and_dispose( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_put_and_dispose", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_put_and_dispose_1
   add_test_to_suite( p_suite, test_put_and_dispose_1, "test_put_and_dispose_1" );

   // test_put_and_dispose_2
   add_test_to_suite( p_suite, test_put_and_dispose_2, "test_put_and_dispose_2" );

   // test_put_and_dispose_3
   add_test_to_suite( p_suite, test_put_and_dispose_3, "test_put_and_dispose_3" );

   // test_put_and_dispose_4
   add_test_to_suite( p_suite, test_put_and_dispose_4, "test_put_and_dispose_4" );

   // test_put_and_dispose_5
   add_test_to_suite( p_suite, test_put_and_dispose_5, "test_put_and_dispose_5" );

   // test_put_and_dispose_6
   add_test_to_suite( p_suite, test_put_and_dispose_6, "test_put_and_dispose_6" );

   // test_put_and_dispose_7
   add_test_to_suite( p_suite, test_put_and_dispose_7, "test_put_and_dispose_7" );

   // test_put_and_dispose_8
   add_test_to_suite( p_suite, test_put_and_dispose_8, "test_put_and_dispose_8" );

   // test_put_and_dispose_9
   add_test_to_suite( p_suite, test_put_and_dispose_9, "test_put_and_dispose_9" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

