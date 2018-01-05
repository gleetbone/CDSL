/**
 @file AList_test_remove_first.c
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
   test_remove_first_1
*/

void test_remove_first_1( void )
{
   int_alist_t *list = NULL;

   list = int_alist_make();
   
   int_alist_put_last( list, 24 );

   int_alist_start( list );
   
   int_alist_remove_first( list );

   CU_ASSERT( int_alist_count( list ) == 0 );

   int_alist_dispose( list );

   return;
}

void test_remove_first_2( void )
{
   int_alist_t *list = NULL;

   list = int_alist_make();
   
   int_alist_put_last( list, 24 );
   int_alist_put_last( list, 13 );

   int_alist_remove_first( list );

   CU_ASSERT( int_alist_count( list ) == 1 );

   int_alist_start( list );
   
   CU_ASSERT( int_alist_item_at( list ) == 13 );

   int_alist_dispose( list );

   return;
}

void test_remove_first_3( void )
{
   int_alist_t *list = NULL;

   list = int_alist_make();
   
   int_alist_put_last( list, 24 );
   int_alist_put_last( list, 13 );
   int_alist_put_last( list, 7 );

   int_alist_start( list );
   
   int_alist_remove_first( list );

   CU_ASSERT( int_alist_item_at( list ) == 13 );

   CU_ASSERT( int_alist_count( list ) == 2 );

   int_alist_start( list );
   
   CU_ASSERT( int_alist_item_at( list ) == 13 );

   int_alist_forth( list );
   
   CU_ASSERT( int_alist_item_at( list ) == 7 );

   int_alist_dispose( list );

   return;
}


int
add_test_remove_first( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_remove_first", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_remove_first_1
   add_test_to_suite( p_suite, test_remove_first_1, "test_remove_first_1" );

   // test_remove_first_2
   add_test_to_suite( p_suite, test_remove_first_2, "test_remove_first_2" );

   // test_remove_first_3
   add_test_to_suite( p_suite, test_remove_first_3, "test_remove_first_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

