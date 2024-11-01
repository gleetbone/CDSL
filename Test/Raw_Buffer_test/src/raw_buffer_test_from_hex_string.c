/**
 @file raw_buffer_test_from_hex_string.c
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
   test_from_hex_string_1
*/

void test_from_hex_string_1( void )
{
   string_t *string = string_make_from_cstring( "0000000000000000" );
   raw_buffer_t *raw_buffer = raw_buffer_from_hex_string( string );
   
   CU_ASSERT( raw_buffer != NULL );
   CU_ASSERT( raw_buffer_count( raw_buffer)  == 8 );
   CU_ASSERT( raw_buffer_read_uint8( raw_buffer, 0 )  == 0 );
   CU_ASSERT( raw_buffer_read_uint8( raw_buffer, 1 )  == 0 );
   CU_ASSERT( raw_buffer_read_uint8( raw_buffer, 2 )  == 0 );
   CU_ASSERT( raw_buffer_read_uint8( raw_buffer, 3 )  == 0 );
   CU_ASSERT( raw_buffer_read_uint8( raw_buffer, 4 )  == 0 );
   CU_ASSERT( raw_buffer_read_uint8( raw_buffer, 5 )  == 0 );
   CU_ASSERT( raw_buffer_read_uint8( raw_buffer, 6 )  == 0 );
   CU_ASSERT( raw_buffer_read_uint8( raw_buffer, 7 )  == 0 );
   
   raw_buffer_deep_dispose( &raw_buffer );
   string_deep_dispose( &string );

   return;
}

/**
   test_from_hex_string_2
*/

void test_from_hex_string_2( void )
{
   string_t *string = string_make_from_cstring( "0102030405060708" );
   raw_buffer_t *raw_buffer = raw_buffer_from_hex_string( string );
   
   CU_ASSERT( raw_buffer != NULL );
   CU_ASSERT( raw_buffer_count( raw_buffer)  == 8 );
   CU_ASSERT( raw_buffer_read_uint8( raw_buffer, 0 )  == 1 );
   CU_ASSERT( raw_buffer_read_uint8( raw_buffer, 1 )  == 2 );
   CU_ASSERT( raw_buffer_read_uint8( raw_buffer, 2 )  == 3 );
   CU_ASSERT( raw_buffer_read_uint8( raw_buffer, 3 )  == 4 );
   CU_ASSERT( raw_buffer_read_uint8( raw_buffer, 4 )  == 5 );
   CU_ASSERT( raw_buffer_read_uint8( raw_buffer, 5 )  == 6 );
   CU_ASSERT( raw_buffer_read_uint8( raw_buffer, 6 )  == 7 );
   CU_ASSERT( raw_buffer_read_uint8( raw_buffer, 7 )  == 8 );
   
   raw_buffer_deep_dispose( &raw_buffer );
   string_deep_dispose( &string );

   return;
}

/**
   test_from_hex_string_3
*/

void test_from_hex_string_3( void )
{
   string_t *string = string_make_from_cstring( "01\n02030405060708" );
   raw_buffer_t *raw_buffer = raw_buffer_from_hex_string( string );
   
   CU_ASSERT( raw_buffer != NULL );
   CU_ASSERT( raw_buffer_count( raw_buffer)  == 8 );
   CU_ASSERT( raw_buffer_read_uint8( raw_buffer, 0 )  == 1 );
   CU_ASSERT( raw_buffer_read_uint8( raw_buffer, 1 )  == 2 );
   CU_ASSERT( raw_buffer_read_uint8( raw_buffer, 2 )  == 3 );
   CU_ASSERT( raw_buffer_read_uint8( raw_buffer, 3 )  == 4 );
   CU_ASSERT( raw_buffer_read_uint8( raw_buffer, 4 )  == 5 );
   CU_ASSERT( raw_buffer_read_uint8( raw_buffer, 5 )  == 6 );
   CU_ASSERT( raw_buffer_read_uint8( raw_buffer, 6 )  == 7 );
   CU_ASSERT( raw_buffer_read_uint8( raw_buffer, 7 )  == 8 );
   
   raw_buffer_deep_dispose( &raw_buffer );
   string_deep_dispose( &string );

   return;
}



int
add_test_from_hex_string( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_from_hex_string", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_from_hex_string_1
   add_test_to_suite( p_suite, test_from_hex_string_1, "test_from_hex_string_1" );

   // test_from_hex_string_2
   add_test_to_suite( p_suite, test_from_hex_string_2, "test_from_hex_string_2" );

   // test_from_hex_string_3
   add_test_to_suite( p_suite, test_from_hex_string_3, "test_from_hex_string_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

