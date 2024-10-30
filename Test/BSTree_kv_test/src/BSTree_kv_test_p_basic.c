/**
 @file BSTree_test_p_basic.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BSTree P_Basic"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for BSTree_kv_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_BSTree_kv.h"
#include "ss_BSTree_kv.h"
#include "Protocol_Base.h"
#include "p_Basic.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_p_basic_1
*/

void test_p_basic_1( void )
{
   ii_bstree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;
   
   tree = ii_bstree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;
   
   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   p_basic_dispose( &pb_tree );
 
   return;
}

/**
   test_p_basic_2
*/

void test_p_basic_2( void )
{
   ii_bstree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;

   tree = ii_bstree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   p_basic_deep_dispose( &pb_tree );

   return;
}

/**
   test_p_basic_3
*/

void test_p_basic_3( void )
{
   ii_bstree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;
   protocol_base_t *pb_tree1 = NULL;

   tree = ii_bstree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   pb_tree1 = p_basic_clone( pb_tree );
   CU_ASSERT( pb_tree1 != NULL );

   p_basic_dispose( &pb_tree );
   p_basic_dispose( &pb_tree1 );

   return;
}

/**
   test_p_basic_4
*/

void test_p_basic_4( void )
{
   ii_bstree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;
   protocol_base_t *pb_tree1 = NULL;

   tree = ii_bstree_kv_make();
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   pb_tree1 = p_basic_deep_clone( pb_tree );
   CU_ASSERT( pb_tree1 != NULL );

   p_basic_dispose( &pb_tree );
   p_basic_dispose( &pb_tree1 );

   return;
}

/**
   test_p_basic_5
*/

void test_p_basic_5( void )
{
   ss_bstree_kv_t *tree = NULL;
   protocol_base_t *pb_tree = NULL;
   protocol_base_t *pb_tree1 = NULL;

   string_t *s1 = NULL;
   string_t *s10 = NULL;
   
   s1 = string_make_from_cstring( "1" );
   s10 = string_make_from_cstring( "10" );
   
   tree = ss_bstree_kv_make();
   ss_bstree_kv_put( tree, s10, s1 );
   
   pb_tree = ( protocol_base_t * ) tree;

   CU_ASSERT( tree != NULL );
   CU_ASSERT( pb_tree != NULL );

   pb_tree1 = p_basic_deep_clone( pb_tree );
   CU_ASSERT( pb_tree1 != NULL );

   p_basic_deep_dispose( &pb_tree );
   p_basic_deep_dispose( &pb_tree1 );

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

