/**
 @file BTree_test_is_equal.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BTree_kv_is_equal"
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
   test_is_equal_1
*/

void test_is_equal_1( void )
{
   ii_btree_kv_t *btree = NULL;
   ii_btree_kv_t *btree1 = NULL;

   btree = ii_btree_kv_make( 3 );
   btree1 = ii_btree_kv_make( 3 );
   ii_btree_kv_copy( btree1, btree );
   
   CU_ASSERT( ii_btree_kv_is_equal( btree, btree1 ) == 1 );

   ii_btree_kv_dispose( &btree );
   ii_btree_kv_dispose( &btree1 );

   return;
}

/**
   test_is_equal_2
*/

void test_is_equal_2( void )
{
   ii_btree_kv_t *btree = NULL;
   ii_btree_kv_t *btree1 = NULL;

   btree = ii_btree_kv_make( 3 );
   ii_btree_kv_put( btree, 130, 13 );

   btree1 = ii_btree_kv_make( 3 );
   
   ii_btree_kv_copy( btree1, btree );

   CU_ASSERT( ii_btree_kv_is_equal( btree, btree1 ) == 1 );

   ii_btree_kv_dispose( &btree );
   ii_btree_kv_dispose( &btree1 );

   return;
}

/**
   test_is_equal_2a
*/

void test_is_equal_2a( void )
{
   ii_btree_kv_t *btree = NULL;
   ii_btree_kv_t *btree1 = NULL;

   btree = ii_btree_kv_make( 3 );
   ii_btree_kv_put( btree, 130, 13 );

   btree1 = ii_btree_kv_make( 3 );
   
   CU_ASSERT( ii_btree_kv_is_equal( btree, btree1 ) == 0 );

   ii_btree_kv_dispose( &btree );
   ii_btree_kv_dispose( &btree1 );

   return;
}

/**
   test_is_equal_2b
*/

void test_is_equal_2b( void )
{
   ii_btree_kv_t *btree = NULL;
   ii_btree_kv_t *btree1 = NULL;

   btree = ii_btree_kv_make( 3 );
   ii_btree_kv_put( btree, 130, 13 );

   btree1 = ii_btree_kv_make( 3 );
   ii_btree_kv_put( btree1, 30, 3 );
   
   CU_ASSERT( ii_btree_kv_is_equal( btree, btree1 ) == 0 );

   ii_btree_kv_dispose( &btree );
   ii_btree_kv_dispose( &btree1 );

   return;
}

/**
   test_is_equal_3
*/

void test_is_equal_3( void )
{
   ii_btree_kv_t *btree = NULL;
   ii_btree_kv_t *btree1 = NULL;

   btree = ii_btree_kv_make( 3 );
   btree1 = ii_btree_kv_make( 3 );
   ii_btree_kv_deep_copy( btree1, btree );
   
   CU_ASSERT( ii_btree_kv_is_deep_equal( btree, btree1 ) == 1 );

   ii_btree_kv_dispose( &btree );
   ii_btree_kv_dispose( &btree1 );

   return;
}

/**
   test_is_equal_4
*/

void test_is_equal_4( void )
{
   ii_btree_kv_t *btree = NULL;
   ii_btree_kv_t *btree1 = NULL;

   btree = ii_btree_kv_make( 3 );
   ii_btree_kv_put( btree, 130, 13 );

   btree1 = ii_btree_kv_make( 3 );
   
   ii_btree_kv_deep_copy( btree1, btree );

   CU_ASSERT( ii_btree_kv_is_deep_equal( btree, btree1 ) == 1 );

   ii_btree_kv_dispose( &btree );
   ii_btree_kv_dispose( &btree1 );

   return;
}

/**
   test_is_equal_4a
*/

