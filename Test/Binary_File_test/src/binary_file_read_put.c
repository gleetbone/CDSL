/**
 @file binary_file_test_read_put.c
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
   test_read_put_1
*/

void test_read_put_1( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;
   int8_t arg = 0;
   int8_t arg1 = 0;
   int8_t argx = 0;

   name = string_make();

   string_append_cstring( name, "src/test/cfile.bin" );

   file = binary_file_make( name );
   binary_file_delete( file );
   binary_file_dispose( file );

   file = binary_file_make_open_append( name );

   arg = 13;

   binary_file_put_int8( file, arg );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_int8( file );

   CU_ASSERT( argx == arg );
   CU_ASSERT( binary_file_count( file ) == sizeof( arg ) );

   binary_file_close( file );

   binary_file_open_append( file );

   arg1 = 29;

   binary_file_put_int8( file, arg1 );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_int8( file );

   CU_ASSERT( argx == arg );

   argx = binary_file_read_int8( file );

   CU_ASSERT( argx == arg1 );

   CU_ASSERT( binary_file_count( file ) == 2*sizeof( arg ) );

   binary_file_close( file );

   binary_file_open_read_write( file );

   arg = 11;

   binary_file_put_int8( file, arg );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_int8( file );

   CU_ASSERT( argx == arg );

   argx = binary_file_read_int8( file );

   CU_ASSERT( argx == arg1 );

   CU_ASSERT( binary_file_count( file ) == 2*sizeof( arg ) );

   string_dispose_with_contents( name );
   binary_file_dispose( file );

   return;
}

/**
   test_read_put_2
*/

void test_read_put_2( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;
   int16_t arg = 0;
   int16_t arg1 = 0;
   int16_t argx = 0;

   name = string_make();

   string_append_cstring( name, "src/test/cfile.bin" );

   file = binary_file_make( name );
   binary_file_delete( file );
   binary_file_dispose( file );

   file = binary_file_make_open_append( name );

   arg = 13;

   binary_file_put_int16( file, arg );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_int16( file );

   CU_ASSERT( argx == arg );
   CU_ASSERT( binary_file_count( file ) == sizeof( arg ) );

   binary_file_close( file );

   binary_file_open_append( file );

   arg1 = 29;

   binary_file_put_int16( file, arg1 );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_int16( file );

   CU_ASSERT( argx == arg );

   argx = binary_file_read_int16( file );

   CU_ASSERT( argx == arg1 );

   CU_ASSERT( binary_file_count( file ) == 2*sizeof( arg ) );

   binary_file_close( file );

   binary_file_open_read_write( file );

   arg = 11;

   binary_file_put_int16( file, arg );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_int16( file );

   CU_ASSERT( argx == arg );

   argx = binary_file_read_int16( file );

   CU_ASSERT( argx == arg1 );

   CU_ASSERT( binary_file_count( file ) == 2*sizeof( arg ) );

   string_dispose_with_contents( name );
   binary_file_dispose( file );

   return;
}

/**
   test_read_put_3
*/

void test_read_put_3( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;
   int32_t arg = 0;
   int32_t arg1 = 0;
   int32_t argx = 0;

   name = string_make();

   string_append_cstring( name, "src/test/cfile.bin" );

   file = binary_file_make( name );
   binary_file_delete( file );
   binary_file_dispose( file );

   file = binary_file_make_open_append( name );

   arg = 13;

   binary_file_put_int32( file, arg );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_int32( file );

   CU_ASSERT( argx == arg );
   CU_ASSERT( binary_file_count( file ) == sizeof( arg ) );

   binary_file_close( file );

   binary_file_open_append( file );

   arg1 = 29;

   binary_file_put_int32( file, arg1 );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_int32( file );

   CU_ASSERT( argx == arg );

   argx = binary_file_read_int32( file );

   CU_ASSERT( argx == arg1 );

   CU_ASSERT( binary_file_count( file ) == 2*sizeof( arg ) );

   binary_file_close( file );

   binary_file_open_read_write( file );

   arg = 11;

   binary_file_put_int32( file, arg );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_int32( file );

   CU_ASSERT( argx == arg );

   argx = binary_file_read_int32( file );

   CU_ASSERT( argx == arg1 );

   CU_ASSERT( binary_file_count( file ) == 2*sizeof( arg ) );

   string_dispose_with_contents( name );
   binary_file_dispose( file );

   return;
}

