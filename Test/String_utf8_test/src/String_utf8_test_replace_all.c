/**
 @file string_utf8_test_replace_all.c
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
   test_replace_all_1
*/

void test_replace_all_1( void )
{
   string_utf8_t *string = NULL;
   string_utf8_t *string_utf8_original = NULL;
   string_utf8_t *string_utf8_new = NULL;

   string = string_utf8_make_from_cstring( "ABCD" );
   string_utf8_original = string_utf8_make_from_cstring( "B" );
   string_utf8_new = string_utf8_make_from_cstring( "Q" );

   string_utf8_replace_all( string, string_utf8_original, string_utf8_new );

   string_utf8_t *stringt = string_utf8_make_from_cstring( "AQCD" );

   CU_ASSERT( string_utf8_is_equal( string, stringt ) == 1 );

   string_utf8_deep_dispose( &string );
   string_utf8_deep_dispose( &string_utf8_original );
   string_utf8_deep_dispose( &string_utf8_new );
   string_utf8_deep_dispose( &stringt );

   return;
}

/**
   test_replace_all_2
*/

void test_replace_all_2( void )
{
   string_utf8_t *string = NULL;
   string_utf8_t *string_utf8_original = NULL;
   string_utf8_t *string_utf8_new = NULL;

   string = string_utf8_make_from_cstring( "ABCD" );
   string_utf8_original = string_utf8_make_from_cstring( "B" );
   string_utf8_new = string_utf8_make_from_cstring( "QR" );

   string_utf8_replace_all( string, string_utf8_original, string_utf8_new );

   string_utf8_t *stringt = string_utf8_make_from_cstring( "AQRCD" );

   CU_ASSERT( string_utf8_is_equal( string, stringt ) == 1 );

   string_utf8_deep_dispose( &string );
   string_utf8_deep_dispose( &string_utf8_original );
   string_utf8_deep_dispose( &string_utf8_new );
   string_utf8_deep_dispose( &stringt );

   return;
}

/**
   test_replace_all_3
*/

void test_replace_all_3( void )
{
   string_utf8_t *string = NULL;
   string_utf8_t *string_utf8_original = NULL;
   string_utf8_t *string_utf8_new = NULL;

   string = string_utf8_make_from_cstring( "ABCD" );
   string_utf8_original = string_utf8_make_from_cstring( "AB" );
   string_utf8_new = string_utf8_make_from_cstring( "X" );

   string_utf8_replace_all( string, string_utf8_original, string_utf8_new );

   string_utf8_t *stringt = string_utf8_make_from_cstring( "XCD" );

   CU_ASSERT( string_utf8_is_equal( string, stringt ) == 1 );

   string_utf8_deep_dispose( &string );
   string_utf8_deep_dispose( &string_utf8_original );
   string_utf8_deep_dispose( &string_utf8_new );
   string_utf8_deep_dispose( &stringt );

   return;
}

/**
   test_replace_all_4
*/

void test_replace_all_4( void )
{
   string_utf8_t *string = NULL;
   string_utf8_t *string_utf8_original = NULL;
   string_utf8_t *string_utf8_new = NULL;

   string = string_utf8_make_from_cstring( "ABCD" );
   string_utf8_original = string_utf8_make_from_cstring( "CD" );
   string_utf8_new = string_utf8_make_from_cstring( "XYZ" );

   string_utf8_replace_all( string, string_utf8_original, string_utf8_new );

   string_utf8_t *stringt = string_utf8_make_from_cstring( "ABXYZ" );

   CU_ASSERT( string_utf8_is_equal( string, stringt ) == 1 );

   string_utf8_deep_dispose( &string );
   string_utf8_deep_dispose( &string_utf8_original );
   string_utf8_deep_dispose( &string_utf8_new );
   string_utf8_deep_dispose( &stringt );

   return;
}

/**
   test_replace_all_5
*/

void test_replace_all_5( void )
{
   string_utf8_t *string = NULL;
   string_utf8_t *string_utf8_original = NULL;
   string_utf8_t *string_utf8_new = NULL;

   string = string_utf8_make_from_cstring( "ABCD" );
   string_utf8_original = string_utf8_make_from_cstring( "BCD" );
   string_utf8_new = string_utf8_make_from_cstring( "Q" );

   string_utf8_replace_all( string, string_utf8_original, string_utf8_new );

   string_utf8_t *stringt = string_utf8_make_from_cstring( "AQ" );

   CU_ASSERT( string_utf8_is_equal( string, stringt ) == 1 );

   string_utf8_deep_dispose( &string );
   string_utf8_deep_dispose( &string_utf8_original );
   string_utf8_deep_dispose( &string_utf8_new );
   string_utf8_deep_dispose( &stringt );

   return;
}

/**
   test_replace_all_6
*/

void test_replace_all_6( void )
{
   string_utf8_t *string = NULL;
   string_utf8_t *string_utf8_original = NULL;
   string_utf8_t *string_utf8_new = NULL;

   string = string_utf8_make_from_cstring( "ABCDE" );
   string_utf8_original = string_utf8_make_from_cstring( "BC" );
   string_utf8_new = string_utf8_make_from_cstring( "QRWXYZ" );

   string_utf8_replace_all( string, string_utf8_original, string_utf8_new );

   string_utf8_t *stringt = string_utf8_make_from_cstring( "AQRWXYZDE" );

   CU_ASSERT( string_utf8_is_equal( string, stringt ) == 1 );

   string_utf8_deep_dispose( &string );
   string_utf8_deep_dispose( &string_utf8_original );
   string_utf8_deep_dispose( &string_utf8_new );
   string_utf8_deep_dispose( &stringt );

   return;
}

int
add_test_replace_all( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_replace_all", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_replace_all_1
   add_test_to_suite( p_suite, test_replace_all_1, "test_replace_all_1" );

   // test_replace_all_2
   add_test_to_suite( p_suite, test_replace_all_2, "test_replace_all_2" );

   // test_replace_all_3
   add_test_to_suite( p_suite, test_replace_all_3, "test_replace_all_4" );

   // test_replace_all_4
   add_test_to_suite( p_suite, test_replace_all_4, "test_replace_all_4" );

   // test_replace_all_5
   add_test_to_suite( p_suite, test_replace_all_5, "test_replace_all_5" );

   // test_replace_all_6
   add_test_to_suite( p_suite, test_replace_all_6, "test_replace_all_6" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

