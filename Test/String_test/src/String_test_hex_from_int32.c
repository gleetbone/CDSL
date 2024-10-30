/**
 @file string_test_hex_from_int32.c
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
#include "String_utilities.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_hex_from_int32_1
*/

void test_hex_from_int32_1( void )
{
   int32_t i32 = 0;

   string_t *string = string_hex_from_int32( i32 );

   CU_ASSERT( string_is_equal_cstring( string, "00000000" ) == 1 );

   string_deep_dispose( &string );

   return;
}

/**
   test_hex_from_int32_2
*/

void test_hex_from_int32_2( void )
{
   int32_t i32 = 1;

   string_t *string = string_hex_from_int32( i32 );

   CU_ASSERT( string_is_equal_cstring( string, "00000001" ) == 1 );

   string_deep_dispose( &string );

   return;
}

/**
   test_hex_from_int32_3
*/

void test_hex_from_int32_3( void )
{
   int32_t i32 = 16;

   string_t *string = string_hex_from_int32( i32 );

   CU_ASSERT( string_is_equal_cstring( string, "00000010" ) == 1 );

   string_deep_dispose( &string );

   return;
}


/**
   test_hex_from_int32_4
*/

void test_hex_from_int32_4( void )
{
   int32_t i32 = 240;

   string_t *string = string_hex_from_int32( i32 );

   CU_ASSERT( string_is_equal_cstring( string, "000000F0" ) == 1 );

   string_deep_dispose( &string );

   return;
}

/**
   test_hex_from_int32_5
*/

void test_hex_from_int32_5( void )
{
   int32_t i32 = 16001;

   string_t *string = string_hex_from_int32( i32 );

   CU_ASSERT( string_is_equal_cstring( string, "00003E81" ) == 1 );

   string_deep_dispose( &string );

   return;
}

/**
   test_hex_from_int32_6
*/

void test_hex_from_int32_6( void )
{
   int32_t i32 = 65537;

   string_t *string = string_hex_from_int32( i32 );

   CU_ASSERT( string_is_equal_cstring( string, "00010001" ) == 1 );

   string_deep_dispose( &string );

   return;
}

/**
   test_hex_from_int32_7
*/

void test_hex_from_int32_7( void )
{
   int32_t i32 = 305419896;

   string_t *string = string_hex_from_int32( i32 );

   CU_ASSERT( string_is_equal_cstring( string, "12345678" ) == 1 );

   string_deep_dispose( &string );

   return;
}

/**
   test_hex_from_int32_8
*/

void test_hex_from_int32_8( void )
{
   int32_t i32 = -1234;

   string_t *string = string_hex_from_int32( i32 );

   CU_ASSERT( string_is_equal_cstring( string, "FFFFFB2E" ) == 1 );

   string_deep_dispose( &string );

   return;
}


int
add_test_hex_from_int32( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_hex_from_int32", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_hex_from_int32_1
   add_test_to_suite( p_suite, test_hex_from_int32_1, "test_hex_from_int32_1" );

   // test_hex_from_int32_2
   add_test_to_suite( p_suite, test_hex_from_int32_2, "test_hex_from_int32_2" );

   // test_hex_from_int32_3
   add_test_to_suite( p_suite, test_hex_from_int32_3, "test_hex_from_int32_3" );

   // test_hex_from_int32_4
   add_test_to_suite( p_suite, test_hex_from_int32_4, "test_hex_from_int32_4" );

   // test_hex_from_int32_5
   add_test_to_suite( p_suite, test_hex_from_int32_5, "test_hex_from_int32_5" );

   // test_hex_from_int32_6
   add_test_to_suite( p_suite, test_hex_from_int32_6, "test_hex_from_int32_6" );

   // test_hex_from_int32_7
   add_test_to_suite( p_suite, test_hex_from_int32_7, "test_hex_from_int32_7" );

   // test_hex_from_int32_8
   add_test_to_suite( p_suite, test_hex_from_int32_8, "test_hex_from_int32_8" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

