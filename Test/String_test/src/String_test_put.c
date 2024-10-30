/**
 @file string_test_put.c
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
   test_put_1
*/

void test_put_1( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "abc" );
   
   string_put( string, 'X', 0 );
   
   CU_ASSERT( string_item( string, 0 ) == 'X' );
   CU_ASSERT( string_item( string, 1 ) == 'b' );
   CU_ASSERT( string_item( string, 2 ) == 'c' );
 
   string_deep_dispose( &string );

   return;
}

/**
   test_put_2
*/

void test_put_2( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "abc" );
   
   string_put( string, 'X', 1 );
   
   CU_ASSERT( string_item( string, 0 ) == 'a' );
   CU_ASSERT( string_item( string, 1 ) == 'X' );
   CU_ASSERT( string_item( string, 2 ) == 'c' );
 
   string_deep_dispose( &string );

   return;
}

/**
   test_put_3
*/

void test_put_3( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "abc" );
   
   string_put( string, 'X', 2 );
   
   CU_ASSERT( string_item( string, 0 ) == 'a' );
   CU_ASSERT( string_item( string, 1 ) == 'b' );
   CU_ASSERT( string_item( string, 2 ) == 'X' );
 
   string_deep_dispose( &string );

   return;
}

/**
   test_put_4
*/

void test_put_4( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "abc" );
   
   string_put( string, 'X', 3 );
   
   CU_ASSERT( string_item( string, 0 ) == 'a' );
   CU_ASSERT( string_item( string, 1 ) == 'b' );
   CU_ASSERT( string_item( string, 2 ) == 'c' );
   CU_ASSERT( string_item( string, 3 ) == 'X' );
 
   string_deep_dispose( &string );

   return;
}

int
add_test_put( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_put", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_put_1
   add_test_to_suite( p_suite, test_put_1, "test_put_1" );

   // test_put_2
   add_test_to_suite( p_suite, test_put_2, "test_put_2" );

   // test_put_3
   add_test_to_suite( p_suite, test_put_3, "test_put_3" );

   // test_put_4
   add_test_to_suite( p_suite, test_put_4, "test_put_4" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

