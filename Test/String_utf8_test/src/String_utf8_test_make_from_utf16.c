/**
 @file string_utf8_test_make_from_utf16.c
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
   test_make_from_utf16_1
*/

void test_make_from_utf16_1( void )
{
   string_utf8_t *string = NULL;
   string_utf8_t *string16 = NULL;
   utf16_t *s16 = NULL;

   string = string_utf8_make_from_cstring( "abcd" );

   s16 = string_utf8_as_utf16( string );
   
   string16 = string_utf8_make_from_utf16( s16 );
   
   CU_ASSERT( string16 != NULL );
   CU_ASSERT( string_utf8_is_equal( string, string16 ) == 0 );

   string_utf8_deep_dispose( &string );
   string_utf8_deep_dispose( &string16 );
   free( s16 );

   return;
}

/**
   test_make_from_utf16_2
*/

void test_make_from_utf16_2( void )
{
   string_utf8_t *string = NULL;
   string_utf8_t *string16 = NULL;
   utf16_t *s16 = NULL;

   string = string_utf8_make_from_cstring( "abcdefg" );

   s16 = string_utf8_as_utf16( string );
   
   string16 = string_utf8_make_from_utf16( s16 );
   
   CU_ASSERT( string16 != NULL );
   CU_ASSERT( string_utf8_is_equal( string, string16 ) == 0 );

   string_utf8_deep_dispose( &string );
   string_utf8_deep_dispose( &string16 );
   free( s16 );

   return;
}

int
add_test_make_from_utf16( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make_from_utf16", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_from_utf16_1
   add_test_to_suite( p_suite, test_make_from_utf16_1, "test_make_from_utf16_1" );

   // test_make_from_utf16_2
   add_test_to_suite( p_suite, test_make_from_utf16_2, "test_make_from_utf16_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

