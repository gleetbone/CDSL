/**
 @file BSTree_test_cursor_finish.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for BSTree_make"
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

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_cursor_finish_1
*/

void test_cursor_finish_1( void )
{
   ii_bstree_kv_t *bstree = NULL;
   ii_bstree_kv_cursor_t *cursor = NULL;
   
   bstree = ii_bstree_kv_make();
   cursor = ii_bstree_kv_cursor_make( bstree );
   
   ii_bstree_kv_put( bstree, 10, 1 );
   
   ii_bstree_kv_cursor_finish( cursor );
   
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 10 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}

/**
   test_cursor_finish_2
*/

void test_cursor_finish_2( void )
{
   ii_bstree_kv_t *bstree = NULL;
   ii_bstree_kv_cursor_t *cursor = NULL;
   
   bstree = ii_bstree_kv_make();
   cursor = ii_bstree_kv_cursor_make( bstree );
   
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   ii_bstree_kv_cursor_finish( cursor );
   
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 30 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}

/**
   test_cursor_finish_3
*/

void test_cursor_finish_3( void )
{
   ii_bstree_kv_t *bstree = NULL;
   ii_bstree_kv_cursor_t *cursor = NULL;
   
   bstree = ii_bstree_kv_make();
   cursor = ii_bstree_kv_cursor_make( bstree );
   
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   
   ii_bstree_kv_cursor_finish( cursor );
   
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 30 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}

/**
   test_cursor_finish_4
*/

void test_cursor_finish_4( void )
{
   ii_bstree_kv_t *bstree = NULL;
   ii_bstree_kv_cursor_t *cursor = NULL;
   
   bstree = ii_bstree_kv_make();
   cursor = ii_bstree_kv_cursor_make( bstree );
   
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   ii_bstree_kv_cursor_finish( cursor );
   
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 30 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}

/**
   test_cursor_finish_5
   
            4
         2      6
       1  
*/

void test_cursor_finish_5( void )
{
   ii_bstree_kv_t *bstree = NULL;
   ii_bstree_kv_cursor_t *cursor = NULL;
   
   bstree = ii_bstree_kv_make();
   cursor = ii_bstree_kv_cursor_make( bstree );
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 10, 1 );
   
   ii_bstree_kv_cursor_finish( cursor );
   
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 60 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}

/**
   test_cursor_finish_6
   
            4
         2      6
            3       
*/

void test_cursor_finish_6( void )
{
   ii_bstree_kv_t *bstree = NULL;
   ii_bstree_kv_cursor_t *cursor = NULL;
   
   bstree = ii_bstree_kv_make();
   cursor = ii_bstree_kv_cursor_make( bstree );
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   ii_bstree_kv_cursor_finish( cursor );
   
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 60 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}


int
add_test_cursor_finish( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_cursor_finish", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_cursor_finish_1
   add_test_to_suite( p_suite, test_cursor_finish_1, "test_cursor_finish_1" );

   // test_cursor_finish_2
   add_test_to_suite( p_suite, test_cursor_finish_2, "test_cursor_finish_2" );

   // test_cursor_finish_3
   add_test_to_suite( p_suite, test_cursor_finish_3, "test_cursor_finish_3" );

   // test_cursor_finish_4
   add_test_to_suite( p_suite, test_cursor_finish_4, "test_cursor_finish_4" );

   // test_cursor_finish_5
   add_test_to_suite( p_suite, test_cursor_finish_5, "test_cursor_finish_5" );

   // test_cursor_finish_6
   add_test_to_suite( p_suite, test_cursor_finish_6, "test_cursor_finish_6" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

