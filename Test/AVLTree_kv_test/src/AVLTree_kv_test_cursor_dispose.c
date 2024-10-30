/**
 @file AVLTree_test_cursor_dispose.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for AVLTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for AVLTree_kv_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_AVLTree_kv.h"
#include "ss_AVLTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_cursor_dispose_1
*/

void test_cursor_dispose_1( void )
{
   ii_avltree_kv_t *avltree = NULL;
   ii_avltree_kv_cursor_t *cursor = NULL;
   
   avltree = ii_avltree_kv_make();
   cursor = ii_avltree_kv_cursor_make( avltree );
   
   CU_ASSERT( cursor != NULL );

   ii_avltree_kv_cursor_dispose( &cursor );
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_cursor_dispose_2
*/

void test_cursor_dispose_2( void )
{
   ii_avltree_kv_t *avltree = NULL;
   ii_avltree_kv_cursor_t *cursor1 = NULL;
   ii_avltree_kv_cursor_t *cursor2 = NULL;

   avltree = ii_avltree_kv_make();
   cursor1 = ii_avltree_kv_cursor_make( avltree );
   cursor2 = ii_avltree_kv_cursor_make( avltree );

   CU_ASSERT( cursor1 != NULL );
   CU_ASSERT( cursor2 != NULL );

   ii_avltree_kv_cursor_dispose( &cursor2 );
   ii_avltree_kv_cursor_dispose( &cursor1 );
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_cursor_dispose_3
*/

void test_cursor_dispose_3( void )
{
   ss_avltree_kv_t *avltree = NULL;
   ss_avltree_kv_cursor_t *cursor = NULL;
   
   avltree = ss_avltree_kv_make();
   cursor = ss_avltree_kv_cursor_make( avltree );
   
   CU_ASSERT( cursor != NULL );

   ss_avltree_kv_cursor_dispose( &cursor );
   
   ss_avltree_kv_dispose( &avltree );

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

