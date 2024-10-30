/**
 @file BTree_test_key_at.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BTree_kv_key_at"
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
   test_key_at_1
*/

void test_key_at_1( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );

   ii_btree_kv_start( btree );

   CU_ASSERT( ii_btree_kv_key_at( btree ) == 1 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_key_at_2
*/

void test_key_at_2( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );

   ii_btree_kv_start( btree );
   CU_ASSERT( ii_btree_kv_key_at( btree ) == 1 );

   ii_btree_kv_forth( btree );
   CU_ASSERT( ii_btree_kv_key_at( btree ) == 2 );

   ii_btree_kv_forth( btree );
   CU_ASSERT( ii_btree_kv_key_at( btree ) == 3 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_key_at_3
*/

void test_key_at_3( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );

   ii_btree_kv_start( btree );
   CU_ASSERT( ii_btree_kv_key_at( btree ) == 1 );

   ii_btree_kv_forth( btree );
   CU_ASSERT( ii_btree_kv_key_at( btree ) == 2 );

   ii_btree_kv_forth( btree );
   CU_ASSERT( ii_btree_kv_key_at( btree ) == 3 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_key_at_4
*/

void test_key_at_4( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );

   ii_btree_kv_start( btree );
   CU_ASSERT( ii_btree_kv_key_at( btree ) == 1 );

   ii_btree_kv_forth( btree );
   CU_ASSERT( ii_btree_kv_key_at( btree ) == 2 );

   ii_btree_kv_forth( btree );
   CU_ASSERT( ii_btree_kv_key_at( btree ) == 3 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_key_at_5
*/

void test_key_at_5( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 10, 1 );

   ii_btree_kv_start( btree );
   CU_ASSERT( ii_btree_kv_key_at( btree ) == 1 );

   ii_btree_kv_forth( btree );
   CU_ASSERT( ii_btree_kv_key_at( btree ) == 2 );

   ii_btree_kv_forth( btree );
   CU_ASSERT( ii_btree_kv_key_at( btree ) == 4 );

   ii_btree_kv_forth( btree );
   CU_ASSERT( ii_btree_kv_key_at( btree ) == 6 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_key_at_6
*/

void test_key_at_6( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 30, 3 );

   ii_btree_kv_start( btree );
   CU_ASSERT( ii_btree_kv_key_at( btree ) == 2 );

   ii_btree_kv_forth( btree );
   CU_ASSERT( ii_btree_kv_key_at( btree ) == 3 );

   ii_btree_kv_forth( btree );
   CU_ASSERT( ii_btree_kv_key_at( btree ) == 4 );

   ii_btree_kv_forth( btree );
   CU_ASSERT( ii_btree_kv_key_at( btree ) == 6 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_key_at_7
*/

void test_key_at_7( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 50, 5 );

   ii_btree_kv_start( btree );
   CU_ASSERT( ii_btree_kv_key_at( btree ) == 2 );

   ii_btree_kv_forth( btree );
   CU_ASSERT( ii_btree_kv_key_at( btree ) == 4 );

   ii_btree_kv_forth( btree );
   CU_ASSERT( ii_btree_kv_key_at( btree ) == 5 );

   ii_btree_kv_forth( btree );
   CU_ASSERT( ii_btree_kv_key_at( btree ) == 6 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_key_at_8
*/

void test_key_at_8( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 70, 7 );

   ii_btree_kv_start( btree );
   CU_ASSERT( ii_btree_kv_key_at( btree ) == 2 );

   ii_btree_kv_forth( btree );
   CU_ASSERT( ii_btree_kv_key_at( btree ) == 4 );

   ii_btree_kv_forth( btree );
   CU_ASSERT( ii_btree_kv_key_at( btree ) == 6 );

   ii_btree_kv_forth( btree );
   CU_ASSERT( ii_btree_kv_key_at( btree ) == 7 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_key_at_9
*/

void test_key_at_9( void )
{
   ss_btree_kv_t *btree = NULL;
   string_t *s1v = NULL;
   string_t *s1k = NULL;
   string_t *s2v = NULL;
   string_t *s2k = NULL;
   string_t *s3v = NULL;
   string_t *s3k = NULL;
   string_t *s4v = NULL;
   string_t *s4k = NULL;
   
   s1k = string_make_from_cstring( "4" );
   s1v = string_make_from_cstring( "40" );
   
   s2k = string_make_from_cstring( "2" );
   s2v = string_make_from_cstring( "20" );
   
   s3k = string_make_from_cstring( "6" );
   s3v = string_make_from_cstring( "60" );
   
   s4k = string_make_from_cstring( "7" );
   s4v = string_make_from_cstring( "70" );
      
   btree = ss_btree_kv_make( 3 );

   ss_btree_kv_put( btree, s1v, s1k );
   ss_btree_kv_put( btree, s2v, s2k );
   ss_btree_kv_put( btree, s3v, s3k );
   ss_btree_kv_put( btree, s4v, s4k );

   ss_btree_kv_start( btree );
   CU_ASSERT( string_is_equal( ss_btree_kv_key_at( btree ), s2k ) );

   ss_btree_kv_forth( btree );
   CU_ASSERT( string_is_equal( ss_btree_kv_key_at( btree ), s1k ) );

   ss_btree_kv_forth( btree );
   CU_ASSERT( string_is_equal( ss_btree_kv_key_at( btree ), s3k ) );

   ss_btree_kv_forth( btree );
   CU_ASSERT( string_is_equal( ss_btree_kv_key_at( btree ), s4k ) );

   ss_btree_kv_deep_dispose( &btree );

   return;
}

int
add_test_key_at( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_key_at", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_key_at_1
   add_test_to_suite( p_suite, test_key_at_1, "test_key_at_1" );

   // test_key_at_2
   add_test_to_suite( p_suite, test_key_at_2, "test_key_at_2" );

   // test_key_at_3
   add_test_to_suite( p_suite, test_key_at_3, "test_key_at_3" );

   // test_key_at_4
   add_test_to_suite( p_suite, test_key_at_4, "test_key_at_4" );

   // test_key_at_5
   add_test_to_suite( p_suite, test_key_at_5, "test_key_at_5" );

   // test_key_at_6
   add_test_to_suite( p_suite, test_key_at_6, "test_key_at_6" );

   // test_key_at_7
   add_test_to_suite( p_suite, test_key_at_7, "test_key_at_7" );

   // test_key_at_8
   add_test_to_suite( p_suite, test_key_at_8, "test_key_at_8" );

   // test_key_at_9
   add_test_to_suite( p_suite, test_key_at_9, "test_key_at_9" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

