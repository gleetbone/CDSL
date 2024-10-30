/**
 @file ifr_test_make.c
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
#include "String_utilities.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_make_1
*/

void test_make_1( void )
{
   ifr_t *ifr = NULL;
   string_t *file_name = NULL;
   
   file_name = string_make_from_cstring( "src/input_files/XXX.txt" );

   if ( file_exists( file_name ) == 1 )
   {
      ifr = ifr_make( file_name );
   }

   CU_ASSERT( ifr == NULL );

   string_deep_dispose( &file_name );

   file_name = string_make_from_cstring( "src/input_files/f_empty.txt" );
   
   ifr = ifr_make( file_name );

   CU_ASSERT( ifr != NULL );

   ifr_dispose( &ifr );
   string_deep_dispose( &file_name );
   
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

