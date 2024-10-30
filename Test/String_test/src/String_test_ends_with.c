/**
 @file string_test_ends_with.c
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
   test_ends_with_1
*/

void test_ends_with_1( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "A" );
   string1 = string_make_from_cstring( "A" );
   
   CU_ASSERT( string_ends_with( string, string1 ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

/**
   test_ends_with_2
*/

void test_ends_with_2( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "AB" );
   string1 = string_make_from_cstring( "B" );
   
   CU_ASSERT( string_ends_with( string, string1 ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

/**
   test_ends_with_3
*/

void test_ends_with_3( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "BA" );
   string1 = string_make_from_cstring( "B" );
   
   CU_ASSERT( string_ends_with( string, string1 ) == 0 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

/**
   test_ends_with_4
*/

void test_ends_with_4( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABC" );
   string1 = string_make_from_cstring( "BC" );
   
   CU_ASSERT( string_ends_with( string, string1 ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

/**
   test_ends_with_5
*/

void test_ends_with_5( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABCDE" );
   string1 = string_make_from_cstring( "CD" );
   
   CU_ASSERT( string_ends_with( string, string1 ) == 0 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

/**
   test_ends_with_6
*/

void test_ends_with_6( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABCDE" );
   string1 = string_make_from_cstring( "ABCDEF" );
   
   CU_ASSERT( string_ends_with( string, string1 ) == 0 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

int
add_test_ends_with( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_ends_with", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_ends_with_1
   add_test_to_suite( p_suite, test_ends_with_1, "test_ends_with_1" );

   // test_ends_with_2
   add_test_to_suite( p_suite, test_ends_with_2, "test_ends_with_2" );

   // test_ends_with_3
   add_test_to_suite( p_suite, test_ends_with_3, "test_ends_with_4" );

   // test_ends_with_4
   add_test_to_suite( p_suite, test_ends_with_4, "test_ends_with_4" );

   // test_ends_with_5
   add_test_to_suite( p_suite, test_ends_with_5, "test_ends_with_5" );

   // test_ends_with_6
   add_test_to_suite( p_suite, test_ends_with_6, "test_ends_with_6" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

