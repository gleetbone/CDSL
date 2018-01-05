/**
 @file DList_test_keep_first.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for DList_put"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for DList_item_at.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "int_DList.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_keep_first_1
*/

void test_keep_first_1( void )
{
   int_dlist_t *list = NULL;

   list = int_dlist_make();
   
   int_dlist_put_last( list, 24 );

   int_dlist_keep_first( list, 1 );

   CU_ASSERT( int_dlist_count( list ) == 1 );

   int_dlist_dispose( list );

   return;
}

/**
   test_keep_first_2
*/

void test_keep_first_2( void )
{
   int_dlist_t *list = NULL;

   list = int_dlist_make();
   
   int_dlist_put_last( list, 24 );

   int_dlist_keep_first( list, 0 );

   CU_ASSERT( int_dlist_count( list ) == 0 );

   int_dlist_dispose( list );

   return;
}

/**
   test_keep_first_3
*/

void test_keep_first_3( void )
{
   int_dlist_t *list = NULL;

   list = int_dlist_make();
   
   int_dlist_put_last( list, 24 );
   int_dlist_put_last( list, 13 );

   int_dlist_keep_first( list, 1 );

   CU_ASSERT( int_dlist_count( list ) == 1 );

   int_dlist_start( list );
   
   CU_ASSERT( int_dlist_item_at( list ) == 24 );

   int_dlist_dispose( list );

   return;
}

/**
   test_keep_first_4
*/

void test_keep_first_4( void )
{
   int_dlist_t *list = NULL;

   list = int_dlist_make();
   
   int_dlist_put_last( list, 24 );
   int_dlist_put_last( list, 13 );

   int_dlist_keep_first( list, 2 );

   CU_ASSERT( int_dlist_count( list ) == 2 );

   int_dlist_start( list );
   
   CU_ASSERT( int_dlist_item_at( list ) == 24 );

   int_dlist_forth( list );
   
   CU_ASSERT( int_dlist_item_at( list ) == 13 );

   int_dlist_dispose( list );

   return;
}

/**
   test_keep_first_5
*/

void test_keep_first_5( void )
{
   int_dlist_t *list = NULL;

   list = int_dlist_make();
   int_dlist_put_last( list, 24 );
   int_dlist_put_last( list, 13 );
   int_dlist_put_last( list, 7 );

   int_dlist_keep_first( list, 1 );
   
   int_dlist_start( list );
   
   CU_ASSERT( int_dlist_item_at( list ) == 24 );

   CU_ASSERT( int_dlist_count( list ) == 1 );

   int_dlist_dispose( list );

   return;
}

/**
   test_keep_first_6
*/

void test_keep_first_6( void )
{
   int_dlist_t *list = NULL;

   list = int_dlist_make();
   int_dlist_put_last( list, 24 );
   int_dlist_put_last( list, 13 );
   int_dlist_put_last( list, 7 );

   int_dlist_keep_first( list, 2 );
   
   int_dlist_start( list );
   
   CU_ASSERT( int_dlist_item_at( list ) == 24 );

   int_dlist_forth( list );
   
   CU_ASSERT( int_dlist_item_at( list ) == 13 );

   CU_ASSERT( int_dlist_count( list ) == 2 );

   int_dlist_dispose( list );

   return;
}

/**
   test_keep_first_7
*/

void test_keep_first_7( void )
{
   int_dlist_t *list = NULL;

   list = int_dlist_make();
   int_dlist_put_last( list, 24 );
   int_dlist_put_last( list, 13 );
   int_dlist_put_last( list, 7 );

   int_dlist_keep_first( list, 3 );
   
   CU_ASSERT( int_dlist_count( list ) == 3 );

   int_dlist_start( list );
   
   CU_ASSERT( int_dlist_item_at( list ) == 24 );

   int_dlist_forth( list );
   
   CU_ASSERT( int_dlist_item_at( list ) == 13 );

   int_dlist_forth( list );
   
   CU_ASSERT( int_dlist_item_at( list ) == 7);

   int_dlist_dispose( list );

   return;
}

int
add_test_keep_first( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_keep_first", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_keep_first_1
   add_test_to_suite( p_suite, test_keep_first_1, "test_keep_first_1" );

   // test_keep_first_2
   add_test_to_suite( p_suite, test_keep_first_2, "test_keep_first_2" );

   // test_keep_first_3
   add_test_to_suite( p_suite, test_keep_first_3, "test_keep_first_3" );

   // test_keep_first_4
   add_test_to_suite( p_suite, test_keep_first_4, "test_keep_first_4" );

   // test_keep_first_5
   add_test_to_suite( p_suite, test_keep_first_5, "test_keep_first_5" );

   // test_keep_first_6
   add_test_to_suite( p_suite, test_keep_first_6, "test_keep_first_6" );

   // test_keep_first_7
   add_test_to_suite( p_suite, test_keep_first_7, "test_keep_first_7" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

