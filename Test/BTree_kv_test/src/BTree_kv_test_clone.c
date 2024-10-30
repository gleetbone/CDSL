/**
 @file BTree_test_clone.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BTree_kv_clone"
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
   test_clone_1
*/

void test_clone_1( void )
{
   ii_btree_kv_t *btree = NULL;
   ii_btree_kv_t *btree1 = NULL;

   btree = ii_btree_kv_make( 3 );
   btree1 = ii_btree_kv_clone( btree );
   
   CU_ASSERT( btree != NULL );
   CU_ASSERT( btree1 != NULL );

   ii_btree_kv_dispose( &btree );
   ii_btree_kv_dispose( &btree1 );

   return;
}

/**
   test_clone_2
*/

void test_clone_2( void )
{
   ii_btree_kv_t *btree = NULL;
   ii_btree_kv_t *btree1 = NULL;

   btree = ii_btree_kv_make( 3 );
   ii_btree_kv_put( btree, 130, 13 );

   CU_ASSERT( btree != NULL );
   CU_ASSERT( ii_btree_kv_count( btree ) == 1 );
   CU_ASSERT( ii_btree_kv_has( btree, 13 ) == 1 );

   btree1 = ii_btree_kv_clone( btree );

   CU_ASSERT( btree1 != NULL );
   CU_ASSERT( ii_btree_kv_count( btree1 ) == 1 );
   CU_ASSERT( ii_btree_kv_has( btree1, 13 ) == 1 );

   ii_btree_kv_dispose( &btree );
   ii_btree_kv_dispose( &btree1 );

   return;
}

/**
   test_clone_3
*/

void test_clone_3( void )
{
   ii_btree_kv_t *btree = NULL;
   ii_btree_kv_t *btree1 = NULL;

   btree = ii_btree_kv_make( 3 );
   btree1 = ii_btree_kv_deep_clone( btree );
   
   CU_ASSERT( btree != NULL );
   CU_ASSERT( btree1 != NULL );

   ii_btree_kv_dispose( &btree );
   ii_btree_kv_dispose( &btree1 );

   return;
}

/**
   test_clone_4
*/

void test_clone_4( void )
{
   ii_btree_kv_t *btree = NULL;
   ii_btree_kv_t *btree1 = NULL;

   btree = ii_btree_kv_make( 3 );
   ii_btree_kv_put( btree, 130, 13 );

   CU_ASSERT( btree != NULL );
   CU_ASSERT( ii_btree_kv_count( btree ) == 1 );
   CU_ASSERT( ii_btree_kv_has( btree, 13 ) == 1 );

   btree1 = ii_btree_kv_deep_clone( btree );

   CU_ASSERT( btree1 != NULL );
   CU_ASSERT( ii_btree_kv_count( btree1 ) == 1 );
   CU_ASSERT( ii_btree_kv_has( btree1, 13 ) == 1 );

   ii_btree_kv_dispose( &btree );
   ii_btree_kv_dispose( &btree1 );

   return;
}

/**
   test_clone_5
*/

void test_clone_5( void )
{
   ss_btree_kv_t *btree = NULL;
   ss_btree_kv_t *btree1 = NULL;
   string_t *s1v = NULL;
   string_t *s1k = NULL;

   s1k = string_make_from_cstring( "13" );
   s1v = string_make_from_cstring( "130" );
   
   btree = ss_btree_kv_make( 3 );
   ss_btree_kv_put( btree, s1v, s1k );

   CU_ASSERT( btree != NULL );
   CU_ASSERT( ss_btree_kv_count( btree ) == 1 );
   CU_ASSERT( ss_btree_kv_has( btree, s1k ) == 1 );

   btree1 = ss_btree_kv_clone( btree );

   CU_ASSERT( btree1 != NULL );
   CU_ASSERT( ss_btree_kv_count( btree1 ) == 1 );
   CU_ASSERT( ss_btree_kv_has( btree1, s1k) == 1 );

   ss_btree_kv_deep_dispose( &btree );
   ss_btree_kv_dispose( &btree1 );

   return;
}

/**
   test_clone_6
*/

void test_clone_6( void )
{
   ss_btree_kv_t *btree = NULL;
   ss_btree_kv_t *btree1 = NULL;
   string_t *s1v = NULL;
   string_t *s1k = NULL;

   s1k = string_make_from_cstring( "13" );
   s1v = string_make_from_cstring( "130" );
   
   btree = ss_btree_kv_make( 3 );
   ss_btree_kv_put( btree, s1v, s1k );

   CU_ASSERT( btree != NULL );
   CU_ASSERT( ss_btree_kv_count( btree ) == 1 );
   CU_ASSERT( ss_btree_kv_has( btree, s1k ) == 1 );

   btree1 = ss_btree_kv_deep_clone( btree );

   CU_ASSERT( btree1 != NULL );
   CU_ASSERT( ss_btree_kv_count( btree1 ) == 1 );
   CU_ASSERT( ss_btree_kv_has( btree1, s1k) == 1 );

   ss_btree_kv_deep_dispose( &btree );
   ss_btree_kv_deep_dispose( &btree1 );

   return;
}

int
add_test_clone( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_clone", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_clone_1
   add_test_to_suite( p_suite, test_clone_1, "test_clone_1" );

   // test_clone_2
   add_test_to_suite( p_suite, test_clone_2, "test_clone_2" );

   // test_clone_3
   add_test_to_suite( p_suite, test_clone_3, "test_clone_3" );

   // test_clone_4
   add_test_to_suite( p_suite, test_clone_4, "test_clone_4" );

   // test_clone_5
   add_test_to_suite( p_suite, test_clone_5, "test_clone_5" );

   // test_clone_6
   add_test_to_suite( p_suite, test_clone_6, "test_clone_6" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

