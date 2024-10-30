/**
 @file string_utf8_test_append.c
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
   test_append_1
*/

void test_append_1( void )
{
   string_utf8_t *string = NULL;
   string_utf8_t *string1 = NULL;

   string = string_utf8_make_from_cstring( "ABCD" );
   string1 = string_utf8_make_from_cstring( "Q" );

   string_utf8_append( string, string1 );

   string_utf8_t *stringt = string_utf8_make_from_cstring( "ABCDQ" );

   CU_ASSERT( string_utf8_is_equal( string, stringt ) == 1 );

   string_utf8_deep_dispose( &string );
   string_utf8_deep_dispose( &string1 );
   string_utf8_deep_dispose( &stringt );

   return;
}

/**
   test_append_2
*/

void test_append_2( void )
{
   string_utf8_t *string = NULL;
   string_utf8_t *string1 = NULL;

   string = string_utf8_make_from_cstring( "" );
   string1 = string_utf8_make_from_cstring( "ABC" );

   string_utf8_append( string, string1 );

   string_utf8_t *stringt = string_utf8_make_from_cstring( "ABC" );

   CU_ASSERT( string_utf8_is_equal( string, stringt ) == 1 );

   string_utf8_deep_dispose( &string );
   string_utf8_deep_dispose( &string1 );
   string_utf8_deep_dispose( &stringt );

   return;
}

/**
   test_append_3
*/

void test_append_3( void )
{
   string_utf8_t *string = NULL;
   string_utf8_t *string1 = NULL;

   string = string_utf8_make_from_cstring( "ABCD" );
   string1 = string_utf8_make_from_cstring( "XYZ" );

   string_utf8_append( string, string1 );

   string_utf8_t *stringt = string_utf8_make_from_cstring( "ABCDXYZ" );

   CU_ASSERT( string_utf8_is_equal( string, stringt ) == 1 );

   string_utf8_deep_dispose( &string );
   string_utf8_deep_dispose( &string1 );
   string_utf8_deep_dispose( &stringt );

   return;
}

/**
   test_append_4
*/

void test_append_4( void )
{
   string_utf8_t *string = NULL;
   string_utf8_t *string1 = NULL;

   string = string_utf8_make_n( 32 );
   string_utf8_append_cstring( string, "ABCD" );
   string1 = string_utf8_make_from_cstring( "XYZ" );

   string_utf8_append( string, string1 );

   string_utf8_t *stringt = string_utf8_make_from_cstring( "ABCDXYZ" );

   CU_ASSERT( string_utf8_is_equal( string, stringt ) == 1 );

   string_utf8_deep_dispose( &string );
   string_utf8_deep_dispose( &string1 );
   string_utf8_deep_dispose( &stringt );

   return;
}


int
add_test_append( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_append", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_append_1
   add_test_to_suite( p_suite, test_append_1, "test_append_1" );

   // test_append_2
   add_test_to_suite( p_suite, test_append_2, "test_append_2" );

   // test_append_3
   add_test_to_suite( p_suite, test_append_3, "test_append_3" );

   // test_append_4
   add_test_to_suite( p_suite, test_append_4, "test_append_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

