/**
 @file SList_test_go.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for SList_item_at"
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
   test_go_1
*/

void test_go_1( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   int_slist_put_last( list, 24 );

   int_slist_go( list, 0 );

   CU_ASSERT( int_slist_item_at( list ) == 24 );

   int_slist_dispose( list );

   return;
}

void test_go_2( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );
   int_slist_put_last( list, 7 );

   int_slist_go( list, 2 );

   CU_ASSERT( int_slist_item_at( list ) == 7 );

   int_slist_go( list, 0 );

   CU_ASSERT( int_slist_item_at( list ) == 24 );

   int_slist_go( list, 1 );

   CU_ASSERT( int_slist_item_at( list ) == 13 );

   int_slist_dispose( list );

   return;
}

/**
   test_go_3
*/

void test_go_3( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );
   int_slist_put_last( list, 7 );

   int_slist_go( list, 2 );

   CU_ASSERT( int_slist_item_at( list ) == 7 );

   int_slist_go( list, 0 );

   CU_ASSERT( int_slist_item_at( list ) == 24 );

   int_slist_go( list, 1 );

   CU_ASSERT( int_slist_item_at( list ) == 13 );

   int_slist_dispose( list );

   return;
}

int
add_test_go( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_go", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_go_1
   add_test_to_suite( p_suite, test_go_1, "test_go_1" );

   // test_go_2
   add_test_to_suite( p_suite, test_go_2, "test_go_2" );

   // test_go_3
   add_test_to_suite( p_suite, test_go_3, "test_go_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

