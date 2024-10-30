/**
 @file SList_test_as_array.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for SList_put"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for SList_t.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "int_SList.h"
#include "s_SList.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_as_array_1
*/

void test_as_array_1( void )
{
   int_slist_t *list = NULL;
   int32_t *array = NULL;
   int32_t count = 0;

   list = int_slist_make();
   int_slist_put_last( list, 24 );

   array = int_slist_as_array( list, &count );

   CU_ASSERT( count == 1 );

   CU_ASSERT( array[0] == 24 );

   free( array );
   int_slist_dispose( &list );

   return;
}

/**
   test_as_array_2
*/

void test_as_array_2( void )
{
   int_slist_t *list = NULL;
   int32_t *array = NULL;
   int32_t count = 0;

   list = int_slist_make();
   int_slist_put_last( list, 24 );
   
   int_slist_put_last( list, 13 );

   array = int_slist_as_array( list, &count );

   CU_ASSERT( array[0] == 24 );
   CU_ASSERT( array[1] == 13 );

   CU_ASSERT( count == 2 );

   free( array );
   int_slist_dispose( &list );

   return;
}

/**
   test_as_array_3
*/

void test_as_array_3( void )
{
   s_slist_t *list = NULL;
   string_t **array = NULL;
   int32_t count = 0;

   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   
   list = s_slist_make();
   
   s_slist_put_last( list, s1 );
   
   s_slist_put_last( list, s2 );

   array = s_slist_as_array( list, &count );

   CU_ASSERT( array[0] == s1 );
   CU_ASSERT( array[1] == s2 );

   CU_ASSERT( count == 2 );

   free( array );
   s_slist_deep_dispose( &list );

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

   // test_as_array_3
   add_test_to_suite( p_suite, test_as_array_3, "test_as_array_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

