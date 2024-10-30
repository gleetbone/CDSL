/**
 @file AList_test_prune_and_dispose.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for AList_put"
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
   test_prune_and_dispose_1
*/

void test_prune_and_dispose_1( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   
   i_alist_put_last( list, 24 );

   i_alist_prune_and_dispose( list, 0, 1 );

   CU_ASSERT( i_alist_count( list ) == 0 );

   i_alist_dispose( &list );

   return;
}

/**
   test_prune_and_dispose_2
*/

void test_prune_and_dispose_2( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   
   i_alist_put_last( list, 24 );
   i_alist_put_last( list, 13 );

   i_alist_prune_and_dispose( list, 0, 1 );

   CU_ASSERT( i_alist_count( list ) == 1 );

   i_alist_start( list );
   
   CU_ASSERT( i_alist_item_at( list ) == 13 );

   i_alist_dispose( &list );

   return;
}

/**
   test_prune_and_dispose_3
*/

void test_prune_and_dispose_3( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   
   i_alist_put_last( list, 24 );
   i_alist_put_last( list, 13 );

   i_alist_prune_and_dispose( list, 1, 1 );

   CU_ASSERT( i_alist_count( list ) == 1 );

   i_alist_start( list );
   
   CU_ASSERT( i_alist_item_at( list ) == 24 );

   i_alist_dispose( &list );

   return;
}

/**
   test_prune_and_dispose_4
*/

void test_prune_and_dispose_4( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   
   i_alist_put_last( list, 24 );
   i_alist_put_last( list, 13 );

   i_alist_prune_and_dispose( list, 0, 2 );

   CU_ASSERT( i_alist_count( list ) == 0 );

   i_alist_dispose( &list );

   return;
}


/**
   test_prune_and_dispose_5
*/

void test_prune_and_dispose_5( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   i_alist_put_last( list, 24 );
   i_alist_put_last( list, 13 );
   i_alist_put_last( list, 7 );

   i_alist_prune_and_dispose( list, 0, 1 );
   
   i_alist_start( list );
   
   CU_ASSERT( i_alist_item_at( list ) == 13 );

   i_alist_forth( list );

   CU_ASSERT( i_alist_item_at( list ) == 7 );

   CU_ASSERT( i_alist_count( list ) == 2 );

   i_alist_dispose( &list );

   return;
}

/**
   test_prune_and_dispose_6
*/

void test_prune_and_dispose_6( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   i_alist_put_last( list, 24 );
   i_alist_put_last( list, 13 );
   i_alist_put_last( list, 7 );

   i_alist_prune_and_dispose( list, 1, 1 );
   
   i_alist_start( list );
   
   CU_ASSERT( i_alist_item_at( list ) == 24 );

   i_alist_forth( list );

   CU_ASSERT( i_alist_item_at( list ) == 7 );

   CU_ASSERT( i_alist_count( list ) == 2 );

   i_alist_dispose( &list );

   return;
}

/**
   test_prune_and_dispose_7
*/

void test_prune_and_dispose_7( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   i_alist_put_last( list, 24 );
   i_alist_put_last( list, 13 );
   i_alist_put_last( list, 7 );

   i_alist_prune_and_dispose( list, 2, 1 );
   
   i_alist_start( list );
   
   CU_ASSERT( i_alist_item_at( list ) == 24 );

   i_alist_forth( list );

   CU_ASSERT( i_alist_item_at( list ) == 13 );

   CU_ASSERT( i_alist_count( list ) == 2 );

   i_alist_dispose( &list );

   return;
}

/**
   test_prune_and_dispose_8
*/

void test_prune_and_dispose_8( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   i_alist_put_last( list, 24 );
   i_alist_put_last( list, 13 );
   i_alist_put_last( list, 7 );

   i_alist_prune_and_dispose( list, 0, 2 );
   
   i_alist_start( list );
   
   CU_ASSERT( i_alist_item_at( list ) == 7 );

   CU_ASSERT( i_alist_count( list ) == 1 );

   i_alist_dispose( &list );

   return;
}

/**
   test_prune_and_dispose_9
*/

void test_prune_and_dispose_9( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   i_alist_put_last( list, 24 );
   i_alist_put_last( list, 13 );
   i_alist_put_last( list, 7 );

   i_alist_prune_and_dispose( list, 1, 2 );
   
   i_alist_start( list );
   
   CU_ASSERT( i_alist_item_at( list ) == 24 );

   CU_ASSERT( i_alist_count( list ) == 1 );

   i_alist_dispose( &list );

   return;
}

