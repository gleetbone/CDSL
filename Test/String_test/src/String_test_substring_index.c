/**
 @file string_test_substring_index.c
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
   test_substring_index_1
*/

void test_substring_index_1( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "A" );
   string1 = string_make_from_cstring( "A" );
   
   CU_ASSERT( string_substring_index( string, string1 ) == 0 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

/**
   test_substring_index_2
*/

void test_substring_index_2( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "AB" );
   string1 = string_make_from_cstring( "B" );
   
   CU_ASSERT( string_substring_index( string, string1 ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

/**
   test_substring_index_3
*/

void test_substring_index_3( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABC" );
   string1 = string_make_from_cstring( "B" );
   
   CU_ASSERT( string_substring_index( string, string1 ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

/**
   test_substring_index_4
*/

void test_substring_index_4( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABCDEF" );
   string1 = string_make_from_cstring( "BC" );
   
   CU_ASSERT( string_substring_index( string, string1 ) == 1 );
  
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

/**
   test_substring_index_5
*/

void test_substring_index_5( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABCDEFABCDEF" );
   string1 = string_make_from_cstring( "BC" );
   
   CU_ASSERT( string_substring_index( string, string1 ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

/**
   test_substring_index_6
*/

void test_substring_index_6( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABCDEFABCDEF" );
   string1 = string_make_from_cstring( "XYZ" );
   
   CU_ASSERT( string_substring_index( string, string1 ) == -1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

int
add_test_substring_index( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_substring_index", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_substring_index_1
   add_test_to_suite( p_suite, test_substring_index_1, "test_substring_index_1" );

   // test_substring_index_2
   add_test_to_suite( p_suite, test_substring_index_2, "test_substring_index_2" );

   // test_substring_index_3
   add_test_to_suite( p_suite, test_substring_index_3, "test_substring_index_4" );

   // test_substring_index_4
   add_test_to_suite( p_suite, test_substring_index_4, "test_substring_index_4" );

   // test_substring_index_5
   add_test_to_suite( p_suite, test_substring_index_5, "test_substring_index_5" );

   // test_substring_index_6
   add_test_to_suite( p_suite, test_substring_index_6, "test_substring_index_6" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

