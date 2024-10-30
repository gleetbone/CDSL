/**
 @file BTree_kv_test_index.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BTree_kv_index"
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
   test_index_1
*/

void test_index_1( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 240, 24 );
   ii_btree_kv_put( btree, 130, 13 );

   CU_ASSERT( ii_btree_kv_index( btree ) == -1 );

   ii_btree_kv_start( btree );

   CU_ASSERT( ii_btree_kv_index( btree ) == 0 );

   ii_btree_kv_forth( btree );

   CU_ASSERT( ii_btree_kv_index( btree ) == 1 );

   ii_btree_kv_forth( btree );

   CU_ASSERT( ii_btree_kv_index( btree ) == -1 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_index_2
*/

void test_index_2( void )
{
   ss_btree_kv_t *btree = NULL;
   string_t *s1v = NULL;
   string_t *s1k = NULL;
   string_t *s2v = NULL;
   string_t *s2k = NULL;

   s1k = string_make_from_cstring( "24" );
   s1v = string_make_from_cstring( "240" );
   
   s2k = string_make_from_cstring( "13" );
   s2v = string_make_from_cstring( "130" );
   
   btree = ss_btree_kv_make( 3 );

   ss_btree_kv_put( btree, s1v, s1k );
   ss_btree_kv_put( btree, s2v, s2k );

   CU_ASSERT( ss_btree_kv_index( btree ) == -1 );

   ss_btree_kv_start( btree );

   CU_ASSERT( ss_btree_kv_index( btree ) == 0 );

   ss_btree_kv_forth( btree );

   CU_ASSERT( ss_btree_kv_index( btree ) == 1 );

   ss_btree_kv_forth( btree );

   CU_ASSERT( ss_btree_kv_index( btree ) == -1 );

   ss_btree_kv_deep_dispose( &btree );

   return;
}

int
add_test_index( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_index", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_index_1
   add_test_to_suite( p_suite, test_index_1, "test_index_1" );

   // test_index_2
   add_test_to_suite( p_suite, test_index_2, "test_index_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

