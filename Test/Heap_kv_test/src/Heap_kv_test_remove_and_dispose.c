/**
 @file Heap_test_remove_and_dispose.c
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
   test_remove_and_dispose_1
*/

void test_remove_and_dispose_1( void )
{
   ii_heap_kv_t *heap = NULL;
   int32_t result = 0;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 10, 1 );

   ii_heap_kv_remove_and_dispose( heap, 1 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 0 );

   result = ii_heap_kv_has( heap, 1 );
   CU_ASSERT( result == 0 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_2
*/

void test_remove_and_dispose_2( void )
{
   ii_heap_kv_t *heap = NULL;
   int32_t result = 0;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 30, 3 );

   ii_heap_kv_remove_and_dispose( heap, 2 );

   result = ii_heap_kv_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 2 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 2 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_2a
*/

void test_remove_and_dispose_2a( void )
{
   ii_heap_kv_t *heap = NULL;
   int32_t result = 0;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 30, 3 );

   ii_heap_kv_remove_and_dispose( heap, 1 );

   result = ii_heap_kv_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 1 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 2 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_2b
*/

void test_remove_and_dispose_2b( void )
{
   ii_heap_kv_t *heap = NULL;
   int32_t result = 0;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 30, 3 );

   ii_heap_kv_remove_and_dispose( heap, 3 );

   result = ii_heap_kv_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 3 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 2 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_3
*/

void test_remove_and_dispose_3( void )
{
   ii_heap_kv_t *heap = NULL;
   int32_t result = 0;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 30, 3 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 10, 1 );

   ii_heap_kv_remove_and_dispose( heap, 2 );

   result = ii_heap_kv_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 2 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 2 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_3a
*/

void test_remove_and_dispose_3a( void )
{
   ii_heap_kv_t *heap = NULL;
   int32_t result = 0;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 30, 3 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 10, 1 );

   ii_heap_kv_remove_and_dispose( heap, 1 );

   result = ii_heap_kv_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 1 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 2 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_3b
*/

void test_remove_and_dispose_3b( void )
{
   ii_heap_kv_t *heap = NULL;
   int32_t result = 0;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 30, 3 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 10, 1 );

   ii_heap_kv_remove_and_dispose( heap, 2 );

   result = ii_heap_kv_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 2 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 2 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_4
*/

void test_remove_and_dispose_4( void )
{
   ii_heap_kv_t *heap = NULL;
   int32_t result = 0;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 30, 3 );

   ii_heap_kv_remove_and_dispose( heap, 2 );

   result = ii_heap_kv_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 2 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 2 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_4a
*/

void test_remove_and_dispose_4a( void )
{
   ii_heap_kv_t *heap = NULL;
   int32_t result = 0;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 30, 3 );

   ii_heap_kv_remove_and_dispose( heap, 1 );

   result = ii_heap_kv_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 1 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 2 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_4b
*/

void test_remove_and_dispose_4b( void )
{
   ii_heap_kv_t *heap = NULL;
   int32_t result = 0;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 30, 3 );

   ii_heap_kv_remove_and_dispose( heap, 3 );

   result = ii_heap_kv_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 3 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 2 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_5
*/

void test_remove_and_dispose_5( void )
{
   ii_heap_kv_t *heap = NULL;
   int32_t result = 0;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 40, 4 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 60, 6 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 30, 3 );
   ii_heap_kv_put( heap, 50, 5 );
   ii_heap_kv_put( heap, 70, 7 );

   ii_heap_kv_remove_and_dispose( heap, 4 );

   result = ii_heap_kv_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 6 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 5 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 7 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 4 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 6 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_5a
*/

void test_remove_and_dispose_5a( void )
{
   ii_heap_kv_t *heap = NULL;
   int32_t result = 0;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 40, 4 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 60, 6 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 30, 3 );
   ii_heap_kv_put( heap, 50, 5 );
   ii_heap_kv_put( heap, 70, 7 );

   ii_heap_kv_remove_and_dispose( heap, 1 );

   result = ii_heap_kv_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 6 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 4 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 5 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 7 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 1 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 6 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_5b
*/

void test_remove_and_dispose_5b( void )
{
   ii_heap_kv_t *heap = NULL;
   int32_t result = 0;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 40, 4 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 60, 6 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 30, 3 );
   ii_heap_kv_put( heap, 50, 5 );
   ii_heap_kv_put( heap, 70, 7 );

   ii_heap_kv_remove_and_dispose( heap, 2 );

   result = ii_heap_kv_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 6 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 4 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 5 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 7 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 2 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 6 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_5c
*/

void test_remove_and_dispose_5c( void )
{
   ii_heap_kv_t *heap = NULL;
   int32_t result = 0;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 40, 4 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 60, 6 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 30, 3 );
   ii_heap_kv_put( heap, 50, 5 );
   ii_heap_kv_put( heap, 70, 7 );

   ii_heap_kv_remove_and_dispose( heap, 3 );

   result = ii_heap_kv_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 6 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 4 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 5 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 7 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 3 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 6 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_5d
*/

void test_remove_and_dispose_5d( void )
{
   ii_heap_kv_t *heap = NULL;
   int32_t result = 0;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 40, 4 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 60, 6 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 30, 3 );
   ii_heap_kv_put( heap, 50, 5 );
   ii_heap_kv_put( heap, 70, 7 );

   ii_heap_kv_remove_and_dispose( heap, 5 );

   result = ii_heap_kv_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 6 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 4 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 7 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 5 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 6 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_5e
*/

void test_remove_and_dispose_5e( void )
{
   ii_heap_kv_t *heap = NULL;
   int32_t result = 0;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 40, 4 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 60, 6 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 30, 3 );
   ii_heap_kv_put( heap, 50, 5 );
   ii_heap_kv_put( heap, 70, 7 );

   ii_heap_kv_remove_and_dispose( heap, 6 );

   result = ii_heap_kv_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 5 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 4 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 7 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 6 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 6 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_5f
*/

void test_remove_and_dispose_5f( void )
{
   ii_heap_kv_t *heap = NULL;
   int32_t result = 0;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 40, 4 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 60, 6 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 30, 3 );
   ii_heap_kv_put( heap, 50, 5 );
   ii_heap_kv_put( heap, 70, 7 );

   ii_heap_kv_remove_and_dispose( heap, 7 );

   result = ii_heap_kv_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 5 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 4 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 6 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 7 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 6 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_6
*/

void test_remove_and_dispose_6( void )
{
   ii_heap_kv_t *heap = NULL;
   int32_t result = 0;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 40, 4 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 60, 6 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 30, 3 );
   ii_heap_kv_put( heap, 50, 5 );
   ii_heap_kv_put( heap, 70, 7 );

   ii_heap_kv_remove_and_dispose( heap, 1 );

   result = ii_heap_kv_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 6 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 1 );
   CU_ASSERT( result == 0 );

   result = ii_heap_kv_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 5 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 7 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 6 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_6a
