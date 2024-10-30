/**
 @file binary_file_test_open.c
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
#include <string.h>
#include <unistd.h>
#include "CUnit/Basic.h"

#include "Binary_File.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_open_1
*/

void test_open_1( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/rfile.bin" );

   file = binary_file_make( name );
   binary_file_open_read( file );

   CU_ASSERT( binary_file_is_closed( file ) == 0 );
   CU_ASSERT( binary_file_is_open_read( file ) == 1 );
   CU_ASSERT( binary_file_is_open_write( file ) == 0 );
   CU_ASSERT( binary_file_is_open_append( file ) == 0 );

   string_deep_dispose( &name );
   binary_file_dispose( &file );
   
   return;
}

/**
   test_open_2
*/

void test_open_2( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/rfile.bin" );

   file = binary_file_make( name );
   binary_file_open_write( file );

   CU_ASSERT( binary_file_is_closed( file ) == 0 );
   CU_ASSERT( binary_file_is_open_read( file ) == 0 );
   CU_ASSERT( binary_file_is_open_write( file ) == 1 );
   CU_ASSERT( binary_file_is_open_append( file ) == 0 );

   string_deep_dispose( &name );
   binary_file_dispose( &file );
   
   return;
}

/**
   test_open_3
*/

void test_open_3( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/rfile.bin" );

   file = binary_file_make( name );
   binary_file_open_append( file );

   CU_ASSERT( binary_file_is_closed( file ) == 0 );
   CU_ASSERT( binary_file_is_open_read( file ) == 0 );
   CU_ASSERT( binary_file_is_open_write( file ) == 0 );
   CU_ASSERT( binary_file_is_open_append( file ) == 1 );

   string_deep_dispose( &name );
   binary_file_dispose( &file );
   
   return;
}

/**
   test_open_4
*/

void test_open_4( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/rfile.bin" );

   file = binary_file_make( name );
   binary_file_open_read_write( file );

   CU_ASSERT( binary_file_is_closed( file ) == 0 );
   CU_ASSERT( binary_file_is_open_read( file ) == 1 );
   CU_ASSERT( binary_file_is_open_write( file ) == 1 );
   CU_ASSERT( binary_file_is_open_append( file ) == 0 );

   string_deep_dispose( &name );
   binary_file_dispose( &file );
   
   return;
}

/**
   test_open_5
*/

void test_open_5( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/rfile.bin" );

   file = binary_file_make( name );
   binary_file_open_read_append( file );

   CU_ASSERT( binary_file_is_closed( file ) == 0 );
   CU_ASSERT( binary_file_is_open_read( file ) == 1 );
   CU_ASSERT( binary_file_is_open_write( file ) == 0 );
   CU_ASSERT( binary_file_is_open_append( file ) == 1 );

   string_deep_dispose( &name );
   binary_file_dispose( &file );
   
   return;
}

/**
   test_open_6
*/

void test_open_6( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "src/test/rfile.bin" );

   file = binary_file_make( name );
   binary_file_open_read( file );
   binary_file_close( file );
   
   CU_ASSERT( binary_file_is_closed( file ) == 1 );
   CU_ASSERT( binary_file_is_open_read( file ) == 0 );
   CU_ASSERT( binary_file_is_open_write( file ) == 0 );
   CU_ASSERT( binary_file_is_open_append( file ) == 0 );

   string_deep_dispose( &name );
   binary_file_dispose( &file );
   
   return;
}

/**
   test_open_7
*/