void test_is_equal_4a( void )
{
   ii_btree_kv_t *btree = NULL;
   ii_btree_kv_t *btree1 = NULL;

   btree = ii_btree_kv_make( 3 );
   ii_btree_kv_put( btree, 130, 13 );

   btree1 = ii_btree_kv_make( 3 );
   
   CU_ASSERT( ii_btree_kv_is_deep_equal( btree, btree1 ) == 0 );

   ii_btree_kv_dispose( &btree );
   ii_btree_kv_dispose( &btree1 );

   return;
}

/**
   test_is_equal_4b
*/

void test_is_equal_4b( void )
{
   ii_btree_kv_t *btree = NULL;
   ii_btree_kv_t *btree1 = NULL;

   btree = ii_btree_kv_make( 3 );
   ii_btree_kv_put( btree, 130, 13 );

   btree1 = ii_btree_kv_make( 3 );
   ii_btree_kv_put( btree1, 30, 3 );
   
   CU_ASSERT( ii_btree_kv_is_deep_equal( btree, btree1 ) == 0 );

   ii_btree_kv_dispose( &btree );
   ii_btree_kv_dispose( &btree1 );

   return;
}

/**
   test_is_equal_5
*/

void test_is_equal_5( void )
{
   ss_btree_kv_t *btree = NULL;
   ss_btree_kv_t *btree1 = NULL;
   string_t *s1v = NULL;
   string_t *s1k = NULL;

   s1k = string_make_from_cstring( "13" );
   s1v = string_make_from_cstring( "130" );
   
   btree = ss_btree_kv_make( 3 );
   ss_btree_kv_put( btree, s1v, s1k );

   btree1 = ss_btree_kv_make( 3 );
   
   ss_btree_kv_copy( btree1, btree );

   CU_ASSERT( ss_btree_kv_is_equal( btree, btree1 ) == 1 );

   ss_btree_kv_deep_dispose( &btree );
   ss_btree_kv_dispose( &btree1 );

   return;
}

/**
   test_is_equal_5a
*/

void test_is_equal_5a( void )
{
   ss_btree_kv_t *btree = NULL;
   ss_btree_kv_t *btree1 = NULL;
   string_t *s1v = NULL;
   string_t *s1k = NULL;

   s1k = string_make_from_cstring( "13" );
   s1v = string_make_from_cstring( "130" );
   
   btree = ss_btree_kv_make( 3 );
   ss_btree_kv_put( btree, s1v, s1k );

   btree1 = ss_btree_kv_make( 3 );
   
   CU_ASSERT( ss_btree_kv_is_equal( btree, btree1 ) == 0 );

   ss_btree_kv_deep_dispose( &btree );
   ss_btree_kv_deep_dispose( &btree1 );

   return;
}

/**
   test_is_equal_5b
*/

void test_is_equal_5b( void )
{
   ss_btree_kv_t *btree = NULL;
   ss_btree_kv_t *btree1 = NULL;
   string_t *s1v = NULL;
   string_t *s1k = NULL;
   string_t *s2v = NULL;
   string_t *s2k = NULL;

   s1k = string_make_from_cstring( "13" );
   s1v = string_make_from_cstring( "130" );
   
   s2k = string_make_from_cstring( "3" );
   s2v = string_make_from_cstring( "30" );
   
   btree = ss_btree_kv_make( 3 );
   ss_btree_kv_put( btree, s1v, s1k );

   btree1 = ss_btree_kv_make( 3 );
   ss_btree_kv_put( btree1, s2v, s2k );
   
   CU_ASSERT( ss_btree_kv_is_equal( btree, btree1 ) == 0 );

   ss_btree_kv_deep_dispose( &btree );
   ss_btree_kv_deep_dispose( &btree1 );

   return;
}

/**
   test_is_equal_6
*/

