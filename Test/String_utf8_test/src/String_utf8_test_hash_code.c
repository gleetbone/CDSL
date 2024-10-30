/**
 @file string_utf8_test_hash_code.c
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
   test_hash_code_1
*/

void test_hash_code_1( void )
{
   string_utf8_t *string = NULL;

   string = string_utf8_make_from_cstring( "A" );

   CU_ASSERT( string_utf8_hash_code( string ) == 65 );

   string_utf8_deep_dispose( &string );

   return;
}

/**
   test_hash_code_2
*/

void test_hash_code_2( void )
{
   string_utf8_t *string = NULL;

   string = string_utf8_make_from_cstring( "123acb" );

   CU_ASSERT( string_utf8_hash_code( string ) == 958742370 );

   string_utf8_deep_dispose( &string );

   return;
}

int
add_test_hash_code( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_hash_code", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_hash_code_1
   add_test_to_suite( p_suite, test_hash_code_1, "test_hash_code_1" );

   // test_hash_code_2
   add_test_to_suite( p_suite, test_hash_code_2, "test_hash_code_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

