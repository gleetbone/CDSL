/**
 @file Heap_test_as_array.c
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
   test_as_array_1
*/

void test_as_array_1( void )
{
   i_heap_t *heap = NULL;
   int32_t *array = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 1 );

   array = i_heap_as_array( heap );

   CU_ASSERT( array[0] == 1 );

   free( array );
   i_heap_dispose( &heap );

   return;
}

/**
   test_as_array_2
*/

void test_as_array_2( void )
{
   i_heap_t *heap = NULL;
   int32_t *array = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );

   array = i_heap_as_array( heap );

   CU_ASSERT( array[0] == 1 );
   CU_ASSERT( array[1] == 2 );
   CU_ASSERT( array[2] == 3 );

   free( array );
   i_heap_dispose( &heap );

   return;
}

/**
   test_as_array_3
*/

void test_as_array_3( void )
{
   i_heap_t *heap = NULL;
   int32_t *array = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 3 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );

   array = i_heap_as_array( heap );

   CU_ASSERT( array[0] == 1 );
   CU_ASSERT( array[1] == 3 );
   CU_ASSERT( array[2] == 2 );

   free( array );
   i_heap_dispose( &heap );

   return;
}

/**
   test_as_array_4
*/

void test_as_array_4( void )
{
   i_heap_t *heap = NULL;
   int32_t *array = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 1 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 3 );

   array = i_heap_as_array( heap );

   CU_ASSERT( array[0] == 1 );
   CU_ASSERT( array[1] == 2 );
   CU_ASSERT( array[2] == 3 );

   free( array );
   i_heap_dispose( &heap );

   return;
}

/**
   test_as_array_5
*/

void test_as_array_5( void )
{
   i_heap_t *heap = NULL;
   int32_t *array = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 1 );

   array = i_heap_as_array( heap );

   CU_ASSERT( array[0] == 1 );
   CU_ASSERT( array[1] == 2 );
   CU_ASSERT( array[2] == 6 );
   CU_ASSERT( array[3] == 4 );

   free( array );
   i_heap_dispose( &heap );

   return;
}

/**
   test_as_array_6
*/

void test_as_array_6( void )
{
   i_heap_t *heap = NULL;
   int32_t *array = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 3 );

   array = i_heap_as_array( heap );

   CU_ASSERT( array[0] == 2 );
   CU_ASSERT( array[1] == 3 );
   CU_ASSERT( array[2] == 6 );
   CU_ASSERT( array[3] == 4 );

   free( array );
   i_heap_dispose( &heap );

   return;
}

/**
   test_as_array_7
*/

void test_as_array_7( void )
{
   i_heap_t *heap = NULL;
   int32_t *array = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 5 );

   array = i_heap_as_array( heap );

   CU_ASSERT( array[0] == 2 );
   CU_ASSERT( array[1] == 4 );
   CU_ASSERT( array[2] == 6 );
   CU_ASSERT( array[3] == 5 );

   free( array );
   i_heap_dispose( &heap );

   return;
}

/**
   test_as_array_8
*/

void test_as_array_8( void )
{
   i_heap_t *heap = NULL;
   int32_t *array = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 7 );

   array = i_heap_as_array( heap );

   CU_ASSERT( array[0] == 2 );
   CU_ASSERT( array[1] == 4 );
   CU_ASSERT( array[2] == 6 );
   CU_ASSERT( array[3] == 7 );

   free( array );
   i_heap_dispose( &heap );

   return;
}

int
add_test_as_array( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_as_array", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_as_array_1
   add_test_to_suite( p_suite, test_as_array_1, "test_as_array_1" );

   // test_as_array_2
   add_test_to_suite( p_suite, test_as_array_2, "test_as_array_2" );

   // test_as_array_3
   add_test_to_suite( p_suite, test_as_array_3, "test_as_array_3" );

   // test_as_array_4
   add_test_to_suite( p_suite, test_as_array_4, "test_as_array_4" );

   // test_as_array_5
   add_test_to_suite( p_suite, test_as_array_5, "test_as_array_5" );

   // test_as_array_6
   add_test_to_suite( p_suite, test_as_array_6, "test_as_array_6" );

   // test_as_array_7
   add_test_to_suite( p_suite, test_as_array_7, "test_as_array_7" );

   // test_as_array_8
   add_test_to_suite( p_suite, test_as_array_8, "test_as_array_8" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

