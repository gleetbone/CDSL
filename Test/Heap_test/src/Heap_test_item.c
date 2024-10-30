/**
 @file Heap_test_item.c
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
#include "s_Heap.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_item_1
*/

void test_item_1( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 1 );

   CU_ASSERT( i_heap_item( heap ) == 1 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_item_2
*/

void test_item_2( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );

   CU_ASSERT( i_heap_item( heap ) == 1 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_item_3
*/

void test_item_3( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 3 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );

   CU_ASSERT( i_heap_item( heap ) == 1 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_item_4
*/

void test_item_4( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 1 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 3 );

   CU_ASSERT( i_heap_item( heap ) == 1 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_item_5
*/

void test_item_5( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 1 );

   CU_ASSERT( i_heap_item( heap ) == 1 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_item_6
*/

void test_item_6( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 3 );

   CU_ASSERT( i_heap_item( heap ) == 2 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_item_7
*/

void test_item_7( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 5 );

   CU_ASSERT( i_heap_item( heap ) == 2 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_item_8
*/

void test_item_8( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 7 );

   CU_ASSERT( i_heap_item( heap ) == 2 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_item_9
*/

void test_item_9( void )
{
   s_heap_t *heap = NULL;
   string_t *s1 = NULL;
   string_t *s2 = NULL;
   string_t *s3 = NULL;
   string_t *s4 = NULL;

   s1 = string_make_from_cstring( "1" );
   s2 = string_make_from_cstring( "2" );
   s3 = string_make_from_cstring( "3" );
   s4 = string_make_from_cstring( "4" );
   
   heap = s_heap_make();

   s_heap_put( heap, s3 );
   s_heap_put( heap, s2 );
   s_heap_put( heap, s1 );
   s_heap_put( heap, s4 );

   CU_ASSERT( s_heap_item( heap ) == s1 );

   s_heap_dispose( &heap );
   
   string_dispose( &s1 );
   string_dispose( &s2 );
   string_dispose( &s3 );
   string_dispose( &s4 );

   return;
}

/**
   test_item_10
*/

void test_item_10( void )
{
   s_heap_t *heap = NULL;
   string_t *s1 = NULL;
   string_t *s2 = NULL;
   string_t *s3 = NULL;
   string_t *s4 = NULL;

   s1 = string_make_from_cstring( "1" );
   s2 = string_make_from_cstring( "2" );
   s3 = string_make_from_cstring( "3" );
   s4 = string_make_from_cstring( "4" );
   
   heap = s_heap_make();

   s_heap_put( heap, s2 );
   s_heap_put( heap, s1 );
   s_heap_put( heap, s4 );
   s_heap_put( heap, s3 );

   CU_ASSERT( s_heap_item( heap ) == s1 );

   s_heap_deep_dispose( &heap );
   
   return;
}

int
add_test_item( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_item", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_item_1
   add_test_to_suite( p_suite, test_item_1, "test_item_1" );

   // test_item_2
   add_test_to_suite( p_suite, test_item_2, "test_item_2" );

   // test_item_3
   add_test_to_suite( p_suite, test_item_3, "test_item_3" );

   // test_item_4
   add_test_to_suite( p_suite, test_item_4, "test_item_4" );

   // test_item_5
   add_test_to_suite( p_suite, test_item_5, "test_item_5" );

   // test_item_6
   add_test_to_suite( p_suite, test_item_6, "test_item_6" );

   // test_item_7
   add_test_to_suite( p_suite, test_item_7, "test_item_7" );

   // test_item_8
   add_test_to_suite( p_suite, test_item_8, "test_item_8" );

   // test_item_9
   add_test_to_suite( p_suite, test_item_9, "test_item_9" );

   // test_item_10
   add_test_to_suite( p_suite, test_item_10, "test_item_10" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