/**
   test_read_put_4
*/

void test_read_put_4( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;
   int64_t arg = 0;
   int64_t arg1 = 0;
   int64_t argx = 0;

   name = string_make();

   string_append_cstring( name, "src/test/cfile.bin" );

   file = binary_file_make( name );
   binary_file_delete( file );
   binary_file_dispose( file );

   file = binary_file_make_open_append( name );

   arg = 13;

   binary_file_put_int64( file, arg );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_int64( file );

   CU_ASSERT( argx == arg );
   CU_ASSERT( binary_file_count( file ) == sizeof( arg ) );

   binary_file_close( file );

   binary_file_open_append( file );

   arg1 = 29;

   binary_file_put_int64( file, arg1 );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_int64( file );

   CU_ASSERT( argx == arg );

   argx = binary_file_read_int64( file );

   CU_ASSERT( argx == arg1 );

   CU_ASSERT( binary_file_count( file ) == 2*sizeof( arg ) );

   binary_file_close( file );

   binary_file_open_read_write( file );

   arg = 11;

   binary_file_put_int64( file, arg );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_int64( file );

   CU_ASSERT( argx == arg );

   argx = binary_file_read_int64( file );

   CU_ASSERT( argx == arg1 );

   CU_ASSERT( binary_file_count( file ) == 2*sizeof( arg ) );

   string_dispose_with_contents( name );
   binary_file_dispose( file );

   return;
}

/**
   test_read_put_5
*/

void test_read_put_5( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;
   uint8_t arg = 0;
   uint8_t arg1 = 0;
   uint8_t argx = 0;

   name = string_make();

   string_append_cstring( name, "src/test/cfile.bin" );

   file = binary_file_make( name );
   binary_file_delete( file );
   binary_file_dispose( file );

   file = binary_file_make_open_append( name );

   arg = 13;

   binary_file_put_uint8( file, arg );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_uint8( file );

   CU_ASSERT( argx == arg );
   CU_ASSERT( binary_file_count( file ) == sizeof( arg ) );

   binary_file_close( file );

   binary_file_open_append( file );

   arg1 = 29;

   binary_file_put_uint8( file, arg1 );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_uint8( file );

   CU_ASSERT( argx == arg );

   argx = binary_file_read_uint8( file );

   CU_ASSERT( argx == arg1 );

   CU_ASSERT( binary_file_count( file ) == 2*sizeof( arg ) );

   binary_file_close( file );

   binary_file_open_read_write( file );

   arg = 11;

   binary_file_put_uint8( file, arg );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_uint8( file );

   CU_ASSERT( argx == arg );

   argx = binary_file_read_uint8( file );

   CU_ASSERT( argx == arg1 );

   CU_ASSERT( binary_file_count( file ) == 2*sizeof( arg ) );

   string_dispose_with_contents( name );
   binary_file_dispose( file );

   return;
}

/**
   test_read_put_6
*/

