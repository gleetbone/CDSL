/**
 @file SList_test_prune_and_dispose.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for SList_put"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for SList_item_at.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "int_SList.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_prune_and_dispose_1
*/

void test_prune_and_dispose_1( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   
   int_slist_put_last( list, 24 );

   int_slist_prune_and_dispose( list, 0, 1 );

   CU_ASSERT( int_slist_count( list ) == 0 );

   int_slist_dispose( list );

   return;
}

/**
   test_prune_and_dispose_2
*/

void test_prune_and_dispose_2( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );

   int_slist_prune_and_dispose( list, 0, 1 );

   CU_ASSERT( int_slist_count( list ) == 1 );

   int_slist_start( list );
   
   CU_ASSERT( int_slist_item_at( list ) == 13 );

   int_slist_dispose( list );

   return;
}

/**
   test_prune_and_dispose_3
*/

void test_prune_and_dispose_3( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );

   int_slist_prune_and_dispose( list, 1, 1 );

   CU_ASSERT( int_slist_count( list ) == 1 );

   int_slist_start( list );
   
   CU_ASSERT( int_slist_item_at( list ) == 24 );

   int_slist_dispose( list );

   return;
}

/**
   test_prune_and_dispose_4
*/

void test_prune_and_dispose_4( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );

   int_slist_prune_and_dispose( list, 0, 2 );

   CU_ASSERT( int_slist_count( list ) == 0 );

   int_slist_dispose( list );

   return;
}

/**
   test_prune_and_dispose_5
*/

void test_prune_and_dispose_5( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );
   int_slist_put_last( list, 7 );

   int_slist_prune_and_dispose( list, 0, 1 );
   
   int_slist_start( list );
   
   CU_ASSERT( int_slist_item_at( list ) == 13 );

   int_slist_forth( list );

   CU_ASSERT( int_slist_item_at( list ) == 7 );

   CU_ASSERT( int_slist_count( list ) == 2 );

   int_slist_dispose( list );

   return;
}

/**
   test_prune_and_dispose_6
*/

void test_prune_and_dispose_6( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );
   int_slist_put_last( list, 7 );

   int_slist_prune_and_dispose( list, 1, 1 );
   
   int_slist_start( list );
   
   CU_ASSERT( int_slist_item_at( list ) == 24 );

   int_slist_forth( list );

   CU_ASSERT( int_slist_item_at( list ) == 7 );

   CU_ASSERT( int_slist_count( list ) == 2 );

   int_slist_dispose( list );

   return;
}

/**
   test_prune_and_dispose_7
*/

void test_prune_and_dispose_7( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );
   int_slist_put_last( list, 7 );

   int_slist_prune_and_dispose( list, 2, 1 );
   
   int_slist_start( list );
   
   CU_ASSERT( int_slist_item_at( list ) == 24 );

   int_slist_forth( list );

   CU_ASSERT( int_slist_item_at( list ) == 13 );

   CU_ASSERT( int_slist_count( list ) == 2 );

   int_slist_dispose( list );

   return;
}

/**
   test_prune_and_dispose_8
*/

void test_prune_and_dispose_8( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );
   int_slist_put_last( list, 7 );

   int_slist_prune_and_dispose( list, 0, 2 );
   
   int_slist_start( list );
   
   CU_ASSERT( int_slist_item_at( list ) == 7 );

   CU_ASSERT( int_slist_count( list ) == 1 );

   int_slist_dispose( list );

   return;
}

/**
   test_prune_and_dispose_9
*/

void test_prune_and_dispose_9( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );
   int_slist_put_last( list, 7 );

   int_slist_prune_and_dispose( list, 1, 2 );
   
   int_slist_start( list );
   
   CU_ASSERT( int_slist_item_at( list ) == 24 );

   CU_ASSERT( int_slist_count( list ) == 1 );

   int_slist_dispose( list );

   return;
}

/**
   test_prune_and_dispose_10
*/

void test_prune_and_dispose_10( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );
   int_slist_put_last( list, 7 );
   int_slist_put_last( list, 31 );

   int_slist_prune_and_dispose( list, 1, 2 );
   
   int_slist_start( list );
   
   CU_ASSERT( int_slist_item_at( list ) == 24 );

   int_slist_forth( list );

   CU_ASSERT( int_slist_item_at( list ) == 31 );

   CU_ASSERT( int_slist_count( list ) == 2 );

   int_slist_dispose( list );

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

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */
