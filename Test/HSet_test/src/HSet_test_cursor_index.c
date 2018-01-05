/**
 @file HSet_test_cursor_index.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for HSet_cursor_item_at"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for HSet_cursor_item_at.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_HSet.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_cursor_index_1
*/

void test_cursor_index_1( void )
{
   i_hset_t *list = NULL;

   list = i_hset_make();
   
   i_hset_cursor_t *cursor = i_hset_cursor_make( list );

   CU_ASSERT( i_hset_cursor_off( cursor ) == 1 );
   CU_ASSERT( i_hset_cursor_index( cursor ) == -1 );
   
   i_hset_put( list, 24 );
   i_hset_put( list, 13 );
   
   i_hset_cursor_start( cursor );
   CU_ASSERT( i_hset_cursor_index( cursor ) == 0 );
   
   i_hset_cursor_forth( cursor );

   CU_ASSERT( i_hset_cursor_index( cursor ) == 1 );

   i_hset_cursor_forth( cursor );

   CU_ASSERT( i_hset_cursor_index( cursor ) == -1 );

   i_hset_cursor_dispose( cursor );
   i_hset_dispose( list );

   return;
}

int
add_test_cursor_index( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_cursor_index", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_cursor_index_1
   add_test_to_suite( p_suite, test_cursor_index_1, "test_cursor_index_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