/**
   test_prune_and_dispose_10
*/

void test_prune_and_dispose_10( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   i_alist_put_last( list, 24 );
   i_alist_put_last( list, 13 );
   i_alist_put_last( list, 7 );
   i_alist_put_last( list, 31 );

   i_alist_prune_and_dispose( list, 1, 2 );
   
   i_alist_start( list );
   
   CU_ASSERT( i_alist_item_at( list ) == 24 );

   i_alist_forth( list );

   CU_ASSERT( i_alist_item_at( list ) == 31 );

   CU_ASSERT( i_alist_count( list ) == 2 );

   i_alist_dispose( &list );

   return;
}

/**
   test_prune_and_dispose_10a
*/

void test_prune_and_dispose_10a( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   i_alist_put_last( list, 24 );
   i_alist_put_last( list, 13 );
   i_alist_put_last( list, 7 );
   i_alist_put_last( list, 31 );

   i_alist_prune_and_dispose( list, 1, 3 );
   
   i_alist_start( list );
   
   CU_ASSERT( i_alist_item_at( list ) == 24 );

   CU_ASSERT( i_alist_count( list ) == 1 );

   i_alist_dispose( &list );

   return;
}

/**
   test_prune_and_dispose_11
*/

void test_prune_and_dispose_11( void )
{
   s_alist_t *list = NULL;

   list = s_alist_make();
   
   string_t *s1 = string_make_from_cstring( "a" ); 
   string_t *s2 = string_make_from_cstring( "b" ); 
   string_t *s3 = string_make_from_cstring( "c" ); 
   string_t *s4 = string_make_from_cstring( "d" ); 
   
   s_alist_put_last( list, s1 );
   s_alist_put_last( list, s2 );
   s_alist_put_last( list, s3 );
   s_alist_put_last( list, s4 );

   s_alist_prune_and_dispose( list, 1, 2 );
   
   s_alist_start( list );
   
   CU_ASSERT( string_is_equal( s_alist_item_at( list ), s1 ) == 1 );
   s_alist_forth( list );

   CU_ASSERT( string_is_equal( s_alist_item_at( list ), s4 ) == 1 );
   
   CU_ASSERT( s_alist_count( list ) == 2 );

   s_alist_deep_dispose( &list );

   return;
}

int
add_test_prune_and_dispose( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_prune_and_dispose", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_prune_and_dispose_1
   add_test_to_suite( p_suite, test_prune_and_dispose_1, "test_prune_and_dispose_1" );

   // test_prune_and_dispose_2
   add_test_to_suite( p_suite, test_prune_and_dispose_2, "test_prune_and_dispose_2" );

   // test_prune_and_dispose_3
   add_test_to_suite( p_suite, test_prune_and_dispose_3, "test_prune_and_dispose_3" );

   // test_prune_and_dispose_4
   add_test_to_suite( p_suite, test_prune_and_dispose_4, "test_prune_and_dispose_4" );

   // test_prune_and_dispose_5
   add_test_to_suite( p_suite, test_prune_and_dispose_5, "test_prune_and_dispose_5" );

   // test_prune_and_dispose_6
   add_test_to_suite( p_suite, test_prune_and_dispose_6, "test_prune_and_dispose_6" );

   // test_prune_and_dispose_7
   add_test_to_suite( p_suite, test_prune_and_dispose_7, "test_prune_and_dispose_7" );

   // test_prune_and_dispose_8
   add_test_to_suite( p_suite, test_prune_and_dispose_8, "test_prune_and_dispose_8" );

   // test_prune_and_dispose_9
   add_test_to_suite( p_suite, test_prune_and_dispose_9, "test_prune_and_dispose_9" );

   // test_prune_and_dispose_10
   add_test_to_suite( p_suite, test_prune_and_dispose_10, "test_prune_and_dispose_10" );

   // test_prune_and_dispose_10a
   add_test_to_suite( p_suite, test_prune_and_dispose_10a, "test_prune_and_dispose_10a" );

   // test_prune_and_dispose_11
   add_test_to_suite( p_suite, test_prune_and_dispose_11, "test_prune_and_dispose_11" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

