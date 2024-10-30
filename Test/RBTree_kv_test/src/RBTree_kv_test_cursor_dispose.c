/**
 @file RBTree_test_cursor_dispose.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for RBTree_make"
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
#include "ss_RBTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_cursor_dispose_1
*/

void test_cursor_dispose_1( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   ii_rbtree_kv_cursor_t *cursor = NULL;
   
   rbtree = ii_rbtree_kv_make();
   cursor = ii_rbtree_kv_cursor_make( rbtree );
   
   CU_ASSERT( cursor != NULL );

   ii_rbtree_kv_cursor_dispose( &cursor );
   
   ii_rbtree_kv_dispose( &rbtree );
   
   return;
}

/**
   test_cursor_dispose_2
*/

void test_cursor_dispose_2( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   ii_rbtree_kv_cursor_t *cursor1 = NULL;
   ii_rbtree_kv_cursor_t *cursor2 = NULL;

   rbtree = ii_rbtree_kv_make();
   cursor1 = ii_rbtree_kv_cursor_make( rbtree );
   cursor2 = ii_rbtree_kv_cursor_make( rbtree );

   CU_ASSERT( cursor1 != NULL );
   CU_ASSERT( cursor2 != NULL );

   ii_rbtree_kv_cursor_dispose( &cursor2 );
   ii_rbtree_kv_cursor_dispose( &cursor1 );

   ii_rbtree_kv_dispose( &rbtree );
   
   return;
}

/**
   test_cursor_dispose_3
*/

void test_cursor_dispose_3( void )
{
   ss_rbtree_kv_t *rbtree = NULL;
   ss_rbtree_kv_cursor_t *cursor = NULL;
   
   rbtree = ss_rbtree_kv_make();
   cursor = ss_rbtree_kv_cursor_make( rbtree );
   
   CU_ASSERT( cursor != NULL );

   ss_rbtree_kv_cursor_dispose( &cursor );
   
   ss_rbtree_kv_dispose( &rbtree );

   return;
}

int
add_test_cursor_dispose( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_cursor_dispose", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_cursor_dispose_1
   add_test_to_suite( p_suite, test_cursor_dispose_1, "test_cursor_dispose_1" );

   // test_cursor_dispose_2
   add_test_to_suite( p_suite, test_cursor_dispose_2, "test_cursor_dispose_2" );

   // test_cursor_dispose_3
   add_test_to_suite( p_suite, test_cursor_dispose_3, "test_cursor_dispose_3" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

