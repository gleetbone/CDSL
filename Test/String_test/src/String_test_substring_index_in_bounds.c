/**
 @file string_test_substring_index_in_bounds.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for string_make_from_cstring"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for string_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "String.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_substring_index_in_bounds_1
*/

void test_substring_index_in_bounds_1( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "A" );
   string1 = string_make_from_cstring( "A" );
   
   CU_ASSERT( string_substring_index_in_bounds( string, string1, 0, 0 ) == 0 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

/**
   test_substring_index_in_bounds_2
*/

void test_substring_index_in_bounds_2( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "AB" );
   string1 = string_make_from_cstring( "B" );
   
   CU_ASSERT( string_substring_index_in_bounds( string, string1, 0, 1 ) == 1 );
 
   CU_ASSERT( string_substring_index_in_bounds( string, string1, 0, 0 ) == -1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

/**
   test_substring_index_in_bounds_3
*/

void test_substring_index_in_bounds_3( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABC" );
   string1 = string_make_from_cstring( "B" );
   
   CU_ASSERT( string_substring_index_in_bounds( string, string1, 0, 2 ) == 1 );
 
   CU_ASSERT( string_substring_index_in_bounds( string, string1, 0, 1 ) == 1 );
 
   CU_ASSERT( string_substring_index_in_bounds( string, string1, 1, 2 ) == 1 );
 
   CU_ASSERT( string_substring_index_in_bounds( string, string1, 0, 0 ) == -1 );
 
   CU_ASSERT( string_substring_index_in_bounds( string, string1, 2, 2 ) == -1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

/**
   test_substring_index_in_bounds_4
*/

void test_substring_index_in_bounds_4( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABCDEF" );
   string1 = string_make_from_cstring( "BC" );
   
   CU_ASSERT( string_substring_index_in_bounds( string, string1, 0, 5 ) == 1 );
 
   CU_ASSERT( string_substring_index_in_bounds( string, string1, 0, 2 ) == 1 );
 
   CU_ASSERT( string_substring_index_in_bounds( string, string1, 0, 5 ) == 1 );
 
   CU_ASSERT( string_substring_index_in_bounds( string, string1, 1, 5 ) == 1 );
 
   CU_ASSERT( string_substring_index_in_bounds( string, string1, 2, 5 ) == -1 );
 
   CU_ASSERT( string_substring_index_in_bounds( string, string1, 4, 5 ) == -1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

/**
   test_substring_index_in_bounds_5
*/

void test_substring_index_in_bounds_5( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABCDEFABCDEF" );
   string1 = string_make_from_cstring( "BC" );
   
   CU_ASSERT( string_substring_index_in_bounds( string, string1, 0, 7 ) == 1 );
 
   CU_ASSERT( string_substring_index_in_bounds( string, string1, 0, 2 ) == 1 );
 
   CU_ASSERT( string_substring_index_in_bounds( string, string1, 0, 5 ) == 1 );
 
   CU_ASSERT( string_substring_index_in_bounds( string, string1, 1, 5 ) == 1 );
 
   CU_ASSERT( string_substring_index_in_bounds( string, string1, 4, 11 ) == 7 );
 
   CU_ASSERT( string_substring_index_in_bounds( string, string1, 8, 11 ) == -1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

int
add_test_substring_index_in_bounds( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_substring_index_in_bounds", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_substring_index_in_bounds_1
   add_test_to_suite( p_suite, test_substring_index_in_bounds_1, "test_substring_index_in_bounds_1" );

   // test_substring_index_in_bounds_2
   add_test_to_suite( p_suite, test_substring_index_in_bounds_2, "test_substring_index_in_bounds_2" );

   // test_substring_index_in_bounds_3
   add_test_to_suite( p_suite, test_substring_index_in_bounds_3, "test_substring_index_in_bounds_4" );

   // test_substring_index_in_bounds_4
   add_test_to_suite( p_suite, test_substring_index_in_bounds_4, "test_substring_index_in_bounds_4" );

   // test_substring_index_in_bounds_5
   add_test_to_suite( p_suite, test_substring_index_in_bounds_5, "test_substring_index_in_bounds_5" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

