/**
 @file RBTree_test_p_diterable.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for RBTree P_DIterable"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for RBTree_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_RBTree.h"
#include "s_RBTree.h"
#include "Protocol_Base.h"
#include "i_DIterable.h"
#include "s_DIterable.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_p_diterable_1
*/

void test_p_diterable_1( void )
{
   i_rbtree_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;
   
   tree = i_rbtree_make();
   pb_tree = ( protocol_base_t * ) tree;
   
   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   i_rbtree_dispose( &tree );
 
   return;
}

/**
   test_p_diterable_2
*/

void test_p_diterable_2( void )
{
   i_rbtree_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = i_rbtree_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   i_rbtree_deep_dispose( &tree );

   return;
}

/**
   test_p_diterable_3
*/

void test_p_diterable_3( void )
{
   i_rbtree_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = i_rbtree_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   i_rbtree_put( tree, 24 );

   CU_ASSERT( i_diterable_count( pb_tree ) == 1 );

   i_rbtree_dispose( &tree );

   return;
}

/**
   test_p_diterable_4
*/

void test_p_diterable_4( void )
{
   i_rbtree_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = i_rbtree_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   i_rbtree_put( tree, 24 );
   i_rbtree_start( tree );

   CU_ASSERT( i_diterable_item( pb_tree) == 24 );

   i_rbtree_dispose( &tree );

   return;
}

/**
   test_p_diterable_5
*/

void test_p_diterable_5( void )
{
   i_rbtree_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = i_rbtree_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   i_rbtree_put( tree, 24 );

   CU_ASSERT( i_diterable_off( pb_tree ) == 1 );

   i_rbtree_dispose( &tree );

   return;
}

/**
   test_p_diterable_6
*/

void test_p_diterable_6( void )
{
   i_rbtree_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = i_rbtree_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   CU_ASSERT( i_diterable_is_empty( pb_tree ) == 1 );

   i_rbtree_dispose( &tree );

   return;
}

/**
   test_p_diterable_7
*/

void test_p_diterable_7( void )
{
   i_rbtree_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = i_rbtree_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   i_rbtree_put( tree, 24 );
   i_diterable_start( pb_tree );

   CU_ASSERT( i_diterable_item( pb_tree) == 24 );

   i_rbtree_dispose( &tree );

   return;
}

/**
   test_p_diterable_8
*/

void test_p_diterable_8( void )
{
   i_rbtree_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = i_rbtree_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   i_rbtree_put( tree, 24 );
   i_rbtree_put( tree, 13 );

   i_rbtree_start( tree );
   i_diterable_forth( pb_tree );

   CU_ASSERT( i_diterable_item( pb_tree) == 24 );

   i_rbtree_dispose( &tree );

   return;
}

/**
   test_p_diterable_9
*/

void test_p_diterable_9( void )
{
   i_rbtree_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = i_rbtree_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   i_rbtree_put( tree, 24 );
   i_rbtree_put( tree, 13 );
   i_diterable_finish( pb_tree );

   CU_ASSERT( i_diterable_item( pb_tree) == 24 );

   i_rbtree_dispose( &tree );

   return;
}

/**
   test_p_diterable_10
*/

void test_p_diterable_10( void )
{
   i_rbtree_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = i_rbtree_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   i_rbtree_put( tree, 24 );
   i_rbtree_put( tree, 13 );

   i_rbtree_finish( tree );
   i_diterable_back( pb_tree );

   CU_ASSERT( i_diterable_item( pb_tree) == 13 );

   i_rbtree_dispose( &tree );

   return;
}

/**
   test_p_diterable_11
*/

void test_p_diterable_11( void )
{
   s_rbtree_t *rbtree = NULL;
   protocol_base_t *pb_rbtree = NULL;

   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   
   rbtree = s_rbtree_make();
   pb_rbtree = ( protocol_base_t * ) rbtree;

   CU_ASSERT( rbtree != NULL );
   CU_ASSERT( pb_rbtree != NULL );

   s_rbtree_put( rbtree, s2 );
   s_rbtree_put( rbtree, s1 );

   s_rbtree_finish( rbtree );
   s_diterable_back( pb_rbtree );

   CU_ASSERT( s_diterable_item( pb_rbtree) == s1 );

   s_rbtree_deep_dispose( &rbtree );

   return;
}

int
add_test_p_diterable( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_p_diterable", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_p_diterable_1
   add_test_to_suite( p_suite, test_p_diterable_1, "test_p_diterable_1" );

   // test_p_diterable_2
   add_test_to_suite( p_suite, test_p_diterable_2, "test_p_diterable_2" );

   // test_p_diterable_3
   add_test_to_suite( p_suite, test_p_diterable_3, "test_p_diterable_3" );

   // test_p_diterable_4
   add_test_to_suite( p_suite, test_p_diterable_4, "test_p_diterable_4" );

   // test_p_diterable_5
   add_test_to_suite( p_suite, test_p_diterable_5, "test_p_diterable_5" );

   // test_p_diterable_6
   add_test_to_suite( p_suite, test_p_diterable_6, "test_p_diterable_6" );

   // test_p_diterable_7
   add_test_to_suite( p_suite, test_p_diterable_7, "test_p_diterable_7" );

   // test_p_diterable_8
   add_test_to_suite( p_suite, test_p_diterable_8, "test_p_diterable_8" );

   // test_p_diterable_9
   add_test_to_suite( p_suite, test_p_diterable_9, "test_p_diterable_9" );

   // test_p_diterable_10
   add_test_to_suite( p_suite, test_p_diterable_10, "test_p_diterable_10" );

   // test_p_diterable_11
   add_test_to_suite( p_suite, test_p_diterable_11, "test_p_diterable_11" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

