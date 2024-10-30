/**
 @file string_test_replace.c
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
   test_replace_1
*/

void test_replace_1( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABCD" );
   string1 = string_make_from_cstring( "Q" );
   
   string_replace( string, string1, 1, 1 );
   
   string_t *stringt = string_make_from_cstring( "AQCD" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );
   string_deep_dispose( &stringt );

   return;
}

/**
   test_replace_2
*/

void test_replace_2( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABCD" );
   string1 = string_make_from_cstring( "QR" );
   
   string_replace( string, string1, 1, 1 );
   
   string_t *stringt = string_make_from_cstring( "AQCD" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );
   string_deep_dispose( &stringt );

   return;
}

/**
   test_replace_3
*/

void test_replace_3( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABCD" );
   string1 = string_make_from_cstring( "QR" );
   
   string_replace( string, string1, 1, 2 );
   
   string_t *stringt = string_make_from_cstring( "AQRD" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );
   string_deep_dispose( &stringt );

   return;
}

/**
   test_replace_4
*/

void test_replace_4( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABCD" );
   string1 = string_make_from_cstring( "QR" );
   
   string_replace( string, string1, 0, 1 );
   
   string_t *stringt = string_make_from_cstring( "QRCD" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );
   string_deep_dispose( &stringt );

   return;
}

/**
   test_replace_5
*/

void test_replace_5( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABCD" );
   string1 = string_make_from_cstring( "QR" );
   
   string_replace( string, string1, 2, 3 );
   
   string_t *stringt = string_make_from_cstring( "ABQR" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );
   string_deep_dispose( &stringt );

   return;
}

/**
   test_replace_6
*/

void test_replace_6( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABCD" );
   string1 = string_make_from_cstring( "PQRSTUV" );
   
   string_replace( string, string1, 1, 2 );
   
   string_t *stringt = string_make_from_cstring( "APQD" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );
   string_deep_dispose( &stringt );

   return;
}

int
add_test_replace( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_replace", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_replace_1
   add_test_to_suite( p_suite, test_replace_1, "test_replace_1" );

   // test_replace_2
   add_test_to_suite( p_suite, test_replace_2, "test_replace_2" );

   // test_replace_3
   add_test_to_suite( p_suite, test_replace_3, "test_replace_3" );

   // test_replace_4
   add_test_to_suite( p_suite, test_replace_4, "test_replace_4" );

   // test_replace_5
   add_test_to_suite( p_suite, test_replace_5, "test_replace_5" );

   // test_replace_6
   add_test_to_suite( p_suite, test_replace_6, "test_replace_6" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

