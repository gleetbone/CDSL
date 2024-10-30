/**
 @file string_test_deep_dispose.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for string_make"
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
   test_deep_dispose_1
*/

void test_deep_dispose_1( void )
{
   string_t *string = NULL;
   
   string = string_make();
   
   CU_ASSERT( string != NULL );
   CU_ASSERT( string_count( string ) == 0 );
   CU_ASSERT( string_capacity( string ) == 1 );
   CU_ASSERT( string_is_empty( string ) == 1 );
 
   string_deep_dispose( &string );
   
   return;
}

void test_deep_dispose_2( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "abcde" );
   
   CU_ASSERT( string != NULL );
   CU_ASSERT( string_count( string ) == 5 );
   CU_ASSERT( string_capacity( string ) == 6 );
   CU_ASSERT( string_is_empty( string ) == 0 );
 
   string_deep_dispose( &string );
   
   return;
}

int
add_test_deep_dispose( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_deep_dispose", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_deep_dispose_1
   add_test_to_suite( p_suite, test_deep_dispose_1, "test_deep_dispose_1" );

   // test_deep_dispose_2
   add_test_to_suite( p_suite, test_deep_dispose_2, "test_deep_dispose_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

