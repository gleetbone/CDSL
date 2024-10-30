/**
 @file string_utf8_test_cstring_hex_from_uint8.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for string_make_from_cstring"
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

#include "String_utilities_utf8.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_cstring_hex_from_uint8_1
*/

void test_cstring_hex_from_uint8_1( void )
{
   uint8_t u8 = 0;

   char_t *string = cstring_hex_from_uint8( u8 );

   CU_ASSERT( strcmp( string, "00" ) == 0 );

   free( string );

   return;
}

/**
   test_cstring_hex_from_uint8_2
*/

void test_cstring_hex_from_uint8_2( void )
{
   uint8_t u8 = 1;

   char_t *string = cstring_hex_from_uint8( u8 );

   CU_ASSERT( strcmp( string, "01" ) == 0 );

   free( string );

   return;
}

/**
   test_cstring_hex_from_uint8_3
*/

void test_cstring_hex_from_uint8_3( void )
{
   uint8_t u8 = 16;

   char_t *string = cstring_hex_from_uint8( u8 );

   CU_ASSERT( strcmp( string, "10" ) == 0 );

   free( string );

   return;
}


/**
   test_cstring_hex_from_uint8_4
*/

void test_cstring_hex_from_uint8_4( void )
{
   uint8_t u8 = 240;

   char_t *string = cstring_hex_from_uint8( u8 );

   CU_ASSERT( strcmp( string, "F0" ) == 0 );

   free( string );

   return;
}


int
add_test_cstring_hex_from_uint8( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_cstring_hex_from_uint8", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_cstring_hex_from_uint8_1
   add_test_to_suite( p_suite, test_cstring_hex_from_uint8_1, "test_cstring_hex_from_uint8_1" );

   // test_cstring_hex_from_uint8_2
   add_test_to_suite( p_suite, test_cstring_hex_from_uint8_2, "test_cstring_hex_from_uint8_2" );

   // test_cstring_hex_from_uint8_3
   add_test_to_suite( p_suite, test_cstring_hex_from_uint8_3, "test_cstring_hex_from_uint8_3" );

   // test_cstring_hex_from_uint8_4
   add_test_to_suite( p_suite, test_cstring_hex_from_uint8_4, "test_cstring_hex_from_uint8_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

