/**
 @file SList_test_put_right.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for SList_put_right"
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
   test_put_right_1
*/

void test_put_right_1( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   int_slist_put_last( list, 24 );

   int_slist_start( list );

   int_slist_put_right( list, 13 );
   
   int_slist_start( list );

   CU_ASSERT( int_slist_item_at( list ) == 24 );

   int_slist_forth( list );

   CU_ASSERT( int_slist_item_at( list ) == 13 );

   CU_ASSERT( int_slist_count( list ) == 2 );

   int_slist_dispose( &list );

   return;
}

/**
   test_put_right_2
*/

void test_put_right_2( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 7 );

   int_slist_start( list );
   
   int_slist_put_right( list, 13 );

   int_slist_start( list );
   
   CU_ASSERT( int_slist_item_at( list ) == 24 );

   int_slist_forth( list );

   CU_ASSERT( int_slist_item_at( list ) == 13 );

   int_slist_forth( list );

   CU_ASSERT( int_slist_item_at( list ) == 7 );

   int_slist_dispose( &list );

   return;
}

/**
   test_put_right_3
*/

void test_put_right_3( void )
{
   s_slist_t *list = NULL;

   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s3 = string_make_from_cstring( "3" );
   
   list = s_slist_make();
   
   s_slist_put_last( list, s1 );
   s_slist_put_last( list, s3 );

   s_slist_start( list );
   
   s_slist_put_right( list, s2 );

   s_slist_start( list );
   
   CU_ASSERT( s_slist_item_at( list ) == s1 );

   s_slist_forth( list );

   CU_ASSERT( s_slist_item_at( list ) == s2 );

   s_slist_forth( list );

   CU_ASSERT( s_slist_item_at( list ) == s3 );

   s_slist_deep_dispose( &list );

   return;
}

int
add_test_put_right( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_put_right", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_put_right_1
   add_test_to_suite( p_suite, test_put_right_1, "test_put_right_1" );

   // test_put_right_2
   add_test_to_suite( p_suite, test_put_right_2, "test_put_right_2" );

   // test_put_right_3
   add_test_to_suite( p_suite, test_put_right_3, "test_put_right_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

