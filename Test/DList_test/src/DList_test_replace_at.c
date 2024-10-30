/**
 @file DList_test_replace_at.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for DList_put"
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
   test_replace_at_1
*/

void test_replace_at_1( void )
{
   i_dlist_t *list = NULL;

   list = i_dlist_make();
   i_dlist_put( list, 24, 0 );

   i_dlist_start( list );
   
   i_dlist_replace_at( list, 25 );

   CU_ASSERT( i_dlist_item_at( list ) == 25 );

   i_dlist_dispose( &list );

   return;
}

/**
   test_replace_at_2
*/

void test_replace_at_2( void )
{
   i_dlist_t *list = NULL;

   list = i_dlist_make();
   i_dlist_put_last( list, 24 );
   i_dlist_put_last( list, 13 );
   i_dlist_put_last( list, 7 );

   i_dlist_finish( list );
   
   i_dlist_replace_at( list, 8 );
   
   i_dlist_back( list );
   
   i_dlist_replace_at( list, 14 );
   
   i_dlist_back( list );
   
   i_dlist_replace_at( list, 25 );

   i_dlist_start( list );
   
   CU_ASSERT( i_dlist_item_at( list ) == 25 );

   i_dlist_forth( list );

   CU_ASSERT( i_dlist_item_at( list ) == 14 );

   i_dlist_forth( list );

   CU_ASSERT( i_dlist_item_at( list ) == 8 );

   CU_ASSERT( i_dlist_count( list ) == 3 );

   i_dlist_dispose( &list );

   return;
}

/**
   test_replace_at_3
*/

void test_replace_at_3( void )
{
   s_dlist_t *list = NULL;

   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s3 = string_make_from_cstring( "3" );
   
   string_t *s4 = string_make_from_cstring( "4" );
   string_t *s5 = string_make_from_cstring( "5" );
   string_t *s6 = string_make_from_cstring( "6" );
   
   list = s_dlist_make();
   s_dlist_put_last( list, s1 );
   s_dlist_put_last( list, s2 );
   s_dlist_put_last( list, s3 );

   s_dlist_finish( list );
   
   s_dlist_replace_at( list, s6 );
   
   s_dlist_back( list );
   
   s_dlist_replace_at( list, s5 );
   
   s_dlist_back( list );
   
   s_dlist_replace_at( list, s4 );

   s_dlist_start( list );
   
   CU_ASSERT( s_dlist_item_at( list ) == s4 );

   s_dlist_forth( list );

   CU_ASSERT( s_dlist_item_at( list ) == s5 );

   s_dlist_forth( list );

   CU_ASSERT( s_dlist_item_at( list ) == s6 );

   CU_ASSERT( s_dlist_count( list ) == 3 );

   string_deep_dispose( &s1 );
   string_deep_dispose( &s2 );
   string_deep_dispose( &s3 );
   
   s_dlist_deep_dispose( &list );

   return;
}

int
add_test_replace_at( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_replace_at", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_replace_at_1
   add_test_to_suite( p_suite, test_replace_at_1, "test_replace_at_1" );

   // test_replace_at_2
   add_test_to_suite( p_suite, test_replace_at_2, "test_replace_at_2" );

   // test_replace_at_3
   add_test_to_suite( p_suite, test_replace_at_3, "test_replace_at_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

