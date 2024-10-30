/**
 @file string_utf8_test_from_file_cstring.c
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
   test_from_file_cstring_utf8_1
*/

void test_from_file_cstring_utf8_1( void )
{
   FILE *fp = NULL;

   fp = fopen( "test.txt", "w" );
   fputs( "abcd", fp );
   fclose( fp );

   string_utf8_t *string = string_utf8_from_file_cstring( "test.txt" );

   CU_ASSERT( string != NULL );
   CU_ASSERT( string_utf8_count( string ) == 4 );
   CU_ASSERT( string_utf8_is_equal_cstring( string, "abcd" ) == 1 );

   string_utf8_deep_dispose( &string );

   return;
}

int
add_test_from_file_cstring( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_from_file_cstring", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_from_file_cstring_utf8_1
   add_test_to_suite( p_suite, test_from_file_cstring_utf8_1, "test_from_file_cstring_utf8_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

