/**
 @file ifr_test_line.c
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
   test_line_1
*/

void test_line_1( void )
{
   ifr_t *ifr = NULL;
   string_t *file_name = NULL;
   string_t *line = NULL;
   
   string_t *l1 = NULL;
   
   l1 = string_make_from_cstring( "one two three" );
   
   file_name = string_make_from_cstring( "src/input_files/f_one_line.txt" );
   
   ifr = ifr_make( file_name );

   ifr_forth( ifr );
   
   line = ifr_line( ifr );
   
   CU_ASSERT( string_count( line ) == 13 );

   CU_ASSERT( string_is_equal( line, l1 ) == 1 );
      
   ifr_deep_dispose( &ifr );
   string_deep_dispose( &file_name );
   string_deep_dispose( &l1 );
   
   return;
}

int
add_test_line( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_line", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_line_1
   add_test_to_suite( p_suite, test_line_1, "test_line_1" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

