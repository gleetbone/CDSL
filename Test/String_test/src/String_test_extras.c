/**
 @file string_test_extras.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for string_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for string_make.

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "String_extras.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_extras_1
*/

void test_extras_1( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make();
   string1 = s_make_from( string );
   
   CU_ASSERT( string != NULL );
   CU_ASSERT( string1 != NULL );
   CU_ASSERT( string_count( string ) == 0 );
   CU_ASSERT( string_count( string1 ) == 0 );
   CU_ASSERT( string_count( string ) == 0 );
   CU_ASSERT( string_count( string1 ) == 0 );
   CU_ASSERT( string_is_empty( string ) == 1 );
   CU_ASSERT( string_is_empty( string1 ) == 1 );

   string_dispose_with_contents( string );
   string_dispose_with_contents( string1 );

   return;
}

/**
   test_extras_2
*/

void test_extras_2( void )
{
   string_t *string = NULL;
   int32_t i = 0;

   string = string_make_from_cstring( "abcd" );

   i = s_hash_code( string );

   CU_ASSERT( string != NULL );
   CU_ASSERT( i == 1633837924 );

   string_dispose_with_contents( string );

   return;
}

/**
   test_extras_3
*/

void test_extras_3( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   int32_t i = 0;

   string = string_make_from_cstring( "abcd" );
   string1 = string_make_from_cstring( "abcd" );

   i = s_is_equal( string, string1 );

   CU_ASSERT( string != NULL );
   CU_ASSERT( string1 != NULL );
   CU_ASSERT( i == 1 );

   string_dispose_with_contents( string );
   string_dispose_with_contents( string1 );

   return;
}

/**
   test_extras_4
*/

void test_extras_4( void )
{
   string_t *string = NULL;

   string = string_make_from_cstring( "abcd" );

   CU_ASSERT( string != NULL );

   s_dispose_with_contents( string );

   return;
}

int
add_test_extras( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_extras", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_extras_1
   add_test_to_suite( p_suite, test_extras_1, "test_extras_1" );

   // test_extras_2
   add_test_to_suite( p_suite, test_extras_2, "test_extras_2" );

   // test_extras_3
   add_test_to_suite( p_suite, test_extras_3, "test_extras_3" );

   // test_extras_4
   add_test_to_suite( p_suite, test_extras_4, "test_extras_4" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

