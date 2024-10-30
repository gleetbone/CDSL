/**
 @file AVLTree_test_p_diterable.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for AVLTree P_DIterable"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for AVLTree_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_AVLTree.h"
#include "Protocol_Base.h"
#include "i_DIterable.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_p_diterable_1
*/

void test_p_diterable_1( void )
{
   i_avltree_t *tree = NULL;
   protocol_base_t *pb = NULL;
   
   tree = i_avltree_make();
   pb = ( protocol_base_t * ) tree;
   
   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb != NULL );

   i_avltree_dispose( &tree );
 
   return;
}

/**
   test_p_diterable_2
*/

void test_p_diterable_2( void )
{
   i_avltree_t *tree = NULL;
   protocol_base_t *pb = NULL;

   tree = i_avltree_make();
   pb = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb != NULL );

   i_avltree_deep_dispose( &tree );

   return;
}

/**
   test_p_diterable_3
*/

void test_p_diterable_3( void )
{
   i_avltree_t *tree = NULL;
   protocol_base_t *pb = NULL;

   tree = i_avltree_make();
   pb = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb != NULL );

   i_avltree_put( tree, 24 );

   CU_ASSERT( i_diterable_count( pb ) == 1 );

   i_avltree_dispose( &tree );

   return;
}

/**
   test_p_diterable_4
*/

void test_p_diterable_4( void )
{
   i_avltree_t *tree = NULL;
   protocol_base_t *pb = NULL;

   tree = i_avltree_make();
   pb = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb != NULL );

   i_avltree_put( tree, 24 );
   i_avltree_start( tree );

   CU_ASSERT( i_diterable_item( pb) == 24 );

   i_avltree_dispose( &tree );

   return;
}

/**
   test_p_diterable_5
*/

void test_p_diterable_5( void )
{
   i_avltree_t *tree = NULL;
   protocol_base_t *pb = NULL;

   tree = i_avltree_make();
   pb = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb != NULL );

   i_avltree_put( tree, 24 );

   CU_ASSERT( i_diterable_off( pb ) == 1 );

   i_avltree_dispose( &tree );

   return;
}

/**
   test_p_diterable_6
*/

void test_p_diterable_6( void )
{
   i_avltree_t *tree = NULL;
   protocol_base_t *pb = NULL;

   tree = i_avltree_make();
   pb = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb != NULL );

   CU_ASSERT( i_diterable_is_empty( pb ) == 1 );

   i_avltree_dispose( &tree );

   return;
}

/**
   test_p_diterable_7
*/

void test_p_diterable_7( void )
{
   i_avltree_t *tree = NULL;
   protocol_base_t *pb = NULL;

   tree = i_avltree_make();
   pb = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb != NULL );

   i_avltree_put( tree, 24 );
   i_diterable_start( pb );

   CU_ASSERT( i_diterable_item( pb) == 24 );

   i_avltree_dispose( &tree );

   return;
}

/**
   test_p_diterable_8
*/

void test_p_diterable_8( void )
{
   i_avltree_t *tree = NULL;
   protocol_base_t *pb = NULL;

   tree = i_avltree_make();
   pb = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb != NULL );

   i_avltree_put( tree, 24 );
   i_avltree_put( tree, 13 );

   i_avltree_start( tree );
   i_diterable_forth( pb );

   CU_ASSERT( i_diterable_item( pb) == 24 );

   i_avltree_dispose( &tree );

   return;
}

/**
   test_p_diterable_9
*/

void test_p_diterable_9( void )
{
   i_avltree_t *tree = NULL;
   protocol_base_t *pb = NULL;

   tree = i_avltree_make();
   pb = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb != NULL );

   i_avltree_put( tree, 24 );
   i_avltree_put( tree, 13 );
   i_diterable_finish( pb );

   CU_ASSERT( i_diterable_item( pb) == 24 );

   i_avltree_dispose( &tree );

   return;
}

/**
   test_p_diterable_10
*/

void test_p_diterable_10( void )
{
   i_avltree_t *tree = NULL;
   protocol_base_t *pb = NULL;

   tree = i_avltree_make();
   pb = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb != NULL );

   i_avltree_put( tree, 24 );
   i_avltree_put( tree, 13 );

   i_avltree_finish( tree );
   i_diterable_back( pb );

   CU_ASSERT( i_diterable_item( pb) == 13 );

   i_avltree_dispose( &tree );

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

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

