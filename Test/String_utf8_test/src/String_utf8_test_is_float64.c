/**
 @file string_utf8_test_is_float64.c
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
   test_is_float64_1
*/

void test_is_float64_1( void )
{
   string_utf8_t *string = NULL;

   string = string_utf8_make_from_cstring( "abcd" );

   CU_ASSERT( string_utf8_is_float64( string ) == 0 );

   string_utf8_deep_dispose( &string );

   return;
}

/**
   test_is_float64_2
*/

void test_is_float64_2( void )
{
   string_utf8_t *string = NULL;

   string = string_utf8_make_from_cstring( "123" );

   CU_ASSERT( string_utf8_is_float64( string ) == 1 );

   string_utf8_deep_dispose( &string );

   return;
}

/**
   test_is_float64_3
*/

void test_is_float64_3( void )
{
   string_utf8_t *string = NULL;

   string = string_utf8_make_from_cstring( "123.456" );

   CU_ASSERT( string_utf8_is_float64( string ) == 1 );

   string_utf8_deep_dispose( &string );

   return;
}

/**
   test_is_float64_4
*/

void test_is_float64_4( void )
{
   string_utf8_t *string = NULL;

   string = string_utf8_make_from_cstring( "1E2" );

   CU_ASSERT( string_utf8_is_float64( string ) == 1 );

   string_utf8_deep_dispose( &string );

   return;
}

/**
   test_is_float64_5
*/

void test_is_float64_5( void )
{
   string_utf8_t *string = NULL;

   string = string_utf8_make_from_cstring( ".123" );

   CU_ASSERT( string_utf8_is_float64( string ) == 1 );

   string_utf8_deep_dispose( &string );

   return;
}

/**
   test_is_float64_6
*/

void test_is_float64_6( void )
{
   string_utf8_t *string = NULL;

   string = string_utf8_make_from_cstring( ".123E4" );

   CU_ASSERT( string_utf8_is_float64( string ) == 1 );

   string_utf8_deep_dispose( &string );

   return;
}

int
add_test_is_float64( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_float64", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_float64_1
   add_test_to_suite( p_suite, test_is_float64_1, "test_is_float64_1" );

   // test_is_float64_2
   add_test_to_suite( p_suite, test_is_float64_2, "test_is_float64_2" );

   // test_is_float64_3
   add_test_to_suite( p_suite, test_is_float64_3, "test_is_float64_3" );

   // test_is_float64_4
   add_test_to_suite( p_suite, test_is_float64_3, "test_is_float64_4" );

   // test_is_float64_5
   add_test_to_suite( p_suite, test_is_float64_3, "test_is_float64_5" );

   // test_is_float64_6
   add_test_to_suite( p_suite, test_is_float64_3, "test_is_float64_6" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

