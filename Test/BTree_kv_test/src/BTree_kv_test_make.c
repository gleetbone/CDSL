/**
 @file BTree_test_make.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BTree_kv_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)

 @section Description

 Unit tests for BTree_kv_t

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_BTree_kv.h"
#include "ss_BTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_make_1
*/

void test_make_1( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   CU_ASSERT( btree != NULL );
   CU_ASSERT( ii_btree_kv_count( btree ) == 0 );
   CU_ASSERT( ii_btree_kv_is_empty( btree ) == 1 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_make_1a
*/

void test_make_1a( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );
   ii_btree_kv_put( btree, 130, 13 );

   CU_ASSERT( btree != NULL );
   CU_ASSERT( ii_btree_kv_count( btree ) == 1 );
   CU_ASSERT( ii_btree_kv_has( btree, 13 ) == 1 );

   ii_btree_kv_deep_dispose( &btree );

   return;
}

/**
   test_make_2
*/

void test_make_2( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t key_array[3] = { 13, 0, 0 };
   int32_t value_array[3] = { 130, 0, 0 };

   btree = ii_btree_kv_make_from_array( key_array, value_array, 1, 5 );

   CU_ASSERT( btree != NULL );
   CU_ASSERT( ii_btree_kv_count( btree ) == 1 );
   CU_ASSERT( ii_btree_kv_has( btree, 13 ) == 1 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_make_3
*/

void test_make_3( void )
{
   ss_btree_kv_t *btree = NULL;
   string_t *s1v = NULL;
   string_t *s1k = NULL;
   
   s1k = string_make_from_cstring( "13" );
   s1v = string_make_from_cstring( "130" );
   
   string_t * key_array[3] = { s1k, NULL, NULL };
   string_t * value_array[3] = { s1v, NULL, NULL };

   btree = ss_btree_kv_make_from_array( key_array, value_array, 1, 5 );

   CU_ASSERT( btree != NULL );
   CU_ASSERT( ss_btree_kv_count( btree ) == 1 );
   CU_ASSERT( ss_btree_kv_has( btree, s1k ) == 1 );

   ss_btree_kv_deep_dispose( &btree );

   return;
}

int
add_test_make( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_1
   add_test_to_suite( p_suite, test_make_1, "test_make_1" );

   // test_make_1a
   add_test_to_suite( p_suite, test_make_1a, "test_make_1a" );

   // test_make_2
   add_test_to_suite( p_suite, test_make_2, "test_make_2" );

   // test_make_3
   add_test_to_suite( p_suite, test_make_3, "test_make_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

