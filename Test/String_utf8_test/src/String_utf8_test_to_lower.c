/**
 @file string_utf8_test_to_lower.c
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
   test_to_lower_1
*/

void test_to_lower_1( void )
{
   string_utf8_t *string = NULL;

   string = string_utf8_make_from_cstring( "ABcD5" );

   string_utf8_to_lower( string );

   CU_ASSERT( string_utf8_item_ascii( string, 0 ) == 'a' );
   CU_ASSERT( string_utf8_item_ascii( string, 1 ) == 'b' );
   CU_ASSERT( string_utf8_item_ascii( string, 2 ) == 'c' );
   CU_ASSERT( string_utf8_item_ascii( string, 3 ) == 'd' );
   CU_ASSERT( string_utf8_item_ascii( string, 4 ) == '5' );

   string_utf8_deep_dispose( &string );

   return;
}

int
add_test_to_lower( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_to_lower", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_to_lower_1
   add_test_to_suite( p_suite, test_to_lower_1, "test_to_lower_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

