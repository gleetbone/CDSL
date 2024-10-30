/**
 @file string_utf8_utf8_test_make.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for string_utf8_make"
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
   test_make_1
*/

void test_make_1( void )
{
   string_utf8_t *string = NULL;

   string = string_utf8_make();

   CU_ASSERT( string != NULL );
   CU_ASSERT( string_utf8_count( string ) == 0 );
   CU_ASSERT( string_utf8_capacity( string ) == 4 );
   CU_ASSERT( string_utf8_is_empty( string ) == 1 );

   string_utf8_deep_dispose( &string );

   return;
}

int
add_test_make( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_1
   add_test_to_suite( p_suite, test_make_1, "test_make_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

