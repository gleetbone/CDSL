/**
 @file string_test_deep_copy.c
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
   test_deep_copy_1
*/

void test_deep_copy_1( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABC" );
   string1 = string_make( );
   
   string_deep_copy( string1, string );
   
   CU_ASSERT( string_is_equal( string, string1 ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

/**
   test_deep_copy_2
*/

void test_deep_copy_2( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "" );
   string1 = string_make( );
   
   string_deep_copy( string1, string );
   
   CU_ASSERT( string_is_equal( string, string1 ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

/**
   test_deep_copy_3
*/

void test_deep_copy_3( void )
{
   string_t *string = NULL;
   string_t *string1 = NULL;
   
   string = string_make_from_cstring( "ABCDEF" );
   string1 = string_make_from_cstring("XYZ" );
   
   string_deep_copy( string1, string );
   
   CU_ASSERT( string_is_equal( string, string1 ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &string1 );

   return;
}

int
add_test_deep_copy( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_deep_copy", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_deep_copy_1
   add_test_to_suite( p_suite, test_deep_copy_1, "test_deep_copy_1" );

   // test_deep_copy_2
   add_test_to_suite( p_suite, test_deep_copy_2, "test_deep_copy_2" );

   // test_deep_copy_3
   add_test_to_suite( p_suite, test_deep_copy_3, "test_deep_copy_3" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

