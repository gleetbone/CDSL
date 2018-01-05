/**
 @file binary_file_test_movement.c
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
   test_movement_1
*/

void test_movement_1( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/file.dat" );

   file = binary_file_make_open_read( name );

   CU_ASSERT( binary_file_count( file ) == 6 );

   string_dispose_with_contents( name );
   binary_file_dispose( file );
   
   return;
}

/**
   test_movement_2
*/

void test_movement_2( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/file.dat" );

   file = binary_file_make_open_read( name );

   CU_ASSERT( binary_file_position( file ) == 0 );

   CU_ASSERT( binary_file_after( file ) == 0 );
   CU_ASSERT( binary_file_before( file ) == 1 );
   CU_ASSERT( binary_file_off( file ) == 1 );
   CU_ASSERT( binary_file_end_of_file( file ) == 0 );

   string_dispose_with_contents( name );
   binary_file_dispose( file );
   
   return;
}

/**
   test_movement_3
*/

void test_movement_3( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/file.dat" );

   file = binary_file_make_open_read( name );

   binary_file_forth( file );
   
   CU_ASSERT( binary_file_position( file ) == 1 );

   CU_ASSERT( binary_file_after( file ) == 0 );
   CU_ASSERT( binary_file_before( file ) == 0 );
   CU_ASSERT( binary_file_off( file ) == 0 );
   CU_ASSERT( binary_file_end_of_file( file ) == 0 );

   string_dispose_with_contents( name );
   binary_file_dispose( file );
   
   return;
}

/**
   test_movement_4
*/

void test_movement_4( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/file.dat" );

   file = binary_file_make_open_read( name );

   binary_file_go( file, 3 );
   
   CU_ASSERT( binary_file_position( file ) == 3 );

   CU_ASSERT( binary_file_after( file ) == 0 );
   CU_ASSERT( binary_file_before( file ) == 0 );
   CU_ASSERT( binary_file_off( file ) == 0 );
   CU_ASSERT( binary_file_end_of_file( file ) == 0 );

   string_dispose_with_contents( name );
   binary_file_dispose( file );
   
   return;
}

/**
   test_movement_5
*/

void test_movement_5( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/file.dat" );

   file = binary_file_make_open_read( name );

   binary_file_forth( file );
   binary_file_move( file, 3 );
   
   CU_ASSERT( binary_file_position( file ) == 4 );

   CU_ASSERT( binary_file_after( file ) == 0 );
   CU_ASSERT( binary_file_before( file ) == 0 );
   CU_ASSERT( binary_file_off( file ) == 0 );
   CU_ASSERT( binary_file_end_of_file( file ) == 0 );

   string_dispose_with_contents( name );
   binary_file_dispose( file );
   
   return;
}

/**
   test_movement_6
*/

void test_movement_6( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/file.dat" );

   file = binary_file_make_open_read( name );

   binary_file_recede( file, 2 );
   
   CU_ASSERT( binary_file_position( file ) == 4 );

   CU_ASSERT( binary_file_after( file ) == 0 );
   CU_ASSERT( binary_file_before( file ) == 0 );
   CU_ASSERT( binary_file_off( file ) == 0 );
   CU_ASSERT( binary_file_end_of_file( file ) == 0 );

   string_dispose_with_contents( name );
   binary_file_dispose( file );
   
   return;
}

/**
   test_movement_7
*/

void test_movement_7( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/file.dat" );

   file = binary_file_make_open_read( name );

   binary_file_go( file, 5 );
   binary_file_forth( file );
   
   CU_ASSERT( binary_file_position( file ) == 6 );

   CU_ASSERT( binary_file_after( file ) == 1 );
   CU_ASSERT( binary_file_before( file ) == 0 );
   CU_ASSERT( binary_file_off( file ) == 1 );
   CU_ASSERT( binary_file_end_of_file( file ) == 1 );

   string_dispose_with_contents( name );
   binary_file_dispose( file );
   
   return;
}

/**
   test_movement_8
*/

void test_movement_8( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/rfile.bin" );

   file = binary_file_make_open_read( name );
   
   CU_ASSERT( binary_file_position( file ) == 0 );

   CU_ASSERT( binary_file_after( file ) == 1 );
   CU_ASSERT( binary_file_before( file ) == 1 );
   CU_ASSERT( binary_file_off( file ) == 1 );
   CU_ASSERT( binary_file_end_of_file( file ) == 1 );

   string_dispose_with_contents( name );
   binary_file_dispose( file );
   
   return;
}

/**
   test_movement_9
*/

void test_movement_9( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/file.dat" );

   file = binary_file_make_open_read( name );

   binary_file_go( file, 4 );
   binary_file_back( file );
   
   CU_ASSERT( binary_file_position( file ) == 3 );

   CU_ASSERT( binary_file_after( file ) == 0 );
   CU_ASSERT( binary_file_before( file ) == 0 );
   CU_ASSERT( binary_file_off( file ) == 0 );
   CU_ASSERT( binary_file_end_of_file( file ) == 0 );

   string_dispose_with_contents( name );
   binary_file_dispose( file );
   
   return;
}

/**
   test_movement_10
*/

void test_movement_10( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();

   string_append_cstring( name, "src/test/file.dat" );

   file = binary_file_make_open_read( name );

   binary_file_go( file, 4 );
   binary_file_start( file );

   CU_ASSERT( binary_file_position( file ) == 0 );

   CU_ASSERT( binary_file_after( file ) == 0 );
   CU_ASSERT( binary_file_before( file ) == 1 );
   CU_ASSERT( binary_file_off( file ) == 1 );
   CU_ASSERT( binary_file_end_of_file( file ) == 0 );

   string_dispose_with_contents( name );
   binary_file_dispose( file );

   return;
}

/**
   test_movement_11
*/

void test_movement_11( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();

   string_append_cstring( name, "src/test/file.dat" );

   file = binary_file_make_open_read( name );

   binary_file_go( file, 4 );
   binary_file_finish( file );

   CU_ASSERT( binary_file_position( file ) == 6 );

   CU_ASSERT( binary_file_after( file ) == 1 );
   CU_ASSERT( binary_file_before( file ) == 0 );
   CU_ASSERT( binary_file_off( file ) == 1 );
   CU_ASSERT( binary_file_end_of_file( file ) == 1 );

   string_dispose_with_contents( name );
   binary_file_dispose( file );

   return;
}


int
add_test_movement( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_movement", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_movement_1
   add_test_to_suite( p_suite, test_movement_1, "test_movement_1" );

   // test_movement_2
   add_test_to_suite( p_suite, test_movement_2, "test_movement_2" );

   // test_movement_3
   add_test_to_suite( p_suite, test_movement_3, "test_movement_3" );

   // test_movement_4
   add_test_to_suite( p_suite, test_movement_4, "test_movement_4" );

   // test_movement_5
   add_test_to_suite( p_suite, test_movement_5, "test_movement_5" );

   // test_movement_6
   add_test_to_suite( p_suite, test_movement_6, "test_movement_6" );

   // test_movement_7
   add_test_to_suite( p_suite, test_movement_7, "test_movement_7" );

   // test_movement_8
   add_test_to_suite( p_suite, test_movement_8, "test_movement_8" );

   // test_movement_9
   add_test_to_suite( p_suite, test_movement_9, "test_movement_9" );

   // test_movement_10
   add_test_to_suite( p_suite, test_movement_10, "test_movement_10" );

   // test_movement_11
   add_test_to_suite( p_suite, test_movement_11, "test_movement_11" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

