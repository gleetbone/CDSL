/**
 @file BTree_test_count.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BTree_kv_count"
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
   test_count_1
*/

void test_count_1( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   result = ii_btree_kv_count( btree );
   CU_ASSERT( result == 0 );
   
   ii_btree_kv_put( btree, 10, 1 );

   result = ii_btree_kv_count( btree );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 0 );
   CU_ASSERT( result == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_count_2
*/

void test_count_2( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   result = ii_btree_kv_count( btree );
   CU_ASSERT( result == 0 );
   
   ii_btree_kv_put( btree, 20, 2 );
   
   result = ii_btree_kv_count( btree );
   CU_ASSERT( result == 1 );
   
   ii_btree_kv_put( btree, 10, 1 );
   
   result = ii_btree_kv_count( btree );
   CU_ASSERT( result == 2 );
   
   ii_btree_kv_put( btree, 30, 3 );

   result = ii_btree_kv_count( btree );
   CU_ASSERT( result == 3 );
   
   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_count_3
*/

void test_count_3( void )
{
   ss_btree_kv_t *btree = NULL;
   string_t *s1v = NULL;
   string_t *s1k = NULL;
   string_t *s2v = NULL;
   string_t *s2k = NULL;
   string_t *s3v = NULL;
   string_t *s3k = NULL;
   int32_t result = 0;

   s1k = string_make_from_cstring( "2" );
   s1v = string_make_from_cstring( "20" );
   
   s2k = string_make_from_cstring( "1" );
   s2v = string_make_from_cstring( "10" );
   
   s3k = string_make_from_cstring( "3" );
   s3v = string_make_from_cstring( "30" );
   
   btree = ss_btree_kv_make( 3 );

   result = ss_btree_kv_count( btree );
   CU_ASSERT( result == 0 );
   
   ss_btree_kv_put( btree, s1v, s1k );
   
   result = ss_btree_kv_count( btree );
   CU_ASSERT( result == 1 );
   
   ss_btree_kv_put( btree, s2v, s2k );
   
   result = ss_btree_kv_count( btree );
   CU_ASSERT( result == 2 );
   
   ss_btree_kv_put( btree, s3v, s3k );

   result = ss_btree_kv_count( btree );
   CU_ASSERT( result == 3 );
   
   ss_btree_kv_deep_dispose( &btree );

   return;
}

int
add_test_count( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_count", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_count_1
   add_test_to_suite( p_suite, test_count_1, "test_count_1" );

   // test_count_2
   add_test_to_suite( p_suite, test_count_2, "test_count_2" );

   // test_count_3
   add_test_to_suite( p_suite, test_count_3, "test_count_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

