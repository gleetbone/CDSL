/**
 @file DList_test_append_last.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for DList_append"
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
   test_append_last_1
*/

void test_append_last_1( void )
{
   i_dlist_t *list = NULL;

   list = i_dlist_make();
   
   i_dlist_t *list1 = NULL;

   list1 = i_dlist_make();
   i_dlist_put_last( list1, 24 );

   i_dlist_start( list );
   
   i_dlist_append_last( list, list1 );

   i_dlist_start( list );

   CU_ASSERT( i_dlist_count( list ) == 1 );

   CU_ASSERT( i_dlist_item_at( list ) == 24 );

   i_dlist_dispose( &list );
   i_dlist_dispose( &list1 );

   return;
}

/**
   test_append_last_2
*/

void test_append_last_2( void )
{
   i_dlist_t *list = NULL;

   list = i_dlist_make();
   
   i_dlist_put_last( list, 24 );
   
   i_dlist_t *list1 = NULL;

   list1 = i_dlist_make();
   
   i_dlist_put_last( list1, 13 );
   
   i_dlist_start( list );
   
   i_dlist_append_last( list, list1 );

   i_dlist_start( list );

   CU_ASSERT( i_dlist_item_at( list ) == 24 );

   i_dlist_forth( list );

   CU_ASSERT( i_dlist_item_at( list ) == 13 );

   CU_ASSERT( i_dlist_count( list ) == 2 );

   i_dlist_dispose( &list );
   i_dlist_dispose( &list1 );

   return;
}

/**
   test_append_last_3
*/

void test_append_last_3( void )
{
   i_dlist_t *list = NULL;

   list = i_dlist_make();
   i_dlist_put_last( list, 24 );
   i_dlist_put_last( list, 13 );

   i_dlist_t *list1 = NULL;

   list1 = i_dlist_make();
   i_dlist_put_last( list1, 7 );
   i_dlist_put_last( list1, 31 );
   
   i_dlist_start( list );
   
   i_dlist_append_last( list, list1 );

   i_dlist_start( list );
   
   CU_ASSERT( i_dlist_item_at( list ) == 24 );

   i_dlist_forth( list );

   CU_ASSERT( i_dlist_item_at( list ) == 13 );

   i_dlist_forth( list );

   CU_ASSERT( i_dlist_item_at( list ) == 7 );
   
   i_dlist_forth( list );

   CU_ASSERT( i_dlist_item_at( list ) == 31 );

   CU_ASSERT( i_dlist_count( list ) == 4 );

   i_dlist_dispose( &list );
   i_dlist_dispose( &list1 );

   return;
}

/**
   test_append_last_4
*/

void test_append_last_4( void )
{
   s_dlist_t *list = NULL;
   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s3 = string_make_from_cstring( "3" );
   string_t *s4 = string_make_from_cstring( "4" );

   list = s_dlist_make();
   s_dlist_put_last( list, s1 );
   s_dlist_put_last( list, s2 );

   s_dlist_t *list1 = NULL;

   list1 = s_dlist_make();
   s_dlist_put_last( list1, s3 );
   s_dlist_put_last( list1, s4 );
   
   s_dlist_start( list );
   
   s_dlist_append_last( list, list1 );

   s_dlist_start( list );
   
   CU_ASSERT( s_dlist_item_at( list ) == s1 );

   s_dlist_forth( list );

   CU_ASSERT( s_dlist_item_at( list ) == s2 );

   s_dlist_forth( list );

   CU_ASSERT( s_dlist_item_at( list ) == s3 );
   
   s_dlist_forth( list );

   CU_ASSERT( s_dlist_item_at( list ) == s4 );

   CU_ASSERT( s_dlist_count( list ) == 4 );

   s_dlist_deep_dispose( &list );
   s_dlist_dispose( &list1 );

   return;
}

int
add_test_append_last( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_append_last", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_append_last_1
   add_test_to_suite( p_suite, test_append_last_1, "test_append_last_1" );

   // test_append_last_2
   add_test_to_suite( p_suite, test_append_last_2, "test_append_last_2" );

   // test_append_last_3
   add_test_to_suite( p_suite, test_append_last_3, "test_append_last_3" );

   // test_append_last_4
   add_test_to_suite( p_suite, test_append_last_4, "test_append_last_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

