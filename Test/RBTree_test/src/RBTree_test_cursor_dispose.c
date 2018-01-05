/**
 @file RBTree_test_cursor_dispose.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for RBTree_make"
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

#include "i_RBTree.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_cursor_dispose_1
*/

void test_cursor_dispose_1( void )
{
   i_rbtree_t *rbtree = NULL;
   i_rbtree_cursor_t *cursor = NULL;
   
   rbtree = i_rbtree_make();
   cursor = i_rbtree_cursor_make( rbtree );
   
   CU_ASSERT( cursor != NULL );

   i_rbtree_cursor_dispose( cursor );
   
   i_rbtree_dispose( rbtree );
   
   return;
}

/**
   test_cursor_dispose_2
*/

void test_cursor_dispose_2( void )
{
   i_rbtree_t *rbtree = NULL;
   i_rbtree_cursor_t *cursor1 = NULL;
   i_rbtree_cursor_t *cursor2 = NULL;

   rbtree = i_rbtree_make();
   cursor1 = i_rbtree_cursor_make( rbtree );
   cursor2 = i_rbtree_cursor_make( rbtree );

   CU_ASSERT( cursor1 != NULL );
   CU_ASSERT( cursor2 != NULL );

   i_rbtree_cursor_dispose( cursor2 );
   i_rbtree_cursor_dispose( cursor1 );

   i_rbtree_dispose( rbtree );
   
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

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

