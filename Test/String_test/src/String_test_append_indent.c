/**
 @file string_test_append_indent.c
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
   test_append_indent_1
*/

void test_append_indent_1( void )
{
   string_t *string = NULL;

   string = string_make_from_cstring( "ABCD" );

   string_append_indent( string, 0 );

   CU_ASSERT( string_is_equal_cstring( string, "ABCD" ) == 1 );

   string_deep_dispose( &string );

   return;
}

/**
   test_append_indent_2
*/

void test_append_indent_2( void )
{
   string_t *string = NULL;

   string = string_make_from_cstring( "ABCD" );

   string_append_indent( string, 1 );

   CU_ASSERT( string_is_equal_cstring( string, "ABCD   " ) == 1 );

   string_deep_dispose( &string );

   return;
}

/**
   test_append_indent_3
*/

void test_append_indent_3( void )
{
   string_t *string = NULL;

   string = string_make_from_cstring( "ABCD" );

   string_append_indent( string, 2 );

   CU_ASSERT( string_is_equal_cstring( string, "ABCD      " ) == 1 );

   string_deep_dispose( &string );

   return;
}


int
add_test_append_indent( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_append_indent", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_append_indent_1
   add_test_to_suite( p_suite, test_append_indent_1, "test_append_indent_1" );

   // test_append_indent_2
   add_test_to_suite( p_suite, test_append_indent_2, "test_append_indent_2" );

   // test_append_indent_3
   add_test_to_suite( p_suite, test_append_indent_3, "test_append_indent_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