void test_read_put_6( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;
   uint16_t arg = 0;
   uint16_t arg1 = 0;
   uint16_t argx = 0;

   name = string_make();

   string_append_cstring( name, "src/test/cfile.bin" );

   file = binary_file_make( name );
   binary_file_delete( file );
   binary_file_dispose( file );

   file = binary_file_make_open_append( name );

   arg = 13;

   binary_file_put_uint16( file, arg );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_uint16( file );

   CU_ASSERT( argx == arg );
   CU_ASSERT( binary_file_count( file ) == sizeof( arg ) );

   binary_file_close( file );

   binary_file_open_append( file );

   arg1 = 29;

   binary_file_put_uint16( file, arg1 );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_uint16( file );

   CU_ASSERT( argx == arg );

   argx = binary_file_read_uint16( file );

   CU_ASSERT( argx == arg1 );

   CU_ASSERT( binary_file_count( file ) == 2*sizeof( arg ) );

   binary_file_close( file );

   binary_file_open_read_write( file );

   arg = 11;

   binary_file_put_uint16( file, arg );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_uint16( file );

   CU_ASSERT( argx == arg );

   argx = binary_file_read_uint16( file );

   CU_ASSERT( argx == arg1 );

   CU_ASSERT( binary_file_count( file ) == 2*sizeof( arg ) );

   string_dispose_with_contents( name );
   binary_file_dispose( file );

   return;
}

/**
   test_read_put_7
*/

void test_read_put_7( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;
   uint32_t arg = 0;
   uint32_t arg1 = 0;
   uint32_t argx = 0;

   name = string_make();

   string_append_cstring( name, "src/test/cfile.bin" );

   file = binary_file_make( name );
   binary_file_delete( file );
   binary_file_dispose( file );

   file = binary_file_make_open_append( name );

   arg = 13;

   binary_file_put_uint32( file, arg );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_uint32( file );

   CU_ASSERT( argx == arg );
   CU_ASSERT( binary_file_count( file ) == sizeof( arg ) );

   binary_file_close( file );

   binary_file_open_append( file );

   arg1 = 29;

   binary_file_put_uint32( file, arg1 );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_uint32( file );

   CU_ASSERT( argx == arg );

   argx = binary_file_read_uint32( file );

   CU_ASSERT( argx == arg1 );

   CU_ASSERT( binary_file_count( file ) == 2*sizeof( arg ) );

   binary_file_close( file );

   binary_file_open_read_write( file );

   arg = 11;

   binary_file_put_uint32( file, arg );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_uint32( file );

   CU_ASSERT( argx == arg );

   argx = binary_file_read_uint32( file );

   CU_ASSERT( argx == arg1 );

   CU_ASSERT( binary_file_count( file ) == 2*sizeof( arg ) );

   string_dispose_with_contents( name );
   binary_file_dispose( file );

   return;
}

/**
   test_read_put_8
*/

void test_read_put_8( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;
   uint64_t arg = 0;
   uint64_t arg1 = 0;
   uint64_t argx = 0;

   name = string_make();

   string_append_cstring( name, "src/test/cfile.bin" );

   file = binary_file_make( name );
   binary_file_delete( file );
   binary_file_dispose( file );

   file = binary_file_make_open_append( name );

   arg = 13;

   binary_file_put_uint64( file, arg );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_uint64( file );

   CU_ASSERT( argx == arg );
   CU_ASSERT( binary_file_count( file ) == sizeof( arg ) );

   binary_file_close( file );

   binary_file_open_append( file );

   arg1 = 29;

   binary_file_put_uint64( file, arg1 );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_uint64( file );

   CU_ASSERT( argx == arg );

   argx = binary_file_read_uint64( file );

   CU_ASSERT( argx == arg1 );

   CU_ASSERT( binary_file_count( file ) == 2*sizeof( arg ) );

   binary_file_close( file );

   binary_file_open_read_write( file );

   arg = 11;

   binary_file_put_uint64( file, arg );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_uint64( file );

   CU_ASSERT( argx == arg );

   argx = binary_file_read_uint64( file );

   CU_ASSERT( argx == arg1 );

   CU_ASSERT( binary_file_count( file ) == 2*sizeof( arg ) );

   string_dispose_with_contents( name );
   binary_file_dispose( file );

   return;
}

/**
   test_read_put_9
*/

