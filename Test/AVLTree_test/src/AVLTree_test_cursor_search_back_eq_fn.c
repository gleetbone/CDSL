/**
 @file AVLTree_test_cursor_search_back_eq_fn.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for AVLTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for AVLTree_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_AVLTree.h"
#include "s_AVLTree.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

static int32_t is_equal_int( int32_t i1, int32_t i2 )
{
   return ( i1 == i2 );
}

static int32_t is_equal_s( string_t *s1, string_t *s2 )
{
   return ( string_is_equal( s1, s2 ) == 1 );
}

/**
   test_cursor_search_back_eq_fn_1
*/

void test_cursor_search_back_eq_fn_1( void )
{
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );
   
   i_avltree_cursor_finish( cursor );
   i_avltree_cursor_search_back_eq_fn( cursor, 1, is_equal_int );
   CU_ASSERT( i_avltree_cursor_off( cursor ) == 1 );
 
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_cursor_search_back_eq_fn_2
*/

void test_cursor_search_back_eq_fn_2( void )
{
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );
   
   i_avltree_put( avltree, 1 );
   
   i_avltree_cursor_finish( cursor );
   i_avltree_cursor_search_back_eq_fn( cursor, 1, is_equal_int );
   CU_ASSERT( i_avltree_cursor_off( cursor ) == 0 );
   CU_ASSERT( i_avltree_cursor_item_at( cursor ) == 1 );
   CU_ASSERT( i_avltree_cursor_index( cursor) == 0 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_cursor_search_back_eq_fn_3
*/

void test_cursor_search_back_eq_fn_3( void )
{
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );
   
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   
   i_avltree_cursor_finish( cursor );
   i_avltree_cursor_search_back_eq_fn( cursor, 2, is_equal_int );
   CU_ASSERT( i_avltree_cursor_off( cursor ) == 0 );
   CU_ASSERT( i_avltree_cursor_item_at( cursor ) == 2 );
   CU_ASSERT( i_avltree_cursor_index( cursor ) == 1 );

   i_avltree_cursor_search_back_eq_fn( cursor, 2, is_equal_int );
   CU_ASSERT( i_avltree_cursor_off( cursor ) == 0 );
   CU_ASSERT( i_avltree_cursor_item_at( cursor ) == 2 );
   CU_ASSERT( i_avltree_cursor_index( cursor ) == 1 );

   i_avltree_cursor_back( cursor );
   i_avltree_cursor_search_back_eq_fn( cursor, 2, is_equal_int );
   CU_ASSERT( i_avltree_cursor_off( cursor ) == 1 );
 
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_cursor_search_back_eq_fn_4
*/

void test_cursor_search_back_eq_fn_4( void )
{
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );
   
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 2 );
   
   i_avltree_cursor_finish( cursor );
   i_avltree_cursor_search_back_eq_fn( cursor, 2, is_equal_int );
   CU_ASSERT( i_avltree_cursor_off( cursor ) == 0 );
   CU_ASSERT( i_avltree_cursor_item_at( cursor ) == 2 );
   CU_ASSERT( i_avltree_cursor_index( cursor ) == 2 );

   i_avltree_cursor_search_back_eq_fn( cursor, 2, is_equal_int );
   CU_ASSERT( i_avltree_cursor_off( cursor ) == 0 );
   CU_ASSERT( i_avltree_cursor_item_at( cursor ) == 2 );
   CU_ASSERT( i_avltree_cursor_index( cursor ) == 2 );

   i_avltree_cursor_back( cursor );
   i_avltree_cursor_search_back_eq_fn( cursor, 2, is_equal_int );
   CU_ASSERT( i_avltree_cursor_off( cursor ) == 0 );
   CU_ASSERT( i_avltree_cursor_item_at( cursor ) == 2 );
   CU_ASSERT( i_avltree_cursor_index( cursor ) == 1 );

   i_avltree_cursor_back( cursor );
   i_avltree_cursor_search_back_eq_fn( cursor, 2, is_equal_int );
   CU_ASSERT( i_avltree_cursor_off( cursor ) == 1 );
 
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_cursor_search_back_eq_fn_5
*/

void test_cursor_search_back_eq_fn_5( void )
{
   s_avltree_t *avltree = NULL;
   s_avltree_cursor_t *cursor = NULL;
   
   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s2a = string_make_from_cstring( "2" );
   string_t *s3 = string_make_from_cstring( "3" );
   
   avltree = s_avltree_make();
   cursor = s_avltree_cursor_make( avltree );
   
   s_avltree_put( avltree, s1 );
   s_avltree_put( avltree, s2 );
   s_avltree_put( avltree, s3 );
   s_avltree_put( avltree, s2a );
   
   s_avltree_cursor_finish( cursor );
   s_avltree_cursor_search_back_eq_fn( cursor, s2, is_equal_s );
   CU_ASSERT( s_avltree_cursor_off( cursor ) == 0 );
   CU_ASSERT( s_avltree_cursor_item_at( cursor ) == s2 );
   CU_ASSERT( s_avltree_cursor_index( cursor ) == 2 );

   s_avltree_cursor_search_back_eq_fn( cursor, s2, is_equal_s );
   CU_ASSERT( s_avltree_cursor_off( cursor ) == 0 );
   CU_ASSERT( s_avltree_cursor_item_at( cursor ) == s2 );
   CU_ASSERT( s_avltree_cursor_index( cursor ) == 2 );

   s_avltree_cursor_back( cursor );
   s_avltree_cursor_search_back_eq_fn( cursor, s2, is_equal_s );
   CU_ASSERT( s_avltree_cursor_off( cursor ) == 0 );
   CU_ASSERT( s_avltree_cursor_item_at( cursor ) == s2a );
   CU_ASSERT( s_avltree_cursor_index( cursor ) == 1 );

   s_avltree_cursor_back( cursor );
   s_avltree_cursor_search_back_eq_fn( cursor, s2, is_equal_s );
   CU_ASSERT( s_avltree_cursor_off( cursor ) == 1 );
 
   s_avltree_deep_dispose( &avltree );

   return;
}

int
add_test_cursor_search_back_eq_fn( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_cursor_search_back_eq_fn", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_cursor_search_back_eq_fn_1
   add_test_to_suite( p_suite, test_cursor_search_back_eq_fn_1, "test_cursor_search_back_eq_fn_1" );

   // test_cursor_search_back_eq_fn_2
   add_test_to_suite( p_suite, test_cursor_search_back_eq_fn_2, "test_cursor_search_back_eq_fn_2" );

   // test_cursor_search_back_eq_fn_3
   add_test_to_suite( p_suite, test_cursor_search_back_eq_fn_3, "test_cursor_search_back_eq_fn_3" );

   // test_cursor_search_back_eq_fn_4
   add_test_to_suite( p_suite, test_cursor_search_back_eq_fn_4, "test_cursor_search_back_eq_fn_4" );

   // test_cursor_search_back_eq_fn_5
   add_test_to_suite( p_suite, test_cursor_search_back_eq_fn_5, "test_cursor_search_back_eq_fn_5" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

