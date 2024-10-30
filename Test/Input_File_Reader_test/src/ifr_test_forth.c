/**
 @file ifr_test_forth.c
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
   test_forth_1
*/

void test_forth_1( void )
{
   ifr_t *ifr = NULL;
   string_t *file_name = NULL;
   
   file_name = string_make_from_cstring( "src/input_files/f_multiline.txt" );
   
   ifr = ifr_make( file_name );

   CU_ASSERT( ifr_eof( ifr ) == 0 );
   
   // first line
   ifr_forth( ifr );
   
   // second line skipped - blank
   
   // third line
   ifr_forth( ifr );
   
   // fourth line
   ifr_forth( ifr );
   
   // fourth line
   ifr_forth( ifr );
 
   // fifth line skipped - blank
      
   // sixth line
   ifr_forth( ifr );

   // seventh and eighth line skipped - blank
   
   // end of file
   ifr_forth( ifr );
   
   CU_ASSERT( ifr_eof( ifr ) == 1 );

   ifr_deep_dispose( &ifr );
   string_deep_dispose( &file_name );
   
   return;
}

int
add_test_forth( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_forth", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_forth_1
   add_test_to_suite( p_suite, test_forth_1, "test_forth_1" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

