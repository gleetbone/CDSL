/**
 @file string_test_make_from.c
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
   test_make_from_1
*/

void test_make_from_1( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "abcd" );
   
   string_t *string1 = NULL;
   
   string1 = string_make_from( string );
   
   CU_ASSERT( string1 != NULL );
   CU_ASSERT( string_count( string1 ) == 4 );
   CU_ASSERT( string_capacity( string1 ) == 5 );
   CU_ASSERT( string_is_empty( string1 ) == 0 );
 
   string_dispose_with_contents( string );
   string_dispose_with_contents( string1 );

   return;
}

int
add_test_make_from( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make_from", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_from_1
   add_test_to_suite( p_suite, test_make_from_1, "test_make_from_1" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

