/**
 @file binary_file_test_info.c
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

#include "Binary_File.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_info_1
*/

void test_info_1( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/rfile.bin" );

   file = binary_file_make( name );

   CU_ASSERT( binary_file_exists( file ) == 1 );

   string_dispose_with_contents( name );
   binary_file_dispose( file );
   
   return;
}

/**
   test_info_2
*/

void test_info_2( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/xfile.bin" );

   file = binary_file_make( name );

   CU_ASSERT( binary_file_exists( file ) == 0 );

   string_dispose_with_contents( name );
   binary_file_dispose( file );
   
   return;
}

/**
   test_info_3
*/

void test_info_3( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/rfile.bin" );

   file = binary_file_make( name );

   CU_ASSERT( binary_file_is_closed( file ) == 1 );

   string_dispose_with_contents( name );
   binary_file_dispose( file );
   
   return;
}

/**
   test_info_4
*/

void test_info_4( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/rfile.bin" );

   file = binary_file_make_open_read( name );

   CU_ASSERT( binary_file_is_closed( file ) == 0 );

   string_dispose_with_contents( name );
   binary_file_dispose( file );
   
   return;
}

/**
   test_info_5
*/

void test_info_5( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/rfile.bin" );

   file = binary_file_make_open_read( name );

   CU_ASSERT( binary_file_is_open_read( file ) == 1 );
   CU_ASSERT( binary_file_is_open_write( file ) == 0 );
   CU_ASSERT( binary_file_is_open_append( file ) == 0 );

   string_dispose_with_contents( name );
   binary_file_dispose( file );
   
   return;
}

/**
   test_info_6
*/

void test_info_6( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/rfile.bin" );

   file = binary_file_make_open_write( name );

   CU_ASSERT( binary_file_is_open_read( file ) == 0 );
   CU_ASSERT( binary_file_is_open_write( file ) == 1 );
   CU_ASSERT( binary_file_is_open_append( file ) == 0 );

   string_dispose_with_contents( name );
   binary_file_dispose( file );
   
   return;
}

/**
   test_info_7
*/

void test_info_7( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/rfile.bin" );

   file = binary_file_make_open_read_write( name );

   CU_ASSERT( binary_file_is_open_read( file ) == 1 );
   CU_ASSERT( binary_file_is_open_write( file ) == 1 );
   CU_ASSERT( binary_file_is_open_append( file ) == 0 );

   string_dispose_with_contents( name );
   binary_file_dispose( file );
   
   return;
}

/**
   test_info_8
*/

void test_info_8( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/rfile.bin" );

   file = binary_file_make_open_append( name );

   CU_ASSERT( binary_file_is_open_read( file ) == 0 );
   CU_ASSERT( binary_file_is_open_write( file ) == 0 );
   CU_ASSERT( binary_file_is_open_append( file ) == 1 );

   string_dispose_with_contents( name );
   binary_file_dispose( file );
   
   return;
}

/**
   test_info_9
*/

void test_info_9( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/rfile.bin" );

   file = binary_file_make_open_read_append( name );

   CU_ASSERT( binary_file_is_open_read( file ) == 1 );
   CU_ASSERT( binary_file_is_open_write( file ) == 0 );
   CU_ASSERT( binary_file_is_open_append( file ) == 1 );

   string_dispose_with_contents( name );
   binary_file_dispose( file );
   
   return;
}


int
add_test_info( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_info", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_info_1
   add_test_to_suite( p_suite, test_info_1, "test_info_1" );

   // test_info_2
   add_test_to_suite( p_suite, test_info_2, "test_info_2" );

   // test_info_3
   add_test_to_suite( p_suite, test_info_3, "test_info_3" );

   // test_info_4
   add_test_to_suite( p_suite, test_info_4, "test_info_4" );

   // test_info_5
   add_test_to_suite( p_suite, test_info_5, "test_info_5" );

   // test_info_6
   add_test_to_suite( p_suite, test_info_6, "test_info_6" );

   // test_info_7
   add_test_to_suite( p_suite, test_info_7, "test_info_7" );

   // test_info_8
   add_test_to_suite( p_suite, test_info_8, "test_info_8" );

   // test_info_9
   add_test_to_suite( p_suite, test_info_9, "test_info_9" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

