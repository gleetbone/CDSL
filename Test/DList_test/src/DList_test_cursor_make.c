/**
 @file DList_test_cursor_make.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for DList_cursor_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for DList_t.

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_DList.h"
#include "s_DList.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_cursor_make_1
*/

void test_cursor_make_1( void )
{
   i_dlist_t *list = NULL;
   
   list = i_dlist_make();
   
   i_dlist_cursor_t *cursor = i_dlist_cursor_make( list );
   
   CU_ASSERT( cursor != NULL );
   CU_ASSERT( i_dlist_cursor_off( cursor ) == 1 );
  
   i_dlist_dispose( &list );

   return;
}

/**
   test_cursor_make_2
*/

void test_cursor_make_2( void )
{
   i_dlist_t *list = NULL;
   
   list = i_dlist_make();
   i_dlist_put_last( list, 24 );
   
   i_dlist_cursor_t *cursor = i_dlist_cursor_make( list );
   
   i_dlist_cursor_start( cursor );
   CU_ASSERT( i_dlist_cursor_item_at( cursor ) == 24 );
 
   i_dlist_dispose( &list );

   return;
}

/**
   test_cursor_make_3
*/

void test_cursor_make_3( void )
{
   i_dlist_t *list = NULL;
   i_dlist_cursor_t *cursor = NULL;
   i_dlist_cursor_t *cursor1 = NULL;

   list = i_dlist_make();
   i_dlist_put_last( list, 24 );

   cursor = i_dlist_cursor_make( list );
   cursor1 = i_dlist_cursor_make( list );

   i_dlist_cursor_start( cursor );
   i_dlist_cursor_start( cursor1 );
   CU_ASSERT( i_dlist_cursor_item_at( cursor ) == 24 );

   i_dlist_dispose( &list );

   return;
}

/**
   test_cursor_make_4
*/

void test_cursor_make_4( void )
{
   s_dlist_t *list = NULL;
   s_dlist_cursor_t *cursor = NULL;
   s_dlist_cursor_t *cursor1 = NULL;

   string_t *s1 = string_make_from_cstring( "1" );
   
   list = s_dlist_make();
   
   s_dlist_put_last( list, s1 );

   cursor = s_dlist_cursor_make( list );
   cursor1 = s_dlist_cursor_make( list );

   s_dlist_cursor_start( cursor );
   s_dlist_cursor_start( cursor1 );
   
   CU_ASSERT( s_dlist_cursor_item_at( cursor ) == s1 );

   s_dlist_deep_dispose( &list );

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

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

