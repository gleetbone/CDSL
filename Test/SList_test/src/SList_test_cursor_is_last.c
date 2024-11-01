/**
 @file SList_test_cursor_is_last.c
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

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_cursor_is_last_1
*/

void test_cursor_is_last_1( void )
{
   int_slist_t *list = NULL;
   int_slist_cursor_t *cursor = NULL;

   list = int_slist_make();
   cursor = int_slist_cursor_make( list );
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );

   int_slist_cursor_start( cursor );

   CU_ASSERT( int_slist_cursor_is_last( cursor ) == 0 );

   int_slist_cursor_forth( cursor );

   CU_ASSERT( int_slist_cursor_is_last( cursor ) == 1 );

   int_slist_dispose( &list );

   return;
}

int
add_test_cursor_is_last( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_cursor_is_last", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_cursor_is_last_1
   add_test_to_suite( p_suite, test_cursor_is_last_1, "test_cursor_is_last_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

