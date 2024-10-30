/**
 @file Heap_test_is_equal.c
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
   test_is_equal_1
*/

void test_is_equal_1( void )
{
   i_heap_t *heap = NULL;
   i_heap_t *heap1 = NULL;

   heap = i_heap_make_n( 20 );
   
   i_heap_put( heap, 13 );

   CU_ASSERT( i_heap_is_equal( heap, heap ) == 1 );
   
   heap1 = i_heap_make();
   
   CU_ASSERT( i_heap_is_equal( heap1, heap ) == 0 );
   
   i_heap_put( heap1, 23 );
   
   CU_ASSERT( i_heap_is_equal( heap1, heap ) == 0 );

   i_heap_dispose( &heap );
   i_heap_dispose( &heap1 );

   return;
}

/**
   test_is_equal_2
*/

void test_is_equal_2( void )
{
   s_heap_t *heap = NULL;
   s_heap_t *heap1 = NULL;
   string_t *s1 = NULL;

   s1 = string_make_from_cstring( "13" );
   
   heap = s_heap_make_n( 20 );
   
   s_heap_put( heap, s1 );

   CU_ASSERT( s_heap_is_equal( heap, heap ) == 1 );
   
   heap1 = s_heap_make();
   
   CU_ASSERT( s_heap_is_equal( heap1, heap ) == 0 );
   
   s_heap_copy( heap1, heap );

   CU_ASSERT( s_heap_is_equal( heap1, heap ) == 1 );

   s_heap_dispose( &heap );
   s_heap_dispose( &heap1 );

   string_dispose( &s1 );
  
   return;
}

int
add_test_is_equal( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_equal", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_equal_1
   add_test_to_suite( p_suite, test_is_equal_1, "test_is_equal_1" );
   return CUE_SUCCESS;

   // test_is_equal_2
   add_test_to_suite( p_suite, test_is_equal_2, "test_is_equal_2" );
   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

