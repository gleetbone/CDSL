/**
 @file Heap_test_put.c
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
   test_put_1
*/

void test_put_1( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 1 );

   CU_ASSERT( i_heap_count( heap ) == 1 );
   CU_ASSERT( i_heap_is_empty( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_put_2
*/

void test_put_2( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );

   CU_ASSERT( i_heap_count( heap ) == 3 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_put_3
*/

void test_put_3( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 3 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );

   CU_ASSERT( i_heap_count( heap ) == 3 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_put_4
*/

void test_put_4( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 1 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 3 );

   CU_ASSERT( i_heap_count( heap ) == 3 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_put_5
*/

void test_put_5( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 1 );

   CU_ASSERT( i_heap_count( heap ) == 4 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_put_6
*/

void test_put_6( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 3 );

   CU_ASSERT( i_heap_count( heap ) == 4 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_put_7
*/

void test_put_7( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 5 );

   CU_ASSERT( i_heap_count( heap ) == 4 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_put_8
*/

void test_put_8( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 7 );

   CU_ASSERT( i_heap_count( heap ) == 4 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_put_9
*/

void test_put_9( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap,  1 );
   i_heap_put( heap,  2 );
   i_heap_put( heap,  3 );
   i_heap_put( heap,  4 );
   i_heap_put( heap,  5 );
   i_heap_put( heap,  6 );
   i_heap_put( heap,  7 );
   i_heap_put( heap,  8 );
   i_heap_put( heap,  9 );
   i_heap_put( heap, 10 );
   i_heap_put( heap, 11 );
   i_heap_put( heap, 12 );
   i_heap_put( heap, 13 );
   i_heap_put( heap, 14 );
   i_heap_put( heap, 15 );
   i_heap_put( heap, 16 );
   i_heap_put( heap, 17 );

   CU_ASSERT( i_heap_count( heap ) == 17 );

   i_heap_dispose( &heap );

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

