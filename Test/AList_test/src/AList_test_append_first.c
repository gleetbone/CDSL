/**
 @file AList_test_append_first.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for AList_append"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for AList_t

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_AList.h"
#include "s_AList.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_append_first_1
*/

void test_append_first_1( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   
   i_alist_t *list1 = NULL;

   list1 = i_alist_make();
   i_alist_put_last( list1, 24 );

   i_alist_start( list );
   
   i_alist_append_first( list, list1 );

   i_alist_start( list );

   CU_ASSERT( i_alist_count( list ) == 1 );

   CU_ASSERT( i_alist_item_at( list ) == 24 );

   i_alist_dispose( &list );
   i_alist_dispose( &list1 );

   return;
}

/**
   test_append_first_2
*/

void test_append_first_2( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   
   i_alist_put_last( list, 24 );
   
   i_alist_t *list1 = NULL;

   list1 = i_alist_make();
   
   i_alist_put_last( list1, 13 );
   
   i_alist_start( list );
   
   i_alist_append_first( list, list1 );

   i_alist_start( list );

   CU_ASSERT( i_alist_item_at( list ) == 13 );

   i_alist_forth( list );

   CU_ASSERT( i_alist_item_at( list ) == 24 );

   CU_ASSERT( i_alist_count( list ) == 2 );

   i_alist_dispose( &list );
   i_alist_dispose( &list1 );

   return;
}


/**
   test_append_first_3
*/

void test_append_first_3( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   i_alist_put_last( list, 24 );
   i_alist_put_last( list, 13 );

   i_alist_t *list1 = NULL;

   list1 = i_alist_make();
   i_alist_put_last( list1, 7 );
   i_alist_put_last( list1, 31 );
   
   i_alist_start( list );
   
   i_alist_append_first( list, list1 );

   i_alist_start( list );
   
   CU_ASSERT( i_alist_item_at( list ) == 7 );

   i_alist_forth( list );

   CU_ASSERT( i_alist_item_at( list ) == 31 );

   i_alist_forth( list );

   CU_ASSERT( i_alist_item_at( list ) == 24 );
   
   i_alist_forth( list );

   CU_ASSERT( i_alist_item_at( list ) == 13 );

   CU_ASSERT( i_alist_count( list ) == 4 );

   i_alist_dispose( &list );
   i_alist_dispose( &list1 );

   return;
}

/**
   test_append_first_4
*/

void test_append_first_4( void )
{
   s_alist_t *list = NULL;
   s_alist_t *list1 = NULL;
   
   list = s_alist_make();
   list1 = s_alist_make();
   
   string_t *s1 = string_make_from_cstring( "a" ); 
   string_t *s2 = string_make_from_cstring( "b" ); 
   string_t *s3 = string_make_from_cstring( "c" ); 
   string_t *s4 = string_make_from_cstring( "d" ); 

   s_alist_put_last( list, s1 );
   s_alist_put_last( list, s2 );

   s_alist_put_last( list1, s3 );
   s_alist_put_last( list1, s4 );
   
   s_alist_start( list );
   
   s_alist_append_first( list, list1 );

   s_alist_start( list );
   CU_ASSERT( string_is_equal( s_alist_item_at( list ), s3 ) == 1 );

   s_alist_forth( list );
   CU_ASSERT( string_is_equal( s_alist_item_at( list ), s4 ) == 1 );

   s_alist_forth( list );
   CU_ASSERT( string_is_equal( s_alist_item_at( list ), s1 ) == 1 );

   s_alist_forth( list );
   CU_ASSERT( string_is_equal( s_alist_item_at( list ), s2 ) == 1 );

   CU_ASSERT( s_alist_count( list ) == 4 );

   s_alist_dispose( &list1 );
   s_alist_deep_dispose( &list );

   return;
}

int
add_test_append_first( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_append_first", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_append_first_1
   add_test_to_suite( p_suite, test_append_first_1, "test_append_first_1" );

   // test_append_first_2
   add_test_to_suite( p_suite, test_append_first_2, "test_append_first_2" );

   // test_append_first_3
   add_test_to_suite( p_suite, test_append_first_3, "test_append_first_3" );

   // test_append_first_4
   add_test_to_suite( p_suite, test_append_first_4, "test_append_first_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

