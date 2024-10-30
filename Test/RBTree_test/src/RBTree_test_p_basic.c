/**
 @file RBTree_test_p_basic.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for RBTree P_Basic"
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
#include "i_Basic.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_p_basic_1
*/

void test_p_basic_1( void )
{
   i_rbtree_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;
   
   tree = i_rbtree_make();
   pb_tree = ( protocol_base_t * ) tree;
   
   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   i_basic_dispose( &pb_tree );
 
   return;
}

/**
   test_p_basic_2
*/

void test_p_basic_2( void )
{
   i_rbtree_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = i_rbtree_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   i_basic_deep_dispose( &pb_tree );

   return;
}

/**
   test_p_basic_3
*/

void test_p_basic_3( void )
{
   i_rbtree_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;
   protocol_base_t *pb_tree1 = NULL;

   tree = i_rbtree_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   pb_tree1 = i_basic_clone( pb_tree );
   CU_ASSERT( pb_tree1 != NULL );

   i_basic_dispose( &pb_tree );
   i_basic_dispose( &pb_tree1 );

   return;
}

/**
   test_p_basic_4
*/

void test_p_basic_4( void )
{
   i_rbtree_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;
   protocol_base_t *pb_tree1 = NULL;

   tree = i_rbtree_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   pb_tree1 = i_basic_deep_clone( pb_tree );
   CU_ASSERT( pb_tree1 != NULL );

   i_basic_dispose( &pb_tree );
   i_basic_dispose( &pb_tree1 );

   return;
}

/**
   test_p_basic_5
*/

void test_p_basic_5( void )
{
   s_rbtree_t *rbtree = NULL;
   protocol_base_t *pb_rbtree = NULL;
   protocol_base_t *pb_rbtree1 = NULL;

   rbtree = s_rbtree_make();
   pb_rbtree = ( protocol_base_t * ) rbtree;

   CU_ASSERT( rbtree != NULL );
   CU_ASSERT( pb_rbtree != NULL );

   pb_rbtree1 = i_basic_deep_clone( pb_rbtree );
   CU_ASSERT( pb_rbtree1 != NULL );

   i_basic_dispose( &pb_rbtree );
   i_basic_dispose( &pb_rbtree1 );

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

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

