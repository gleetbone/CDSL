/**
 @file BTree_test_has.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BTree_kv_has"
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
   test_has_1
*/

void test_has_1( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 0 );
   CU_ASSERT( result == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_has_2
*/

void test_has_2( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 0 );
   CU_ASSERT( result == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_has_3
*/

void test_has_3( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 0 );
   CU_ASSERT( result == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_has_4
*/

void test_has_4( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 0 );
   CU_ASSERT( result == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_has_5
*/

void test_has_5( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 10, 1 );

   result = ii_btree_kv_has( btree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 0 );
   CU_ASSERT( result == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_has_6
*/

void test_has_6( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 30, 3 );

   result = ii_btree_kv_has( btree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 0 );
   CU_ASSERT( result == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_has_7
*/

void test_has_7( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 50, 5 );

   result = ii_btree_kv_has( btree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 5 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 0 );
   CU_ASSERT( result == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_has_8
*/

void test_has_8( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 70, 7 );

   result = ii_btree_kv_has( btree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 0 );
   CU_ASSERT( result == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_has_9
*/

void test_has_9( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 4 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 70, 7 );

   result = ii_btree_kv_has( btree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 0 );
   CU_ASSERT( result == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_has_10
*/

void test_has_10( void )
{
   ss_btree_kv_t *btree = NULL;
   int32_t result = 0;
   string_t *s1v = NULL;
   string_t *s1k = NULL;
   string_t *s2v = NULL;
   string_t *s2k = NULL;
   string_t *s3v = NULL;
   string_t *s3k = NULL;
   string_t *s4v = NULL;
   string_t *s4k = NULL;
   string_t *s0k = NULL;

   s1k = string_make_from_cstring( "4" );
   s1v = string_make_from_cstring( "40" );
   
   s2k = string_make_from_cstring( "2" );
   s2v = string_make_from_cstring( "20" );
   
   s3k = string_make_from_cstring( "6" );
   s3v = string_make_from_cstring( "60" );
   
   s4k = string_make_from_cstring( "7" );
   s4v = string_make_from_cstring( "70" );
   
   s0k = string_make_from_cstring( "0" );
      
   btree = ss_btree_kv_make( 4 );

   ss_btree_kv_put( btree, s1v, s1k );
   ss_btree_kv_put( btree, s2v, s2k );
   ss_btree_kv_put( btree, s3v, s3k );
   ss_btree_kv_put( btree, s4v, s4k );

   result = ss_btree_kv_has( btree, s1k );
   CU_ASSERT( result == 1 );

   result = ss_btree_kv_has( btree, s2k );
   CU_ASSERT( result == 1 );

   result = ss_btree_kv_has( btree, s3k );
   CU_ASSERT( result == 1 );

   result = ss_btree_kv_has( btree, s4k );
   CU_ASSERT( result == 1 );

   result = ss_btree_kv_has( btree, s0k );
   CU_ASSERT( result == 0 );

   ss_btree_kv_deep_dispose( &btree );
   string_dispose( &s0k );

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

   // test_has_9
   add_test_to_suite( p_suite, test_has_9, "test_has_9" );

   // test_has_10
   add_test_to_suite( p_suite, test_has_10, "test_has_10" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

