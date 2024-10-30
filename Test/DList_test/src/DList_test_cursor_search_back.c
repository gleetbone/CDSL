/**
 @file DList_test_cursor_search_back.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for DList_back"
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
   test_cursor_search_back_1
*/

void test_cursor_search_back_1( void )
{
   i_dlist_t *list = NULL;

   list = i_dlist_make();
   
   i_dlist_put_last( list, 24 );
   i_dlist_put_last( list, 13 );

   i_dlist_cursor_t *cursor = i_dlist_cursor_make( list );
   i_dlist_cursor_finish( cursor );
   
   i_dlist_cursor_search_back( cursor, 24 );
   
   CU_ASSERT( i_dlist_cursor_index( cursor ) == 0 );

   i_dlist_dispose( &list );

   return;
}

/**
   test_cursor_search_back_2
*/

void test_cursor_search_back_2( void )
{
   i_dlist_t *list = NULL;

   list = i_dlist_make();
   i_dlist_put_last( list, 24 );
   i_dlist_put_last( list, 13 );
   i_dlist_put_last( list, 7 );

   i_dlist_cursor_t *cursor = i_dlist_cursor_make( list );
   i_dlist_cursor_finish( cursor );
   
   i_dlist_cursor_search_back( cursor, 13 );
   
   CU_ASSERT( i_dlist_cursor_index( cursor ) == 1 );
   
   i_dlist_cursor_search_back( cursor, 13 );
   
   CU_ASSERT( i_dlist_cursor_index( cursor ) == 1 );
   
   CU_ASSERT( i_dlist_cursor_off( cursor ) == 0 );
   
   i_dlist_cursor_back( cursor );
   
   i_dlist_cursor_search_back( cursor, 13 );
   
   CU_ASSERT( i_dlist_cursor_off( cursor ) == 1 );
   
   i_dlist_dispose( &list );

   return;
}

/**
   test_cursor_search_back_3
*/

void test_cursor_search_back_3( void )
{
   i_dlist_t *list = NULL;

   list = i_dlist_make();
   i_dlist_put_last( list, 24 );
   i_dlist_put_last( list, 13 );
   i_dlist_put_last( list, 7 );
   i_dlist_put_last( list, 13 );

   i_dlist_cursor_t *cursor = i_dlist_cursor_make( list );
   i_dlist_cursor_finish( cursor );
   
   i_dlist_cursor_search_back( cursor, 13 );
   
   CU_ASSERT( i_dlist_cursor_index( cursor ) == 3 );
   CU_ASSERT( i_dlist_cursor_off( cursor ) == 0 );
   
   i_dlist_cursor_search_back( cursor, 13 );
   
   CU_ASSERT( i_dlist_cursor_index( cursor ) == 3 );
   CU_ASSERT( i_dlist_cursor_off( cursor ) == 0 );
   
   i_dlist_cursor_back( cursor );
   
   i_dlist_cursor_search_back( cursor, 13 );
   
   CU_ASSERT( i_dlist_cursor_index( cursor ) == 1 );
   CU_ASSERT( i_dlist_cursor_off( cursor ) == 0 );
   
   i_dlist_cursor_search_back( cursor, 13 );
   
   CU_ASSERT( i_dlist_cursor_index( cursor ) == 1 );
   CU_ASSERT( i_dlist_cursor_off( cursor ) == 0 );
   
   i_dlist_dispose( &list );

   return;
}

/**
   test_cursor_search_back_4
*/

void test_cursor_search_back_4( void )
{
   s_dlist_t *list = s_dlist_make();
   
   string_t *s1 = string_make_from_cstring( "a" ); 
   string_t *s2 = string_make_from_cstring( "b" ); 
   string_t *s3 = string_make_from_cstring( "c" ); 
   string_t *s4 = string_make_from_cstring( "a" ); 
   
   s_dlist_put_last( list, s1 );
   s_dlist_put_last( list, s2 );
   s_dlist_put_last( list, s3 );
   s_dlist_put_last( list, s4 );

   s_dlist_cursor_t *cursor = s_dlist_cursor_make( list );
   s_dlist_cursor_finish( cursor );
   s_dlist_cursor_search_back( cursor, s1 );
   
   CU_ASSERT( s_dlist_cursor_index( cursor ) == 0 );
   
   s_dlist_cursor_back( cursor );
   
   CU_ASSERT( s_dlist_cursor_off( cursor ) == 1 );
   
   s_dlist_deep_dispose( &list );

   return;
}

int
add_test_cursor_search_back( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_cursor_search_back", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_cursor_search_back_1
   add_test_to_suite( p_suite, test_cursor_search_back_1, "test_cursor_search_back_1" );

   // test_cursor_search_back_2
   add_test_to_suite( p_suite, test_cursor_search_back_2, "test_cursor_search_back_2" );

   // test_cursor_search_back_3
   add_test_to_suite( p_suite, test_cursor_search_back_3, "test_cursor_search_back_3" );

   // test_cursor_search_back_4
   add_test_to_suite( p_suite, test_cursor_search_back_4, "test_cursor_search_back_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

