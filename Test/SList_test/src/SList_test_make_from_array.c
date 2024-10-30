/**
 @file SList_test_make_from_array.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for SList_make_from_array"
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
   test_make_from_array_1
*/

void test_make_from_array_1( void )
{
   int32_t array[3] = { 0, 0, 0 };
   
   int_slist_t *list = int_slist_make_from_array( array, 0 );
   
   CU_ASSERT( list != NULL );
   CU_ASSERT( int_slist_count( list ) == 0 );
   CU_ASSERT( int_slist_is_empty( list ) == 1 );
  
   int_slist_dispose( &list );

   return;
}

/**
   test_make_from_array_2
*/

void test_make_from_array_2( void )
{
   int32_t array[3] = { 24, 0, 0 };
   
   int_slist_t *list = int_slist_make_from_array( array, 1 );
   
   CU_ASSERT( list != NULL );
   CU_ASSERT( int_slist_count( list ) == 1 );
   CU_ASSERT( int_slist_is_empty( list ) == 0 );
   CU_ASSERT( int_slist_first( list ) == 24 );
 
   int_slist_dispose( &list );

   return;
}

/**
   test_make_from_array_3
*/

void test_make_from_array_3( void )
{
   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s3 = string_make_from_cstring( "3" );
   
   string_t *array[3] = { s1, NULL, NULL };
   
   s_slist_t *list = s_slist_make_from_array( array, 1 );
   
   CU_ASSERT( list != NULL );
   CU_ASSERT( s_slist_count( list ) == 1 );
   CU_ASSERT( s_slist_is_empty( list ) == 0 );
   CU_ASSERT( s_slist_first( list ) == s1 );
 
   s_slist_deep_dispose( &list );
   string_deep_dispose( &s2 );
   string_deep_dispose( &s3 );

   return;
}

int
add_test_make_from_array( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make_from_array", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_from_array_1
   add_test_to_suite( p_suite, test_make_from_array_1, "test_make_from_array_1" );

   // test_make_from_array_2
   add_test_to_suite( p_suite, test_make_from_array_2, "test_make_from_array_2" );

   // test_make_from_array_3
   add_test_to_suite( p_suite, test_make_from_array_3, "test_make_from_array_3" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