void test_is_equal_6( void )
{
   ss_btree_kv_t *btree = NULL;
   ss_btree_kv_t *btree1 = NULL;
   string_t *s1v = NULL;
   string_t *s1k = NULL;

   s1k = string_make_from_cstring( "13" );
   s1v = string_make_from_cstring( "130" );
   
   btree = ss_btree_kv_make( 3 );
   ss_btree_kv_put( btree, s1v, s1k );

   btree1 = ss_btree_kv_make( 3 );
   
   ss_btree_kv_deep_copy( btree1, btree );

   CU_ASSERT( ss_btree_kv_is_deep_equal( btree, btree1 ) == 1 );

   ss_btree_kv_deep_dispose( &btree );
   ss_btree_kv_deep_dispose( &btree1 );

   return;
}

/**
   test_is_equal_6a
*/

void test_is_equal_6a( void )
{
   ss_btree_kv_t *btree = NULL;
   ss_btree_kv_t *btree1 = NULL;
   string_t *s1v = NULL;
   string_t *s1k = NULL;

   s1k = string_make_from_cstring( "13" );
   s1v = string_make_from_cstring( "130" );
   
   btree = ss_btree_kv_make( 3 );
   ss_btree_kv_put( btree, s1v, s1k );

   btree1 = ss_btree_kv_make( 3 );
   
   CU_ASSERT( ss_btree_kv_is_deep_equal( btree, btree1 ) == 0 );

   ss_btree_kv_deep_dispose( &btree );
   ss_btree_kv_deep_dispose( &btree1 );

   return;
}

/**
   test_is_equal_6b
*/

void test_is_equal_6b( void )
{
   ss_btree_kv_t *btree = NULL;
   ss_btree_kv_t *btree1 = NULL;
   string_t *s1v = NULL;
   string_t *s1k = NULL;
   string_t *s2v = NULL;
   string_t *s2k = NULL;

   s1k = string_make_from_cstring( "13" );
   s1v = string_make_from_cstring( "130" );
   
   s2k = string_make_from_cstring( "3" );
   s2v = string_make_from_cstring( "30" );
   
   btree = ss_btree_kv_make( 3 );
   ss_btree_kv_put( btree, s1v, s1k );

   btree1 = ss_btree_kv_make( 3 );
   ss_btree_kv_put( btree1, s2v, s2k );
   
   CU_ASSERT( ss_btree_kv_is_deep_equal( btree, btree1 ) == 0 );

   ss_btree_kv_deep_dispose( &btree );
   ss_btree_kv_deep_dispose( &btree1 );

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

   // test_is_equal_2
   add_test_to_suite( p_suite, test_is_equal_2, "test_is_equal_2" );

   // test_is_equal_2a
   add_test_to_suite( p_suite, test_is_equal_2a, "test_is_equal_2a" );

   // test_is_equal_2b
   add_test_to_suite( p_suite, test_is_equal_2b, "test_is_equal_2b" );

   // test_is_equal_3
   add_test_to_suite( p_suite, test_is_equal_3, "test_is_equal_3" );

   // test_is_equal_4
   add_test_to_suite( p_suite, test_is_equal_4, "test_is_equal_4" );

   // test_is_equal_4a
   add_test_to_suite( p_suite, test_is_equal_4a, "test_is_equal_4a" );

   // test_is_equal_4b
   add_test_to_suite( p_suite, test_is_equal_4b, "test_is_equal_4b" );

   // test_is_equal_5
   add_test_to_suite( p_suite, test_is_equal_5, "test_is_equal_5" );

   // test_is_equal_5a
   add_test_to_suite( p_suite, test_is_equal_5a, "test_is_equal_5a" );

   // test_is_equal_5b
   add_test_to_suite( p_suite, test_is_equal_5b, "test_is_equal_5b" );

   // test_is_equal_6
   add_test_to_suite( p_suite, test_is_equal_6, "test_is_equal_6" );

   // test_is_equal_6a
   add_test_to_suite( p_suite, test_is_equal_6a, "test_is_equal_6a" );

   // test_is_equal_6b
   add_test_to_suite( p_suite, test_is_equal_6b, "test_is_equal_6b" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

