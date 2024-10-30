/**
 @file string_test_cstring_hex_from_int32.c
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

#include "String_utilities.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_cstring_hex_from_int32_1
*/

void test_cstring_hex_from_int32_1( void )
{
   int32_t i32 = 0;
   
   char_t *string = cstring_hex_from_int32( i32 );
   
   CU_ASSERT( strcmp( string, "00000000" ) == 0 );
 
   free( string );

   return;
}

/**
   test_cstring_hex_from_int32_2
*/

void test_cstring_hex_from_int32_2( void )
{
   int32_t i32 = 1;
   
   char_t *string = cstring_hex_from_int32( i32 );
   
   CU_ASSERT( strcmp( string, "00000001" ) == 0 );
 
   free( string );

   return;
}

/**
   test_cstring_hex_from_int32_3
*/

void test_cstring_hex_from_int32_3( void )
{
   int32_t i32 = 16;
   
   char_t *string = cstring_hex_from_int32( i32 );
   
   CU_ASSERT( strcmp( string, "00000010" ) == 0 );
 
   free( string );

   return;
}


/**
   test_cstring_hex_from_int32_4
*/

void test_cstring_hex_from_int32_4( void )
{
   int32_t i32 = 240;
   
   char_t *string = cstring_hex_from_int32( i32 );
   
   CU_ASSERT( strcmp( string, "000000F0" ) == 0 );
 
   free( string );

   return;
}

/**
   test_cstring_hex_from_int32_5
*/

void test_cstring_hex_from_int32_5( void )
{
   int32_t i32 = 16001;
   
   char_t *string = cstring_hex_from_int32( i32 );
   
   CU_ASSERT( strcmp( string, "00003E81" ) == 0 );
 
   free( string );

   return;
}

/**
   test_cstring_hex_from_int32_6
*/

void test_cstring_hex_from_int32_6( void )
{
   int32_t i32 = 65537;
   
   char_t *string = cstring_hex_from_int32( i32 );
   
   CU_ASSERT( strcmp( string, "00010001" ) == 0 );
 
   free( string );

   return;
}

/**
   test_cstring_hex_from_int32_7
*/

void test_cstring_hex_from_int32_7( void )
{
   int32_t i32 = 305419896;
   
   char_t *string = cstring_hex_from_int32( i32 );
   
   CU_ASSERT( strcmp( string, "12345678" ) == 0 );
 
   free( string );

   return;
}

/**
   test_cstring_hex_from_int32_8
*/

void test_cstring_hex_from_int32_8( void )
{
   int32_t i32 = -1234;
   
   char_t *string = cstring_hex_from_int32( i32 );
   
   CU_ASSERT( strcmp( string, "FFFFFB2E" ) == 0 );
 
   free( string );

   return;
}


int
add_test_cstring_hex_from_int32( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_cstring_hex_from_int32", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_cstring_hex_from_int32_1
   add_test_to_suite( p_suite, test_cstring_hex_from_int32_1, "test_cstring_hex_from_int32_1" );

   // test_cstring_hex_from_int32_2
   add_test_to_suite( p_suite, test_cstring_hex_from_int32_2, "test_cstring_hex_from_int32_2" );

   // test_cstring_hex_from_int32_3
   add_test_to_suite( p_suite, test_cstring_hex_from_int32_3, "test_cstring_hex_from_int32_3" );

   // test_cstring_hex_from_int32_4
   add_test_to_suite( p_suite, test_cstring_hex_from_int32_4, "test_cstring_hex_from_int32_4" );

   // test_cstring_hex_from_int32_5
   add_test_to_suite( p_suite, test_cstring_hex_from_int32_5, "test_cstring_hex_from_int32_5" );

   // test_cstring_hex_from_int32_6
   add_test_to_suite( p_suite, test_cstring_hex_from_int32_6, "test_cstring_hex_from_int32_6" );

   // test_cstring_hex_from_int32_7
   add_test_to_suite( p_suite, test_cstring_hex_from_int32_7, "test_cstring_hex_from_int32_7" );

   // test_cstring_hex_from_int32_8
   add_test_to_suite( p_suite, test_cstring_hex_from_int32_8, "test_cstring_hex_from_int32_8" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

