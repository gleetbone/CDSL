/**
 @file SList_test_replace_at.c
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
   test_replace_at_1
*/

void test_replace_at_1( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   int_slist_put( list, 24, 0 );

   int_slist_start( list );

   int_slist_replace_at( list, 25 );

   CU_ASSERT( int_slist_item_at( list ) == 25 );

   int_slist_dispose( &list );

   return;
}

/**
   test_replace_at_2
*/

void test_replace_at_2( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );
   int_slist_put_last( list, 7 );

   int_slist_go( list, 2 );

   int_slist_replace_at( list, 8 );

   int_slist_go( list, 1 );

   int_slist_replace_at( list, 14 );

   int_slist_go( list, 0 );

   int_slist_replace_at( list, 25 );

   int_slist_start( list );

   CU_ASSERT( int_slist_item_at( list ) == 25 );

   int_slist_forth( list );

   CU_ASSERT( int_slist_item_at( list ) == 14 );

   int_slist_forth( list );

   CU_ASSERT( int_slist_item_at( list ) == 8 );

   CU_ASSERT( int_slist_count( list ) == 3 );

   int_slist_dispose( &list );

   return;
}

/**
   test_replace_at_3
*/

void test_replace_at_3( void )
{
   s_slist_t *list = NULL;

   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s3 = string_make_from_cstring( "3" );
   
   string_t *s4 = string_make_from_cstring( "4" );
   string_t *s5 = string_make_from_cstring( "5" );
   string_t *s6 = string_make_from_cstring( "6" );
   
   list = s_slist_make();
   
   s_slist_put_last( list, s1 );
   s_slist_put_last( list, s2 );
   s_slist_put_last( list, s3 );

   s_slist_go( list, 2 );

   s_slist_replace_at( list, s6 );

   s_slist_go( list, 1 );

   s_slist_replace_at( list, s5 );

   s_slist_go( list, 0 );

   s_slist_replace_at( list, s4 );

   s_slist_start( list );

   CU_ASSERT( s_slist_item_at( list ) == s4 );

   s_slist_forth( list );

   CU_ASSERT( s_slist_item_at( list ) == s5 );

   s_slist_forth( list );

   CU_ASSERT( s_slist_item_at( list ) == s6 );

   CU_ASSERT( s_slist_count( list ) == 3 );

   s_slist_deep_dispose( &list );
   string_deep_dispose( &s1 );
   string_deep_dispose( &s2 );
   string_deep_dispose( &s3 );

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

