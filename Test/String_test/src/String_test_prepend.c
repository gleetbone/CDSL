/**
 @file string_test_prepend.c
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
   test_prepend_1
*/

void test_prepend_1( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABCD" );
   string1 = string_make_from_cstring( "Q" );
   
   string_prepend( string, string1 );
   
   string_t *stringt = string_make_from_cstring( "QABCD" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );
   string_deep_dispose( &stringt );

   return;
}

/**
   test_prepend_2
*/

void test_prepend_2( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "" );
   string1 = string_make_from_cstring( "ABC" );
   
   string_prepend( string, string1 );
   
   string_t *stringt = string_make_from_cstring( "ABC" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );
   string_deep_dispose( &stringt );

   return;
}

/**
   test_prepend_3
*/

void test_prepend_3( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABCD" );
   string1 = string_make_from_cstring( "XYZ" );
   
   string_prepend( string, string1 );
   
   string_t *stringt = string_make_from_cstring( "XYZABCD" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );
   string_deep_dispose( &stringt );

   return;
}

/**
   test_prepend_4
*/

void test_prepend_4( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;

   string = string_make_n( 32 );
   string_append_cstring( string, "ABCD" );
   string1 = string_make_from_cstring( "XYZ" );

   string_prepend( string, string1 );

   string_t *stringt = string_make_from_cstring( "XYZABCD" );

   CU_ASSERT( string_is_equal( string, stringt ) == 1 );

   string_deep_dispose( &string );
   string_deep_dispose( &string1 );
   string_deep_dispose( &stringt );

   return;
}


int
add_test_prepend( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_prepend", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_prepend_1
   add_test_to_suite( p_suite, test_prepend_1, "test_prepend_1" );

   // test_prepend_2
   add_test_to_suite( p_suite, test_prepend_2, "test_prepend_2" );

   // test_prepend_3
   add_test_to_suite( p_suite, test_prepend_3, "test_prepend_3" );

   // test_prepend_4
   add_test_to_suite( p_suite, test_prepend_4, "test_prepend_4" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

