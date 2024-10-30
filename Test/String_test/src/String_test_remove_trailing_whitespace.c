/**
 @file string_test_remove_trailing_whitespace.c
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

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_remove_trailing_whitespace_1
*/

void test_remove_trailing_whitespace_1( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "  ABcD5 " );
   string_remove_trailing_whitespace( string );
   CU_ASSERT( string_is_equal_cstring( string, "  ABcD5" ) );

   string_wipe_out( string );
   string_append_cstring( string, " ABcD5" );
   string_remove_trailing_whitespace( string );
   CU_ASSERT( string_is_equal_cstring( string, " ABcD5" ) );
 
   string_deep_dispose( &string );

   return;
}

int
add_test_remove_trailing_whitespace( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_remove_trailing_whitespace", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_remove_trailing_whitespace_1
   add_test_to_suite( p_suite, test_remove_trailing_whitespace_1, "test_remove_trailing_whitespace_1" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

