/**
 @file BTree_kv_test_p_basic.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BTree_kv P_Clonable"
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
#include "Protocol_Base.h"
#include "p_Basic.h"
#include "ss_BTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_p_basic_1
*/

void test_p_basic_1( void )
{
   ii_btree_kv_t *btree = NULL;
   protocol_base_t *pb_btree = NULL;
   
   btree = ii_btree_kv_make( 4 );
   pb_btree = ( protocol_base_t * ) btree;
   
   CU_ASSERT( btree != NULL );
   CU_ASSERT( pb_btree != NULL );

   p_basic_dispose( &pb_btree );
 
   return;
}

/**
   test_p_basic_2
*/

void test_p_basic_2( void )
{
   ii_btree_kv_t *btree = NULL;
   protocol_base_t *pb_btree = NULL;

   btree = ii_btree_kv_make( 4 );
   pb_btree = ( protocol_base_t * ) btree;

   CU_ASSERT( btree != NULL );
   CU_ASSERT( pb_btree != NULL );

   p_basic_deep_dispose( &pb_btree );

   return;
}

/**
   test_p_basic_3
*/

void test_p_basic_3( void )
{
   ii_btree_kv_t *btree = NULL;
   protocol_base_t *pb_btree = NULL;
   protocol_base_t *pb_btree1 = NULL;

   btree = ii_btree_kv_make( 4 );
   pb_btree = ( protocol_base_t * ) btree;

   CU_ASSERT( btree != NULL );
   CU_ASSERT( pb_btree != NULL );

   pb_btree1 = p_basic_clone( pb_btree );
   CU_ASSERT( pb_btree1 != NULL );

   p_basic_dispose( &pb_btree );
   p_basic_dispose( &pb_btree1 );

   return;
}

/**
   test_p_basic_4
*/

void test_p_basic_4( void )
{
   ii_btree_kv_t *btree = NULL;
   protocol_base_t *pb_btree = NULL;
   protocol_base_t *pb_btree1 = NULL;

   btree = ii_btree_kv_make( 4 );
   pb_btree = ( protocol_base_t * ) btree;

   CU_ASSERT( btree != NULL );
   CU_ASSERT( pb_btree != NULL );

   pb_btree1 = p_basic_deep_clone( pb_btree );
   CU_ASSERT( pb_btree1 != NULL );

   p_basic_dispose( &pb_btree );
   p_basic_dispose( &pb_btree1 );

   return;
}

/**
   test_p_basic_5
*/

void test_p_basic_5( void )
{
   string_t *s1v = NULL;
   string_t *s1k = NULL;
   string_t *s2v = NULL;
   string_t *s2k = NULL;
   ss_btree_kv_t *btree = NULL;
   ss_btree_kv_t *btree1 = NULL;
   protocol_base_t *pb_btree = NULL;
   protocol_base_t *pb_btree1 = NULL;

   s1k = string_make_from_cstring( "24" );
   s1v = string_make_from_cstring( "240" );
   
   s2k = string_make_from_cstring( "13" );
   s2v = string_make_from_cstring( "130" );
   
   btree = ss_btree_kv_make( 4 );
   btree1 = ss_btree_kv_make( 4 );
   
   pb_btree = ( protocol_base_t * ) btree;
   pb_btree1 = ( protocol_base_t * ) btree1;

   CU_ASSERT( pb_btree != NULL );
   CU_ASSERT( pb_btree1 != NULL );

   CU_ASSERT( p_basic_is_equal( pb_btree, pb_btree1 ) == 1 );
   CU_ASSERT( p_basic_is_deep_equal( pb_btree, pb_btree1 ) == 1 );

   ss_btree_kv_put( btree, s1v, s1k );
   p_basic_copy( pb_btree1, pb_btree );
   
   CU_ASSERT( p_basic_is_equal( pb_btree, pb_btree1 ) == 1 );
   CU_ASSERT( p_basic_is_deep_equal( pb_btree, pb_btree1 ) == 1 );

   ss_btree_kv_put( btree, s2v, s2k );
   
   ss_btree_kv_remove( btree1, s1k );
   p_basic_deep_copy( pb_btree1, pb_btree );
   
   CU_ASSERT( p_basic_is_equal( pb_btree, pb_btree1 ) == 0 );
   CU_ASSERT( p_basic_is_deep_equal( pb_btree, pb_btree1 ) == 1 );

   p_basic_deep_dispose( &pb_btree );
   p_basic_deep_dispose( &pb_btree1 );

   return;
}

/**
   test_p_basic_6
*/

void test_p_basic_6( void )
{
   ss_btree_kv_t *btree = NULL;
   ss_btree_kv_t *btree1 = NULL;
   protocol_base_t *pb_btree = NULL;
   protocol_base_t *pb_btree1 = NULL;
   string_t *s1v = NULL;
   string_t *s1k = NULL;

   s1k = string_make_from_cstring( "4" );
   s1v = string_make_from_cstring( "40" );
   
   btree = ss_btree_kv_make( 4 );
   
   ss_btree_kv_put( btree, s1v, s1k );
   
   pb_btree = ( protocol_base_t * ) btree;
   pb_btree1 = p_basic_clone( pb_btree );
   
   CU_ASSERT( pb_btree != NULL );
   CU_ASSERT( pb_btree1 != NULL );
   
   CU_ASSERT( p_basic_is_equal( pb_btree, pb_btree1 ) == 1 );
   CU_ASSERT( p_basic_is_deep_equal( pb_btree, pb_btree1 ) == 1 );

   p_basic_dispose( &pb_btree1 );
   pb_btree1 = p_basic_deep_clone( pb_btree );

   CU_ASSERT( p_basic_is_equal( pb_btree, pb_btree1 ) == 0 );
   CU_ASSERT( p_basic_is_deep_equal( pb_btree, pb_btree1 ) == 1 );

   p_basic_copy( pb_btree1, pb_btree );
   
   CU_ASSERT( p_basic_is_equal( pb_btree, pb_btree1 ) == 1 );
   CU_ASSERT( p_basic_is_deep_equal( pb_btree, pb_btree1 ) == 1 );

   btree1 = ( ss_btree_kv_t * ) pb_btree1;
   ss_btree_kv_wipe_out( btree1 );
   p_basic_deep_copy( pb_btree1, pb_btree );
   
   CU_ASSERT( p_basic_is_equal( pb_btree, pb_btree1 ) == 0 );
   CU_ASSERT( p_basic_is_deep_equal( pb_btree, pb_btree1 ) == 1 );

   p_basic_deep_dispose( &pb_btree );
   p_basic_deep_dispose( &pb_btree1 );

   return;
}

int
add_test_p_basic( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_p_basic", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_p_basic_1
   add_test_to_suite( p_suite, test_p_basic_1, "test_p_basic_1" );

   // test_p_basic_2
   add_test_to_suite( p_suite, test_p_basic_2, "test_p_basic_2" );

   // test_p_basic_3
   add_test_to_suite( p_suite, test_p_basic_3, "test_p_basic_3" );

   // test_p_basic_4
   add_test_to_suite( p_suite, test_p_basic_4, "test_p_basic_4" );

   // test_p_basic_5
   add_test_to_suite( p_suite, test_p_basic_5, "test_p_basic_5" );

   // test_p_basic_6
   add_test_to_suite( p_suite, test_p_basic_6, "test_p_basic_6" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

