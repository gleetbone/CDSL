/**
 @file string_test_compare.c
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
   test_compare_1
*/

void test_compare_1( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "A" );
   string1 = string_make_from_cstring( "A" );
   
   CU_ASSERT( string_compare( string, string1 ) == 0 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

/**
   test_compare_2
*/

void test_compare_2( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "A" );
   string1 = string_make_from_cstring( "B" );
   
   CU_ASSERT( string_compare( string, string1 ) < 0 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

/**
   test_compare_3
*/

void test_compare_3( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABCDEFGHI" );
   string1 = string_make_from_cstring( "ABCDEFGHI" );
   
   CU_ASSERT( string_compare( string, string1 ) == 0 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

/**
   test_compare_4
*/

void test_compare_4( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABCDEFGHI1" );
   string1 = string_make_from_cstring( "ABCDEFGHI2" );
   
   CU_ASSERT( string_compare( string, string1 ) < 0 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

/**
   test_compare_5
*/

void test_compare_5( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "abc" );
   string1 = string_make_from_cstring( "ABC" );
   
   CU_ASSERT( string_compare( string, string1 ) > 0 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

/**
   test_compare_6
*/

void test_compare_6( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "B" );
   string1 = string_make_from_cstring( "A" );
   
   CU_ASSERT( string_compare( string, string1 ) > 0 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

/**
   test_compare_7
*/

void test_compare_7( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "A" );
   
   CU_ASSERT( string_compare( string, string ) == 0 );
 
   string_deep_dispose( &string );

   return;
}

int
add_test_compare( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_compare", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_compare_1
   add_test_to_suite( p_suite, test_compare_1, "test_compare_1" );

   // test_compare_2
   add_test_to_suite( p_suite, test_compare_2, "test_compare_2" );

   // test_compare_3
   add_test_to_suite( p_suite, test_compare_3, "test_compare_4" );

   // test_compare_4
   add_test_to_suite( p_suite, test_compare_4, "test_compare_4" );

   // test_compare_5
   add_test_to_suite( p_suite, test_compare_5, "test_compare_5" );

   // test_compare_6
   add_test_to_suite( p_suite, test_compare_6, "test_compare_6" );

   // test_compare_7
   add_test_to_suite( p_suite, test_compare_7, "test_compare_7" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

