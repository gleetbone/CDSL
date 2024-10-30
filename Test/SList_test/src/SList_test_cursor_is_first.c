/**
 @file SList_test_cursor_is_first.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for SList_first"
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
   test_cursor_is_first_1
*/

void test_cursor_is_first_1( void )
{
   int_slist_t *list = NULL;
   int_slist_cursor_t *cursor = NULL;

   list = int_slist_make();
   cursor = int_slist_cursor_make( list );
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );

   int_slist_cursor_start( cursor );

   CU_ASSERT( int_slist_cursor_is_first( cursor ) == 1 );

   int_slist_cursor_forth( cursor );

   CU_ASSERT( int_slist_cursor_is_first( cursor ) == 0 );

   int_slist_dispose( &list );

   return;
}

/**
   test_cursor_is_first_2
*/

void test_cursor_is_first_2( void )
{
   s_slist_t *list = NULL;
   s_slist_cursor_t *cursor = NULL;

   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   
   list = s_slist_make();
   
   cursor = s_slist_cursor_make( list );
   
   s_slist_put_last( list, s1 );
   s_slist_put_last( list, s2 );

   s_slist_cursor_start( cursor );

   CU_ASSERT( s_slist_cursor_is_first( cursor ) == 1 );

   s_slist_cursor_forth( cursor );

   CU_ASSERT( s_slist_cursor_is_first( cursor ) == 0 );

   s_slist_deep_dispose( &list );

   return;
}

int
add_test_cursor_is_first( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_cursor_is_first", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_cursor_is_first_1
   add_test_to_suite( p_suite, test_cursor_is_first_1, "test_cursor_is_first_1" );

   // test_cursor_is_first_2
   add_test_to_suite( p_suite, test_cursor_is_first_2, "test_cursor_is_first_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

