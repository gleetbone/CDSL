/**
 @file RBTree_test_p_iterable_kv.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for RBTree P_Iterable"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for RBTree_make.

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_RBTree_kv.h"
#include "Protocol_Base.h"
#include "ii_Iterable_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_p_iterable_kv_1
*/

void test_p_iterable_kv_1( void )
{
   ii_rbtree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;
   
   tree = ii_rbtree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;
   
   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   CU_ASSERT( ii_iterable_kv_dispose_f( pb_tree ) == ii_rbtree_kv_dispose );

   ii_iterable_kv_dispose( pb_tree );
 
   return;
}

/**
   test_p_iterable_kv_2
*/

void test_p_iterable_kv_2( void )
{
   ii_rbtree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = ii_rbtree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   CU_ASSERT( ii_iterable_kv_dispose_with_contents_f( pb_tree ) == ii_rbtree_kv_dispose_with_contents );

   ii_iterable_kv_dispose_with_contents( pb_tree );

   return;
}

/**
   test_p_iterable_kv_3
*/

void test_p_iterable_kv_3( void )
{
   ii_rbtree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = ii_rbtree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   ii_rbtree_kv_put( tree, 24, 240 );

   CU_ASSERT( ii_iterable_kv_count_f( pb_tree ) == ii_rbtree_kv_count );
   CU_ASSERT( ii_iterable_kv_count( pb_tree ) == 1 );

   ii_iterable_kv_dispose( pb_tree );

   return;
}

/**
   test_p_iterable_kv_4
*/

void test_p_iterable_kv_4( void )
{
   ii_rbtree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = ii_rbtree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   ii_rbtree_kv_put( tree, 24, 240 );
   ii_rbtree_kv_start( tree );

   CU_ASSERT( ii_iterable_kv_value_f( pb_tree ) == ii_rbtree_kv_item_at );
   CU_ASSERT( ii_iterable_kv_value( pb_tree) == 24 );

   ii_iterable_kv_dispose( pb_tree );

   return;
}

/**
   test_p_iterable_kv_4a
*/

void test_p_iterable_kv_4a( void )
{
   ii_rbtree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = ii_rbtree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   ii_rbtree_kv_put( tree, 24, 240 );
   ii_rbtree_kv_start( tree );

   CU_ASSERT( ii_iterable_kv_key_f( pb_tree ) == ii_rbtree_kv_key_at );
   CU_ASSERT( ii_iterable_kv_key( pb_tree) == 240 );

   ii_iterable_kv_dispose( pb_tree );

   return;
}

/**
   test_p_iterable_kv_5
*/

void test_p_iterable_kv_5( void )
{
   ii_rbtree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = ii_rbtree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   ii_rbtree_kv_put( tree, 24, 240 );

   CU_ASSERT( ii_iterable_kv_off_f( pb_tree ) == ii_rbtree_kv_off );
   CU_ASSERT( ii_iterable_kv_off( pb_tree ) == 1 );

   ii_iterable_kv_dispose( pb_tree );

   return;
}

/**
   test_p_iterable_kv_6
*/

void test_p_iterable_kv_6( void )
{
   ii_rbtree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = ii_rbtree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   CU_ASSERT( ii_iterable_kv_is_empty_f( pb_tree ) == ii_rbtree_kv_is_empty );
   CU_ASSERT( ii_iterable_kv_is_empty( pb_tree ) == 1 );

   ii_iterable_kv_dispose( pb_tree );

   return;
}

/**
   test_p_iterable_kv_7
*/

void test_p_iterable_kv_7( void )
{
   ii_rbtree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = ii_rbtree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   ii_rbtree_kv_put( tree, 24, 240 );
   ii_iterable_kv_start( pb_tree );

   CU_ASSERT( ii_iterable_kv_value_f( pb_tree ) == ii_rbtree_kv_item_at );
   CU_ASSERT( ii_iterable_kv_value( pb_tree) == 24 );

   ii_iterable_kv_dispose( pb_tree );

   return;
}

/**
   test_p_iterable_kv_8
*/

void test_p_iterable_kv_8( void )
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
   ii_iterable_kv_forth( pb_tree );

   CU_ASSERT( ii_iterable_kv_forth_f( pb_tree ) == ii_rbtree_kv_forth );
   CU_ASSERT( ii_iterable_kv_value( pb_tree) == 24 );

   ii_iterable_kv_dispose( pb_tree );

   return;
}

int
add_test_p_iterable_kv( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_p_iterable_kv", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_p_iterable_kv_1
   add_test_to_suite( p_suite, test_p_iterable_kv_1, "test_p_iterable_kv_1" );

   // test_p_iterable_kv_2
   add_test_to_suite( p_suite, test_p_iterable_kv_2, "test_p_iterable_kv_2" );

   // test_p_iterable_kv_3
   add_test_to_suite( p_suite, test_p_iterable_kv_3, "test_p_iterable_kv_3" );

   // test_p_iterable_kv_4
   add_test_to_suite( p_suite, test_p_iterable_kv_4, "test_p_iterable_kv_4" );

   // test_p_iterable_kv_4a
   add_test_to_suite( p_suite, test_p_iterable_kv_4a, "test_p_iterable_kv_4a" );

   // test_p_iterable_kv_5
   add_test_to_suite( p_suite, test_p_iterable_kv_5, "test_p_iterable_kv_5" );

   // test_p_iterable_kv_6
   add_test_to_suite( p_suite, test_p_iterable_kv_6, "test_p_iterable_kv_6" );

   // test_p_iterable_kv_7
   add_test_to_suite( p_suite, test_p_iterable_kv_7, "test_p_iterable_kv_7" );

   // test_p_iterable_kv_8
   add_test_to_suite( p_suite, test_p_iterable_kv_8, "test_p_iterable_kv_8" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

