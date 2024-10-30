/**
 @file binary_file_test_make.c
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
   test_make_1
*/

void test_make_1( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "file.bin" );

   file = binary_file_make( name );

   CU_ASSERT( file != NULL );

   string_deep_dispose( &name );
   binary_file_dispose( &file );

   return;
}

/**
   test_make_2
*/

void test_make_2( void )
{
   binary_file_t *file= NULL;

   file = binary_file_make_cstring( "file.bin" );

   CU_ASSERT( file != NULL );

   binary_file_dispose( &file );

   return;
}

/**
   test_make_3
*/

void test_make_3( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/rfile.bin" );

   file = binary_file_make_open_read( name );

   CU_ASSERT( file != NULL );
   
   string_deep_dispose( &name );
   binary_file_dispose( &file );
   
   return;
}

/**
   test_make_4
*/

void test_make_4( void )
{
   binary_file_t *file= NULL;

   file = binary_file_make_open_read_cstring( "src/test/rfile.bin" );

   CU_ASSERT( file != NULL );

   binary_file_dispose( &file );
   
   return;
}

/**
   test_make_5
*/

void test_make_5( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/file.bin" );

   file = binary_file_make_open_write( name );

   CU_ASSERT( file != NULL );

   string_deep_dispose( &name );
   binary_file_dispose( &file );
   
   return;
}

/**
   test_make_6
*/

void test_make_6( void )
{
   binary_file_t *file= NULL;

   file = binary_file_make_open_write_cstring( "src/test/file.bin" );

   CU_ASSERT( file != NULL );

   binary_file_dispose( &file );
   
   return;
}

/**
   test_make_7
*/

void test_make_7( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/rfile.bin" );

   file = binary_file_make_open_read_write( name );

   CU_ASSERT( file != NULL );

   string_deep_dispose( &name );
   binary_file_dispose( &file );
   
   return;
}

/**
   test_make_8
*/

void test_make_8( void )
{
   binary_file_t *file= NULL;

   file = binary_file_make_open_read_write_cstring( "src/test/rfile.bin" );

   CU_ASSERT( file != NULL );

   binary_file_dispose( &file );
   
   return;
}

/**
   test_make_9
*/

void test_make_9( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/file.bin" );

   file = binary_file_make_create_read_write( name );

   CU_ASSERT( file != NULL );

   string_deep_dispose( &name );
   binary_file_dispose( &file );
   
   return;
}

/**
   test_make_10
*/

void test_make_10( void )
{
   binary_file_t *file= NULL;

   file = binary_file_make_create_read_write_cstring( "src/test/file.bin" );

   CU_ASSERT( file != NULL );

   binary_file_dispose( &file );
   
   return;
}

/**
   test_make_11
*/

void test_make_11( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/file.bin" );

   file = binary_file_make_open_append( name );

   CU_ASSERT( file != NULL );

   string_deep_dispose( &name );
   binary_file_dispose( &file );
   
   return;
}

/**
   test_make_12
*/

void test_make_12( void )
{
   binary_file_t *file= NULL;

   file = binary_file_make_open_append_cstring( "src/test/file.bin" );

   CU_ASSERT( file != NULL );

   binary_file_dispose( &file );
   
   return;
}

/**
   test_make_13
*/

void test_make_13( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/rfile.bin" );

   file = binary_file_make_open_read_append( name );

   CU_ASSERT( file != NULL );

   string_deep_dispose( &name );
   binary_file_dispose( &file );
   
   return;
}

/**
   test_make_14
*/

void test_make_14( void )
{
   binary_file_t *file= NULL;

   file = binary_file_make_open_read_append_cstring( "src/test/rfile.bin" );

   CU_ASSERT( file != NULL );

   binary_file_dispose( &file );
   
   return;
}

/**
   test_make_15
*/

void test_make_15( void )
{
   binary_file_t *file= NULL;

   file = binary_file_make_cstring( "file.bin" );

   CU_ASSERT( file != NULL );

   binary_file_create_read_write( file );

   binary_file_dispose( &file );

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

   // test_make_2
   add_test_to_suite( p_suite, test_make_2, "test_make_2" );

   // test_make_3
   add_test_to_suite( p_suite, test_make_3, "test_make_3" );

   // test_make_4
   add_test_to_suite( p_suite, test_make_4, "test_make_4" );

   // test_make_5
   add_test_to_suite( p_suite, test_make_5, "test_make_5" );

   // test_make_6
   add_test_to_suite( p_suite, test_make_6, "test_make_6" );

   // test_make_7
   add_test_to_suite( p_suite, test_make_7, "test_make_7" );

   // test_make_8
   add_test_to_suite( p_suite, test_make_8, "test_make_8" );

   // test_make_9
   add_test_to_suite( p_suite, test_make_9, "test_make_9" );

   // test_make_10
   add_test_to_suite( p_suite, test_make_10, "test_make_10" );

   // test_make_11
   add_test_to_suite( p_suite, test_make_11, "test_make_11" );

   // test_make_12
   add_test_to_suite( p_suite, test_make_12, "test_make_12" );

   // test_make_13
   add_test_to_suite( p_suite, test_make_13, "test_make_13" );

   // test_make_14
   add_test_to_suite( p_suite, test_make_14, "test_make_14" );

   // test_make_15
   add_test_to_suite( p_suite, test_make_15, "test_make_15" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

