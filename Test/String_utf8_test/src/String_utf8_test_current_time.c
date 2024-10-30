/**
 @file string_utf8_test_current_time.c
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
#include "String_utilities_utf8.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_current_time_1
*/

void test_current_time_1( void )
{
   string_utf8_t *string = NULL;

   string = current_time_as_string( );

   CU_ASSERT( string_utf8_item_ascii( string, 4 ) == '-' );
   CU_ASSERT( string_utf8_item_ascii( string, 7 ) == '-' );
   CU_ASSERT( string_utf8_item_ascii( string, 10 ) == ' ' );
   CU_ASSERT( string_utf8_item_ascii( string, 13 ) == ':' );
   CU_ASSERT( string_utf8_item_ascii( string, 16 ) == ':' );
   CU_ASSERT( string_utf8_item_ascii( string, 19 ) == '.' );
   CU_ASSERT( string_utf8_count( string ) == 23 );

   string_utf8_deep_dispose( &string );

   return;
}

/**
   test_current_time_2
*/

void test_current_time_2( void )
{
   char_t *string = NULL;

   string = current_time_as_cstring( );

   CU_ASSERT( string[ 4] == '-' );
   CU_ASSERT( string[ 7] == '-' );
   CU_ASSERT( string[10] == ' ' );
   CU_ASSERT( string[13] == ':' );
   CU_ASSERT( string[16] == ':' );
   CU_ASSERT( string[19] == '.' );
   CU_ASSERT( strlen( string ) == 23 );

   free( string );

   return;
}

int
add_test_current_time( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_current_time", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_current_time_1
   add_test_to_suite( p_suite, test_current_time_1, "test_current_time_1" );

   // test_current_time_2
   add_test_to_suite( p_suite, test_current_time_2, "test_current_time_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

