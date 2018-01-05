/**
 @file RBTree_test_cursor_forth.c
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

#include "ii_RBTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_cursor_forth_1
*/

void test_cursor_forth_1( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   ii_rbtree_kv_cursor_t *cursor = NULL;
   
   rbtree = ii_rbtree_kv_make();
   cursor = ii_rbtree_kv_cursor_make( rbtree );
   
   ii_rbtree_kv_put( rbtree, 10, 1 );
   
   ii_rbtree_kv_cursor_start( cursor );
   
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_off( cursor ) == 1 );
 
   ii_rbtree_kv_dispose( rbtree );
   
   return;
}

/**
   test_cursor_forth_2
*/

void test_cursor_forth_2( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   ii_rbtree_kv_cursor_t *cursor = NULL;
   
   rbtree = ii_rbtree_kv_make();
   cursor = ii_rbtree_kv_cursor_make( rbtree );
   
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   ii_rbtree_kv_cursor_start( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_item_at( cursor ) == 10 );
 
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_item_at( cursor ) == 20 );
 
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_item_at( cursor ) == 30 );
 
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_off( cursor ) == 1 );
 
   ii_rbtree_kv_dispose( rbtree );
   
   return;
}

/**
   test_cursor_forth_3
*/

void test_cursor_forth_3( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   ii_rbtree_kv_cursor_t *cursor = NULL;
   
   rbtree = ii_rbtree_kv_make();
   cursor = ii_rbtree_kv_cursor_make( rbtree );
   
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   
   ii_rbtree_kv_cursor_start( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_item_at( cursor ) == 10 );
 
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_item_at( cursor ) == 20 );
 
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_item_at( cursor ) == 30 );
 
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_off( cursor ) == 1 );
 
   ii_rbtree_kv_dispose( rbtree );
   
   return;
}

/**
   test_cursor_forth_4
*/

void test_cursor_forth_4( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   ii_rbtree_kv_cursor_t *cursor = NULL;
   
   rbtree = ii_rbtree_kv_make();
   cursor = ii_rbtree_kv_cursor_make( rbtree );
   
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   ii_rbtree_kv_cursor_start( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_item_at( cursor ) == 10 );
 
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_item_at( cursor ) == 20 );
 
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_item_at( cursor ) == 30 );
 
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_off( cursor ) == 1 );
 
   ii_rbtree_kv_dispose( rbtree );
   
   return;
}

/**
   test_cursor_forth_5
   
            4
         2      6
       1  
*/

void test_cursor_forth_5( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   ii_rbtree_kv_cursor_t *cursor = NULL;
   
   rbtree = ii_rbtree_kv_make();
   cursor = ii_rbtree_kv_cursor_make( rbtree );
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   
   ii_rbtree_kv_cursor_start( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_item_at( cursor ) == 10 );
 
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_item_at( cursor ) == 20 );
 
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_item_at( cursor ) == 40 );
 
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_item_at( cursor ) == 60 );
 
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_off( cursor ) == 1 );
  
   ii_rbtree_kv_dispose( rbtree );
   
   return;
}

/**
   test_cursor_forth_6
   
            4
         2      6
            3       
*/

void test_cursor_forth_6( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   ii_rbtree_kv_cursor_t *cursor = NULL;
   
   rbtree = ii_rbtree_kv_make();
   cursor = ii_rbtree_kv_cursor_make( rbtree );
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   ii_rbtree_kv_cursor_start( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_item_at( cursor ) == 20 );
 
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_item_at( cursor ) == 30 );
 
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_item_at( cursor ) == 40 );
 
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_item_at( cursor ) == 60 );
 
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_off( cursor ) == 1 );
 
   ii_rbtree_kv_dispose( rbtree );
   
   return;
}

/**
   test_cursor_forth_7
   
            4
         2      6
              5 
*/

void test_cursor_forth_7( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   ii_rbtree_kv_cursor_t *cursor = NULL;
   
   rbtree = ii_rbtree_kv_make();
   cursor = ii_rbtree_kv_cursor_make( rbtree );
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 50, 5 );
   
   ii_rbtree_kv_cursor_start( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_item_at( cursor ) == 20 );
 
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_item_at( cursor ) == 40 );
 
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_item_at( cursor ) == 50 );
 
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_item_at( cursor ) == 60 );
 
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_off( cursor ) == 1 );
 
   ii_rbtree_kv_dispose( rbtree );
   
   return;
}

/**
   test_cursor_forth_8
   
            4
         2      6
                  7   
*/

void test_cursor_forth_8( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   ii_rbtree_kv_cursor_t *cursor = NULL;
   
   rbtree = ii_rbtree_kv_make();
   cursor = ii_rbtree_kv_cursor_make( rbtree );
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 70, 7 );
   
   ii_rbtree_kv_cursor_start( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_item_at( cursor ) == 20 );
 
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_item_at( cursor ) == 40 );
 
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_item_at( cursor ) == 60 );
 
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_item_at( cursor ) == 70 );
 
   ii_rbtree_kv_cursor_forth( cursor );
   CU_ASSERT( ii_rbtree_kv_cursor_off( cursor ) == 1 );
 
   ii_rbtree_kv_dispose( rbtree );
   
   return;
}

int
add_test_cursor_forth( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_cursor_forth", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_cursor_forth_1
   add_test_to_suite( p_suite, test_cursor_forth_1, "test_cursor_forth_1" );

   // test_cursor_forth_2
   add_test_to_suite( p_suite, test_cursor_forth_2, "test_cursor_forth_2" );

   // test_cursor_forth_3
   add_test_to_suite( p_suite, test_cursor_forth_3, "test_cursor_forth_3" );

   // test_cursor_forth_4
   add_test_to_suite( p_suite, test_cursor_forth_4, "test_cursor_forth_4" );

   // test_cursor_forth_5
   add_test_to_suite( p_suite, test_cursor_forth_5, "test_cursor_forth_5" );

   // test_cursor_forth_6
   add_test_to_suite( p_suite, test_cursor_forth_6, "test_cursor_forth_6" );

   // test_cursor_forth_7
   add_test_to_suite( p_suite, test_cursor_forth_7, "test_cursor_forth_7" );

   // test_cursor_forth_8
   add_test_to_suite( p_suite, test_cursor_forth_8, "test_cursor_forth_8" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

