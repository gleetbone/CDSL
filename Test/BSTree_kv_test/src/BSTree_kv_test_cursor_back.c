/**
 @file BSTree_test_cursor_back.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BSTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for BSTree_kv_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_BSTree_kv.h"
#include "ss_BSTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_cursor_back_1
*/

void test_cursor_back_1( void )
{
   ii_bstree_kv_t *bstree = NULL;
   ii_bstree_kv_cursor_t *cursor = NULL;
   
   bstree = ii_bstree_kv_make();
   cursor = ii_bstree_kv_cursor_make( bstree );
   
   ii_bstree_kv_put( bstree, 10, 1 );
   
   ii_bstree_kv_cursor_finish( cursor );
   
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_off( cursor ) == 1 );
 
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_cursor_back_2
*/

void test_cursor_back_2( void )
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
 
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 20 );
 
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 10 );
 
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_off( cursor ) == 1 );
 
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_cursor_back_3
*/

void test_cursor_back_3( void )
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
 
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 20 );
 
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 10 );
 
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_off( cursor ) == 1 );
 
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_cursor_back_4
*/

void test_cursor_back_4( void )
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
 
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 20 );
 
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 10 );
 
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_off( cursor ) == 1 );
 
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_cursor_back_5
   
            4
         2      6
       1  
*/

void test_cursor_back_5( void )
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
 
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 40 );
 
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 20 );
 
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 10 );
 
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_off( cursor ) == 1 );
  
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_cursor_back_6
   
            4
         2      6
            3       
*/

void test_cursor_back_6( void )
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
 
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 40 );
 
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 30 );
 
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 20 );
 
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_off( cursor ) == 1 );
 
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_cursor_back_7
   
            4
         2      6
              5 
*/

void test_cursor_back_7( void )
{
   ii_bstree_kv_t *bstree = NULL;
   ii_bstree_kv_cursor_t *cursor = NULL;
   
   bstree = ii_bstree_kv_make();
   cursor = ii_bstree_kv_cursor_make( bstree );
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 50, 5 );
   
   ii_bstree_kv_cursor_finish( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 60 );
 
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 50 );
 
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 40 );
 
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 20 );
 
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_off( cursor ) == 1 );
 
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_cursor_back_8
   
            4
         2      6
                  7   
*/

void test_cursor_back_8( void )
{
   ii_bstree_kv_t *bstree = NULL;
   ii_bstree_kv_cursor_t *cursor = NULL;
   
   bstree = ii_bstree_kv_make();
   cursor = ii_bstree_kv_cursor_make( bstree );
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 70, 7 );
   
   ii_bstree_kv_cursor_finish( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 70 );
 
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 60 );
 
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 40 );
 
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_item_at( cursor ) == 20 );
 
   ii_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ii_bstree_kv_cursor_off( cursor ) == 1 );
 
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_cursor_back_9
*/

void test_cursor_back_9( void )
{
   ss_bstree_kv_t *bstree = NULL;
   ss_bstree_kv_cursor_t *cursor = NULL;
   
   string_t *s2 = NULL;
   string_t *s20 = NULL;
   string_t *s4 = NULL;
   string_t *s40 = NULL;
   string_t *s6 = NULL;
   string_t *s60 = NULL;
   string_t *s7 = NULL;
   string_t *s70 = NULL;
   
   s2 = string_make_from_cstring( "2" );
   s20 = string_make_from_cstring( "20" );
   s4 = string_make_from_cstring( "4" );
   s40 = string_make_from_cstring( "40" );
   s6 = string_make_from_cstring( "6" );
   s60 = string_make_from_cstring( "60" );
   s7 = string_make_from_cstring( "7" );
   s70 = string_make_from_cstring( "70" );
   
   bstree = ss_bstree_kv_make();
   cursor = ss_bstree_kv_cursor_make( bstree );
   
   ss_bstree_kv_put( bstree, s40, s4 );
   ss_bstree_kv_put( bstree, s20, s2 );
   ss_bstree_kv_put( bstree, s60, s6 );
   ss_bstree_kv_put( bstree, s70, s7 );
   
   ss_bstree_kv_cursor_finish( cursor );
   CU_ASSERT( ss_bstree_kv_cursor_item_at( cursor ) == s70 );
 
   ss_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ss_bstree_kv_cursor_item_at( cursor ) == s60 );
 
   ss_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ss_bstree_kv_cursor_item_at( cursor ) == s40 );
 
   ss_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ss_bstree_kv_cursor_item_at( cursor ) == s20 );
 
   ss_bstree_kv_cursor_back( cursor );
   CU_ASSERT( ss_bstree_kv_cursor_off( cursor ) == 1 );
 
   ss_bstree_kv_deep_dispose( &bstree );

   return;
}

int
add_test_cursor_back( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_cursor_back", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_cursor_back_1
   add_test_to_suite( p_suite, test_cursor_back_1, "test_cursor_back_1" );

   // test_cursor_back_2
   add_test_to_suite( p_suite, test_cursor_back_2, "test_cursor_back_2" );

   // test_cursor_back_3
   add_test_to_suite( p_suite, test_cursor_back_3, "test_cursor_back_3" );

   // test_cursor_back_4
   add_test_to_suite( p_suite, test_cursor_back_4, "test_cursor_back_4" );

   // test_cursor_back_5
   add_test_to_suite( p_suite, test_cursor_back_5, "test_cursor_back_5" );

   // test_cursor_back_6
   add_test_to_suite( p_suite, test_cursor_back_6, "test_cursor_back_6" );

   // test_cursor_back_7
   add_test_to_suite( p_suite, test_cursor_back_7, "test_cursor_back_7" );

   // test_cursor_back_8
   add_test_to_suite( p_suite, test_cursor_back_8, "test_cursor_back_8" );

   // test_cursor_back_9
   add_test_to_suite( p_suite, test_cursor_back_9, "test_cursor_back_9" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