void test_read_put_9( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;
   float32_t arg = 0;
   float32_t arg1 = 0;
   float32_t argx = 0;

   name = string_make();

   string_append_cstring( name, "src/test/cfile.bin" );

   file = binary_file_make( name );
   binary_file_delete( file );
   binary_file_dispose( file );

   file = binary_file_make_open_append( name );

   arg = 13;

   binary_file_put_float32( file, arg );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_float32( file );

   CU_ASSERT( argx == arg );
   CU_ASSERT( binary_file_count( file ) == sizeof( arg ) );

   binary_file_close( file );

   binary_file_open_append( file );

   arg1 = 29;

   binary_file_put_float32( file, arg1 );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_float32( file );

   CU_ASSERT( argx == arg );

   argx = binary_file_read_float32( file );

   CU_ASSERT( argx == arg1 );

   CU_ASSERT( binary_file_count( file ) == 2*sizeof( arg ) );

   binary_file_close( file );

   binary_file_open_read_write( file );

   arg = 11;

   binary_file_put_float32( file, arg );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_float32( file );

   CU_ASSERT( argx == arg );

   argx = binary_file_read_float32( file );

   CU_ASSERT( argx == arg1 );

   CU_ASSERT( binary_file_count( file ) == 2*sizeof( arg ) );

   string_dispose_with_contents( name );
   binary_file_dispose( file );

   return;
}

/**
   test_read_put_10
*/

void test_read_put_10( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;
   float64_t arg = 0;
   float64_t arg1 = 0;
   float64_t argx = 0;

   name = string_make();

   string_append_cstring( name, "src/test/cfile.bin" );

   file = binary_file_make( name );
   binary_file_delete( file );
   binary_file_dispose( file );

   file = binary_file_make_open_append( name );

   arg = 13;

   binary_file_put_float64( file, arg );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_float64( file );

   CU_ASSERT( argx == arg );
   CU_ASSERT( binary_file_count( file ) == sizeof( arg ) );

   binary_file_close( file );

   binary_file_open_append( file );

   arg1 = 29;

   binary_file_put_float64( file, arg1 );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_float64( file );

   CU_ASSERT( argx == arg );

   argx = binary_file_read_float64( file );

   CU_ASSERT( argx == arg1 );

   CU_ASSERT( binary_file_count( file ) == 2*sizeof( arg ) );

   binary_file_close( file );

   binary_file_open_read_write( file );

   arg = 11;

   binary_file_put_float64( file, arg );

   string_dispose_with_contents( name );
   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_float64( file );

   CU_ASSERT( argx == arg );

   argx = binary_file_read_float64( file );

   CU_ASSERT( argx == arg1 );

   CU_ASSERT( binary_file_count( file ) == 2*sizeof( arg ) );

   binary_file_dispose( file );

   return;
}

/**
   test_read_put_11
*/

void test_read_put_11( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;
   string_t *arg = NULL;
   string_t *arg1 = NULL;
   string_t *argx = NULL;

   name = string_make();

   string_append_cstring( name, "src/test/cfile.bin" );

   file = binary_file_make( name );
   binary_file_delete( file );
   binary_file_dispose( file );

   file = binary_file_make_open_append( name );

   arg = string_make_from_cstring( "abcde" );

   binary_file_put_string( file, arg );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_string( file, string_count( arg ) );

   CU_ASSERT( string_is_equal( argx, arg ) == 1 );
   CU_ASSERT( binary_file_count( file ) == string_count( arg ) + 1 );

   binary_file_close( file );

   binary_file_open_append( file );

   arg1 = string_make_from_cstring( "xyz" );;

   binary_file_put_string( file, arg1 );

   string_dispose_with_contents( argx );
   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_string( file, string_count( arg ) );

   CU_ASSERT( string_is_equal( argx, arg ) == 1 );

   string_dispose_with_contents( argx );

   argx = binary_file_read_string( file, string_count( arg1 ) );

   CU_ASSERT( string_is_equal( argx, arg1 ) == 1 );

   CU_ASSERT( binary_file_count( file ) == string_count( arg ) + 1 + string_count( arg1 ) + 1);

   binary_file_close( file );

   binary_file_open_read_write( file );

   string_wipe_out( arg );
   string_append_cstring( arg, "fghij" );

   binary_file_put_string( file, arg );

   string_dispose_with_contents( argx );
   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_string( file, string_count( arg ) );

   CU_ASSERT( string_is_equal( argx, arg ) == 1 );

   string_dispose_with_contents( argx );

   argx = binary_file_read_string( file, string_count( arg1 ) );

   CU_ASSERT( string_is_equal( argx, arg1 ) == 1 );

   CU_ASSERT( binary_file_count( file ) == string_count( arg ) + 1 + string_count( arg1 ) + 1 );

   string_dispose_with_contents( arg );
   string_dispose_with_contents( arg1 );
   string_dispose_with_contents( argx );

   string_dispose_with_contents( name );
   binary_file_dispose( file );

   return;
}

