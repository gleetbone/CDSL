/**
 @file SList_test_cursor_search_forth.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for SList_forth"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for SList_t.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "int_SList.h"
#include "s_SList.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_cursor_search_forth_1
*/

void test_cursor_search_forth_1( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );

   int_slist_cursor_t *cursor = int_slist_cursor_make( list );
   
   int_slist_cursor_start( cursor );
   
   int_slist_cursor_search_forth( cursor, 24 );
   
   CU_ASSERT( int_slist_cursor_index( cursor ) == 0 );

   int_slist_dispose( &list );

   return;
}

/**
   test_cursor_search_forth_2
*/

void test_cursor_search_forth_2( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );
   int_slist_put_last( list, 7 );

   int_slist_cursor_t *cursor = int_slist_cursor_make( list );
   
   int_slist_cursor_start( cursor );
   
   int_slist_cursor_search_forth( cursor, 13 );
   
   CU_ASSERT( int_slist_cursor_index( cursor ) == 1 );
   
   int_slist_cursor_search_forth( cursor, 13 );
   
   CU_ASSERT( int_slist_cursor_index( cursor ) == 1 );
   
   CU_ASSERT( int_slist_cursor_off( cursor ) == 0 );
   
   int_slist_cursor_forth( cursor );
   
   int_slist_cursor_search_forth( cursor, 13 );
   
   CU_ASSERT( int_slist_cursor_off( cursor ) == 1 );
   
   int_slist_dispose( &list );

   return;
}

/**
   test_cursor_search_forth_3
*/

void test_cursor_search_forth_3( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );
   int_slist_put_last( list, 7 );
   int_slist_put_last( list, 13 );

   int_slist_cursor_t *cursor = int_slist_cursor_make( list );
   
   int_slist_cursor_start( cursor );
   
   int_slist_cursor_search_forth( cursor, 13 );
   
   CU_ASSERT( int_slist_cursor_index( cursor ) == 1 );
   CU_ASSERT( int_slist_cursor_off( cursor ) == 0 );
   
   int_slist_cursor_search_forth( cursor, 13 );
   
   CU_ASSERT( int_slist_cursor_index( cursor ) == 1 );
   CU_ASSERT( int_slist_cursor_off( cursor ) == 0 );
   
   int_slist_cursor_forth( cursor );
   
   int_slist_cursor_search_forth( cursor, 13 );
   
   CU_ASSERT( int_slist_cursor_index( cursor ) == 3 );
   CU_ASSERT( int_slist_cursor_off( cursor ) == 0 );
   
   int_slist_cursor_search_forth( cursor, 13 );
   
   CU_ASSERT( int_slist_cursor_index( cursor ) == 3 );
   CU_ASSERT( int_slist_cursor_off( cursor ) == 0 );
   
   int_slist_dispose( &list );

   return;
}

/**
   test_cursor_search_forth_4
*/

void test_cursor_search_forth_4( void )
{
   s_slist_t *list = s_slist_make();
   
   string_t *s1 = string_make_from_cstring( "a" ); 
   string_t *s2 = string_make_from_cstring( "b" ); 
   string_t *s3 = string_make_from_cstring( "c" ); 
   string_t *s4 = string_make_from_cstring( "a" ); 
   
   s_slist_put_last( list, s1 );
   s_slist_put_last( list, s2 );
   s_slist_put_last( list, s3 );
   s_slist_put_last( list, s4 );

   s_slist_cursor_t *cursor = s_slist_cursor_make( list );
   s_slist_cursor_start( cursor );
   s_slist_cursor_search_forth( cursor, s1 );
   
   CU_ASSERT( s_slist_cursor_index( cursor ) == 0 );
   
   s_slist_cursor_forth( cursor );
   s_slist_cursor_search_forth( cursor, s1 );
   
   CU_ASSERT( s_slist_cursor_off( cursor ) == 1 );
   
   s_slist_deep_dispose( &list );

   return;
}

int
add_test_cursor_search_forth( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_cursor_search_forth", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_cursor_search_forth_1
   add_test_to_suite( p_suite, test_cursor_search_forth_1, "test_cursor_search_forth_1" );

   // test_cursor_search_forth_2
   add_test_to_suite( p_suite, test_cursor_search_forth_2, "test_cursor_search_forth_2" );

   // test_cursor_search_forth_3
   add_test_to_suite( p_suite, test_cursor_search_forth_3, "test_cursor_search_forth_3" );

   // test_cursor_search_forth_4
   add_test_to_suite( p_suite, test_cursor_search_forth_4, "test_cursor_search_forth_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

