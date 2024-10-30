/**
 @file DList_test_sort.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for DList_item_at"
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


static
int32_t
sort_func( int32_t v1, int32_t v2 )
{
   int32_t result = 0;
   
   if ( v1 > v2 )
   {
      result = -1;
   }
   else if ( v1 < v2 )
   {
      result = +1;
   }
   
   return result;
}

static
int32_t
s_sort_func( string_t *v1, string_t *v2 )
{
   int32_t result = 0;
   
   if ( string_is_greater_than( v1, v2 ) == 1 )
   {
      result = -1;
   }
   else if ( string_is_less_than( v1, v2 ) == 1 )
   {
      result = +1;
   }
   
   return result;
}

/**
   test_sort_1
*/

void test_sort_1( void )
{
   i_dlist_t *list = NULL;

   list = i_dlist_make();

   i_dlist_sort( list, sort_func );

   CU_ASSERT( i_dlist_count( list ) == 0 );

   i_dlist_dispose( &list );

   return;
}

/**
   test_sort_2
*/

void test_sort_2( void )
{
   i_dlist_t *list = NULL;

   list = i_dlist_make();
   i_dlist_put_last( list, 24 );

   i_dlist_sort( list, sort_func );

   CU_ASSERT( i_dlist_count( list ) == 1 );

   i_dlist_dispose( &list );

   return;
}

/**
   test_sort_3
*/

void test_sort_3( void )
{
   i_dlist_t *list = NULL;

   list = i_dlist_make();
   i_dlist_put_last( list, 13 );
   i_dlist_put_last( list, 24 );

   i_dlist_sort( list, sort_func );
   
   i_dlist_start( list );

   CU_ASSERT( i_dlist_item_at( list ) == 24 );

   i_dlist_forth( list );

   CU_ASSERT( i_dlist_item_at( list ) == 13 );

   i_dlist_dispose( &list );

   return;
}

/**
   test_sort_4
*/

void test_sort_4( void )
{
   i_dlist_t *list = NULL;

   list = i_dlist_make();
   i_dlist_put_last( list, 13 );
   i_dlist_put_last( list, 24 );
   i_dlist_put_last( list, 7 );
   i_dlist_put_last( list, 17 );

   i_dlist_sort( list, sort_func );

   i_dlist_start( list );

   CU_ASSERT( i_dlist_item_at( list ) == 24 );

   i_dlist_forth( list );

   CU_ASSERT( i_dlist_item_at( list ) == 17 );

   i_dlist_dispose( &list );

   return;
}

/**
   test_sort_5
*/

void test_sort_5( void )
{
   s_dlist_t *list = NULL;

   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s3 = string_make_from_cstring( "3" );
   string_t *s4 = string_make_from_cstring( "4" );
   
   list = s_dlist_make();
   s_dlist_put_last( list, s3 );
   s_dlist_put_last( list, s1 );
   s_dlist_put_last( list, s4 );
   s_dlist_put_last( list, s2 );

   s_dlist_sort( list, s_sort_func );

   s_dlist_start( list );

   CU_ASSERT( s_dlist_item_at( list ) == s4 );

   s_dlist_forth( list );

   CU_ASSERT( s_dlist_item_at( list ) == s3 );

   s_dlist_deep_dispose( &list );

   return;
}

int
add_test_sort( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_sort", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_sort_1
   add_test_to_suite( p_suite, test_sort_1, "test_sort_1" );

   // test_sort_2
   add_test_to_suite( p_suite, test_sort_2, "test_sort_2" );

   // test_sort_3
   add_test_to_suite( p_suite, test_sort_3, "test_sort_3" );

   // test_sort_4
   add_test_to_suite( p_suite, test_sort_4, "test_sort_4" );

   // test_sort_5
   add_test_to_suite( p_suite, test_sort_5, "test_sort_5" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

