/**
 @file SList_test_keep_last.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for SList_put"
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
   test_keep_last_1
*/

void test_keep_last_1( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   
   int_slist_put_last( list, 24 );

   int_slist_keep_last( list, 1 );

   CU_ASSERT( int_slist_count( list ) == 1 );

   int_slist_dispose( &list );

   return;
}

/**
   test_keep_last_2
*/

void test_keep_last_2( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   
   int_slist_put_last( list, 24 );

   int_slist_keep_last( list, 0 );

   CU_ASSERT( int_slist_count( list ) == 0 );

   int_slist_dispose( &list );

   return;
}

/**
   test_keep_last_3
*/

void test_keep_last_3( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );

   int_slist_keep_last( list, 1 );

   CU_ASSERT( int_slist_count( list ) == 1 );

   int_slist_start( list );
   
   CU_ASSERT( int_slist_item_at( list ) == 13 );

   int_slist_dispose( &list );

   return;
}

/**
   test_keep_last_4
*/

void test_keep_last_4( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );

   int_slist_keep_last( list, 2 );

   CU_ASSERT( int_slist_count( list ) == 2 );

   int_slist_start( list );
   
   CU_ASSERT( int_slist_item_at( list ) == 24 );

   int_slist_forth( list );
   
   CU_ASSERT( int_slist_item_at( list ) == 13 );

   int_slist_dispose( &list );

   return;
}

/**
   test_keep_last_5
*/

void test_keep_last_5( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );
   int_slist_put_last( list, 7 );

   int_slist_keep_last( list, 1 );
   
   int_slist_start( list );
   
   CU_ASSERT( int_slist_item_at( list ) == 7 );

   CU_ASSERT( int_slist_count( list ) == 1 );

   int_slist_dispose( &list );

   return;
}

/**
   test_keep_last_6
*/

void test_keep_last_6( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );
   int_slist_put_last( list, 7 );

   int_slist_keep_last( list, 2 );
   
   int_slist_start( list );
   
   CU_ASSERT( int_slist_item_at( list ) == 13 );

   int_slist_forth( list );
   
   CU_ASSERT( int_slist_item_at( list ) == 7 );

   CU_ASSERT( int_slist_count( list ) == 2 );

   int_slist_dispose( &list );

   return;
}

/**
   test_keep_last_7
*/

void test_keep_last_7( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );
   int_slist_put_last( list, 7 );

   int_slist_keep_last( list, 3 );
   
   CU_ASSERT( int_slist_count( list ) == 3 );

   int_slist_start( list );
   
   CU_ASSERT( int_slist_item_at( list ) == 24 );

   int_slist_forth( list );
   
   CU_ASSERT( int_slist_item_at( list ) == 13 );

   int_slist_forth( list );
   
   CU_ASSERT( int_slist_item_at( list ) == 7);

   int_slist_dispose( &list );

   return;
}

/**
   test_keep_last_8
*/

void test_keep_last_8( void )
{
   s_slist_t *list = NULL;

   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s3 = string_make_from_cstring( "3" );
   
   list = s_slist_make();
   
   s_slist_put_last( list, s1 );
   s_slist_put_last( list, s2 );
   s_slist_put_last( list, s3 );

   s_slist_keep_last( list, 2 );
   
   s_slist_start( list );
   
   CU_ASSERT( s_slist_item_at( list ) == s2 );

   s_slist_forth( list );
   
   CU_ASSERT( s_slist_item_at( list ) == s3 );

   CU_ASSERT( s_slist_count( list ) == 2 );

   s_slist_deep_dispose( &list );
   string_deep_dispose( &s1 );

   return;
}

int
add_test_keep_last( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_keep_last", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_keep_last_1
   add_test_to_suite( p_suite, test_keep_last_1, "test_keep_last_1" );

   // test_keep_last_2
   add_test_to_suite( p_suite, test_keep_last_2, "test_keep_last_2" );

   // test_keep_last_3
   add_test_to_suite( p_suite, test_keep_last_3, "test_keep_last_3" );

   // test_keep_last_4
   add_test_to_suite( p_suite, test_keep_last_4, "test_keep_last_4" );

   // test_keep_last_5
   add_test_to_suite( p_suite, test_keep_last_5, "test_keep_last_5" );

   // test_keep_last_6
   add_test_to_suite( p_suite, test_keep_last_6, "test_keep_last_6" );

   // test_keep_last_7
   add_test_to_suite( p_suite, test_keep_last_7, "test_keep_last_7" );

   // test_keep_last_8
   add_test_to_suite( p_suite, test_keep_last_8, "test_keep_last_8" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

