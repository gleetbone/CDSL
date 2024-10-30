/**
 @file string_test_copy_cstring.c
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
   test_copy_cstring_1
*/

void test_copy_cstring_1( void )
{
   char_t *string = NULL;
   string_t *string1 = NULL;
   
   string = "ABC";
   string1 = string_make( );
   
   string_copy_cstring( string1, string );
   
   CU_ASSERT( string_is_equal_cstring( string1, string ) == 1 );
 
   string_deep_dispose( &string1 );

   return;
}

/**
   test_copy_cstring_2
*/

void test_copy_cstring_2( void )
{
   char_t *string = NULL;
   string_t *string1 = NULL;
   
   string = "";
   string1 = string_make( );
   
   string_copy_cstring( string1, string );
   
   CU_ASSERT( string_is_equal_cstring( string1, string ) == 1 );
 
   string_deep_dispose( &string1 );

   return;
}

/**
   test_copy_cstring_3
*/

void test_copy_cstring_3( void )
{
   char_t *string = NULL;
   string_t *string1 = NULL;
   
   string = "ABCDEF";
   string1 = string_make_from_cstring("XYZ" );
   
   string_copy_cstring( string1, string );
   
   CU_ASSERT( string_is_equal_cstring( string1, string ) == 1 );
 
   string_deep_dispose( &string1 );

   return;
}

int
add_test_copy_cstring( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_copy_cstring", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_copy_1
   add_test_to_suite( p_suite, test_copy_cstring_1, "test_copy_cstring_1" );

   // test_copy_2
   add_test_to_suite( p_suite, test_copy_cstring_2, "test_copy_cstring_2" );

   // test_copy_3
   add_test_to_suite( p_suite, test_copy_cstring_3, "test_copy_cstring_3" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

