/**
 @file string_test_capacity.c
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
   test_capacity_1
*/

void test_capacity_1( void )
{
   string_t *string = NULL;
   
   string = string_make_n( 13 );
   
   CU_ASSERT( string_capacity( string ) == 13 );
 
   string_dispose_with_contents( string );

   return;
}

/**
   test_capacity_2
*/

void test_capacity_2( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "abcd" );
   
   CU_ASSERT( string_capacity( string ) == 5 );
 
   string_dispose_with_contents( string );

   return;
}

int
add_test_capacity( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_capacity", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_capacity_1
   add_test_to_suite( p_suite, test_capacity_1, "test_capacity_1" );

   // test_capacity_2
   add_test_to_suite( p_suite, test_capacity_2, "test_capacity_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

