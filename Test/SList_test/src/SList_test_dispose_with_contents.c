/**
 @file SList_test_dispose_with_contents.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for SList_dispose_with_contents"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for SList_dispose_with_contents.

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
   test_dispose_with_contents_1
*/

void test_dispose_with_contents_1( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();

   CU_ASSERT( list != NULL );

   int_slist_dispose_with_contents( list );

   return;
}

/**
   test_dispose_with_contents_2
*/

void test_dispose_with_contents_2( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 12 );

   CU_ASSERT( list != NULL );

   int_slist_dispose_with_contents( list );

   return;
}

int
add_test_dispose_with_contents( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_dispose_with_contents", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_dispose_with_contents_1
   add_test_to_suite( p_suite, test_dispose_with_contents_1, "test_dispose_with_contents_1" );

   // test_dispose_with_contents_2
   add_test_to_suite( p_suite, test_dispose_with_contents_2, "test_dispose_with_contents_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

