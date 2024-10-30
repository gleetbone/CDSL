/**
 @file string_utf8_test_prepend_character_utf16.c
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
   test_prepend_character_utf16_1
*/

void test_prepend_character_utf16_1( void )
{
   string_utf8_t *string = NULL;
   utf16_t cp[2] = {0};
   utf16_t c = 0;

   string = string_utf8_make();

   cp[0] = 'Q';
   string_utf8_prepend_character_utf16( string, cp[0] );

   c = string_utf8_item_utf16( string, 0 );

   CU_ASSERT( c == cp[0] );

   string_utf8_deep_dispose( &string );

   return;
}

/**
   test_prepend_character_utf16_2
*/

void test_prepend_character_utf16_2( void )
{
   string_utf8_t *string = NULL;
   utf16_t cp[2] = {0};
   utf16_t c = 0;

   string = string_utf8_make_from_cstring( "ABCD" );

   cp[0] = 'Q';
   string_utf8_prepend_character_utf16( string, cp[0] );

   c = string_utf8_item_utf16( string, 0 );
   CU_ASSERT( c == cp[0] );

   c = string_utf8_item_utf16( string, 1 );
   CU_ASSERT( c == 'A' );

   c = string_utf8_item_utf16( string, 2 );
   CU_ASSERT( c == 'B' );

   c = string_utf8_item_utf16( string, 3 );
   CU_ASSERT( c == 'C' );

   c = string_utf8_item_utf16( string, 4 );
   CU_ASSERT( c == 'D' );

   string_utf8_deep_dispose( &string );

   return;
}
 
/**
   test_prepend_character_utf16_3
*/

void test_prepend_character_utf16_3( void )
{
   string_utf8_t *string = NULL;
   utf16_t cp[2] = {0};
   utf16_t c = 0;

   string = string_utf8_make_n( 32 );
   string_utf8_append_cstring( string, "ABCD" );

   cp[0] = 'Q';
   string_utf8_prepend_character_utf16( string, cp[0] );

   c = string_utf8_item_utf16( string, 0 );
   CU_ASSERT( c == cp[0] );

   c = string_utf8_item_utf16( string, 1 );
   CU_ASSERT( c == 'A' );

   c = string_utf8_item_utf16( string, 2 );
   CU_ASSERT( c == 'B' );

   c = string_utf8_item_utf16( string, 3 );
   CU_ASSERT( c == 'C' );

   c = string_utf8_item_utf16( string, 4 );
   CU_ASSERT( c == 'D' );

   string_utf8_deep_dispose( &string );

   return;
}
 

int
add_test_prepend_character_utf16( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_prepend_character", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_prepend_character_utf16_1
   add_test_to_suite( p_suite, test_prepend_character_utf16_1, "test_prepend_character_utf16_1" );

   // test_prepend_character_utf16_2
   add_test_to_suite( p_suite, test_prepend_character_utf16_2, "test_prepend_character_utf16_2" );

   // test_prepend_character_utf16_3
   add_test_to_suite( p_suite, test_prepend_character_utf16_3, "test_prepend_character_utf16_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

