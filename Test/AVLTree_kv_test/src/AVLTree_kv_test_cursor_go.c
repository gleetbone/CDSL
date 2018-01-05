/**
 @file AVLTree_test_cursor_go.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for AVLTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for AVLTree_make.

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_AVLTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_cursor_go_1
*/

void test_cursor_go_1( void )
{
   ii_avltree_kv_t *avltree = NULL;
   ii_avltree_kv_cursor_t *cursor = NULL;
   
   avltree = ii_avltree_kv_make();
   cursor = ii_avltree_kv_cursor_make( avltree );
   
   ii_avltree_kv_put( avltree, 10, 1 );
   
   ii_avltree_kv_cursor_go( cursor, 0 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 10 );
   
   ii_avltree_kv_cursor_dispose( cursor );
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_cursor_go_2
*/

void test_cursor_go_2( void )
{
   ii_avltree_kv_t *avltree = NULL;
   ii_avltree_kv_cursor_t *cursor = NULL;
   
   avltree = ii_avltree_kv_make();
   cursor = ii_avltree_kv_cursor_make( avltree );
   
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   ii_avltree_kv_cursor_go( cursor, 0 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 10 );
 
   ii_avltree_kv_cursor_go( cursor, 1 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 20 );
 
   ii_avltree_kv_cursor_go( cursor, 2 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 30 );
 
   ii_avltree_kv_cursor_dispose( cursor );
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_cursor_go_3
*/

void test_cursor_go_3( void )
{
   ii_avltree_kv_t *avltree = NULL;
   ii_avltree_kv_cursor_t *cursor = NULL;
   
   avltree = ii_avltree_kv_make();
   cursor = ii_avltree_kv_cursor_make( avltree );
   
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   
   ii_avltree_kv_cursor_go( cursor, 0 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 10 );
 
   ii_avltree_kv_cursor_go( cursor, 1 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 20 );
 
   ii_avltree_kv_cursor_go( cursor, 2 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 30 );
 
   ii_avltree_kv_cursor_dispose( cursor );
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_cursor_go_4
*/

void test_cursor_go_4( void )
{
   ii_avltree_kv_t *avltree = NULL;
   ii_avltree_kv_cursor_t *cursor = NULL;
   
   avltree = ii_avltree_kv_make();
   cursor = ii_avltree_kv_cursor_make( avltree );
   
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   ii_avltree_kv_cursor_go( cursor, 0 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 10 );
 
   ii_avltree_kv_cursor_go( cursor, 1 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 20 );
 
   ii_avltree_kv_cursor_go( cursor, 2 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 30 );
 
   ii_avltree_kv_cursor_dispose( cursor );
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_cursor_go_5
   
            4
         2      6
       1  
*/

void test_cursor_go_5( void )
{
   ii_avltree_kv_t *avltree = NULL;
   ii_avltree_kv_cursor_t *cursor = NULL;
   
   avltree = ii_avltree_kv_make();
   cursor = ii_avltree_kv_cursor_make( avltree );
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 10, 1 );
   
   ii_avltree_kv_cursor_go( cursor, 0 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 10 );
 
   ii_avltree_kv_cursor_go( cursor, 1 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 20 );
 
   ii_avltree_kv_cursor_go( cursor, 2 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 40 );
 
   ii_avltree_kv_cursor_go( cursor, 3 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 60 );
 
   ii_avltree_kv_cursor_dispose( cursor );
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_cursor_go_6
   
            4
         2      6
            3       
*/

void test_cursor_go_6( void )
{
   ii_avltree_kv_t *avltree = NULL;
   ii_avltree_kv_cursor_t *cursor = NULL;
   
   avltree = ii_avltree_kv_make();
   cursor = ii_avltree_kv_cursor_make( avltree );
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   ii_avltree_kv_cursor_go( cursor, 0 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 20 );
 
   ii_avltree_kv_cursor_go( cursor, 1 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 30 );
 
   ii_avltree_kv_cursor_go( cursor, 2 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 40 );
 
   ii_avltree_kv_cursor_go( cursor, 3 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 60 );
 
   ii_avltree_kv_cursor_dispose( cursor );
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_cursor_go_7
   
            4
         2      6
              5 
*/

void test_cursor_go_7( void )
{
   ii_avltree_kv_t *avltree = NULL;
   ii_avltree_kv_cursor_t *cursor = NULL;
   
   avltree = ii_avltree_kv_make();
   cursor = ii_avltree_kv_cursor_make( avltree );
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 50, 5 );
   
   ii_avltree_kv_cursor_go( cursor, 0 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 20 );
 
   ii_avltree_kv_cursor_go( cursor, 1 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 40 );
 
   ii_avltree_kv_cursor_go( cursor, 2 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 50 );
 
   ii_avltree_kv_cursor_go( cursor, 3 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 60 );
 
   ii_avltree_kv_cursor_dispose( cursor );
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_cursor_go_8
   
            4
         2      6
                  7   
*/

void test_cursor_go_8( void )
{
   ii_avltree_kv_t *avltree = NULL;
   ii_avltree_kv_cursor_t *cursor = NULL;
   
   avltree = ii_avltree_kv_make();
   cursor = ii_avltree_kv_cursor_make( avltree );
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 70, 7 );
   
   ii_avltree_kv_cursor_go( cursor, 0 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 20 );
 
   ii_avltree_kv_cursor_go( cursor, 1 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 40 );
 
   ii_avltree_kv_cursor_go( cursor, 2 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 60 );

   ii_avltree_kv_cursor_go( cursor, 3 );
   CU_ASSERT( ii_avltree_kv_cursor_item_at( cursor ) == 70 );
 
   ii_avltree_kv_cursor_dispose( cursor );
   ii_avltree_kv_dispose( avltree );

   return;
}

int
add_test_cursor_go( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_cursor_go", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_cursor_go_1
   add_test_to_suite( p_suite, test_cursor_go_1, "test_cursor_go_1" );

   // test_cursor_go_2
   add_test_to_suite( p_suite, test_cursor_go_2, "test_cursor_go_2" );

   // test_cursor_go_3
   add_test_to_suite( p_suite, test_cursor_go_3, "test_cursor_go_3" );

   // test_cursor_go_4
   add_test_to_suite( p_suite, test_cursor_go_4, "test_cursor_go_4" );

   // test_cursor_go_5
   add_test_to_suite( p_suite, test_cursor_go_5, "test_cursor_go_5" );

   // test_cursor_go_6
   add_test_to_suite( p_suite, test_cursor_go_6, "test_cursor_go_6" );

   // test_cursor_go_7
   add_test_to_suite( p_suite, test_cursor_go_7, "test_cursor_go_7" );

   // test_cursor_go_8
   add_test_to_suite( p_suite, test_cursor_go_8, "test_cursor_go_8" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

