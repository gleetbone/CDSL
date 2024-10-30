/**
 @file binary_file_test_name.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for ifr_make_from_cstring"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for binary_file_t

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "Binary_File.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_name_1
*/

void test_name_1( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "file.bin" );

   file = binary_file_make( name );

   CU_ASSERT( string_is_equal( binary_file_name( file ), name ) == 1  );

   string_deep_dispose( &name );
   binary_file_dispose( &file );

   return;
}

/**
   test_name_2
*/

void test_name_2( void )
{
   binary_file_t *file= NULL;

   file = binary_file_make_cstring( "file.bin" );

   CU_ASSERT( strcmp( binary_file_name_cstring( file ), "file.bin" ) == 0 );

   binary_file_dispose( &file );

   return;
}


int
add_test_name( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_name", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_name_1
   add_test_to_suite( p_suite, test_name_1, "test_name_1" );

   // test_name_2
   add_test_to_suite( p_suite, test_name_2, "test_name_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

