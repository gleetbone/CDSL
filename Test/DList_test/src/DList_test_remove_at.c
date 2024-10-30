/**
 @file DList_test_remove_at.c
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
   test_remove_at_1
*/

void test_remove_at_1( void )
{
   i_dlist_t *list = NULL;

   list = i_dlist_make();
   
   i_dlist_put_last( list, 24 );

   i_dlist_start( list );
   
   i_dlist_remove_at( list );

   CU_ASSERT( i_dlist_count( list ) == 0 );

   i_dlist_dispose( &list );

   return;
}

/**
   test_remove_at_2
*/

void test_remove_at_2( void )
{
   i_dlist_t *list = NULL;

   list = i_dlist_make();
   
   i_dlist_put_last( list, 24 );
   i_dlist_put_last( list, 13 );

   i_dlist_start( list );
   
   i_dlist_remove_at( list );

   CU_ASSERT( i_dlist_count( list ) == 1 );

   i_dlist_start( list );
   
   CU_ASSERT( i_dlist_item_at( list ) == 13 );

   i_dlist_dispose( &list );

   return;
}

/**
   test_remove_at_3
*/

void test_remove_at_3( void )
{
   i_dlist_t *list = NULL;

   list = i_dlist_make();
   
   i_dlist_put_last( list, 24 );
   i_dlist_put_last( list, 13 );

   i_dlist_finish( list );
   
   i_dlist_remove_at( list );

   CU_ASSERT( i_dlist_count( list ) == 1 );

   i_dlist_start( list );
   
   CU_ASSERT( i_dlist_item_at( list ) == 24 );

   i_dlist_dispose( &list );

   return;
}

/**
   test_remove_at_4
*/

void test_remove_at_4( void )
{
   i_dlist_t *list = NULL;

   list = i_dlist_make();
   
   i_dlist_put_last( list, 24 );
   i_dlist_put_last( list, 13 );
   i_dlist_put_last( list, 7 );

   i_dlist_start( list );
   i_dlist_forth( list );
   
   i_dlist_remove_at( list );

   CU_ASSERT( i_dlist_item_at( list ) == 7 );

   CU_ASSERT( i_dlist_count( list ) == 2 );

   i_dlist_start( list );
   
   CU_ASSERT( i_dlist_item_at( list ) == 24 );

   i_dlist_forth( list );
   
   CU_ASSERT( i_dlist_item_at( list ) == 7 );

   i_dlist_dispose( &list );

   return;
}

/**
   test_remove_at_5
*/

void test_remove_at_5( void )
{
   s_dlist_t *list = NULL;

   list = s_dlist_make();
   
   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s3 = string_make_from_cstring( "3" );
   
   s_dlist_put_last( list, s1 );
   s_dlist_put_last( list, s2 );
   s_dlist_put_last( list, s3 );

   s_dlist_start( list );
   s_dlist_forth( list );
   
   s_dlist_remove_at( list );

   CU_ASSERT( s_dlist_item_at( list ) == s3 );

   CU_ASSERT( s_dlist_count( list ) == 2 );

   s_dlist_start( list );
   
   CU_ASSERT( s_dlist_item_at( list ) == s1 );

   s_dlist_forth( list );
   
   CU_ASSERT( s_dlist_item_at( list ) == s3 );

   string_deep_dispose( &s2 );
   s_dlist_deep_dispose( &list );

   return;
}


int
add_test_remove_at( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_remove_at", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_remove_at_1
   add_test_to_suite( p_suite, test_remove_at_1, "test_remove_at_1" );

   // test_remove_at_2
   add_test_to_suite( p_suite, test_remove_at_2, "test_remove_at_2" );

   // test_remove_at_3
   add_test_to_suite( p_suite, test_remove_at_3, "test_remove_at_3" );

   // test_remove_at_4
   add_test_to_suite( p_suite, test_remove_at_4, "test_remove_at_4" );

   // test_remove_at_5
   add_test_to_suite( p_suite, test_remove_at_5, "test_remove_at_5" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

