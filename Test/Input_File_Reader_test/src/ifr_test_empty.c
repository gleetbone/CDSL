/**
 @file ifr_test_empty.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for ifr_make_from_cstring"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for ifr_make_from_cstring.

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
   test_empty_1
*/

void test_empty_1( void )
{
   ifr_t *ifr = NULL;
   string_t *filename = NULL;
   string_t *filename1 = NULL;
   string_t *line = NULL;
   s_dlist_t *list = NULL;
   
   filename = string_make_from_cstring( "src/input_files/f_empty.txt" );
   
   ifr = ifr_make( filename );

   ifr_forth( ifr );
   
   list = ifr_tokens( ifr );
   
   CU_ASSERT( s_dlist_count( list ) == 0 );
 
   line = ifr_line( ifr );
   
   CU_ASSERT( string_count( line ) == 0 );
   
   filename1 = ifr_filename( ifr );
   
   CU_ASSERT( string_is_equal( filename, filename1 ) == 1 );
   
   ifr_dispose( ifr );
   string_dispose_with_contents( filename );
   
   return;
}

void test_empty_2( void )
{
   ifr_t *ifr = NULL;
   string_t *filename = NULL;
   string_t *line = NULL;
   s_dlist_t *list = NULL;
   char_t *cp = NULL;
   
   cp = "src/input_files/f_empty.txt";

   ifr = ifr_make_cstring( cp );

   ifr_forth( ifr );
   
   list = ifr_tokens( ifr );
   
   CU_ASSERT( s_dlist_count( list ) == 0 );
 
   line = ifr_line( ifr );
   
   CU_ASSERT( string_count( line ) == 0 );
   
   filename = ifr_filename( ifr );
   
   CU_ASSERT( strcmp( string_as_cstring( filename ), cp ) == 0 );
   
   ifr_dispose( ifr );
   
   return;
}


int
add_test_empty( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_empty", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_empty_1
   add_test_to_suite( p_suite, test_empty_1, "test_empty_1" );

   // test_empty_2
   add_test_to_suite( p_suite, test_empty_2, "test_empty_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

