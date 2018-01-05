/**
 @file SList_test_off.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for SList_last"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for SList_last.

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
   test_off_1
*/

void test_off_1( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   CU_ASSERT( int_slist_off( list ) == 1 );
   
   int_slist_dispose( list );

   return;
}

/**
   test_off_2
*/

void test_off_2( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   
   CU_ASSERT( int_slist_off( list ) == 1 );
   
   int_slist_start( list );
   
   CU_ASSERT( int_slist_off( list ) == 1 );
   
   int_slist_put_last( list, 24 );
   
   CU_ASSERT( int_slist_off( list ) == 1 );
      
   int_slist_start( list );
   
   CU_ASSERT( int_slist_off( list ) == 0 );
   
   int_slist_dispose( list );

   return;
}

int
add_test_off( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_off", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_off_1
   add_test_to_suite( p_suite, test_off_1, "test_off_1" );

   // test_off_2
   add_test_to_suite( p_suite, test_off_2, "test_off_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

