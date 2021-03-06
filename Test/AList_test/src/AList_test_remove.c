/**
 @file AList_test_remove.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for AList_put"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for AList_item_at.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "int_AList.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_remove_1
*/

void test_remove_1( void )
{
   int_alist_t *list = NULL;

   list = int_alist_make();
   
   int_alist_put_last( list, 24 );

   int_alist_remove( list, 0 );

   CU_ASSERT( int_alist_count( list ) == 0 );

   int_alist_dispose( list );

   return;
}

/**
   test_remove_2
*/

void test_remove_2( void )
{
   int_alist_t *list = NULL;

   list = int_alist_make();
   
   int_alist_put_last( list, 24 );
   int_alist_put_last( list, 13 );

   int_alist_remove( list, 0 );

   CU_ASSERT( int_alist_count( list ) == 1 );

   int_alist_start( list );
   
   CU_ASSERT( int_alist_item_at( list ) == 13 );

   int_alist_dispose( list );

   return;
}

/**
   test_remove_3
*/

void test_remove_3( void )
{
   int_alist_t *list = NULL;

   list = int_alist_make();
   
   int_alist_put_last( list, 24 );
   int_alist_put_last( list, 13 );

   int_alist_remove( list, 0 );

   CU_ASSERT( int_alist_count( list ) == 1 );

   int_alist_start( list );
   
   CU_ASSERT( int_alist_item_at( list ) == 13 );

   int_alist_dispose( list );

   return;
}

/**
   test_remove_4
*/

void test_remove_4( void )
{
   int_alist_t *list = NULL;

   list = int_alist_make();
   
   int_alist_put_last( list, 24 );
   int_alist_put_last( list, 13 );

   int_alist_remove( list, 1 );

   CU_ASSERT( int_alist_count( list ) == 1 );

   int_alist_start( list );
   
   CU_ASSERT( int_alist_item_at( list ) == 24 );

   int_alist_dispose( list );

   return;
}

/**
   test_remove_5
*/

void test_remove_5( void )
{
   int_alist_t *list = NULL;

   list = int_alist_make();
   int_alist_put_last( list, 24 );
   int_alist_put_last( list, 13 );
   int_alist_put_last( list, 7 );

   int_alist_remove( list, 1 );
   
   int_alist_start( list );
   
   CU_ASSERT( int_alist_item_at( list ) == 24 );

   int_alist_forth( list );

   CU_ASSERT( int_alist_item_at( list ) == 7 );

   CU_ASSERT( int_alist_count( list ) == 2 );

   int_alist_dispose( list );

   return;
}

/**
   test_remove_6
*/

void test_remove_6( void )
{
   int_alist_t *list = NULL;

   list = int_alist_make();
   int_alist_put_last( list, 24 );
   int_alist_put_last( list, 13 );
   int_alist_put_last( list, 7 );
   int_alist_put_last( list, 19 );

   int_alist_remove( list, 1 );
   int_alist_remove( list, 1 );
   int_alist_remove( list, 1 );

   CU_ASSERT( int_alist_count( list ) == 1 );

   int_alist_dispose( list );

   return;
}

int
add_test_remove( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_remove", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_remove_1
   add_test_to_suite( p_suite, test_remove_1, "test_remove_1" );

   // test_remove_2
   add_test_to_suite( p_suite, test_remove_2, "test_remove_2" );

   // test_remove_3
   add_test_to_suite( p_suite, test_remove_3, "test_remove_3" );

   // test_remove_4
   add_test_to_suite( p_suite, test_remove_4, "test_remove_4" );

   // test_remove_5
   add_test_to_suite( p_suite, test_remove_5, "test_remove_5" );

   // test_remove_6
   add_test_to_suite( p_suite, test_remove_6, "test_remove_6" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

