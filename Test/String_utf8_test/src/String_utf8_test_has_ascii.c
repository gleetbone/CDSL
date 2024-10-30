/**
 @file string_utf8_test_has_ascii.c
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
   test_has_ascii_1
*/

void test_has_ascii_1( void )
{
   string_utf8_t *string = NULL;

   string = string_utf8_make();

   CU_ASSERT( string_utf8_has_ascii( string, 'a' ) == 0 );

   string_utf8_deep_dispose( &string );

   return;
}

/**
   test_has_ascii_2
*/

void test_has_ascii_2( void )
{
   string_utf8_t *string = NULL;

   string = string_utf8_make_from_cstring( "abcde" );

   CU_ASSERT( string_utf8_has_ascii( string, 'a' ) == 1 );
   CU_ASSERT( string_utf8_has_ascii( string, 'b' ) == 1 );
   CU_ASSERT( string_utf8_has_ascii( string, 'c' ) == 1 );
   CU_ASSERT( string_utf8_has_ascii( string, 'd' ) == 1 );
   CU_ASSERT( string_utf8_has_ascii( string, 'e' ) == 1 );
   CU_ASSERT( string_utf8_has_ascii( string, 'A' ) == 0 );

   string_utf8_deep_dispose( &string );

   return;
}

int
add_test_has_ascii( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_has_ascii", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_has_ascii_1
   add_test_to_suite( p_suite, test_has_ascii_1, "test_has_ascii_1" );

   // test_has_ascii_2
   add_test_to_suite( p_suite, test_has_ascii_2, "test_has_ascii_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

