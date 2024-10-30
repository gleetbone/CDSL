/**
 @file RBTree_test_p_iterable.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for RBTree P_Iterable"
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
#include "i_Iterable.h"
#include "s_Iterable.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_p_iterable_1
*/

void test_p_iterable_1( void )
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
   test_p_iterable_2
*/

void test_p_iterable_2( void )
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
   test_p_iterable_3
*/

void test_p_iterable_3( void )
{
   i_rbtree_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = i_rbtree_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   i_rbtree_put( tree, 24 );

   CU_ASSERT( i_iterable_count( pb_tree ) == 1 );

   i_rbtree_dispose( &tree );

   return;
}

/**
   test_p_iterable_4
*/

void test_p_iterable_4( void )
{
   i_rbtree_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = i_rbtree_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   i_rbtree_put( tree, 24 );
   i_rbtree_start( tree );

   CU_ASSERT( i_iterable_item( pb_tree) == 24 );

   i_rbtree_dispose( &tree );

   return;
}

/**
   test_p_iterable_5
*/

void test_p_iterable_5( void )
{
   i_rbtree_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = i_rbtree_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   i_rbtree_put( tree, 24 );

   CU_ASSERT( i_iterable_off( pb_tree ) == 1 );

   i_rbtree_dispose( &tree );

   return;
}

/**
   test_p_iterable_6
*/

void test_p_iterable_6( void )
{
   i_rbtree_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = i_rbtree_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   CU_ASSERT( i_iterable_is_empty( pb_tree ) == 1 );

   i_rbtree_dispose( &tree );

   return;
}

/**
   test_p_iterable_7
*/

void test_p_iterable_7( void )
{
   i_rbtree_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = i_rbtree_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   i_rbtree_put( tree, 24 );
   i_iterable_start( pb_tree );

   CU_ASSERT( i_iterable_item( pb_tree) == 24 );

   i_rbtree_dispose( &tree );

   return;
}

/**
   test_p_iterable_8
*/

void test_p_iterable_8( void )
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
   i_iterable_forth( pb_tree );

   CU_ASSERT( i_iterable_item( pb_tree) == 24 );

   i_rbtree_dispose( &tree );

   return;
}

/**
   test_p_iterable_9
*/

void test_p_iterable_9( void )
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

   s_rbtree_start( rbtree );
   s_iterable_forth( pb_rbtree );

   CU_ASSERT( s_iterable_item( pb_rbtree) == s2 );

   s_rbtree_deep_dispose( &rbtree );

   return;
}

int
add_test_p_iterable( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_p_iterable", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_p_iterable_1
   add_test_to_suite( p_suite, test_p_iterable_1, "test_p_iterable_1" );

   // test_p_iterable_2
   add_test_to_suite( p_suite, test_p_iterable_2, "test_p_iterable_2" );

   // test_p_iterable_3
   add_test_to_suite( p_suite, test_p_iterable_3, "test_p_iterable_3" );

   // test_p_iterable_4
   add_test_to_suite( p_suite, test_p_iterable_4, "test_p_iterable_4" );

   // test_p_iterable_5
   add_test_to_suite( p_suite, test_p_iterable_5, "test_p_iterable_5" );

   // test_p_iterable_6
   add_test_to_suite( p_suite, test_p_iterable_6, "test_p_iterable_6" );

   // test_p_iterable_7
   add_test_to_suite( p_suite, test_p_iterable_7, "test_p_iterable_7" );

   // test_p_iterable_8
   add_test_to_suite( p_suite, test_p_iterable_8, "test_p_iterable_8" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

