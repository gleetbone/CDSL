/**
 @file AList_test_back.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for AList_forth"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for AList_forth.

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
   test_back_1
*/

void test_back_1( void )
{
   int_alist_t *list = NULL;

   list = int_alist_make();
   
   int_alist_put_last( list, 24 );
   int_alist_put_last( list, 13 );

   int_alist_start( list );

   CU_ASSERT( int_alist_item_at( list ) == 24 );

   int_alist_forth( list );
   
   CU_ASSERT( int_alist_item_at( list ) == 13 );

   int_alist_back( list );
   
   CU_ASSERT( int_alist_item_at( list ) == 24 );

   int_alist_dispose( list );

   return;
}

void test_back_2( void )
{
   int_alist_t *list = NULL;

   list = int_alist_make();
   int_alist_put_last( list, 24 );
   int_alist_put_last( list, 13 );
   int_alist_put_last( list, 7 );

   int_alist_start( list );

   CU_ASSERT( int_alist_item_at( list ) == 24 );

   int_alist_forth( list );

   CU_ASSERT( int_alist_item_at( list ) == 13 );

   int_alist_forth( list );

   CU_ASSERT( int_alist_item_at( list ) == 7 );

   int_alist_back( list );

   CU_ASSERT( int_alist_item_at( list ) == 13 );

   int_alist_back( list );

   CU_ASSERT( int_alist_item_at( list ) == 24 );

   int_alist_back( list );

   CU_ASSERT( int_alist_off( list ) == 1 );

   int_alist_dispose( list );

   return;
}

int
add_test_back( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_back", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_back_1
   add_test_to_suite( p_suite, test_back_1, "test_back_1" );

   // test_back_2
   add_test_to_suite( p_suite, test_back_2, "test_back_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