void test_open_7( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;
   FILE *fp;
   char s[1035];
   char s1[1035];
   
   name = string_make();
   
   string_append_cstring( name, "src/test/rfile.bin" );

   // get result of command
   fp = popen( "/bin/ls --full-time src/test/rfile.bin", "r" );
   if (fp == NULL ) 
   {
     printf("Failed to run command\n" );
   } 

   // read the command output
   fgets( s, sizeof(s)-1, fp );

   // close command output
   pclose(fp);
   
   sleep( 1 );
   
   // touch file
   file = binary_file_make( name );
   binary_file_touch( file );

   // get result of command
   fp = popen( "/bin/ls --full-time src/test/rfile.bin", "r" );
   if (fp == NULL ) 
   {
     printf("Failed to run command\n" );
   } 

   // read the command output
   fgets( s1, sizeof(s1)-1, fp );

   // close command output
   pclose(fp);

   // see that output is different   
   CU_ASSERT( strcmp( s, s1 ) != 0 );

   string_deep_dispose( &name );
   binary_file_dispose( &file );
   
   return;
}

/**
   test_open_8
*/

void test_open_8( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;
   string_t *name1 = NULL;

   // delete files
   system( "/bin/rm src/test/afile.bin" );
   system( "/bin/rm src/test/bfile.bin" );
   
   name = string_make();
   string_append_cstring( name, "src/test/afile.bin" );

   // make afile.bin
   file = binary_file_make_open_write( name );
   binary_file_close( file );
   
   name1 = string_make();
   string_append_cstring( name1, "src/test/bfile.bin" );
   binary_file_rename( file, name1 );

   CU_ASSERT( binary_file_exists( file ) == 1 );

   string_deep_dispose( &name );
   string_deep_dispose( &name1 );
   binary_file_dispose( &file );
   
   return;
}

/**
   test_open_9
*/

void test_open_9( void )
{
   binary_file_t *file = NULL;

   // delete files
   system( "/bin/rm src/test/afile.bin" );
   system( "/bin/rm src/test/bfile.bin" );
   
   // make afile.bin
   file = binary_file_make_open_write_cstring( "src/test/afile.bin" );
   binary_file_close( file );
   
   binary_file_rename_cstring( file, "src/test/bfile.bin" );

   CU_ASSERT( binary_file_exists( file ) == 1 );

   binary_file_dispose( &file );
   
   return;
}

/**
   test_open_10
*/

void test_open_10( void )
{
   binary_file_t *file = NULL;

   // delete files
   system( "/bin/rm src/test/afile.bin" );
   system( "/bin/rm src/test/bfile.bin" );
   
   // make afile.bin
   file = binary_file_make_open_write_cstring( "src/test/afile.bin" );
   binary_file_close( file );
   
   binary_file_delete( file );

   CU_ASSERT( binary_file_exists( file ) == 0 );

   binary_file_dispose( &file );
   
   return;
}

/**
   test_open_11
*/

void test_open_11( void )
{
   binary_file_t *file = NULL;

   // create file
   system( "echo Hello > src/test/afile.bin" );
   
   // open afile.bin
   file = binary_file_make_cstring( "src/test/afile.bin" );

   binary_file_wipe_out( file );

   binary_file_open_read( file );
   
   CU_ASSERT( binary_file_count( file ) == 0 );

   binary_file_dispose( &file );
   
   return;
}


int
add_test_open( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_open", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_open_1
   add_test_to_suite( p_suite, test_open_1, "test_open_1" );

   // test_open_2
   add_test_to_suite( p_suite, test_open_2, "test_open_2" );

   // test_open_3
   add_test_to_suite( p_suite, test_open_3, "test_open_3" );

   // test_open_4
   add_test_to_suite( p_suite, test_open_4, "test_open_4" );

   // test_open_5
   add_test_to_suite( p_suite, test_open_5, "test_open_5" );

   // test_open_6
   add_test_to_suite( p_suite, test_open_6, "test_open_6" );

   // test_open_7
   add_test_to_suite( p_suite, test_open_7, "test_open_7" );

   // test_open_8
   add_test_to_suite( p_suite, test_open_8, "test_open_8" );

   // test_open_9
   add_test_to_suite( p_suite, test_open_9, "test_open_9" );

   // test_open_10
   add_test_to_suite( p_suite, test_open_10, "test_open_10" );

   // test_open_11
   add_test_to_suite( p_suite, test_open_11, "test_open_11" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

