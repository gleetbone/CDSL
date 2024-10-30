/**
 @file RBTree_test_p_diterable_kv.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for RBTree P_DIterable"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for RBTree_kv_t

*/

#ifdef _cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_RBTree_kv.h"
#include "ss_RBTree_kv.h"
#include "Protocol_Base.h"
#include "ii_DIterable_kv.h"
#include "ss_DIterable_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_p_diterable_kv_1
*/

void test_p_diterable_kv_1( void )
{
   ii_rbtree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;
   
   tree = ii_rbtree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;
   
   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   ii_rbtree_kv_dispose( &tree );
 
   return;
}

/**
   test_p_diterable_kv_2
*/

void test_p_diterable_kv_2( void )
{
   ii_rbtree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = ii_rbtree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   ii_rbtree_kv_deep_dispose( &tree );

   return;
}

/**
   test_p_diterable_kv_3
*/

void test_p_diterable_kv_3( void )
{
   ii_rbtree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = ii_rbtree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   ii_rbtree_kv_put( tree, 24, 240 );

   CU_ASSERT( ii_diterable_kv_count( pb_tree ) == 1 );

   ii_rbtree_kv_dispose( &tree );

   return;
}

/**
   test_p_diterable_kv_4
*/

void test_p_diterable_kv_4( void )
{
   ii_rbtree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = ii_rbtree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   ii_rbtree_kv_put( tree, 24, 240 );
   ii_rbtree_kv_start( tree );

   CU_ASSERT( ii_diterable_kv_value( pb_tree) == 24 );

   ii_rbtree_kv_dispose( &tree );

   return;
}

/**
   test_p_diterable_kv_4a
*/

void test_p_diterable_kv_4a( void )
{
   ii_rbtree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = ii_rbtree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   ii_rbtree_kv_put( tree, 24, 240 );
   ii_rbtree_kv_start( tree );

   CU_ASSERT( ii_diterable_kv_key( pb_tree) == 240 );

   ii_rbtree_kv_dispose( &tree );

   return;
}

/**
   test_p_diterable_kv_5
*/

void test_p_diterable_kv_5( void )
{
   ii_rbtree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = ii_rbtree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   ii_rbtree_kv_put( tree, 24, 240 );

   CU_ASSERT( ii_diterable_kv_off( pb_tree ) == 1 );

   ii_rbtree_kv_dispose( &tree );

   return;
}

/**
   test_p_diterable_kv_6
*/

void test_p_diterable_kv_6( void )
{
   ii_rbtree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = ii_rbtree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   CU_ASSERT( ii_diterable_kv_is_empty( pb_tree ) == 1 );

   ii_rbtree_kv_dispose( &tree );

   return;
}

/**
   test_p_diterable_kv_7
*/

void test_p_diterable_kv_7( void )
{
   ii_rbtree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = ii_rbtree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   ii_rbtree_kv_put( tree, 24, 240 );
   ii_diterable_kv_start( pb_tree );

   CU_ASSERT( ii_diterable_kv_value( pb_tree) == 24 );

   ii_rbtree_kv_dispose( &tree );

   return;
}

/**
   test_p_diterable_kv_8
*/

void test_p_diterable_kv_8( void )
{
   ii_rbtree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = ii_rbtree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   ii_rbtree_kv_put( tree, 24, 240 );
   ii_rbtree_kv_put( tree, 13, 130 );

   ii_rbtree_kv_start( tree );
   ii_diterable_kv_forth( pb_tree );

   CU_ASSERT( ii_diterable_kv_value( pb_tree) == 24 );

   ii_rbtree_kv_dispose( &tree );

   return;
}

/**
   test_p_diterable_kv_9
*/

void test_p_diterable_kv_9( void )
{
   ii_rbtree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = ii_rbtree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   ii_rbtree_kv_put( tree, 24, 240 );
   ii_rbtree_kv_put( tree, 13, 130 );
   ii_diterable_kv_finish( pb_tree );

   CU_ASSERT( ii_diterable_kv_value( pb_tree) == 24 );

   ii_rbtree_kv_dispose( &tree );

   return;
}

/**
   test_p_diterable_kv_10
*/

void test_p_diterable_kv_10( void )
{
   ii_rbtree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = ii_rbtree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   ii_rbtree_kv_put( tree, 24, 240 );
   ii_rbtree_kv_put( tree, 13, 130 );

   ii_rbtree_kv_finish( tree );
   ii_diterable_kv_back( pb_tree );

   CU_ASSERT( ii_diterable_kv_value( pb_tree) == 13 );

   ii_rbtree_kv_dispose( &tree );

   return;
}

/**
   test_p_diterable_kv_11
*/

void test_p_diterable_kv_11( void )
{
   ss_rbtree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   string_t *s1 = NULL;
   string_t *s10 = NULL;
   string_t *s2 = NULL;
   string_t *s20 = NULL;
   
   s1 = string_make_from_cstring( "1" );
   s10 = string_make_from_cstring( "10" );
   s2 = string_make_from_cstring( "2" );
   s20 = string_make_from_cstring( "20" );
   
   tree = ss_rbtree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   ss_rbtree_kv_put( tree, s20, s2 );
   ss_rbtree_kv_put( tree, s10, s1 );

   ss_rbtree_kv_finish( tree );
   ss_diterable_kv_back( pb_tree );

   CU_ASSERT( ss_diterable_kv_value( pb_tree) == s10 );

   ss_rbtree_kv_deep_dispose( &tree );

   return;
}

int
add_test_p_diterable_kv( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_p_diterable_kv", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_p_diterable_kv_1
   add_test_to_suite( p_suite, test_p_diterable_kv_1, "test_p_diterable_kv_1" );

   // test_p_diterable_kv_2
   add_test_to_suite( p_suite, test_p_diterable_kv_2, "test_p_diterable_kv_2" );

   // test_p_diterable_kv_3
   add_test_to_suite( p_suite, test_p_diterable_kv_3, "test_p_diterable_kv_3" );

   // test_p_diterable_kv_4
   add_test_to_suite( p_suite, test_p_diterable_kv_4, "test_p_diterable_kv_4" );

   // test_p_diterable_kv_4a
   add_test_to_suite( p_suite, test_p_diterable_kv_4a, "test_p_diterable_kv_4a" );

   // test_p_diterable_kv_5
   add_test_to_suite( p_suite, test_p_diterable_kv_5, "test_p_diterable_kv_5" );

   // test_p_diterable_kv_6
   add_test_to_suite( p_suite, test_p_diterable_kv_6, "test_p_diterable_kv_6" );

   // test_p_diterable_kv_7
   add_test_to_suite( p_suite, test_p_diterable_kv_7, "test_p_diterable_kv_7" );

   // test_p_diterable_kv_8
   add_test_to_suite( p_suite, test_p_diterable_kv_8, "test_p_diterable_kv_8" );

   // test_p_diterable_kv_9
   add_test_to_suite( p_suite, test_p_diterable_kv_9, "test_p_diterable_kv_9" );

   // test_p_diterable_kv_10
   add_test_to_suite( p_suite, test_p_diterable_kv_10, "test_p_diterable_kv_10" );

   // test_p_diterable_kv_11
   add_test_to_suite( p_suite, test_p_diterable_kv_11, "test_p_diterable_kv_11" );

   return CUE_SUCCESS;
   
}

#ifdef _cplusplus
}
#endif

/* End of file */

