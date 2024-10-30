/**
 @file BSTree_test_cursor_dispose.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BSTree_make"
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
   test_cursor_dispose_1
*/

void test_cursor_dispose_1( void )
{
   i_bstree_t *bstree = NULL;
   i_bstree_cursor_t *cursor = NULL;
   
   bstree = i_bstree_make();
   cursor = i_bstree_cursor_make( bstree );
   
   CU_ASSERT( cursor != NULL );

   i_bstree_cursor_dispose( &cursor );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_cursor_dispose_2
*/

void test_cursor_dispose_2( void )
{
   s_bstree_t *bstree = NULL;
   s_bstree_cursor_t *cursor = NULL;
   
   bstree = s_bstree_make();
   cursor = s_bstree_cursor_make( bstree );
   
   CU_ASSERT( cursor != NULL );

   s_bstree_cursor_dispose( &cursor );
   
   s_bstree_dispose( &bstree );

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

