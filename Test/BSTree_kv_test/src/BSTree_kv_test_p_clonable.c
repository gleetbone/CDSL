/**
 @file BSTree_test_p_clonable.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for BSTree P_Clonable"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for BSTree_make.

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_BSTree_kv.h"
#include "Protocol_Base.h"
#include "i_Clonable.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_p_clonable_1
*/

void test_p_clonable_1( void )
{
   ii_bstree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;
   
   tree = ii_bstree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;
   
   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   CU_ASSERT( i_clonable_dispose_f( pb_tree ) == ii_bstree_kv_dispose );

   i_clonable_dispose( pb_tree );
 
   return;
}

/**
   test_p_clonable_2
*/

void test_p_clonable_2( void )
{
   ii_bstree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = ii_bstree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   CU_ASSERT( i_clonable_dispose_with_contents_f( pb_tree ) == ii_bstree_kv_dispose_with_contents );

   i_clonable_dispose_with_contents( pb_tree );

   return;
}

/**
   test_p_clonable_3
*/

void test_p_clonable_3( void )
{
   ii_bstree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;
   protocol_base_t *pb_tree1 = NULL;

   tree = ii_bstree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   pb_tree1 = i_clonable_clone( pb_tree );
   CU_ASSERT( pb_tree1 != NULL );

   CU_ASSERT( i_clonable_clone_f( pb_tree ) == ii_bstree_kv_make_from );

   i_clonable_dispose( pb_tree );
   i_clonable_dispose( pb_tree1 );

   return;
}

/**
   test_p_clonable_4
*/

void test_p_clonable_4( void )
{
   ii_bstree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;
   protocol_base_t *pb_tree1 = NULL;

   tree = ii_bstree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   pb_tree1 = i_clonable_deep_clone( pb_tree );
   CU_ASSERT( pb_tree1 != NULL );

   CU_ASSERT( i_clonable_deep_clone_f( pb_tree ) == ii_bstree_kv_make_duplicate_from );

   i_clonable_dispose( pb_tree );
   i_clonable_dispose( pb_tree1 );

   return;
}

int
add_test_p_clonable( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_p_clonable", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_p_clonable_1
   add_test_to_suite( p_suite, test_p_clonable_1, "test_p_clonable_1" );

   // test_p_clonable_2
   add_test_to_suite( p_suite, test_p_clonable_2, "test_p_clonable_2" );

   // test_p_clonable_3
   add_test_to_suite( p_suite, test_p_clonable_3, "test_p_clonable_3" );

   // test_p_clonable_4
   add_test_to_suite( p_suite, test_p_clonable_4, "test_p_clonable_4" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

