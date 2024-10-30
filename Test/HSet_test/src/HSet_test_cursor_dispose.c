/**
 @file HSet_test_cursor_dispose.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for HSet_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for HSet_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_HSet.h"
#include "s_HSet.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_cursor_make_1
*/

void test_cursor_dispose_1( void )
{
   i_hset_t *hset = NULL;
   
   hset = i_hset_make();
   
   i_hset_cursor_t *cursor = NULL;
   
   cursor = i_hset_cursor_make( hset );
   
   CU_ASSERT( cursor != NULL );
   
   i_hset_cursor_dispose( &cursor );
   CU_ASSERT( cursor == NULL );
   
   i_hset_dispose( &hset );

   return;
}

/**
   test_cursor_make_2
*/

void test_cursor_dispose_2( void )
{
   i_hset_t *hset = NULL;

   hset = i_hset_make();

   i_hset_cursor_t *cursor1 = NULL;
   i_hset_cursor_t *cursor2 = NULL;

   cursor1 = i_hset_cursor_make( hset );
   cursor2 = i_hset_cursor_make( hset );

   CU_ASSERT( cursor1 != NULL );
   CU_ASSERT( cursor2 != NULL );

   i_hset_cursor_dispose( &cursor2 );
   CU_ASSERT( cursor2 == NULL );

   i_hset_cursor_dispose( &cursor1 );
   CU_ASSERT( cursor1 == NULL );

   i_hset_dispose( &hset );

   return;
}

/**
   test_cursor_make_3
*/

void test_cursor_dispose_3( void )
{
   s_hset_t *hset = NULL;

   hset = s_hset_make();

   s_hset_cursor_t *cursor1 = NULL;
   s_hset_cursor_t *cursor2 = NULL;

   cursor1 = s_hset_cursor_make( hset );
   cursor2 = s_hset_cursor_make( hset );

   CU_ASSERT( cursor1 != NULL );
   CU_ASSERT( cursor2 != NULL );

   s_hset_cursor_dispose( &cursor2 );
   CU_ASSERT( cursor2 == NULL );

   s_hset_cursor_dispose( &cursor1 );
   CU_ASSERT( cursor1 == NULL );

   s_hset_dispose( &hset );

   return;
}

int
add_test_cursor_dispose( void )
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
   add_test_to_suite( p_suite, test_cursor_dispose_1, "test_cursor_dispose_1" );

   // test_cursor_make_2
   add_test_to_suite( p_suite, test_cursor_dispose_2, "test_cursor_dispose_2" );

   // test_cursor_make_3
   add_test_to_suite( p_suite, test_cursor_dispose_3, "test_cursor_dispose_3" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

