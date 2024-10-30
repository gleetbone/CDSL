/**
 @file AList_test_cursor_append_right.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for AList_append"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for AList_t

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_AList.h"
#include "s_AList.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_cursor_append_right_1
*/

void test_cursor_append_right_1( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   
   i_alist_t *list1 = NULL;

   list1 = i_alist_make();
   i_alist_put_last( list1, 24 );

   i_alist_cursor_t *cursor = i_alist_cursor_make( list );
   i_alist_cursor_start( cursor );
   i_alist_cursor_append_right( cursor, list1 );

   i_alist_start( list );

   CU_ASSERT( i_alist_count( list ) == 1 );

   CU_ASSERT( i_alist_item_at( list ) == 24 );

   i_alist_cursor_dispose( &cursor );
   i_alist_dispose( &list );
   i_alist_dispose( &list1 );

   return;
}

/**
   test_cursor_append_right_2
*/

void test_cursor_append_right_2( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   
   i_alist_put_last( list, 24 );
   
   i_alist_t *list1 = NULL;

   list1 = i_alist_make();
   
   i_alist_put_last( list1, 13 );
   
   i_alist_cursor_t *cursor = i_alist_cursor_make( list );
   i_alist_cursor_start( cursor );
   i_alist_cursor_append_right( cursor, list1 );

   i_alist_start( list );

   CU_ASSERT( i_alist_item_at( list ) == 24 );

   i_alist_forth( list );

   CU_ASSERT( i_alist_item_at( list ) == 13 );

   CU_ASSERT( i_alist_count( list ) == 2 );

   i_alist_cursor_dispose( &cursor );
   i_alist_dispose( &list );
   i_alist_dispose( &list1 );

   return;
}

/**
   test_cursor_append_right_3
*/

void test_cursor_append_right_3( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   i_alist_put_last( list, 24 );
   i_alist_put_last( list, 13 );

   i_alist_t *list1 = NULL;

   list1 = i_alist_make();
   i_alist_put_last( list1, 7 );
   i_alist_put_last( list1, 31 );
   
   i_alist_cursor_t *cursor = i_alist_cursor_make( list );
   i_alist_cursor_start( cursor );
   i_alist_cursor_append_right( cursor, list1 );


   i_alist_start( list );
   
   CU_ASSERT( i_alist_item_at( list ) == 24 );

   i_alist_forth( list );

   CU_ASSERT( i_alist_item_at( list ) == 7 );

   i_alist_forth( list );

   CU_ASSERT( i_alist_item_at( list ) == 31 );
   
   i_alist_forth( list );

   CU_ASSERT( i_alist_item_at( list ) == 13 );

   CU_ASSERT( i_alist_count( list ) == 4 );

   i_alist_cursor_dispose( &cursor );
   i_alist_dispose( &list );
   i_alist_dispose( &list1 );

   return;
}

/**
   test_cursor_append_right_4
*/

void test_cursor_append_right_4( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   i_alist_put_last( list, 24 );
   i_alist_put_last( list, 13 );

   i_alist_t *list1 = NULL;

   list1 = i_alist_make();
   i_alist_put_last( list1, 7 );
   i_alist_put_last( list1, 31 );
   
   i_alist_cursor_t *cursor = i_alist_cursor_make( list );
   i_alist_cursor_start( cursor );
   i_alist_cursor_forth( cursor );
   
   i_alist_cursor_append_right( cursor, list1 );

   i_alist_start( list );
   
   CU_ASSERT( i_alist_item_at( list ) == 24 );

   i_alist_forth( list );

   CU_ASSERT( i_alist_item_at( list ) == 13 );

   i_alist_forth( list );

   CU_ASSERT( i_alist_item_at( list ) == 7 );
   
   i_alist_forth( list );

   CU_ASSERT( i_alist_item_at( list ) == 31 );

   CU_ASSERT( i_alist_count( list ) == 4 );

   i_alist_cursor_dispose( &cursor );
   i_alist_dispose( &list );
   i_alist_dispose( &list1 );

   return;
}

/**
   test_cursor_append_right_5
*/

void test_cursor_append_right_5( void )
{
   s_alist_t *list = s_alist_make();
   s_alist_t *list1 = s_alist_make();
   s_alist_cursor_t *cursor = s_alist_cursor_make( list );

   string_t *s1 = string_make_from_cstring( "a" ); 
   string_t *s2 = string_make_from_cstring( "b" ); 
   string_t *s3 = string_make_from_cstring( "c" ); 
   string_t *s4 = string_make_from_cstring( "d" ); 

   s_alist_put_last( list, s1 );
   s_alist_put_last( list, s2 );

   s_alist_put_last( list1, s3);
   s_alist_put_last( list1, s4 );
   
   s_alist_cursor_start( cursor );
   s_alist_cursor_forth( cursor );
   s_alist_cursor_append_right( cursor, list1 );

   s_alist_start( list );
   CU_ASSERT( string_is_equal( s_alist_item_at( list ), s1 ) == 1 );
   
   s_alist_forth( list );
   CU_ASSERT( string_is_equal( s_alist_item_at( list ), s2 ) == 1 );

   s_alist_forth( list );
   CU_ASSERT( string_is_equal( s_alist_item_at( list ), s3 ) == 1 );

   s_alist_forth( list );
   CU_ASSERT( string_is_equal( s_alist_item_at( list ), s4 ) == 1 );

   s_alist_cursor_dispose( &cursor );
   s_alist_dispose( &list1 );
   s_alist_deep_dispose( &list );

   return;
}

int
add_test_cursor_append_right( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_cursor_append_right", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_cursor_append_right_1
   add_test_to_suite( p_suite, test_cursor_append_right_1, "test_cursor_append_right_1" );

   // test_cursor_append_right_2
   add_test_to_suite( p_suite, test_cursor_append_right_2, "test_cursor_append_right_2" );

   // test_cursor_append_right_3
   add_test_to_suite( p_suite, test_cursor_append_right_3, "test_cursor_append_right_3" );

   // test_cursor_append_right_4
   add_test_to_suite( p_suite, test_cursor_append_right_4, "test_cursor_append_right_4" );

   // test_cursor_append_right_5
   add_test_to_suite( p_suite, test_cursor_append_right_5, "test_cursor_append_right_5" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

