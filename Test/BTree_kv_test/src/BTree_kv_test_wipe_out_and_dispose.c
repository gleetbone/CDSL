/**
 @file BTree_test_wipe_out_and_dispose.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BTree_kv_wipe_out_and_dispose"
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
   test_wipe_out_and_dispose_1
*/

void test_wipe_out_and_dispose_1( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );

   ii_btree_kv_wipe_out_and_dispose( btree );

   CU_ASSERT( ii_btree_kv_count( btree ) == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_wipe_out_and_dispose_2
*/

void test_wipe_out_and_dispose_2( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );

   ii_btree_kv_wipe_out_and_dispose( btree );

   CU_ASSERT( ii_btree_kv_count( btree ) == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_wipe_out_and_dispose_2a
*/

void test_wipe_out_and_dispose_2a( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );

   ii_btree_kv_wipe_out_and_dispose( btree );

   CU_ASSERT( ii_btree_kv_count( btree ) == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_wipe_out_and_dispose_2b
*/

void test_wipe_out_and_dispose_2b( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );

   ii_btree_kv_wipe_out_and_dispose( btree );

   CU_ASSERT( ii_btree_kv_count( btree ) == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_wipe_out_and_dispose_3
*/

void test_wipe_out_and_dispose_3( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );

   ii_btree_kv_wipe_out_and_dispose( btree );

   CU_ASSERT( ii_btree_kv_count( btree ) == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_wipe_out_and_dispose_3a
*/

void test_wipe_out_and_dispose_3a( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );

   ii_btree_kv_wipe_out_and_dispose( btree );

   CU_ASSERT( ii_btree_kv_count( btree ) == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_wipe_out_and_dispose_3b
*/

void test_wipe_out_and_dispose_3b( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );

   ii_btree_kv_wipe_out_and_dispose( btree );

   CU_ASSERT( ii_btree_kv_count( btree ) == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_wipe_out_and_dispose_4
*/

void test_wipe_out_and_dispose_4( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );

   ii_btree_kv_wipe_out_and_dispose( btree );

   CU_ASSERT( ii_btree_kv_count( btree ) == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_wipe_out_and_dispose_4a
*/

void test_wipe_out_and_dispose_4a( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );

   ii_btree_kv_wipe_out_and_dispose( btree );

   CU_ASSERT( ii_btree_kv_count( btree ) == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_wipe_out_and_dispose_4b
*/

void test_wipe_out_and_dispose_4b( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );

   ii_btree_kv_wipe_out_and_dispose( btree );

   CU_ASSERT( ii_btree_kv_count( btree ) == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_wipe_out_and_dispose_5

            4
         2      6
       1   3  5   7
*/

void test_wipe_out_and_dispose_5( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 70, 7 );

   ii_btree_kv_wipe_out_and_dispose( btree );

   CU_ASSERT( ii_btree_kv_count( btree ) == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_wipe_out_and_dispose_5a

            4
         2      6
       1   3  5   7
*/

void test_wipe_out_and_dispose_5a( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 70, 7 );

   ii_btree_kv_wipe_out_and_dispose( btree );

   CU_ASSERT( ii_btree_kv_count( btree ) == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_wipe_out_and_dispose_5b

            4
         2      6
       1   3  5   7
*/

void test_wipe_out_and_dispose_5b( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 70, 7 );

   ii_btree_kv_wipe_out_and_dispose( btree );

   CU_ASSERT( ii_btree_kv_count( btree ) == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_wipe_out_and_dispose_5c

            4
         2      6
       1   3  5   7
*/

void test_wipe_out_and_dispose_5c( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 70, 7 );

   ii_btree_kv_wipe_out_and_dispose( btree );

   CU_ASSERT( ii_btree_kv_count( btree ) == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_wipe_out_and_dispose_5d

            4
         2      6
       1   3  5   7
*/

void test_wipe_out_and_dispose_5d( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 70, 7 );

   ii_btree_kv_wipe_out_and_dispose( btree );

   CU_ASSERT( ii_btree_kv_count( btree ) == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_wipe_out_and_dispose_5e

            4
         2      6
       1   3  5   7
*/

void test_wipe_out_and_dispose_5e( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 70, 7 );

   ii_btree_kv_wipe_out_and_dispose( btree );

   CU_ASSERT( ii_btree_kv_count( btree ) == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_wipe_out_and_dispose_5f

            4
         2      6
       1   3  5   7
*/

void test_wipe_out_and_dispose_5f( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 70, 7 );

   ii_btree_kv_wipe_out_and_dispose( btree );

   CU_ASSERT( ii_btree_kv_count( btree ) == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_wipe_out_and_dispose_6
*/

void test_wipe_out_and_dispose_6( void )
{
   ii_btree_kv_t *btree = NULL;
   ii_btree_kv_cursor_t *cursor = NULL;

   btree = ii_btree_kv_make( 3 );
   cursor = ii_btree_kv_cursor_make( btree );

   ii_btree_kv_put( btree, 10, 1 );

   ii_btree_kv_wipe_out_and_dispose( btree );

   CU_ASSERT( ii_btree_kv_count( btree ) == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_wipe_out_and_dispose_7
*/

void test_wipe_out_and_dispose_7( void )
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
   string_t *s5v = NULL;
   string_t *s5k = NULL;
   string_t *s6v = NULL;
   string_t *s6k = NULL;
   string_t *s7v = NULL;
   string_t *s7k = NULL;
   ss_btree_kv_cursor_t *cursor = NULL;

   s1k = string_make_from_cstring( "4" );
   s1v = string_make_from_cstring( "40" );
   
   s2k = string_make_from_cstring( "2" );
   s2v = string_make_from_cstring( "20" );
   
   s3k = string_make_from_cstring( "6" );
   s3v = string_make_from_cstring( "60" );
   
   s4k = string_make_from_cstring( "1" );
   s4v = string_make_from_cstring( "10" );
   
   s5k = string_make_from_cstring( "3" );
   s5v = string_make_from_cstring( "30" );
   
   s6k = string_make_from_cstring( "5" );
   s6v = string_make_from_cstring( "50" );
   
   s7k = string_make_from_cstring( "7" );
   s7v = string_make_from_cstring( "70" );
   
   btree = ss_btree_kv_make( 3 );
   cursor = ss_btree_kv_cursor_make( btree );

   ss_btree_kv_put( btree, s1v, s1k );
   ss_btree_kv_put( btree, s2v, s2k );
   ss_btree_kv_put( btree, s3v, s3k );
   ss_btree_kv_put( btree, s4v, s4k );
   ss_btree_kv_put( btree, s5v, s5k );
   ss_btree_kv_put( btree, s6v, s6k );
   ss_btree_kv_put( btree, s7v, s7k );
   
   ss_btree_kv_wipe_out_and_dispose( btree );
   
   CU_ASSERT( ss_btree_kv_count( btree ) == 0 );

   ss_btree_kv_deep_dispose( &btree );

   return;
}

int
add_test_wipe_out_and_dispose( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_wipe_out_and_dispose", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_wipe_out_and_dispose_1
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_1, "test_wipe_out_and_dispose_1" );

   // test_wipe_out_and_dispose_2
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_2, "test_wipe_out_and_dispose_2" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_2a, "test_wipe_out_and_dispose_2a" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_2b, "test_wipe_out_and_dispose_2b" );

   // test_wipe_out_and_dispose_3
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_3, "test_wipe_out_and_dispose_3" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_3a, "test_wipe_out_and_dispose_3a" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_3b, "test_wipe_out_and_dispose_3b" );

   // test_wipe_out_and_dispose_4
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_4, "test_wipe_out_and_dispose_4" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_4a, "test_wipe_out_and_dispose_4a" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_4b, "test_wipe_out_and_dispose_4b" );

   // test_wipe_out_and_dispose_5
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_5, "test_wipe_out_and_dispose_5" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_5a, "test_wipe_out_and_dispose_5a" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_5b, "test_wipe_out_and_dispose_5b" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_5c, "test_wipe_out_and_dispose_5c" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_5d, "test_wipe_out_and_dispose_5d" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_5e, "test_wipe_out_and_dispose_5e" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_5f, "test_wipe_out_and_dispose_5f" );

   // test_wipe_out_and_dispose_6
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_6, "test_wipe_out_and_dispose_6" );

   // test_wipe_out_and_dispose_7
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_7, "test_wipe_out_and_dispose_7" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

