/**
 @file string_test_split_cstring.c
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
   test_split_cstring_1
*/

void test_split_cstring_1( void )
{
   string_t *string = NULL;
   string_t **result = NULL;
   int32_t count = 0;
   string_t *stringt = NULL;
   
   string = string_make_from_cstring( "a b" );
   
   result = string_split_cstring( string, " ", &count );
   
   CU_ASSERT( result != NULL );
   CU_ASSERT( count == 2 );
   
   stringt = string_make_from_cstring( "a" );
   
   CU_ASSERT( string_is_equal( result[0], stringt ) == 1 );
   
   string_deep_dispose( &stringt );
   string_deep_dispose( &result[0] );
 
   stringt = string_make_from_cstring( "b" );
   
   CU_ASSERT( string_is_equal( result[1], stringt ) == 1 );
   
   string_deep_dispose( &string );
   string_deep_dispose( &stringt );
   string_deep_dispose( &result[1] );
   free( result );
 
   return;
}

void test_split_cstring_2( void )
{
   string_t *string = NULL;
   string_t **result = NULL;
   int32_t count = 0;
   string_t *stringt = NULL;
   
   string = string_make_from_cstring( "a b;c" );
   
   result = string_split_cstring( string, " ;", &count );
   
   CU_ASSERT( result != NULL );
   CU_ASSERT( count == 3 );
   
   stringt = string_make_from_cstring( "a" );
   
   CU_ASSERT( string_is_equal( result[0], stringt ) == 1 );
   
   string_deep_dispose( &stringt );
   string_deep_dispose( &result[0] );
  
   stringt = string_make_from_cstring( "b" );
   
   CU_ASSERT( string_is_equal( result[1], stringt ) == 1 );
   
   string_deep_dispose( &stringt );
   string_deep_dispose( &result[1] );
 
   stringt = string_make_from_cstring( "c" );
   
   CU_ASSERT( string_is_equal( result[2], stringt ) == 1 );
   
   string_deep_dispose( &string );
   string_deep_dispose( &stringt );
   string_deep_dispose( &result[2] );
   free( result );
 
   return;
}

void test_split_cstring_3( void )
{
   string_t *string = NULL;
   string_t **result = NULL;
   int32_t count = 0;
   int32_t i = 0;

   string = string_make_from_cstring( "a;b;c;d;e;f;g;h;i;j;k" );

   result = string_split_cstring( string, ";", &count );

   CU_ASSERT( result != NULL );
   CU_ASSERT( count == 11 );

   for ( i=0; i<count; i++ )
   {
      string_deep_dispose( &result[i] );
   }

   free( result );
   string_deep_dispose( &string );

   return;
}

int
add_test_split_cstring( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_split_cstring", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_split_cstring_1
   add_test_to_suite( p_suite, test_split_cstring_1, "test_split_cstring_1" );

   // test_split_cstring_2
   add_test_to_suite( p_suite, test_split_cstring_2, "test_split_cstring_2" );

   // test_split_cstring_3
   add_test_to_suite( p_suite, test_split_cstring_3, "test_split_cstring_3" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

