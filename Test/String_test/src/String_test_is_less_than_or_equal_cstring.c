/**
 @file string_test_is_less_than_or_equal_cstring.c
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
   test_is_less_than_or_equal_cstring_1
*/

void test_is_less_than_or_equal_cstring_1( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "A" );
   
   CU_ASSERT( string_is_less_than_or_equal_cstring( string, "A" ) == 1 );
 
   string_deep_dispose( &string );

   return;
}

/**
   test_is_less_than_or_equal_cstring_2
*/

void test_is_less_than_or_equal_cstring_2( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "A" );
   
   CU_ASSERT( string_is_less_than_or_equal_cstring( string, "B" ) == 1 );
 
   string_deep_dispose( &string );

   return;
}

/**
   test_is_less_than_or_equal_cstring_3
*/

void test_is_less_than_or_equal_cstring_3( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "ABCDEFGHI" );
   
   CU_ASSERT( string_is_less_than_or_equal_cstring( string, "ABCDEFGHI" ) == 1 );
 
   string_deep_dispose( &string );

   return;
}

/**
   test_is_less_than_or_equal_cstring_4
*/

void test_is_less_than_or_equal_cstring_4( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "ABCDEFGHI1" );
   
   CU_ASSERT( string_is_less_than_or_equal_cstring( string, "ABCDEFGHI2" ) == 1 );
 
   string_deep_dispose( &string );

   return;
}

/**
   test_is_less_than_or_equal_cstring_5
*/

void test_is_less_than_or_equal_cstring_5( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "abc" );
   
   CU_ASSERT( string_is_less_than_or_equal_cstring( string, "ABC" ) == 0 );
 
   string_deep_dispose( &string );

   return;
}

int
add_test_is_less_than_or_equal_cstring( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_less_than_or_equal_cstring", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_less_than_or_equal_cstring_1
   add_test_to_suite( p_suite, test_is_less_than_or_equal_cstring_1, "test_is_less_than_or_equal_cstring_1" );

   // test_is_less_than_or_equal_cstring_2
   add_test_to_suite( p_suite, test_is_less_than_or_equal_cstring_2, "test_is_less_than_or_equal_cstring_2" );

   // test_is_less_than_or_equal_cstring_3
   add_test_to_suite( p_suite, test_is_less_than_or_equal_cstring_3, "test_is_less_than_or_equal_cstring_4" );

   // test_is_less_than_or_equal_cstring_4
   add_test_to_suite( p_suite, test_is_less_than_or_equal_cstring_4, "test_is_less_than_or_equal_cstring_4" );

   // test_is_less_than_or_equal_cstring_5
   add_test_to_suite( p_suite, test_is_less_than_or_equal_cstring_5, "test_is_less_than_or_equal_cstring_5" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

