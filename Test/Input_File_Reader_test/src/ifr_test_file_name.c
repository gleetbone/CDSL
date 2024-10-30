/**
 @file ifr_test_file_name.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for ifr_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for ifr_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "Input_File_Reader.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_file_name_1
*/

void test_file_name_1( void )
{
   ifr_t *ifr = NULL;
   string_t *file_name = NULL;
   string_t *s = NULL;
   
   file_name = string_make_from_cstring( "src/input_files/f_one_line.txt" );
   
   ifr = ifr_make( file_name );

   s = ifr_file_name( ifr );
   
   CU_ASSERT( string_is_equal( file_name, s ) == 1 );

   ifr_deep_dispose( &ifr );
   string_deep_dispose( &file_name );
   string_deep_dispose( &s );
   
   return;
}

int
add_test_file_name( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_file_name", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_file_name_1
   add_test_to_suite( p_suite, test_file_name_1, "test_file_name_1" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

