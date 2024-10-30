/**
 @file RBTree_kv_test_cursor_index.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for RBTree_kv_cursor_item_at"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for RBTree_kv_t

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_RBTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_cursor_index_1
*/

void test_cursor_index_1( void )
{
   ii_rbtree_kv_t *rbtree = NULL;

   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_cursor_t *cursor = ii_rbtree_kv_cursor_make( rbtree );

   CU_ASSERT( ii_rbtree_kv_cursor_off( cursor ) == 1 );
   CU_ASSERT( ii_rbtree_kv_cursor_index( cursor ) == -1 );
   
   ii_rbtree_kv_put( rbtree, 240, 24 );
   ii_rbtree_kv_put( rbtree, 130, 13 );
   
   ii_rbtree_kv_cursor_start( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_index( cursor ) == 0 );
   
   ii_rbtree_kv_cursor_forth( cursor );

   CU_ASSERT( ii_rbtree_kv_cursor_index( cursor ) == 1 );

   ii_rbtree_kv_cursor_forth( cursor );

   CU_ASSERT( ii_rbtree_kv_cursor_index( cursor ) == -1 );

   ii_rbtree_kv_cursor_dispose( &cursor );
   ii_rbtree_kv_dispose( &rbtree );

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

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

