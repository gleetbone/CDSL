/**
 @file AList_test_cursor_make.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for AList_cursor_make"
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
   test_cursor_make_1
*/

void test_cursor_make_1( void )
{
   i_alist_t *list = NULL;
   
   list = i_alist_make();
   
   i_alist_cursor_t *cursor = i_alist_cursor_make( list );
   
   CU_ASSERT( cursor != NULL );
   CU_ASSERT( i_alist_cursor_off( cursor ) == 1 );
  
   i_alist_cursor_dispose( &cursor );
   i_alist_dispose( &list );

   return;
}

/**
   test_cursor_make_2
*/

void test_cursor_make_2( void )
{
   i_alist_t *list = NULL;
   
   list = i_alist_make();
   i_alist_put_last( list, 24 );
   
   i_alist_cursor_t *cursor = i_alist_cursor_make( list );
   
   i_alist_cursor_start( cursor );
   CU_ASSERT( i_alist_cursor_item_at( cursor ) == 24 );
 
   i_alist_cursor_dispose( &cursor );
   i_alist_dispose( &list );

   return;
}

/**
   test_cursor_make_3
*/

void test_cursor_make_3( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   i_alist_put_last( list, 24 );

   i_alist_cursor_t *cursor = i_alist_cursor_make( list );
   i_alist_cursor_t *cursor1 = i_alist_cursor_make( list );

   i_alist_cursor_start( cursor );
   CU_ASSERT( i_alist_cursor_item_at( cursor ) == 24 );

   i_alist_cursor_start( cursor1 );
   CU_ASSERT( i_alist_cursor_item_at( cursor1) == 24 );

   i_alist_cursor_dispose( &cursor );
   i_alist_cursor_dispose( &cursor1 );
   i_alist_dispose( &list );

   return;
}

/**
   test_cursor_make_4
*/

void test_cursor_make_4( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   i_alist_put_last( list, 24 );

   i_alist_cursor_t *cursor = i_alist_cursor_make( list );
   i_alist_cursor_t *cursor1 = i_alist_cursor_make( list );
   i_alist_cursor_t *cursor2 = i_alist_cursor_make( list );
   i_alist_cursor_t *cursor3 = i_alist_cursor_make( list );

   i_alist_cursor_start( cursor );
   CU_ASSERT( i_alist_cursor_item_at( cursor ) == 24 );

   i_alist_cursor_start( cursor1 );
   CU_ASSERT( i_alist_cursor_item_at( cursor1 ) == 24 );

   i_alist_cursor_start( cursor2 );
   CU_ASSERT( i_alist_cursor_item_at( cursor2 ) == 24 );

   i_alist_cursor_start( cursor3 );
   CU_ASSERT( i_alist_cursor_item_at( cursor3 ) == 24 );

   i_alist_cursor_dispose( &cursor3 );
   i_alist_cursor_dispose( &cursor2 );
   i_alist_cursor_dispose( &cursor );
   i_alist_cursor_dispose( &cursor1 );
   i_alist_dispose( &list );

   return;
}

/**
   test_cursor_make_5
*/

void test_cursor_make_5( void )
{
   s_alist_t *list = s_alist_make();
   
   s_alist_cursor_t *cursor = s_alist_cursor_make( list );
   s_alist_cursor_t *cursor1 = s_alist_cursor_make( list );
   s_alist_cursor_t *cursor2 = s_alist_cursor_make( list );
   s_alist_cursor_t *cursor3 = s_alist_cursor_make( list );

   string_t *s1 = string_make_from_cstring( "a" ); 
   s_alist_put_last( list, s1 );
   
   s_alist_cursor_start( cursor );
   CU_ASSERT( string_is_equal( s_alist_cursor_item_at( cursor ), s1 ) == 1 );

   s_alist_cursor_start( cursor1 );
   CU_ASSERT( string_is_equal( s_alist_cursor_item_at( cursor1 ), s1 ) == 1 );

   s_alist_cursor_start( cursor2 );
   CU_ASSERT( string_is_equal( s_alist_cursor_item_at( cursor2 ), s1 ) == 1 );

   s_alist_cursor_start( cursor3 );
   CU_ASSERT( string_is_equal( s_alist_cursor_item_at( cursor3 ), s1 ) == 1 );

   s_alist_cursor_dispose( &cursor3 );
   s_alist_cursor_dispose( &cursor2 );
   s_alist_cursor_dispose( &cursor );
   s_alist_cursor_dispose( &cursor1 );
   s_alist_deep_dispose( &list );

   return;
}

int
add_test_cursor_make( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_cursor_make", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_cursor_make_1
   add_test_to_suite( p_suite, test_cursor_make_1, "test_cursor_make_1" );

   // test_cursor_make_2
   add_test_to_suite( p_suite, test_cursor_make_2, "test_cursor_make_2" );

   // test_cursor_make_3
   add_test_to_suite( p_suite, test_cursor_make_3, "test_cursor_make_3" );

   // test_cursor_make_4
   add_test_to_suite( p_suite, test_cursor_make_4, "test_cursor_make_4" );

   // test_cursor_make_5
   add_test_to_suite( p_suite, test_cursor_make_5, "test_cursor_make_5" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

