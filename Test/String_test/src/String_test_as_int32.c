/**
 @file string_test_as_int32.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for string_make_from_cstring"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for string_make_from_cstring.

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
   test_as_int32_1
*/

void test_as_int32_1( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "abcd" );
   
   CU_ASSERT( string_as_int32( string ) == 0 );
 
   string_dispose_with_contents( string );

   return;
}

/**
   test_as_int32_2
*/

void test_as_int32_2( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "123" );
   
   CU_ASSERT( string_as_int32( string ) == 123 );
 
   string_dispose_with_contents( string );

   return;
}

int
add_test_as_int32( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_as_int32", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_as_int32_1
   add_test_to_suite( p_suite, test_as_int32_1, "test_as_int32_1" );

   // test_as_int32_2
   add_test_to_suite( p_suite, test_as_int32_2, "test_as_int32_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