/**
   test_read_put_12
*/

void test_read_put_12( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;
   char_t *arg = NULL;
   char_t *arg1 = NULL;
   char_t *argx = NULL;

   name = string_make();

   string_append_cstring( name, "src/test/cfile.bin" );

   file = binary_file_make( name );
   binary_file_delete( file );
   binary_file_dispose( file );

   file = binary_file_make_open_append( name );

   arg = "abcde";

   binary_file_put_cstring( file, arg );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_cstring( file, strlen( arg ) );

   CU_ASSERT( strcmp( argx, arg ) == 0 );
   CU_ASSERT( binary_file_count( file ) == strlen( arg ) + 1 );

   free( argx );
   binary_file_close( file );

   binary_file_open_append( file );

   arg1 = "xyz" ;

   binary_file_put_cstring( file, arg1 );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_cstring( file, strlen( arg ) );

   CU_ASSERT( strcmp( argx, arg ) == 0 );
   free( argx );

   argx = binary_file_read_cstring( file, strlen( arg1 ) );

   CU_ASSERT( strcmp( argx, arg1 ) == 0 );

   CU_ASSERT( binary_file_count( file ) == strlen( arg ) + 1 + strlen( arg1 ) + 1);

   free( argx );
   binary_file_close( file );

   binary_file_open_read_write( file );

   arg = "fghij";

   binary_file_put_cstring( file, arg );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_cstring( file, strlen( arg ) );

   CU_ASSERT( strcmp( argx, arg ) == 0 );

   free( argx );

   argx = binary_file_read_cstring( file, strlen( arg1 ) );

   CU_ASSERT( strcmp( argx, arg1 ) == 0 );

   CU_ASSERT( binary_file_count( file ) == strlen( arg ) + 1 + strlen( arg1 ) + 1 );

   free( argx );
   string_dispose_with_contents( name );
   binary_file_dispose( file );

   return;
}

/**
   test_read_put_13
*/

