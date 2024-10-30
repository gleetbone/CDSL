/**
 @file BSTree_test_cursor_index.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BSTree_cursor_item_at"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for BSTree_t

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_BSTree.h"
#include "s_BSTree.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_cursor_index_1
*/

void test_cursor_index_1( void )
{
   i_bstree_t *bstree = NULL;

   bstree = i_bstree_make();
   
   i_bstree_cursor_t *cursor = i_bstree_cursor_make( bstree );

   CU_ASSERT( i_bstree_cursor_off( cursor ) == 1 );
   CU_ASSERT( i_bstree_cursor_index( cursor ) == -1 );
   
   i_bstree_put( bstree, 24 );
   i_bstree_put( bstree, 13 );
   
   i_bstree_cursor_start( cursor );
   CU_ASSERT( i_bstree_cursor_index( cursor ) == 0 );
   
   i_bstree_cursor_forth( cursor );

   CU_ASSERT( i_bstree_cursor_index( cursor ) == 1 );

   i_bstree_cursor_forth( cursor );

   CU_ASSERT( i_bstree_cursor_index( cursor ) == -1 );

   i_bstree_cursor_dispose( &cursor );
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_cursor_index_2
*/

void test_cursor_index_2( void )
{
   s_bstree_t *bstree = NULL;

   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   
   bstree = s_bstree_make();
   
   s_bstree_cursor_t *cursor = s_bstree_cursor_make( bstree );

   CU_ASSERT( s_bstree_cursor_off( cursor ) == 1 );
   CU_ASSERT( s_bstree_cursor_index( cursor ) == -1 );
   
   s_bstree_put( bstree, s2 );
   s_bstree_put( bstree, s1 );
   
   s_bstree_cursor_start( cursor );
   CU_ASSERT( s_bstree_cursor_index( cursor ) == 0 );
   
   s_bstree_cursor_forth( cursor );

   CU_ASSERT( s_bstree_cursor_index( cursor ) == 1 );

   s_bstree_cursor_forth( cursor );

   CU_ASSERT( s_bstree_cursor_index( cursor ) == -1 );

   s_bstree_cursor_dispose( &cursor );
   s_bstree_deep_dispose( &bstree );

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

