/**
 @file Heap_kv_test_is_deep_equal.c
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
#include "ss_Heap_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_is_deep_equal_1
*/

void test_is_deep_equal_1( void )
{
   ii_heap_kv_t *heap = NULL;
   ii_heap_kv_t *heap1 = NULL;

   heap = ii_heap_kv_make_n( 20 );
   
   ii_heap_kv_put( heap, 13, 37 );

   CU_ASSERT( ii_heap_kv_is_deep_equal( heap, heap ) == 1 );
   
   heap1 = ii_heap_kv_make();
   
   CU_ASSERT( ii_heap_kv_is_deep_equal( heap1, heap ) == 0 );
   
   ii_heap_kv_put( heap1, 23, 47 );
   
   CU_ASSERT( ii_heap_kv_is_deep_equal( heap1, heap ) == 0 );

   ii_heap_kv_dispose( &heap );
   ii_heap_kv_dispose( &heap1 );

   return;
}

/**
   test_is_deep_equal_1a
*/

void test_is_deep_equal_1a( void )
{
   ii_heap_kv_t *heap = NULL;
   ii_heap_kv_t *heap1 = NULL;

   heap = ii_heap_kv_make_n( 20 );
   
   ii_heap_kv_put( heap, 13, 37 );

   CU_ASSERT( ii_heap_kv_is_deep_equal( heap, heap ) == 1 );
   
   heap1 = ii_heap_kv_make();
   
   CU_ASSERT( ii_heap_kv_is_deep_equal( heap1, heap ) == 0 );
   
   ii_heap_kv_put( heap1, 23, 37 );
   
   CU_ASSERT( ii_heap_kv_is_deep_equal( heap1, heap ) == 0 );

   ii_heap_kv_dispose( &heap );
   ii_heap_kv_dispose( &heap1 );

   return;
}

/**
   test_is_deep_equal_2
*/

void test_is_deep_equal_2( void )
{
   ss_heap_kv_t *heap = NULL;
   ss_heap_kv_t *heap1 = NULL;
   string_t *s1 = NULL;
   string_t *s1k = NULL;

   s1 = string_make_from_cstring( "13" );
   s1k = string_make_from_cstring( "1" );
   
   heap = ss_heap_kv_make_n( 20 );
   
   ss_heap_kv_put( heap, s1, s1k );

   CU_ASSERT( ss_heap_kv_is_equal( heap, heap ) == 1 );
   
   heap1 = ss_heap_kv_make();
   
   CU_ASSERT( ss_heap_kv_is_equal( heap1, heap ) == 0 );
   
   ss_heap_kv_copy( heap1, heap );

   CU_ASSERT( ss_heap_kv_is_equal( heap1, heap ) == 1 );

   ss_heap_kv_deep_dispose( &heap );
   ss_heap_kv_deep_dispose( &heap1 );
  
   return;
}

int
add_test_is_deep_equal( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_deep_equal", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_deep_equal_1
   add_test_to_suite( p_suite, test_is_deep_equal_1, "test_is_deep_equal_1" );

   // test_is_deep_equal_1a
   add_test_to_suite( p_suite, test_is_deep_equal_1a, "test_is_deep_equal_1a" );

   // test_is_deep_equal_2
//   add_test_to_suite( p_suite, test_is_deep_equal_2, "test_is_deep_equal_2" );
   
   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

