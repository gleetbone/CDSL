/**
 @file raw_buffer_test_to_hex_string.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for raw_buffer_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for raw_buffer_t

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "Raw_Buffer.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );


/**
   test_to_hex_string_1
*/

void test_to_hex_string_1( void )
{
   raw_buffer_t *raw_buffer = raw_buffer_make( 8 );
   string_t *string = raw_buffer_to_hex_string( raw_buffer );
   
   CU_ASSERT( string_is_equal_cstring( string, "0000000000000000" ) == 1 );
   
   raw_buffer_deep_dispose( &raw_buffer );
   string_deep_dispose( &string );

   return;
}

/**
   test_to_hex_string_2
*/

void test_to_hex_string_2( void )
{
   raw_buffer_t *raw_buffer = raw_buffer_make( 8 );
   raw_buffer_put_uint8( raw_buffer, 1, 0 );
   raw_buffer_put_uint8( raw_buffer, 2, 1 );
   raw_buffer_put_uint8( raw_buffer, 3, 2 );
   raw_buffer_put_uint8( raw_buffer, 4, 3 );
   raw_buffer_put_uint8( raw_buffer, 5, 4 );
   raw_buffer_put_uint8( raw_buffer, 6, 5 );
   raw_buffer_put_uint8( raw_buffer, 7, 6 );
   raw_buffer_put_uint8( raw_buffer, 8, 7 );
   
   string_t *string = raw_buffer_to_hex_string( raw_buffer );
   
   CU_ASSERT( string_is_equal_cstring( string, "0102030405060708" ) == 1 );
   
   raw_buffer_deep_dispose( &raw_buffer );
   string_deep_dispose( &string );

   return;
}

/**
   test_to_hex_string_3
*/

void test_to_hex_string_3( void )
{
   raw_buffer_t *raw_buffer = raw_buffer_make( 33 );
   string_t *string = raw_buffer_to_hex_string( raw_buffer );
   
   CU_ASSERT
   ( 
      string_is_equal_cstring
      ( 
         string, 
         "0000000000000000000000000000000000000000000000000000000000000000\n00" 
      ) == 1 
   );
   
   raw_buffer_deep_dispose( &raw_buffer );
   string_deep_dispose( &string );

   return;
}


int
add_test_to_hex_string( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_to_hex_string", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_to_hex_string_1
   add_test_to_suite( p_suite, test_to_hex_string_1, "test_to_hex_string_1" );

   // test_to_hex_string_2
   add_test_to_suite( p_suite, test_to_hex_string_2, "test_to_hex_string_2" );

   // test_to_hex_string_3
   add_test_to_suite( p_suite, test_to_hex_string_3, "test_to_hex_string_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

