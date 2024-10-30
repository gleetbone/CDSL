/**
 @file string_utf8_test_as_wchar.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for string_utf8_make_from_utf8"
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
   test_as_wchar_1
*/

void test_as_wchar_1( void )
{
   string_utf8_t *string = NULL;
   wchar_t *cstring = NULL;

   string = string_utf8_make_from_cstring( "abcd" );
   cstring = string_utf8_as_wchar( string );

   CU_ASSERT( cstring[0] == 'a' );
   CU_ASSERT( cstring[1] == 'b' );
   CU_ASSERT( cstring[2] == 'c' );
   CU_ASSERT( cstring[3] == 'd' );
   CU_ASSERT( cstring[4] == 0 );
   
   string_utf8_deep_dispose( &string );
   free( cstring );

   return;
}

int
add_test_as_wchar( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_as_wchar", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_as_wchar_1
   add_test_to_suite( p_suite, test_as_wchar_1, "test_as_wchar_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

