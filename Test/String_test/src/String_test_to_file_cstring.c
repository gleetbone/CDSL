/**
 @file string_test_to_file_cstring.c
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
   test_to_file_cstring_1
*/

void test_to_file_cstring_1( void )
{
   FILE *fp = NULL;

   fp = fopen( "test.txt", "w" );
   fclose( fp );

   string_t *s = string_make_from_cstring( "abcd" );
   string_to_file_cstring( s, "test.txt" );

   string_t *s1 = string_from_file_cstring( "test.txt" );

   CU_ASSERT( s1 != NULL );
   CU_ASSERT( string_count( s1 ) == 4 );
   CU_ASSERT( string_is_equal_cstring( s1, "abcd" ) == 1 );

   string_dispose_with_contents( s );
   string_dispose_with_contents( s1 );

   return;
}

int
add_test_to_file_cstring( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_to_file_cstring", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_to_file_cstring_1
   add_test_to_suite( p_suite, test_to_file_cstring_1, "test_to_file_cstring_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

