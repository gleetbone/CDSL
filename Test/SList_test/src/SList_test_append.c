/**
 @file SList_test_append.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for SList_append"
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
   test_append_1
*/

void test_append_1( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   
   int_slist_t *list1 = NULL;

   list1 = int_slist_make();
   int_slist_put_last( list1, 24 );
   
   int_slist_append( list, list1, 0 );

   int_slist_start( list );

   CU_ASSERT( int_slist_count( list ) == 1 );

   CU_ASSERT( int_slist_item_at( list ) == 24 );

   int_slist_dispose( &list );
   int_slist_dispose( &list1 );

   return;
}

/**
   test_append_2
*/

void test_append_2( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   
   int_slist_put_last( list, 24 );
   
   int_slist_t *list1 = NULL;

   list1 = int_slist_make();
   
   int_slist_put_last( list1, 13 );
   
   int_slist_append( list, list1, 0 );

   int_slist_start( list );

   CU_ASSERT( int_slist_item_at( list ) == 13 );

   int_slist_forth( list );

   CU_ASSERT( int_slist_item_at( list ) == 24 );

   CU_ASSERT( int_slist_count( list ) == 2 );

   int_slist_dispose( &list );
   int_slist_dispose( &list1 );

   return;
}

/**
   test_append_3
*/

void test_append_3( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   
   int_slist_put_last( list, 24 );
   
   int_slist_t *list1 = NULL;

   list1 = int_slist_make();
   
   int_slist_put_last( list1, 13 );
   
   int_slist_append( list, list1, 1 );
   
   int_slist_start( list );

   CU_ASSERT( int_slist_item_at( list ) == 24 );

   int_slist_forth( list );

   CU_ASSERT( int_slist_item_at( list ) == 13 );

   CU_ASSERT( int_slist_count( list ) == 2 );

   int_slist_dispose( &list );
   int_slist_dispose( &list1 );

   return;
}

/**
   test_append_4
*/

void test_append_4( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );

   int_slist_t *list1 = NULL;

   list1 = int_slist_make();
   int_slist_put_last( list1, 7 );
   int_slist_put_last( list1, 31 );
   
   int_slist_append( list, list1, 0 );

   int_slist_start( list );
   
   CU_ASSERT( int_slist_item_at( list ) == 7 );

   int_slist_forth( list );

   CU_ASSERT( int_slist_item_at( list ) == 31 );

   int_slist_forth( list );

   CU_ASSERT( int_slist_item_at( list ) == 24 );
   
   int_slist_forth( list );

   CU_ASSERT( int_slist_item_at( list ) == 13 );

   CU_ASSERT( int_slist_count( list ) == 4 );

   int_slist_dispose( &list );
   int_slist_dispose( &list1 );

   return;
}

/**
   test_append_5
*/

void test_append_5( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );

   int_slist_t *list1 = NULL;

   list1 = int_slist_make();
   int_slist_put_last( list1, 7 );
   int_slist_put_last( list1, 31 );
   
   int_slist_append( list, list1, 1 );

   int_slist_start( list );
   
   CU_ASSERT( int_slist_item_at( list ) == 24 );

   int_slist_forth( list );

   CU_ASSERT( int_slist_item_at( list ) == 7 );

   int_slist_forth( list );

   CU_ASSERT( int_slist_item_at( list ) == 31 );
   
   int_slist_forth( list );

   CU_ASSERT( int_slist_item_at( list ) == 13 );

   CU_ASSERT( int_slist_count( list ) == 4 );

   int_slist_dispose( &list );
   int_slist_dispose( &list1 );

   return;
}

/**
   test_append_6
*/

void test_append_6( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );

   int_slist_t *list1 = NULL;

   list1 = int_slist_make();
   int_slist_put_last( list1, 7 );
   int_slist_put_last( list1, 31 );
   
   int_slist_append( list, list1, 2 );

   int_slist_start( list );
   
   CU_ASSERT( int_slist_item_at( list ) == 24 );

   int_slist_forth( list );

   CU_ASSERT( int_slist_item_at( list ) == 13 );

   int_slist_forth( list );

   CU_ASSERT( int_slist_item_at( list ) == 7 );
   
   int_slist_forth( list );

   CU_ASSERT( int_slist_item_at( list ) == 31 );

   CU_ASSERT( int_slist_count( list ) == 4 );

   int_slist_dispose( &list );
   int_slist_dispose( &list1 );

   return;
}

/**
   test_append_7
*/

void test_append_7( void )
{
   s_slist_t *list = NULL;

   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s3 = string_make_from_cstring( "3" );
   string_t *s4 = string_make_from_cstring( "4" );

   list = s_slist_make();
   
   s_slist_put_last( list, s1 );
   s_slist_put_last( list, s2 );

   s_slist_t *list1 = NULL;

   list1 = s_slist_make();
   s_slist_put_last( list1, s3 );
   s_slist_put_last( list1, s4 );
   
   s_slist_append( list, list1, 2 );

   s_slist_start( list );
   
   CU_ASSERT( s_slist_item_at( list ) == s1 );

   s_slist_forth( list );

   CU_ASSERT( s_slist_item_at( list ) == s2 );

   s_slist_forth( list );

   CU_ASSERT( s_slist_item_at( list ) == s3 );
   
   s_slist_forth( list );

   CU_ASSERT( s_slist_item_at( list ) == s4 );

   CU_ASSERT( s_slist_count( list ) == 4 );

   s_slist_dispose( &list1 );
   s_slist_deep_dispose( &list );

   return;
}

int
add_test_append( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_append", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_append_1
   add_test_to_suite( p_suite, test_append_1, "test_append_1" );

   // test_append_2
   add_test_to_suite( p_suite, test_append_2, "test_append_2" );

   // test_append_3
   add_test_to_suite( p_suite, test_append_3, "test_append_3" );

   // test_append_4
   add_test_to_suite( p_suite, test_append_4, "test_append_4" );

   // test_append_5
   add_test_to_suite( p_suite, test_append_5, "test_append_5" );

   // test_append_6
   add_test_to_suite( p_suite, test_append_6, "test_append_6" );

   // test_append_7
   add_test_to_suite( p_suite, test_append_7, "test_append_7" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

