/**
 @file string_test_replace_cstring.c
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
   test_replace_cstring_1
*/

void test_replace_cstring_1( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "ABCD" );
   
   string_replace_cstring( string, "Q", 1, 1 );
   
   string_t *stringt = string_make_from_cstring( "AQCD" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_dispose_with_contents( string );
   string_dispose_with_contents( stringt );

   return;
}

/**
   test_replace_cstring_2
*/

void test_replace_cstring_2( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "ABCD" );
   
   string_replace_cstring( string, "QR", 1, 1 );
   
   string_t *stringt = string_make_from_cstring( "AQCD" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_dispose_with_contents( string );
   string_dispose_with_contents( stringt );

   return;
}

/**
   test_replace_cstring_3
*/

void test_replace_cstring_3( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "ABCD" );
   
   string_replace_cstring( string, "QR", 1, 2 );
   
   string_t *stringt = string_make_from_cstring( "AQRD" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_dispose_with_contents( string );
   string_dispose_with_contents( stringt );

   return;
}

/**
   test_replace_cstring_4
*/

void test_replace_cstring_4( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "ABCD" );
   
   string_replace_cstring( string, "QR", 0, 1 );
   
   string_t *stringt = string_make_from_cstring( "QRCD" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_dispose_with_contents( string );
   string_dispose_with_contents( stringt );

   return;
}

/**
   test_replace_cstring_5
*/

void test_replace_cstring_5( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "ABCD" );
   
   string_replace_cstring( string, "QR", 2, 3 );
   
   string_t *stringt = string_make_from_cstring( "ABQR" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_dispose_with_contents( string );
   string_dispose_with_contents( stringt );

   return;
}

/**
   test_replace_cstring_6
*/

void test_replace_cstring_6( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "ABCD" );
   
   string_replace_cstring( string, "PQRSTUV", 1, 2 );
   
   string_t *stringt = string_make_from_cstring( "APQD" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_dispose_with_contents( string );
   string_dispose_with_contents( stringt );

   return;
}

int
add_test_replace_cstring( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_replace_cstring", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_replace_cstring_1
   add_test_to_suite( p_suite, test_replace_cstring_1, "test_replace_cstring_1" );

   // test_replace_cstring_2
   add_test_to_suite( p_suite, test_replace_cstring_2, "test_replace_cstring_2" );

   // test_replace_cstring_3
   add_test_to_suite( p_suite, test_replace_cstring_3, "test_replace_cstring_3" );

   // test_replace_cstring_4
   add_test_to_suite( p_suite, test_replace_cstring_4, "test_replace_cstring_4" );

   // test_replace_cstring_5
   add_test_to_suite( p_suite, test_replace_cstring_5, "test_replace_cstring_5" );

   // test_replace_cstring_6
   add_test_to_suite( p_suite, test_replace_cstring_6, "test_replace_cstring_6" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

