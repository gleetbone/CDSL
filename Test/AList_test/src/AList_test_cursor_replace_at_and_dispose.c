/**
 @file AList_test_cursor_replace_at_and_dispose.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for AList_put"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for AList_item_at.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "int_AList.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_cursor_replace_at_and_dispose_1
*/

void test_cursor_replace_at_and_dispose_1( void )
{
   int_alist_t *list = NULL;

   list = int_alist_make();
   
   int_alist_put_last( list, 24);

   int_alist_cursor_t *cursor = int_alist_cursor_make( list );
   
   int_alist_cursor_start( cursor );
   
   int_alist_cursor_replace_at_and_dispose( cursor, 25 );

   CU_ASSERT( int_alist_cursor_item_at( cursor ) == 25 );
   
   CU_ASSERT( int_alist_count( list ) == 1 );

   int_alist_cursor_dispose( cursor );
   int_alist_dispose( list );

   return;
}

void test_cursor_replace_at_and_dispose_2( void )
{
   int_alist_t *list = NULL;

   list = int_alist_make();
   int_alist_put_last( list, 24 );
   int_alist_put_last( list, 13 );
   int_alist_put_last( list, 7 );

   int_alist_cursor_t *cursor = int_alist_cursor_make( list );
   
   int_alist_cursor_finish( cursor );
   
   int_alist_cursor_replace_at_and_dispose( cursor, 8 );
   
   int_alist_cursor_back( cursor );
   
   int_alist_cursor_replace_at_and_dispose( cursor, 14 );
   
   int_alist_cursor_back( cursor );
   
   int_alist_cursor_replace_at_and_dispose( cursor, 25 );

   int_alist_cursor_start( cursor );
   
   CU_ASSERT( int_alist_cursor_item_at( cursor ) == 25 );

   int_alist_cursor_forth( cursor );

   CU_ASSERT( int_alist_cursor_item_at( cursor ) == 14 );

   int_alist_cursor_forth( cursor );

   CU_ASSERT( int_alist_cursor_item_at( cursor ) == 8 );

   CU_ASSERT( int_alist_count( list ) == 3 );

   int_alist_cursor_dispose( cursor );
   int_alist_dispose( list );

   return;
}

int
add_test_cursor_replace_at_and_dispose( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_cursor_replace_at_and_dispose", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_cursor_replace_at_and_dispose_1
   add_test_to_suite( p_suite, test_cursor_replace_at_and_dispose_1, "test_cursor_replace_at_and_dispose_1" );

   // test_cursor_replace_at_and_dispose_2
   add_test_to_suite( p_suite, test_cursor_replace_at_and_dispose_2, "test_cursor_replace_at_and_dispose_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