void test_read_put_13( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;
   raw_buffer_t *arg = NULL;
   raw_buffer_t *arg1 = NULL;
   raw_buffer_t *argx = NULL;

   name = string_make();

   string_append_cstring( name, "src/test/cfile.bin" );

   file = binary_file_make( name );
   binary_file_delete( file );
   binary_file_dispose( file );

   file = binary_file_make_open_append( name );

   arg = raw_buffer_make( 4 );
   raw_buffer_put_uint8( arg, 13, 0 );
   raw_buffer_put_uint8( arg, 14, 1 );
   raw_buffer_put_uint8( arg, 15, 2 );
   raw_buffer_put_uint8( arg, 16, 3 );

   binary_file_put_raw_buffer( file, arg );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_raw_buffer( file, raw_buffer_count( arg ) );

   CU_ASSERT( raw_buffer_read_uint8( argx, 0 ) == raw_buffer_read_uint8( arg, 0 ) );
   CU_ASSERT( raw_buffer_read_uint8( argx, 1 ) == raw_buffer_read_uint8( arg, 1 ) );
   CU_ASSERT( raw_buffer_read_uint8( argx, 2 ) == raw_buffer_read_uint8( arg, 2 ) );
   CU_ASSERT( raw_buffer_read_uint8( argx, 3 ) == raw_buffer_read_uint8( arg, 3 ) );
   CU_ASSERT( binary_file_count( file ) == raw_buffer_count( arg ) );

   binary_file_close( file );

   binary_file_open_append( file );

   arg1 = raw_buffer_make( 3 );
   raw_buffer_put_uint8( arg1, 23, 0 );
   raw_buffer_put_uint8( arg1, 24, 1 );
   raw_buffer_put_uint8( arg1, 25, 2 );

   binary_file_put_raw_buffer( file, arg1 );

   raw_buffer_dispose_with_contents( argx );
   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_raw_buffer( file, raw_buffer_count( arg ) );

   CU_ASSERT( raw_buffer_read_uint8( argx, 0 ) == raw_buffer_read_uint8( arg, 0 ) );
   CU_ASSERT( raw_buffer_read_uint8( argx, 1 ) == raw_buffer_read_uint8( arg, 1 ) );
   CU_ASSERT( raw_buffer_read_uint8( argx, 2 ) == raw_buffer_read_uint8( arg, 2 ) );
   CU_ASSERT( raw_buffer_read_uint8( argx, 3 ) == raw_buffer_read_uint8( arg, 3 ) );

   raw_buffer_dispose_with_contents( argx );

   argx = binary_file_read_raw_buffer( file, raw_buffer_count( arg1 ) );

   CU_ASSERT( raw_buffer_read_uint8( argx, 0 ) == raw_buffer_read_uint8( arg1, 0 ) );
   CU_ASSERT( raw_buffer_read_uint8( argx, 1 ) == raw_buffer_read_uint8( arg1, 1 ) );
   CU_ASSERT( raw_buffer_read_uint8( argx, 2 ) == raw_buffer_read_uint8( arg1, 2 ) );

   CU_ASSERT( binary_file_count( file ) == raw_buffer_count( arg ) + raw_buffer_count( arg1 ) );

   raw_buffer_dispose_with_contents( argx );
   binary_file_close( file );

   binary_file_open_read_write( file );

   raw_buffer_put_uint8( arg, 33, 0 );
   raw_buffer_put_uint8( arg, 34, 1 );
   raw_buffer_put_uint8( arg, 35, 2 );
   raw_buffer_put_uint8( arg, 36, 3 );

   binary_file_put_raw_buffer( file, arg );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_raw_buffer( file, raw_buffer_count( arg ) );

   CU_ASSERT( raw_buffer_read_uint8( argx, 0 ) == raw_buffer_read_uint8( arg, 0 ) );
   CU_ASSERT( raw_buffer_read_uint8( argx, 1 ) == raw_buffer_read_uint8( arg, 1 ) );
   CU_ASSERT( raw_buffer_read_uint8( argx, 2 ) == raw_buffer_read_uint8( arg, 2 ) );
   CU_ASSERT( raw_buffer_read_uint8( argx, 3 ) == raw_buffer_read_uint8( arg, 3 ) );

   raw_buffer_dispose_with_contents( argx );

   argx = binary_file_read_raw_buffer( file, raw_buffer_count( arg1 ) );

   CU_ASSERT( raw_buffer_read_uint8( argx, 0 ) == raw_buffer_read_uint8( arg1, 0 ) );
   CU_ASSERT( raw_buffer_read_uint8( argx, 1 ) == raw_buffer_read_uint8( arg1, 1 ) );
   CU_ASSERT( raw_buffer_read_uint8( argx, 2 ) == raw_buffer_read_uint8( arg1, 2 ) );

   CU_ASSERT( binary_file_count( file ) == raw_buffer_count( arg ) + raw_buffer_count( arg1 ) );

   raw_buffer_dispose_with_contents( arg );
   raw_buffer_dispose_with_contents( arg1 );
   raw_buffer_dispose_with_contents( argx );

   string_dispose_with_contents( name );
   binary_file_dispose( file );

   return;
}

