/**
 @file string_utf8_test_put.c
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
   test_put_1
*/

void test_put_1( void )
{
   string_utf8_t *string = NULL;
   char_t cp[4] = {0};

   string = string_utf8_make_from_cstring( "abc" );

   cp[0] = 'X';
   string_utf8_put( string, cp, 0 );

   CU_ASSERT( string_utf8_item_ascii( string, 0 ) == 'X' );
   CU_ASSERT( string_utf8_item_ascii( string, 1 ) == 'b' );
   CU_ASSERT( string_utf8_item_ascii( string, 2 ) == 'c' );

   string_utf8_deep_dispose( &string );

   return;
}

/**
   test_put_2
*/

void test_put_2( void )
{
   string_utf8_t *string = NULL;
   char_t cp[4] = {0};

   string = string_utf8_make_from_cstring( "abc" );

   cp[0] = 'X';
   string_utf8_put( string, cp, 1 );

   CU_ASSERT( string_utf8_item_ascii( string, 0 ) == 'a' );
   CU_ASSERT( string_utf8_item_ascii( string, 1 ) == 'X' );
   CU_ASSERT( string_utf8_item_ascii( string, 2 ) == 'c' );

   string_utf8_deep_dispose( &string );

   return;
}

/**
   test_put_3
*/

void test_put_3( void )
{
   string_utf8_t *string = NULL;
   char_t cp[4] = {0};

   string = string_utf8_make_from_cstring( "abcde" );

   cp[0] = 'X';
   string_utf8_put( string, cp, 2 );

   CU_ASSERT( string_utf8_item_ascii( string, 0 ) == 'a' );
   CU_ASSERT( string_utf8_item_ascii( string, 1 ) == 'b' );
   CU_ASSERT( string_utf8_item_ascii( string, 2 ) == 'X' );

   string_utf8_deep_dispose( &string );

   return;
}

/**
   test_put_4
*/

void test_put_4( void )
{
   string_utf8_t *string = NULL;
   char_t cp[4] = {0};
   char_t *p = NULL;

   string = string_utf8_make_from_cstring( "abc" );

   // Greek alpha 
   cp[0] = 0xCE;
   cp[1] = 0xB1;
   
   string_utf8_put( string, cp, 3 );

   CU_ASSERT( string_utf8_item_ascii( string, 0 ) == 'a' );
   CU_ASSERT( string_utf8_item_ascii( string, 1 ) == 'b' );
   CU_ASSERT( string_utf8_item_ascii( string, 2 ) == 'c' );
   
   p = string_utf8_item( string, 3 );
   CU_ASSERT( p[0] == ( char_t ) 0xCE );
   CU_ASSERT( p[1] == ( char_t ) 0xB1 );
   free( p );

   string_utf8_deep_dispose( &string );

   return;
}

/**
   test_put_5
*/

void test_put_5( void )
{
   string_utf8_t *string = NULL;
   char_t cp[4] = {0};
   char_t *p = NULL;

   string = string_utf8_make_from_cstring( "abc" );

   // Greek alpha 
   cp[0] = 0xCE;
   cp[1] = 0xB1;
   
   string_utf8_put( string, cp, 1 );

   CU_ASSERT( string_utf8_item_ascii( string, 0 ) == 'a' );
   
   p = string_utf8_item( string, 1 );
   CU_ASSERT( p[0] == ( char_t ) 0xCE );
   CU_ASSERT( p[1] == ( char_t ) 0xB1 );
   free( p );
      
   CU_ASSERT( string_utf8_item_ascii( string, 2 ) == 'c' );
   

   string_utf8_deep_dispose( &string );

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

   // test_put_5
   add_test_to_suite( p_suite, test_put_5, "test_put_5" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

