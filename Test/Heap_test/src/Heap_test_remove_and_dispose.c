/**
 @file Heap_test_remove_and_dispose.c
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
   test_remove_and_dispose_1
*/

void test_remove_and_dispose_1( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 1 );

   i_heap_remove_and_dispose( heap, 1 );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   result = i_heap_has( heap, 1 );
   CU_ASSERT( result == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_2
*/

void test_remove_and_dispose_2( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );

   i_heap_remove_and_dispose( heap, 2 );

   result = i_heap_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_heap_count( heap ) == 2 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_2a
*/

void test_remove_and_dispose_2a( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );

   i_heap_remove_and_dispose( heap, 1 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 1 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_heap_count( heap ) == 2 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_2b
*/

void test_remove_and_dispose_2b( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );

   i_heap_remove_and_dispose( heap, 3 );

   result = i_heap_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 3 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_heap_count( heap ) == 2 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_3
*/

void test_remove_and_dispose_3( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 3 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );

   i_heap_remove_and_dispose( heap, 2 );

   result = i_heap_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_heap_count( heap ) == 2 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_3a
*/

void test_remove_and_dispose_3a( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 3 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );

   i_heap_remove_and_dispose( heap, 1 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 1 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_heap_count( heap ) == 2 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_3b
*/

void test_remove_and_dispose_3b( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 3 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );

   i_heap_remove_and_dispose( heap, 2 );

   result = i_heap_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_heap_count( heap ) == 2 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_4
*/

void test_remove_and_dispose_4( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 1 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 3 );

   i_heap_remove_and_dispose( heap, 2 );

   result = i_heap_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_heap_count( heap ) == 2 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_4a
*/

void test_remove_and_dispose_4a( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 1 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 3 );

   i_heap_remove_and_dispose( heap, 1 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 1 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_heap_count( heap ) == 2 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_4b
*/

void test_remove_and_dispose_4b( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 1 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 3 );

   i_heap_remove_and_dispose( heap, 3 );

   result = i_heap_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 3 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_heap_count( heap ) == 2 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_5
*/

void test_remove_and_dispose_5( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );
   i_heap_put( heap, 5 );
   i_heap_put( heap, 7 );

   i_heap_remove_and_dispose( heap, 4 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 6 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 5 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 7 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 4 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_heap_count( heap ) == 6 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_5a
*/

void test_remove_and_dispose_5a( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );
   i_heap_put( heap, 5 );
   i_heap_put( heap, 7 );

   i_heap_remove_and_dispose( heap, 1 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 6 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 4 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 5 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 7 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 1 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_heap_count( heap ) == 6 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_5b
*/

void test_remove_and_dispose_5b( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );
   i_heap_put( heap, 5 );
   i_heap_put( heap, 7 );

   i_heap_remove_and_dispose( heap, 2 );

   result = i_heap_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 6 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 4 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 5 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 7 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_heap_count( heap ) == 6 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_5c
*/

void test_remove_and_dispose_5c( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );
   i_heap_put( heap, 5 );
   i_heap_put( heap, 7 );

   i_heap_remove_and_dispose( heap, 3 );

   result = i_heap_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 6 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 4 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 5 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 7 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 3 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_heap_count( heap ) == 6 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_5d
*/

void test_remove_and_dispose_5d( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );
   i_heap_put( heap, 5 );
   i_heap_put( heap, 7 );

   i_heap_remove_and_dispose( heap, 5 );

   result = i_heap_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 6 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 4 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 7 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 5 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_heap_count( heap ) == 6 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_5e
*/

void test_remove_and_dispose_5e( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );
   i_heap_put( heap, 5 );
   i_heap_put( heap, 7 );

   i_heap_remove_and_dispose( heap, 6 );

   result = i_heap_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 5 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 4 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 7 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 6 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_heap_count( heap ) == 6 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_5f
*/

void test_remove_and_dispose_5f( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );
   i_heap_put( heap, 5 );
   i_heap_put( heap, 7 );

   i_heap_remove_and_dispose( heap, 7 );

   result = i_heap_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 5 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 4 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 6 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 7 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_heap_count( heap ) == 6 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_6
*/

void test_remove_and_dispose_6( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );
   i_heap_put( heap, 5 );
   i_heap_put( heap, 7 );

   i_heap_remove_and_dispose( heap, 1 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 6 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 1 );
   CU_ASSERT( result == 0 );

   result = i_heap_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 5 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 7 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i_heap_count( heap ) == 6 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_6a
*/

void test_remove_and_dispose_6a( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );

   i_heap_remove_and_dispose( heap, 4 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 4 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_heap_count( heap ) == 1 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_6b
*/

void test_remove_and_dispose_6b( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 8 );
   i_heap_put( heap, 7 );
   i_heap_put( heap, 6 );

   i_heap_remove_and_dispose( heap, 8 );

   result = i_heap_has( heap, 4 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 6 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 7 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 8 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_heap_count( heap ) == 3 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_6c
*/

void test_remove_and_dispose_6c( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 3 );

   i_heap_remove_and_dispose( heap, 1 );

   result = i_heap_has( heap, 1 );
   CU_ASSERT( result == 0 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i_heap_count( heap ) == 3 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_remove_7
*/

void test_remove_and_dispose_7( void )
{
   s_heap_t *heap = NULL;
   string_t *s1 = NULL;
   string_t *s2 = NULL;
   string_t *s3 = NULL;
   string_t *s4 = NULL;
   int32_t result = 0;

   heap = s_heap_make();

   s1 = string_make_from_cstring( "1" );
   s2 = string_make_from_cstring( "2" );
   s3 = string_make_from_cstring( "3" );
   s4 = string_make_from_cstring( "4" );
   
   s_heap_put( heap, s4 );
   s_heap_put( heap, s1 );
   s_heap_put( heap, s2 );
   s_heap_put( heap, s3 );

   s_heap_remove_and_dispose( heap, s1 );

   result = s_heap_has( heap, s2 );
   CU_ASSERT( result == 1 );

   result = s_heap_has( heap, s3 );
   CU_ASSERT( result == 1 );

   result = s_heap_has( heap, s4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( s_heap_count( heap ) == 3 );

   s_heap_deep_dispose( &heap );

   return;
}

int
add_test_remove_and_dispose( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_remove_and_dispose", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_remove_and_dispose_1
   add_test_to_suite( p_suite, test_remove_and_dispose_1, "test_remove_and_dispose_1" );

   // test_remove_and_dispose_2
   add_test_to_suite( p_suite, test_remove_and_dispose_2, "test_remove_and_dispose_2" );
   add_test_to_suite( p_suite, test_remove_and_dispose_2a, "test_remove_and_dispose_2a" );
   add_test_to_suite( p_suite, test_remove_and_dispose_2b, "test_remove_and_dispose_2b" );

   // test_remove_and_dispose_3
   add_test_to_suite( p_suite, test_remove_and_dispose_3, "test_remove_and_dispose_3" );
   add_test_to_suite( p_suite, test_remove_and_dispose_3a, "test_remove_and_dispose_3a" );
   add_test_to_suite( p_suite, test_remove_and_dispose_3b, "test_remove_and_dispose_3b" );

   // test_remove_and_dispose_4
   add_test_to_suite( p_suite, test_remove_and_dispose_4, "test_remove_and_dispose_4" );
   add_test_to_suite( p_suite, test_remove_and_dispose_4a, "test_remove_and_dispose_4a" );
   add_test_to_suite( p_suite, test_remove_and_dispose_4b, "test_remove_and_dispose_4b" );

   // test_remove_and_dispose_5
   add_test_to_suite( p_suite, test_remove_and_dispose_5, "test_remove_and_dispose_5" );
   add_test_to_suite( p_suite, test_remove_and_dispose_5a, "test_remove_and_dispose_5a" );
   add_test_to_suite( p_suite, test_remove_and_dispose_5b, "test_remove_and_dispose_5b" );
   add_test_to_suite( p_suite, test_remove_and_dispose_5c, "test_remove_and_dispose_5c" );
   add_test_to_suite( p_suite, test_remove_and_dispose_5d, "test_remove_and_dispose_5d" );
   add_test_to_suite( p_suite, test_remove_and_dispose_5e, "test_remove_and_dispose_5e" );
   add_test_to_suite( p_suite, test_remove_and_dispose_5f, "test_remove_and_dispose_5f" );

   // test_remove_and_dispose_6
   add_test_to_suite( p_suite, test_remove_and_dispose_6, "test_remove_and_dispose_6" );
   add_test_to_suite( p_suite, test_remove_and_dispose_6a, "test_remove_and_dispose_6a" );
   add_test_to_suite( p_suite, test_remove_and_dispose_6b, "test_remove_and_dispose_6b" );
   add_test_to_suite( p_suite, test_remove_and_dispose_6c, "test_remove_and_dispose_6c" );

   // test_remove_and_dispose_7
   add_test_to_suite( p_suite, test_remove_and_dispose_7, "test_remove_and_dispose_7" );
   
   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