/**
   test_read_put_14
*/

void test_read_put_14( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;
   uint8_t *arg = NULL;
   uint8_t *arg1 = NULL;
   uint8_t *argx = NULL;

   name = string_make();

   string_append_cstring( name, "src/test/cfile.bin" );

   file = binary_file_make( name );
   binary_file_delete( file );
   binary_file_dispose( file );

   file = binary_file_make_open_append( name );

   arg = ( uint8_t * ) calloc( 4, sizeof( uint8_t ) );
   arg[0] = 13;
   arg[1] = 14;
   arg[2] = 15;
   arg[3] = 16;

   binary_file_put_bytes( file, arg, 4 );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_bytes( file, 4 );

   CU_ASSERT( argx[0] == arg[0] );
   CU_ASSERT( argx[1] == arg[1] );
   CU_ASSERT( argx[2] == arg[2] );
   CU_ASSERT( argx[3] == arg[3] );
   CU_ASSERT( binary_file_count( file ) == 4 );

   free( argx );
   binary_file_close( file );

   binary_file_open_append( file );

   arg1 = ( uint8_t * ) calloc( 3, sizeof( uint8_t ) );
   arg1[0] = 23;
   arg1[1] = 24;
   arg1[2] = 25;

   binary_file_put_bytes( file, arg1, 3 );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_bytes( file, 4 );

   CU_ASSERT( argx[0] == arg[0] );
   CU_ASSERT( argx[1] == arg[1] );
   CU_ASSERT( argx[2] == arg[2] );
   CU_ASSERT( argx[3] == arg[3] );

   free( argx );

   argx = binary_file_read_bytes( file, 3 );

   CU_ASSERT( argx[0] == arg1[0] );
   CU_ASSERT( argx[1] == arg1[1] );
   CU_ASSERT( argx[2] == arg1[2] );

   CU_ASSERT( binary_file_count( file ) == 4 + 3 );

   free( argx );

   binary_file_close( file );

   binary_file_open_read_write( file );

   arg[0] = 33;
   arg[1] = 34;
   arg[2] = 35;
   arg[3] = 36;

   binary_file_put_bytes( file, arg, 4 );

   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_bytes( file, 4 );

   CU_ASSERT( argx[0] == arg[0] );
   CU_ASSERT( argx[1] == arg[1] );
   CU_ASSERT( argx[2] == arg[2] );
   CU_ASSERT( argx[3] == arg[3] );

   free( arg );
   free( argx );

   argx = binary_file_read_bytes( file, 3 );

   CU_ASSERT( argx[0] == arg1[0] );
   CU_ASSERT( argx[1] == arg1[1] );
   CU_ASSERT( argx[2] == arg1[2] );

   CU_ASSERT( binary_file_count( file ) == 4 + 3 );

   free( arg1 );
   free( argx );
   string_dispose_with_contents( name );
   binary_file_dispose( file );

   return;
}

/**
   test_read_put_15
*/

