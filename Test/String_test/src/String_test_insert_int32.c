/**
 @file string_test_insert_int32.c
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

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_insert_int32_1
*/

void test_insert_int32_1( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "ABC" );
   
   string_insert_int32( string, 123, 0 );
   
   string_t *stringt = string_make_from_cstring( "123ABC" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_dispose_with_contents( string );
   string_dispose_with_contents( stringt );

   return;
}

/**
   test_insert_int32_2
*/

void test_insert_int32_2( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "ABC" );
   
   string_insert_int32( string, 123, 1 );
   
   string_t *stringt = string_make_from_cstring( "A123BC" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_dispose_with_contents( string );
   string_dispose_with_contents( stringt );

   return;
}

/**
   test_insert_int32_3
*/

void test_insert_int32_3( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "ABC" );
   
   string_insert_int32( string, 123, 2 );
   
   string_t *stringt = string_make_from_cstring( "AB123C" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_dispose_with_contents( string );
   string_dispose_with_contents( stringt );

   return;
}

/**
   test_insert_int32_4
*/

void test_insert_int32_4( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "ABC" );
   
   string_insert_int32( string, -123, 1 );
   
   string_t *stringt = string_make_from_cstring( "A-123BC" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_dispose_with_contents( string );
   string_dispose_with_contents( stringt );

   return;
}

/**
   test_insert_int32_5
*/

void test_insert_int32_5( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "ABC" );
   
   string_insert_int32( string, -123, 0 );
   
   string_t *stringt = string_make_from_cstring( "-123ABC" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_dispose_with_contents( string );
   string_dispose_with_contents( stringt );

   return;
}

/**
   test_insert_int32_6
*/

void test_insert_int32_6( void )
{
   string_t *string = NULL;

   string = string_make_n( 32 );
   string_append_cstring( string, "ABC" );

   string_insert_int32( string, -123, 0 );

   string_t *stringt = string_make_from_cstring( "-123ABC" );

   CU_ASSERT( string_is_equal( string, stringt ) == 1 );

   string_dispose_with_contents( string );
   string_dispose_with_contents( stringt );

   return;
}


int
add_test_insert_int32( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_insert_int32", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_insert_int32_1
   add_test_to_suite( p_suite, test_insert_int32_1, "test_insert_int32_1" );

   // test_insert_int32_2
   add_test_to_suite( p_suite, test_insert_int32_2, "test_insert_int32_2" );

   // test_insert_int32_3
   add_test_to_suite( p_suite, test_insert_int32_3, "test_insert_int32_3" );

   // test_insert_int32_4
   add_test_to_suite( p_suite, test_insert_int32_4, "test_insert_int32_4" );

   // test_insert_int32_5
   add_test_to_suite( p_suite, test_insert_int32_5, "test_insert_int32_5" );

   // test_insert_int32_6
   add_test_to_suite( p_suite, test_insert_int32_6, "test_insert_int32_6" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

