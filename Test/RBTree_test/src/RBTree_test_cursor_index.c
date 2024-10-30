/**
 @file RBTree_test_cursor_index.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for RBTree_cursor_item_at"
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

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_cursor_index_1
*/

void test_cursor_index_1( void )
{
   i_rbtree_t *tree = NULL;

   tree = i_rbtree_make();
   
   i_rbtree_cursor_t *cursor = i_rbtree_cursor_make( tree );

   CU_ASSERT( i_rbtree_cursor_off( cursor ) == 1 );
   CU_ASSERT( i_rbtree_cursor_index( cursor ) == -1 );
   
   i_rbtree_put( tree, 24 );
   i_rbtree_put( tree, 13 );
   
   i_rbtree_cursor_start( cursor );
   CU_ASSERT( i_rbtree_cursor_index( cursor ) == 0 );
   
   i_rbtree_cursor_forth( cursor );

   CU_ASSERT( i_rbtree_cursor_index( cursor ) == 1 );

   i_rbtree_cursor_forth( cursor );

   CU_ASSERT( i_rbtree_cursor_index( cursor ) == -1 );

   i_rbtree_cursor_dispose( &cursor );
   i_rbtree_dispose( &tree );

   return;
}

/**
   test_cursor_index_2
*/

void test_cursor_index_2( void )
{
   s_rbtree_t *rbtree = NULL;

   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   
   rbtree = s_rbtree_make();
   
   s_rbtree_cursor_t *cursor = s_rbtree_cursor_make( rbtree );

   CU_ASSERT( s_rbtree_cursor_off( cursor ) == 1 );
   CU_ASSERT( s_rbtree_cursor_index( cursor ) == -1 );
   
   s_rbtree_put( rbtree, s2 );
   s_rbtree_put( rbtree, s1 );
   
   s_rbtree_cursor_start( cursor );
   CU_ASSERT( s_rbtree_cursor_index( cursor ) == 0 );
   
   s_rbtree_cursor_forth( cursor );

   CU_ASSERT( s_rbtree_cursor_index( cursor ) == 1 );

   s_rbtree_cursor_forth( cursor );

   CU_ASSERT( s_rbtree_cursor_index( cursor ) == -1 );

   s_rbtree_cursor_dispose( &cursor );
   s_rbtree_deep_dispose( &rbtree );

   return;
}

int
add_test_cursor_index( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_cursor_index", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_cursor_index_1
   add_test_to_suite( p_suite, test_cursor_index_1, "test_cursor_index_1" );

   // test_cursor_index_2
   add_test_to_suite( p_suite, test_cursor_index_2, "test_cursor_index_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

