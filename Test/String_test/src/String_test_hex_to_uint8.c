/**
 @file string_test_hex_to_uint8.c
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
#include "String_utilities.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_hex_to_uint8_1
*/

void test_hex_to_uint8_1( void )
{
   string_t *string = string_make_from_cstring( "00" );

   uint8_t u8 = string_hex_to_uint8( string );

   CU_ASSERT( u8 == 0 );

   string_dispose_with_contents( string );

   return;
}

/**
   test_hex_to_uint8_2
*/

void test_hex_to_uint8_2( void )
{
   string_t *string = string_make_from_cstring( "01" );

   uint8_t u8 = string_hex_to_uint8( string );

   CU_ASSERT( u8 == 1 );

   string_dispose_with_contents( string );

   return;
}

/**
   test_hex_to_uint8_3
*/

void test_hex_to_uint8_3( void )
{
   string_t *string = string_make_from_cstring( "10" );

   uint8_t u8 = string_hex_to_uint8( string );

   CU_ASSERT( u8 == 16 );

   string_dispose_with_contents( string );

   return;
}


/**
   test_hex_to_uint8_4
*/

void test_hex_to_uint8_4( void )
{
   string_t *string = string_make_from_cstring( "F0" );

   uint8_t u8 = string_hex_to_uint8( string );

   CU_ASSERT( u8 == 240 );

   string_dispose_with_contents( string );

   return;
}


int
add_test_hex_to_uint8( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_hex_to_uint8", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_hex_to_uint8_1
   add_test_to_suite( p_suite, test_hex_to_uint8_1, "test_hex_to_uint8_1" );

   // test_hex_to_uint8_2
   add_test_to_suite( p_suite, test_hex_to_uint8_2, "test_hex_to_uint8_2" );

   // test_hex_to_uint8_3
   add_test_to_suite( p_suite, test_hex_to_uint8_3, "test_hex_to_uint8_3" );

   // test_hex_to_uint8_4
   add_test_to_suite( p_suite, test_hex_to_uint8_4, "test_hex_to_uint8_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

