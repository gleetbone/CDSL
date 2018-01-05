/**
 @file SList_test_start.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for SList_forth"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for SList_forth.

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
   test_start_1
*/

void test_start_1( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );

   CU_ASSERT( int_slist_off( list ) == 1 );

   int_slist_start( list );

   CU_ASSERT( int_slist_off( list ) == 0 );

   CU_ASSERT( int_slist_item_at( list ) == 24 );

   int_slist_forth( list );
   
   CU_ASSERT( int_slist_item_at( list ) == 13 );

   int_slist_start( list );
   
   CU_ASSERT( int_slist_item_at( list ) == 24 );

   int_slist_dispose( list );

   return;
}

/**
   test_start_2
*/

void test_start_2( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );
   int_slist_put_last( list, 7 );

   int_slist_start( list );

   CU_ASSERT( int_slist_item_at( list ) == 24 );

   int_slist_forth( list );

   int_slist_forth( list );

   CU_ASSERT( int_slist_item_at( list ) == 7 );

   int_slist_start( list );

   CU_ASSERT( int_slist_item_at( list ) == 24 );

   int_slist_dispose( list );

   return;
}

int
add_test_start( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_start", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_start_1
   add_test_to_suite( p_suite, test_start_1, "test_start_1" );

   // test_start_2
   add_test_to_suite( p_suite, test_start_2, "test_start_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

