/**
 @file Heap_test_has.c
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
   test_has_1
*/

void test_has_1( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 1 );

   result = i_heap_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 0 );
   CU_ASSERT( result == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_has_2
*/

void test_has_2( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 0 );
   CU_ASSERT( result == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_has_3
*/

void test_has_3( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 3 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 0 );
   CU_ASSERT( result == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_has_4
*/

void test_has_4( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 1 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 3 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 0 );
   CU_ASSERT( result == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_has_5
*/

void test_has_5( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 1 );

   result = i_heap_has( heap, 4 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 6 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 1 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 0 );
   CU_ASSERT( result == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_has_6
*/

void test_has_6( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 3 );

   result = i_heap_has( heap, 4 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 6 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 3 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 0 );
   CU_ASSERT( result == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_has_7
*/

void test_has_7( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 5 );

   result = i_heap_has( heap, 4 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 6 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 5 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 0 );
   CU_ASSERT( result == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_has_8
*/

void test_has_8( void )
{
   i_heap_t *heap = NULL;
   int32_t result = 0;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 7 );

   result = i_heap_has( heap, 4 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 2 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 6 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 7 );
   CU_ASSERT( result == 1 );

   result = i_heap_has( heap, 0 );
   CU_ASSERT( result == 0 );

   i_heap_dispose( &heap );

   return;
}

int
add_test_has( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_has", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_has_1
   add_test_to_suite( p_suite, test_has_1, "test_has_1" );

   // test_has_2
   add_test_to_suite( p_suite, test_has_2, "test_has_2" );

   // test_has_3
   add_test_to_suite( p_suite, test_has_3, "test_has_3" );

   // test_has_4
   add_test_to_suite( p_suite, test_has_4, "test_has_4" );

   // test_has_5
   add_test_to_suite( p_suite, test_has_5, "test_has_5" );

   // test_has_6
   add_test_to_suite( p_suite, test_has_6, "test_has_6" );

   // test_has_7
   add_test_to_suite( p_suite, test_has_7, "test_has_7" );

   // test_has_8
   add_test_to_suite( p_suite, test_has_8, "test_has_8" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

