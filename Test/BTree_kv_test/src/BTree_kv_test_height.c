/**
 @file BTree_test_height.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BTree_kv_height"
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
   test_height_1
*/

void test_height_1( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   CU_ASSERT( ii_btree_kv_height( btree ) == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_height_2
*/

void test_height_2( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );

   CU_ASSERT( ii_btree_kv_height( btree ) == 1 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_height_3
*/

void test_height_3( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );

   CU_ASSERT( ii_btree_kv_height( btree ) == 1 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_height_4
*/

void test_height_4( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 70, 7 );

   CU_ASSERT( ii_btree_kv_height( btree ) == 2 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_height_5
*/

void test_height_5( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree,  10,  1 );
   ii_btree_kv_put( btree,  20,  2 );
   ii_btree_kv_put( btree,  30,  3 );
   ii_btree_kv_put( btree,  40,  4 );
   ii_btree_kv_put( btree,  50,  5 );
   ii_btree_kv_put( btree,  60,  6 );
   ii_btree_kv_put( btree,  70,  7 );
   ii_btree_kv_put( btree,  80,  8 );
   ii_btree_kv_put( btree,  90,  9 );
   ii_btree_kv_put( btree, 100,  10 );
   ii_btree_kv_put( btree, 110,  11 );
   ii_btree_kv_put( btree, 120,  12 );
   ii_btree_kv_put( btree, 130,  13 );
   ii_btree_kv_put( btree, 140,  14 );
   ii_btree_kv_put( btree, 150,  15 );
   ii_btree_kv_put( btree, 160,  16 );

   CU_ASSERT( ii_btree_kv_height( btree ) == 3 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_height_6
*/

void test_height_6( void )
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
   string_t *s8v = NULL;
   string_t *s8k = NULL;
   string_t *s9v = NULL;
   string_t *s9k = NULL;
   string_t *s10v = NULL;
   string_t *s10k = NULL;
   string_t *s11v = NULL;
   string_t *s11k = NULL;
   string_t *s12v = NULL;
   string_t *s12k = NULL;
   string_t *s13v = NULL;
   string_t *s13k = NULL;
   string_t *s14v = NULL;
   string_t *s14k = NULL;
   string_t *s15v = NULL;
   string_t *s15k = NULL;
   string_t *s16v = NULL;
   string_t *s16k = NULL;

   s1k = string_make_from_cstring( "1" );
   s1v = string_make_from_cstring( "10" );
   s2k = string_make_from_cstring( "2" );
   s2v = string_make_from_cstring( "20" );
   s3k = string_make_from_cstring( "3" );
   s3v = string_make_from_cstring( "30" );
   s4k = string_make_from_cstring( "4" );
   s4v = string_make_from_cstring( "40" );
   s5k = string_make_from_cstring( "5" );
   s5v = string_make_from_cstring( "50" );
   s6k = string_make_from_cstring( "6" );
   s6v = string_make_from_cstring( "60" );
   s7k = string_make_from_cstring( "7" );
   s7v = string_make_from_cstring( "70" );
   s8k = string_make_from_cstring( "8" );
   s8v = string_make_from_cstring( "80" );
   s9k = string_make_from_cstring( "9" );
   s9v = string_make_from_cstring( "90" );
   s10k = string_make_from_cstring( "10" );
   s10v = string_make_from_cstring( "100" );
   s11k = string_make_from_cstring( "11" );
   s11v = string_make_from_cstring( "110" );
   s12k = string_make_from_cstring( "12" );
   s12v = string_make_from_cstring( "120" );
   s13k = string_make_from_cstring( "13" );
   s13v = string_make_from_cstring( "130" );
   s14k = string_make_from_cstring( "14" );
   s14v = string_make_from_cstring( "140" );
   s15k = string_make_from_cstring( "15" );
   s15v = string_make_from_cstring( "150" );
   s16k = string_make_from_cstring( "16" );
   s16v = string_make_from_cstring( "160" );
   
   btree = ss_btree_kv_make( 3 );

   ss_btree_kv_put( btree,  s1v,  s1k );
   ss_btree_kv_put( btree,  s2v,  s2k );
   ss_btree_kv_put( btree,  s3v,  s3k );
   ss_btree_kv_put( btree,  s4v,  s4k );
   ss_btree_kv_put( btree,  s5v,  s5k );
   ss_btree_kv_put( btree,  s6v,  s6k );
   ss_btree_kv_put( btree,  s7v,  s7k );
   ss_btree_kv_put( btree,  s8v,  s8k );
   ss_btree_kv_put( btree,  s9v,  s9k );
   ss_btree_kv_put( btree,  s10v,  s10k );
   ss_btree_kv_put( btree,  s11v,  s11k );
   ss_btree_kv_put( btree,  s12v,  s12k );
   ss_btree_kv_put( btree,  s13v,  s13k );
   ss_btree_kv_put( btree,  s14v,  s14k );
   ss_btree_kv_put( btree,  s15v,  s15k );
   ss_btree_kv_put( btree,  s16v,  s16k );

   CU_ASSERT( ss_btree_kv_height( btree ) == 3 );

   ss_btree_kv_deep_dispose( &btree );

   return;
}


int
add_test_height( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_height", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_height_1
   add_test_to_suite( p_suite, test_height_1, "test_height_1" );

   // test_height_2
   add_test_to_suite( p_suite, test_height_2, "test_height_2" );

   // test_height_3
   add_test_to_suite( p_suite, test_height_3, "test_height_3" );

   // test_height_4
   add_test_to_suite( p_suite, test_height_4, "test_height_4" );

   // test_height_5
   add_test_to_suite( p_suite, test_height_5, "test_height_5" );

   // test_height_6
   add_test_to_suite( p_suite, test_height_6, "test_height_6" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

