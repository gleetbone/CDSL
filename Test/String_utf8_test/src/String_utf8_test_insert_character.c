/**
 @file string_utf8_test_insert_character.c
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
   test_insert_character_1
*/

void test_insert_character_1( void )
{
   string_utf8_t *string = NULL;
   char_t cp[2] = {0};

   string = string_utf8_make_from_cstring( "ABCD" );

   cp[0] = 'Q';
   string_utf8_insert_character( string, cp, 0 );

   string_utf8_t *stringt = string_utf8_make_from_cstring( "QABCD" );

   CU_ASSERT( string_utf8_is_equal( string, stringt ) == 1 );

   string_utf8_deep_dispose( &string );
   string_utf8_deep_dispose( &stringt );

   return;
}

/**
   test_insert_character_2
*/

void test_insert_character_2( void )
{
   string_utf8_t *string = NULL;
   char_t cp[2] = {0};

   string = string_utf8_make_from_cstring( "ABCD" );

   cp[0] = 'Q';
   string_utf8_insert_character( string, cp, 1 );

   string_utf8_t *stringt = string_utf8_make_from_cstring( "AQBCD" );

   CU_ASSERT( string_utf8_is_equal( string, stringt ) == 1 );

   string_utf8_deep_dispose( &string );
   string_utf8_deep_dispose( &stringt );

   return;
}

/**
   test_insert_character_3
*/

void test_insert_character_3( void )
{
   string_utf8_t *string = NULL;
   char_t cp[2] = {0};

   string = string_utf8_make_from_cstring( "ABCD" );

   cp[0] = 'Q';
   string_utf8_insert_character( string, cp, 2 );

   string_utf8_t *stringt = string_utf8_make_from_cstring( "ABQCD" );

   CU_ASSERT( string_utf8_is_equal( string, stringt ) == 1 );

   string_utf8_deep_dispose( &string );
   string_utf8_deep_dispose( &stringt );

   return;
}

/**
   test_insert_character_4
*/

void test_insert_character_4( void )
{
   string_utf8_t *string = NULL;
   char_t cp[2] = {0};

   string = string_utf8_make_from_cstring( "ABCD" );

   cp[0] = 'Q';
   string_utf8_insert_character( string, cp, 3 );

   string_utf8_t *stringt = string_utf8_make_from_cstring( "ABCQD" );

   CU_ASSERT( string_utf8_is_equal( string, stringt ) == 1 );

   string_utf8_deep_dispose( &string );
   string_utf8_deep_dispose( &stringt );

   return;
}

/**
   test_insert_character_5
*/

void test_insert_character_5( void )
{
   string_utf8_t *string = NULL;
   char_t cp[2] = {0};

   string = string_utf8_make_from_cstring( "ABCD" );

   cp[0] = 'Q';
   string_utf8_insert_character( string, cp, 4 );

   string_utf8_t *stringt = string_utf8_make_from_cstring( "ABCDQ" );

   CU_ASSERT( string_utf8_is_equal( string, stringt ) == 1 );

   string_utf8_deep_dispose( &string );
   string_utf8_deep_dispose( &stringt );

   return;
}

/**
   test_insert_character_6
*/

void test_insert_character_6( void )
{
   string_utf8_t *string = NULL;
   char_t cp[2] = {0};

   string = string_utf8_make_n( 32 );
   string_utf8_append_cstring( string, "ABCD" );

   cp[0] = 'Q';
   string_utf8_insert_character( string, cp, 4 );

   string_utf8_t *stringt = string_utf8_make_from_cstring( "ABCDQ" );

   CU_ASSERT( string_utf8_is_equal( string, stringt ) == 1 );

   string_utf8_deep_dispose( &string );
   string_utf8_deep_dispose( &stringt );

   return;
}


int
add_test_insert_character( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_insert_character", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_insert_character_1
   add_test_to_suite( p_suite, test_insert_character_1, "test_insert_character_1" );

   // test_insert_character_2
   add_test_to_suite( p_suite, test_insert_character_2, "test_insert_character_2" );

   // test_insert_character_3
   add_test_to_suite( p_suite, test_insert_character_3, "test_insert_character_3" );

   // test_insert_character_4
   add_test_to_suite( p_suite, test_insert_character_4, "test_insert_character_4" );

   // test_insert_character_5
   add_test_to_suite( p_suite, test_insert_character_5, "test_insert_character_5" );

   // test_insert_character_6
   add_test_to_suite( p_suite, test_insert_character_6, "test_insert_character_6" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

