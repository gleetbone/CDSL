/**
 @file AVLTree_test_p_iterable.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for AVLTree P_Iterable"
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
#include "i_Iterable.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_p_iterable_1
*/

void test_p_iterable_1( void )
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
   test_p_iterable_2
*/

void test_p_iterable_2( void )
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
   test_p_iterable_3
*/

void test_p_iterable_3( void )
{
   i_avltree_t *tree = NULL;
   protocol_base_t *pb = NULL;

   tree = i_avltree_make();
   pb = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb != NULL );

   i_avltree_put( tree, 24 );

   CU_ASSERT( i_iterable_count( pb ) == 1 );

   i_avltree_dispose( &tree );

   return;
}

/**
   test_p_iterable_4
*/

void test_p_iterable_4( void )
{
   i_avltree_t *tree = NULL;
   protocol_base_t *pb = NULL;

   tree = i_avltree_make();
   pb = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb != NULL );

   i_avltree_put( tree, 24 );
   i_avltree_start( tree );

   CU_ASSERT( i_iterable_item( pb) == 24 );

   i_avltree_dispose( &tree );

   return;
}

/**
   test_p_iterable_5
*/

void test_p_iterable_5( void )
{
   i_avltree_t *tree = NULL;
   protocol_base_t *pb = NULL;

   tree = i_avltree_make();
   pb = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb != NULL );

   i_avltree_put( tree, 24 );

   CU_ASSERT( i_iterable_off( pb ) == 1 );

   i_avltree_dispose( &tree );

   return;
}

/**
   test_p_iterable_6
*/

void test_p_iterable_6( void )
{
   i_avltree_t *tree = NULL;
   protocol_base_t *pb = NULL;

   tree = i_avltree_make();
   pb = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb != NULL );

   CU_ASSERT( i_iterable_is_empty( pb ) == 1 );

   i_avltree_dispose( &tree );

   return;
}

/**
   test_p_iterable_7
*/

void test_p_iterable_7( void )
{
   i_avltree_t *tree = NULL;
   protocol_base_t *pb = NULL;

   tree = i_avltree_make();
   pb = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb != NULL );

   i_avltree_put( tree, 24 );
   i_iterable_start( pb );

   CU_ASSERT( i_iterable_item( pb) == 24 );

   i_avltree_dispose( &tree );

   return;
}

/**
   test_p_iterable_8
*/

void test_p_iterable_8( void )
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
   i_iterable_forth( pb );

   CU_ASSERT( i_iterable_item( pb) == 24 );

   i_avltree_dispose( &tree );

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