void test_read_put_15( void )
{
   binary_file_t *file = NULL;
   string_t *name = NULL;
   uint8_t *arg = NULL;
   uint8_t *arg1 = NULL;
   uint8_t *argx = NULL;

   name = string_make();

   string_append_cstring( name, "src/test/cfile.bin" );

   file = binary_file_make( name );
   binary_file_delete( file );
   binary_file_dispose( file );

   file = binary_file_make_open_append( name );

   arg = ( uint8_t * ) calloc( 4, sizeof( uint8_t ) );
   arg[0] = 13;
   arg[1] = 14;
   arg[2] = 15;
   arg[3] = 16;

   binary_file_put_bytes( file, arg, 4 );

   binary_file_flush( file );
   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_bytes( file, 4 );

   CU_ASSERT( argx[0] == arg[0] );
   CU_ASSERT( argx[1] == arg[1] );
   CU_ASSERT( argx[2] == arg[2] );
   CU_ASSERT( argx[3] == arg[3] );
   CU_ASSERT( binary_file_count( file ) == 4 );

   binary_file_flush( file );
   binary_file_close( file );

   binary_file_open_append( file );

   arg1 = ( uint8_t * ) calloc( 3, sizeof( uint8_t ) );
   arg1[0] = 23;
   arg1[1] = 24;
   arg1[2] = 25;

   binary_file_put_bytes( file, arg1, 3 );

   free( argx );
   binary_file_flush( file );
   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_bytes( file, 4 );

   CU_ASSERT( argx[0] == arg[0] );
   CU_ASSERT( argx[1] == arg[1] );
   CU_ASSERT( argx[2] == arg[2] );
   CU_ASSERT( argx[3] == arg[3] );

   free( argx );

   argx = binary_file_read_bytes( file, 3 );

   CU_ASSERT( argx[0] == arg1[0] );
   CU_ASSERT( argx[1] == arg1[1] );
   CU_ASSERT( argx[2] == arg1[2] );

   free( argx );

   CU_ASSERT( binary_file_count( file ) == 4 + 3 );

   binary_file_flush( file );
   binary_file_close( file );

   binary_file_open_read_write( file );

   arg[0] = 33;
   arg[1] = 34;
   arg[2] = 35;
   arg[3] = 36;

   binary_file_put_bytes( file, arg, 4 );

   binary_file_flush( file );
   binary_file_close( file );

   binary_file_open_read( file );

   argx = binary_file_read_bytes( file, 4 );

   CU_ASSERT( argx[0] == arg[0] );
   CU_ASSERT( argx[1] == arg[1] );
   CU_ASSERT( argx[2] == arg[2] );
   CU_ASSERT( argx[3] == arg[3] );

   free( argx );

   argx = binary_file_read_bytes( file, 3 );

   CU_ASSERT( argx[0] == arg1[0] );
   CU_ASSERT( argx[1] == arg1[1] );
   CU_ASSERT( argx[2] == arg1[2] );

   CU_ASSERT( binary_file_count( file ) == 4 + 3 );

   free( arg );
   free( arg1 );
   free( argx );
   string_dispose_with_contents( name );
   binary_file_dispose( file );

   return;
}


int
add_test_read_put( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_read_put", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_read_put_1
   add_test_to_suite( p_suite, test_read_put_1, "test_read_put_1" );

   // test_read_put_2
   add_test_to_suite( p_suite, test_read_put_2, "test_read_put_2" );

   // test_read_put_3
   add_test_to_suite( p_suite, test_read_put_3, "test_read_put_3" );

   // test_read_put_4
   add_test_to_suite( p_suite, test_read_put_4, "test_read_put_4" );

   // test_read_put_5
   add_test_to_suite( p_suite, test_read_put_5, "test_read_put_5" );

   // test_read_put_6
   add_test_to_suite( p_suite, test_read_put_6, "test_read_put_6" );

   // test_read_put_7
   add_test_to_suite( p_suite, test_read_put_7, "test_read_put_7" );

   // test_read_put_8
   add_test_to_suite( p_suite, test_read_put_8, "test_read_put_8" );

   // test_read_put_9
   add_test_to_suite( p_suite, test_read_put_9, "test_read_put_9" );

   // test_read_put_10
   add_test_to_suite( p_suite, test_read_put_10, "test_read_put_10" );

   // test_read_put_11
   add_test_to_suite( p_suite, test_read_put_11, "test_read_put_11" );

   // test_read_put_12
   add_test_to_suite( p_suite, test_read_put_12, "test_read_put_12" );

   // test_read_put_13
   add_test_to_suite( p_suite, test_read_put_13, "test_read_put_13" );

   // test_read_put_14
   add_test_to_suite( p_suite, test_read_put_14, "test_read_put_14" );

   // test_read_put_15
   add_test_to_suite( p_suite, test_read_put_15, "test_read_put_15" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

