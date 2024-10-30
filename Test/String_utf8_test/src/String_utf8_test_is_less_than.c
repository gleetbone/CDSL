/**
 @file string_utf8_test_is_less_than.c
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
   test_is_less_than_1
*/

void test_is_less_than_1( void )
{
   string_utf8_t *string = NULL;
   string_utf8_t *string1 = NULL;

   string = string_utf8_make_from_cstring( "A" );
   string1 = string_utf8_make_from_cstring( "A" );

   CU_ASSERT( string_utf8_is_less_than( string, string1 ) == 0 );

   string_utf8_deep_dispose( &string );
   string_utf8_deep_dispose( &string1 );

   return;
}

/**
   test_is_less_than_2
*/

void test_is_less_than_2( void )
{
   string_utf8_t *string = NULL;
   string_utf8_t *string1 = NULL;

   string = string_utf8_make_from_cstring( "A" );
   string1 = string_utf8_make_from_cstring( "B" );

   CU_ASSERT( string_utf8_is_less_than( string, string1 ) == 1 );

   string_utf8_deep_dispose( &string );
   string_utf8_deep_dispose( &string1 );

   return;
}

/**
   test_is_less_than_3
*/

void test_is_less_than_3( void )
{
   string_utf8_t *string = NULL;
   string_utf8_t *string1 = NULL;

   string = string_utf8_make_from_cstring( "ABCDEFGHI" );
   string1 = string_utf8_make_from_cstring( "ABCDEFGHI" );

   CU_ASSERT( string_utf8_is_less_than( string, string1 ) == 0 );

   string_utf8_deep_dispose( &string );
   string_utf8_deep_dispose( &string1 );

   return;
}

/**
   test_is_less_than_4
*/

void test_is_less_than_4( void )
{
   string_utf8_t *string = NULL;
   string_utf8_t *string1 = NULL;

   string = string_utf8_make_from_cstring( "ABCDEFGHI1" );
   string1 = string_utf8_make_from_cstring( "ABCDEFGHI2" );

   CU_ASSERT( string_utf8_is_less_than( string, string1 ) == 1 );

   string_utf8_deep_dispose( &string );
   string_utf8_deep_dispose( &string1 );

   return;
}

/**
   test_is_less_than_5
*/

void test_is_less_than_5( void )
{
   string_utf8_t *string = NULL;
   string_utf8_t *string1 = NULL;

   string = string_utf8_make_from_cstring( "abc" );
   string1 = string_utf8_make_from_cstring( "ABC" );

   CU_ASSERT( string_utf8_is_less_than( string, string1 ) == 0 );

   string_utf8_deep_dispose( &string );
   string_utf8_deep_dispose( &string1 );

   return;
}

int
add_test_is_less_than( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_less_than", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_less_than_1
   add_test_to_suite( p_suite, test_is_less_than_1, "test_is_less_than_1" );

   // test_is_less_than_2
   add_test_to_suite( p_suite, test_is_less_than_2, "test_is_less_than_2" );

   // test_is_less_than_3
   add_test_to_suite( p_suite, test_is_less_than_3, "test_is_less_than_4" );

   // test_is_less_than_4
   add_test_to_suite( p_suite, test_is_less_than_4, "test_is_less_than_4" );

   // test_is_less_than_5
   add_test_to_suite( p_suite, test_is_less_than_5, "test_is_less_than_5" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

