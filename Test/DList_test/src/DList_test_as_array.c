/**
 @file DList_test_as_array.c
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
   test_as_array_1
*/

void test_as_array_1( void )
{
   int_dlist_t *list = NULL;
   int32_t *array = NULL;
   int32_t count = 0;

   list = int_dlist_make();
   int_dlist_put_last( list, 24 );

   array = int_dlist_as_array( list, &count );

   CU_ASSERT( count == 1 );

   CU_ASSERT( array[0] == 24 );

   free( array );
   int_dlist_dispose( list );

   return;
}

void test_as_array_2( void )
{
   int_dlist_t *list = NULL;
   int32_t *array = NULL;
   int32_t count = 0;

   list = int_dlist_make();
   int_dlist_put_last( list, 24 );
   
   int_dlist_put_last( list, 13 );

   array = int_dlist_as_array( list, &count );

   CU_ASSERT( array[0] == 24 );
   CU_ASSERT( array[1] == 13 );

   CU_ASSERT( count == 2 );

   free( array );
   int_dlist_dispose( list );

   return;
}

int
add_test_as_array( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_as_array", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_as_array_1
   add_test_to_suite( p_suite, test_as_array_1, "test_as_array_1" );

   // test_as_array_2
   add_test_to_suite( p_suite, test_as_array_2, "test_as_array_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

