/**
 @file string_test_substring.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for string_make_from_cstring"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for string_make_from_cstring.

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
   test_substring_1
*/

void test_substring_1( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABC" );
   
   string1 = string_substring( string, 0, 0 );
   
   string_t *stringt = string_make_from_cstring( "A" );
   
   CU_ASSERT( string_is_equal( string1, stringt ) == 1 );
 
   string_dispose_with_contents( string );
   string_dispose_with_contents( string1 );
   string_dispose_with_contents( stringt );

   return;
}

/**
   test_substring_2
*/

void test_substring_2( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABC" );
   
   string1 = string_substring( string, 2, 2 );
   
   string_t *stringt = string_make_from_cstring( "C" );
   
   CU_ASSERT( string_is_equal( string1, stringt ) == 1 );
 
   string_dispose_with_contents( string );
   string_dispose_with_contents( string1 );
   string_dispose_with_contents( stringt );

   return;
}

/**
   test_substring_3
*/

void test_substring_3( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABC" );
   
   string1 = string_substring( string, 1, 1 );
   
   string_t *stringt = string_make_from_cstring( "B" );
   
   CU_ASSERT( string_is_equal( string1, stringt ) == 1 );
 
   string_dispose_with_contents( string );
   string_dispose_with_contents( string1 );
   string_dispose_with_contents( stringt );

   return;
}

/**
   test_substring_4
*/

void test_substring_4( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABC" );
   
   string1 = string_substring( string, 0, 1 );
   
   string_t *stringt = string_make_from_cstring( "AB" );
   
   CU_ASSERT( string_is_equal( string1, stringt ) == 1 );
 
   string_dispose_with_contents( string );
   string_dispose_with_contents( string1 );
   string_dispose_with_contents( stringt );

   return;
}

/**
   test_substring_5
*/

void test_substring_5( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABC" );
   
   string1 = string_substring( string, 1, 2 );
   
   string_t *stringt = string_make_from_cstring( "BC" );
   
   CU_ASSERT( string_is_equal( string1, stringt ) == 1 );
 
   string_dispose_with_contents( string );
   string_dispose_with_contents( string1 );
   string_dispose_with_contents( stringt );

   return;
}

/**
   test_substring_6
*/

void test_substring_6( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABCD" );
   
   string1 = string_substring( string, 1, 2 );
   
   string_t *stringt = string_make_from_cstring( "BC" );
   
   CU_ASSERT( string_is_equal( string1, stringt ) == 1 );
 
   string_dispose_with_contents( string );
   string_dispose_with_contents( string1 );
   string_dispose_with_contents( stringt );

   return;
}

int
add_test_substring( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_substring", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_substring_1
   add_test_to_suite( p_suite, test_substring_1, "test_substring_1" );

   // test_substring_2
   add_test_to_suite( p_suite, test_substring_2, "test_substring_2" );

   // test_substring_3
   add_test_to_suite( p_suite, test_substring_3, "test_substring_3" );

   // test_substring_4
   add_test_to_suite( p_suite, test_substring_4, "test_substring_4" );

   // test_substring_5
   add_test_to_suite( p_suite, test_substring_5, "test_substring_5" );

   // test_substring_6
   add_test_to_suite( p_suite, test_substring_6, "test_substring_6" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

