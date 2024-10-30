/**
 @file string_utf8_test_substring_index_in_bounds_cstring.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for string_utf8_make_from_cstring"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)

 @section Description

 Unit tests for string_utf8_t

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "String_utf8.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_substring_index_in_bounds_cstring_utf8_1
*/

void test_substring_index_in_bounds_cstring_utf8_1( void )
{
   string_utf8_t *string = NULL;

   string = string_utf8_make_from_cstring( "A" );

   CU_ASSERT( string_utf8_substring_index_in_bounds_cstring( string, "A", 0, 0 ) == 0 );

   string_utf8_deep_dispose( &string );

   return;
}

/**
   test_substring_index_in_bounds_cstring_utf8_2
*/

void test_substring_index_in_bounds_cstring_utf8_2( void )
{
   string_utf8_t *string = NULL;

   string = string_utf8_make_from_cstring( "AB" );

   CU_ASSERT( string_utf8_substring_index_in_bounds_cstring( string, "B", 0, 1 ) == 1 );

   CU_ASSERT( string_utf8_substring_index_in_bounds_cstring( string, "B", 0, 0 ) == -1 );

   string_utf8_deep_dispose( &string );

   return;
}

/**
   test_substring_index_in_bounds_cstring_utf8_3
*/

void test_substring_index_in_bounds_cstring_utf8_3( void )
{
   string_utf8_t *string = NULL;

   string = string_utf8_make_from_cstring( "ABC" );

   CU_ASSERT( string_utf8_substring_index_in_bounds_cstring( string, "B", 0, 2 ) == 1 );

   CU_ASSERT( string_utf8_substring_index_in_bounds_cstring( string, "B", 0, 1 ) == 1 );

   CU_ASSERT( string_utf8_substring_index_in_bounds_cstring( string, "B", 1, 2 ) == 1 );

   CU_ASSERT( string_utf8_substring_index_in_bounds_cstring( string, "B", 0, 0 ) == -1 );

   CU_ASSERT( string_utf8_substring_index_in_bounds_cstring( string, "B", 2, 2 ) == -1 );

   string_utf8_deep_dispose( &string );

   return;
}

/**
   test_substring_index_in_bounds_cstring_utf8_4
*/

void test_substring_index_in_bounds_cstring_utf8_4( void )
{
   string_utf8_t *string = NULL;

   string = string_utf8_make_from_cstring( "ABCDEF" );

   CU_ASSERT( string_utf8_substring_index_in_bounds_cstring( string, "BC", 0, 5 ) == 1 );

   CU_ASSERT( string_utf8_substring_index_in_bounds_cstring( string, "BC", 0, 2 ) == 1 );

   CU_ASSERT( string_utf8_substring_index_in_bounds_cstring( string, "BC", 0, 5 ) == 1 );

   CU_ASSERT( string_utf8_substring_index_in_bounds_cstring( string, "BC", 1, 5 ) == 1 );

   CU_ASSERT( string_utf8_substring_index_in_bounds_cstring( string, "BC", 2, 5 ) == -1 );

   CU_ASSERT( string_utf8_substring_index_in_bounds_cstring( string, "BC", 4, 5 ) == -1 );

   string_utf8_deep_dispose( &string );

   return;
}

/**
   test_substring_index_in_bounds_cstring_utf8_5
*/

void test_substring_index_in_bounds_cstring_utf8_5( void )
{
   string_utf8_t *string = NULL;

   string = string_utf8_make_from_cstring( "ABCDEFABCDEF" );

   CU_ASSERT( string_utf8_substring_index_in_bounds_cstring( string, "BC", 0, 7 ) == 1 );

   CU_ASSERT( string_utf8_substring_index_in_bounds_cstring( string, "BC", 0, 2 ) == 1 );

   CU_ASSERT( string_utf8_substring_index_in_bounds_cstring( string, "BC", 0, 5 ) == 1 );

   CU_ASSERT( string_utf8_substring_index_in_bounds_cstring( string, "BC", 1, 5 ) == 1 );

   CU_ASSERT( string_utf8_substring_index_in_bounds_cstring( string, "BC", 4, 11 ) == 7 );

   CU_ASSERT( string_utf8_substring_index_in_bounds_cstring( string, "BC", 8, 11 ) == -1 );

   string_utf8_deep_dispose( &string );

   return;
}

int
add_test_substring_index_in_bounds_cstring( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_substring_index_in_bounds_cstring", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_substring_index_in_bounds_cstring_utf8_1
   add_test_to_suite( p_suite, test_substring_index_in_bounds_cstring_utf8_1, "test_substring_index_in_bounds_cstring_utf8_1" );

   // test_substring_index_in_bounds_cstring_utf8_2
   add_test_to_suite( p_suite, test_substring_index_in_bounds_cstring_utf8_2, "test_substring_index_in_bounds_cstring_utf8_2" );

   // test_substring_index_in_bounds_cstring_utf8_3
   add_test_to_suite( p_suite, test_substring_index_in_bounds_cstring_utf8_3, "test_substring_index_in_bounds_cstring_utf8_3" );

   // test_substring_index_in_bounds_cstring_utf8_4
   add_test_to_suite( p_suite, test_substring_index_in_bounds_cstring_utf8_4, "test_substring_index_in_bounds_cstring_utf8_4" );

   // test_substring_index_in_bounds_cstring_utf8_5
   add_test_to_suite( p_suite, test_substring_index_in_bounds_cstring_utf8_5, "test_substring_index_in_bounds_cstring_utf8_5" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

