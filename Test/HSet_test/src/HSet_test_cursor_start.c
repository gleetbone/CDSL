/**
 @file HSet_test_cursor_start.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for HSet_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for HSet_make.

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
   test_cursor_start_1
*/

void test_cursor_start_1( void )
{
   i_hset_t *hset = NULL;
   
   hset = i_hset_make();
   
   i_hset_put( hset, 24 );
   
   i_hset_cursor_t *cursor = NULL;
   
   cursor = i_hset_cursor_make( hset );
   
   CU_ASSERT( i_hset_cursor_off( cursor ) == 1 );
   
   i_hset_cursor_start( cursor );
   
   CU_ASSERT( i_hset_cursor_off( cursor ) == 0 );
 
   i_hset_cursor_forth( cursor );
   
   CU_ASSERT( i_hset_cursor_off( cursor ) == 1 );
   
   i_hset_cursor_start( cursor );
   
   CU_ASSERT( i_hset_cursor_off( cursor ) == 0 );
 
   i_hset_cursor_forth( cursor );
   
   CU_ASSERT( i_hset_cursor_off( cursor ) == 1 );
   
   i_hset_dispose( hset );

   return;
}

int
add_test_cursor_start( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_cursor_start", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_cursor_start_1
   add_test_to_suite( p_suite, test_cursor_start_1, "test_cursor_start_1" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