*/

void test_remove_and_dispose_6a( void )
{
   ii_heap_kv_t *heap = NULL;
   int32_t result = 0;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 40, 4 );
   ii_heap_kv_put( heap, 20, 2 );

   ii_heap_kv_remove_and_dispose( heap, 4 );

   result = ii_heap_kv_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 4 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 1 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_6b
*/

void test_remove_and_dispose_6b( void )
{
   ii_heap_kv_t *heap = NULL;
   int32_t result = 0;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 40, 4 );
   ii_heap_kv_put( heap, 80, 8 );
   ii_heap_kv_put( heap, 70, 7 );
   ii_heap_kv_put( heap, 60, 6 );

   ii_heap_kv_remove_and_dispose( heap, 8 );

   result = ii_heap_kv_has( heap, 4 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 6 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 7 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 8 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 3 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_remove_and_dispose_6c
*/

void test_remove_and_dispose_6c( void )
{
   ii_heap_kv_t *heap = NULL;
   int32_t result = 0;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 40, 4 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 30, 3 );

   ii_heap_kv_remove_and_dispose( heap, 1 );

   result = ii_heap_kv_has( heap, 1 );
   CU_ASSERT( result == 0 );

   result = ii_heap_kv_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = ii_heap_kv_has( heap, 4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ii_heap_kv_count( heap ) == 3 );

   ii_heap_kv_dispose( &heap );

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

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

