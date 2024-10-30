/**
 @file command_line_handler_test_execute.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for command_line_handler_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for command_line_handler_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include "CUnit/Basic.h"

#include "Command_Line_Handler.h"
#include "String.h"
#include "Command.h"
#include "Option.h"
#include <unistd.h>

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_execute_1
*/

void test_execute_1( void )
{
   command_line_handler_t *command_line_handler = NULL;
   string_t *help_string = NULL;
   string_t *usage_string = NULL;
   string_t *version_string = NULL;
   FILE *fp_in = NULL;
   FILE *fp_out = NULL;
   FILE *fp = NULL;
   char_t *line = NULL;
   size_t len = 0;
   
   help_string = string_make_from_cstring( "Help String." );
   usage_string = string_make_from_cstring( "Usage String." );
   version_string = string_make_from_cstring( "Version String." );

   fp_in = fopen( "src/input_files/file_1.txt", "r" );
   fp_out = fopen( "src/output_files/file_1.txt", "w" );
   
   command_line_handler 
      =  command_line_handler_make
         (
            fp_in,
            fp_out,
            help_string,
            usage_string,
            version_string
         );
   
   CU_ASSERT( command_line_handler != NULL );
   
   command_line_handler_execute( command_line_handler );

   fclose( fp_in );
   fclose( fp_out );
   
   // check output file contents ( what was printed to stdout )
   fp = fopen( "src/output_files/file_1.txt", "r" );
   CU_ASSERT( fp != NULL );
   
   getline( &line, &len, fp );
   CU_ASSERT( strcmp( line, "Exiting program.\n" ) == 0 );
   
   fclose( fp );
   free( line );
   
   command_line_handler_deep_dispose( &command_line_handler );

   string_deep_dispose( &help_string );
   string_deep_dispose( &usage_string );
   string_deep_dispose( &version_string );
   
   return;
}

/**
   test_execute_2
*/

void test_execute_2( void )
{
   command_line_handler_t *command_line_handler = NULL;
   string_t *help_string = NULL;
   string_t *usage_string = NULL;
   string_t *version_string = NULL;
   FILE *fp_in = NULL;
   FILE *fp_out = NULL;
   FILE *fp = NULL;
   char_t *line = NULL;
   size_t len = 0;
   
   help_string = string_make_from_cstring( "Help String." );
   usage_string = string_make_from_cstring( "Usage String." );
   version_string = string_make_from_cstring( "Version String." );

   fp_in = fopen( "src/input_files/file_2.txt", "r" );
   fp_out = fopen( "src/output_files/file_2.txt", "w" );
   
   command_line_handler 
      =  command_line_handler_make
         (
            fp_in,
            fp_out,
            help_string,
            usage_string,
            version_string
         );
   
   CU_ASSERT( command_line_handler != NULL );
   
   command_line_handler_execute( command_line_handler );

   fclose( fp_in );
   fclose( fp_out );
   
   // check output file contents ( what was printed to stdout )
   fp = fopen( "src/output_files/file_2.txt", "r" );
   CU_ASSERT( fp != NULL );
   
   getline( &line, &len, fp );
   CU_ASSERT( strcmp( line, "Help String.\n" ) == 0 );
   
   getline( &line, &len, fp );
   CU_ASSERT( strcmp( line, "Usage String.\n" ) == 0 );
   
   getline( &line, &len, fp );
   CU_ASSERT( strcmp( line, "Version String.\n" ) == 0 );
   
   getline( &line, &len, fp );
   CU_ASSERT( strcmp( line, "Exiting program.\n" ) == 0 );
   
   fclose( fp );
   free( line );
   
   command_line_handler_deep_dispose( &command_line_handler );

   string_deep_dispose( &help_string );
   string_deep_dispose( &usage_string );
   string_deep_dispose( &version_string );
   
   return;
}

/**
   test_execute_3
*/

void test_execute_3( void )
{
   command_line_handler_t *command_line_handler = NULL;
   string_t *help_string = NULL;
   string_t *usage_string = NULL;
   string_t *version_string = NULL;
   string_t *short_name = NULL;
   string_t *long_name = NULL;
   string_t *documentation = NULL;
   FILE *fp_in = NULL;
   FILE *fp_out = NULL;
   FILE *fp = NULL;
   char_t *line = NULL;
   size_t len = 0;
   command_t *command = NULL;
   protocol_base_t *p_command = NULL;
   
   help_string = string_make_from_cstring( "Help String." );
   usage_string = string_make_from_cstring( "Usage String." );
   version_string = string_make_from_cstring( "Version String." );

   short_name = string_make_from_cstring( "c" );
   long_name = string_make_from_cstring( "command" );
   documentation = string_make_from_cstring( "c [arg]" );

   fp_in = fopen( "src/input_files/file_3.txt", "r" );
   fp_out = fopen( "src/output_files/file_3.txt", "w" );
   
   command_line_handler 
      =  command_line_handler_make
         (
            fp_in,
            fp_out,
            help_string,
            usage_string,
            version_string
         );
   
   CU_ASSERT( command_line_handler != NULL );
   
   command = command_make( fp_out, short_name, long_name, documentation, 0 );
   p_command = ( protocol_base_t * ) command;
   
   command_line_handler_add_command( command_line_handler, p_command );
   
   command_line_handler_execute( command_line_handler );

   fclose( fp_in );
   fclose( fp_out );
   
   // check output file contents ( what was printed to stdout )
   fp = fopen( "src/output_files/file_3.txt", "r" );
   CU_ASSERT( fp != NULL );
   
   getline( &line, &len, fp );
   CU_ASSERT( strcmp( line, "c arg \n" ) == 0 );
   
   getline( &line, &len, fp );
   CU_ASSERT( strcmp( line, "Exiting program.\n" ) == 0 );
   
   fclose( fp );
   free( line );
   
   command_line_handler_deep_dispose( &command_line_handler );

   string_deep_dispose( &help_string );
   string_deep_dispose( &usage_string );
   string_deep_dispose( &version_string );
   
   string_deep_dispose( &short_name );
   string_deep_dispose( &long_name );
   string_deep_dispose( &documentation );
   
   return;
}

/**
   test_execute_4
*/

void test_execute_4( void )
{
   command_line_handler_t *command_line_handler = NULL;
   string_t *help_string = NULL;
   string_t *usage_string = NULL;
   string_t *version_string = NULL;
   string_t *short_name = NULL;
   string_t *long_name = NULL;
   string_t *documentation = NULL;
   FILE *fp_in = NULL;
   FILE *fp_out = NULL;
   FILE *fp = NULL;
   char_t *line = NULL;
   size_t len = 0;
   command_t *command = NULL;
   option_t *option = NULL;
   protocol_base_t *p_command = NULL;
   protocol_base_t *p_option = NULL;
   
   help_string = string_make_from_cstring( "Help String." );
   usage_string = string_make_from_cstring( "Usage String." );
   version_string = string_make_from_cstring( "Version String." );

   short_name = string_make_from_cstring( "c" );
   long_name = string_make_from_cstring( "command" );
   documentation = string_make_from_cstring( "c [arg]" );

   fp_in = fopen( "src/input_files/file_4.txt", "r" );
   fp_out = fopen( "src/output_files/file_4.txt", "w" );
   
   command_line_handler 
      =  command_line_handler_make
         (
            fp_in,
            fp_out,
            help_string,
            usage_string,
            version_string
         );
   
   CU_ASSERT( command_line_handler != NULL );
   
   command = command_make( fp_out, short_name, long_name, documentation, 0 );
   p_command = ( protocol_base_t * ) command;
   
   command_line_handler_add_command( command_line_handler, p_command );
   
   string_wipe_out( short_name );
   string_append_cstring( short_name, "-o" );
   string_wipe_out( long_name );
   string_append_cstring( long_name, "-option" );
   string_wipe_out( documentation );
   string_append_cstring( documentation, "-o arg" );
   
   option = option_make( short_name, long_name, documentation, 0 );
   p_option = ( protocol_base_t * ) option;
      
   command_line_handler_add_option( command_line_handler, p_option );
   
   command_line_handler_execute( command_line_handler );

   fclose( fp_in );
   fclose( fp_out );
   
   // check output file contents ( what was printed to stdout )
   fp = fopen( "src/output_files/file_4.txt", "r" );
   CU_ASSERT( fp != NULL );
   
   getline( &line, &len, fp );
   CU_ASSERT( strcmp( line, "c arg -o arg \n" ) == 0 );
   
   getline( &line, &len, fp );
   CU_ASSERT( strcmp( line, "Exiting program.\n" ) == 0 );
   
   fclose( fp );
   free( line );
   
   command_line_handler_deep_dispose( &command_line_handler );

   string_deep_dispose( &help_string );
   string_deep_dispose( &usage_string );
   string_deep_dispose( &version_string );
   
   string_deep_dispose( &short_name );
   string_deep_dispose( &long_name );
   string_deep_dispose( &documentation );
   
   return;
}

/**
   test_execute_5
*/

void test_execute_5( void )
{
   command_line_handler_t *command_line_handler = NULL;
   string_t *help_string = NULL;
   string_t *usage_string = NULL;
   string_t *version_string = NULL;
   string_t *short_name = NULL;
   string_t *long_name = NULL;
   string_t *documentation = NULL;
   FILE *fp_in = NULL;
   FILE *fp_out = NULL;
   FILE *fp = NULL;
   char_t *line = NULL;
   size_t len = 0;
   command_t *command = NULL;
   option_t *option = NULL;
   protocol_base_t *p_command = NULL;
   protocol_base_t *p_option = NULL;
   
   help_string = string_make_from_cstring( "Help String." );
   usage_string = string_make_from_cstring( "Usage String." );
   version_string = string_make_from_cstring( "Version String." );

   short_name = string_make_from_cstring( "c" );
   long_name = string_make_from_cstring( "command" );
   documentation = string_make_from_cstring( "c [arg]" );

   fp_in = fopen( "src/input_files/file_5.txt", "r" );
   fp_out = fopen( "src/output_files/file_5.txt", "w" );
   
   command_line_handler 
      =  command_line_handler_make
         (
            fp_in,
            fp_out,
            help_string,
            usage_string,
            version_string
         );
   
   CU_ASSERT( command_line_handler != NULL );
   
   command = command_make( fp_out, short_name, long_name, documentation, 0 );
   p_command = ( protocol_base_t * ) command;
   
   command_line_handler_add_command( command_line_handler, p_command );
   
   string_wipe_out( short_name );
   string_append_cstring( short_name, "-o" );
   string_wipe_out( long_name );
   string_append_cstring( long_name, "-option" );
   string_wipe_out( documentation );
   string_append_cstring( documentation, "-o arg" );
   
   option = option_make( short_name, long_name, documentation, 0 );
   p_option = ( protocol_base_t * ) option;
      
   command_line_handler_add_option( command_line_handler, p_option );
   
   command_line_handler_execute( command_line_handler );

   fclose( fp_in );
   fclose( fp_out );
   
   // check output file contents ( what was printed to stdout )
   fp = fopen( "src/output_files/file_5.txt", "r" );
   CU_ASSERT( fp != NULL );
   
   getline( &line, &len, fp );
   CU_ASSERT( strcmp( line, "Error reading command line.\n" ) == 0 );
   
   fclose( fp );
   free( line );
   
   command_line_handler_deep_dispose( &command_line_handler );

   string_deep_dispose( &help_string );
   string_deep_dispose( &usage_string );
   string_deep_dispose( &version_string );
   
   string_deep_dispose( &short_name );
   string_deep_dispose( &long_name );
   string_deep_dispose( &documentation );
   
   return;
}

/**
   test_execute_6
*/

void test_execute_6( void )
{
   command_line_handler_t *command_line_handler = NULL;
   string_t *help_string = NULL;
   string_t *usage_string = NULL;
   string_t *version_string = NULL;
   string_t *short_name = NULL;
   string_t *long_name = NULL;
   string_t *documentation = NULL;
   FILE *fp_in = NULL;
   FILE *fp_out = NULL;
   FILE *fp = NULL;
   char_t *line = NULL;
   size_t len = 0;
   command_t *command = NULL;
   option_t *option = NULL;
   protocol_base_t *p_command = NULL;
   protocol_base_t *p_option = NULL;
   
   help_string = string_make_from_cstring( "Help String." );
   usage_string = string_make_from_cstring( "Usage String." );
   version_string = string_make_from_cstring( "Version String." );

   short_name = string_make_from_cstring( "c" );
   long_name = string_make_from_cstring( "command" );
   documentation = string_make_from_cstring( "c [arg]" );

   fp_in = fopen( "src/input_files/file_6.txt", "r" );
   fp_out = fopen( "src/output_files/file_6.txt", "w" );
   
   command_line_handler 
      =  command_line_handler_make
         (
            fp_in,
            fp_out,
            help_string,
            usage_string,
            version_string
         );
   
   CU_ASSERT( command_line_handler != NULL );
   
   command = command_make( fp_out, short_name, long_name, documentation, 0 );
   p_command = ( protocol_base_t * ) command;
   
   command_line_handler_add_command( command_line_handler, p_command );
   
   string_wipe_out( short_name );
   string_append_cstring( short_name, "-o" );
   string_wipe_out( long_name );
   string_append_cstring( long_name, "-option" );
   string_wipe_out( documentation );
   string_append_cstring( documentation, "-o arg" );
   
   option = option_make( short_name, long_name, documentation, 0 );
   p_option = ( protocol_base_t * ) option;
      
   command_line_handler_add_option( command_line_handler, p_option );
   
   command_line_handler_execute( command_line_handler );

   fclose( fp_in );
   fclose( fp_out );
   
   // check output file contents ( what was printed to stdout )
   fp = fopen( "src/output_files/file_6.txt", "r" );
   CU_ASSERT( fp != NULL );
   
   getline( &line, &len, fp );
   CU_ASSERT( strcmp( line, "c arg one ar\"g \n" ) == 0 );
   
   getline( &line, &len, fp );
   CU_ASSERT( strcmp( line, "c arg \n" ) == 0 );
   
   getline( &line, &len, fp );
   CU_ASSERT( strcmp( line, "c arg -o arg \n" ) == 0 );
   
   getline( &line, &len, fp );
   CU_ASSERT( strcmp( line, "Error - extra token -p found in command line.\n" ) == 0 );
   
   getline( &line, &len, fp );
   CU_ASSERT( strcmp( line, "Error - extra token arg found in command line.\n" ) == 0 );
   
   getline( &line, &len, fp );
   CU_ASSERT( strcmp( line, "c arg \n" ) == 0 );
   
   getline( &line, &len, fp );
   CU_ASSERT( strcmp( line, "Error - non-command token x found in command line.\n" ) == 0 );
   
   getline( &line, &len, fp );
   CU_ASSERT( strcmp( line, "Error - no command found.\n" ) == 0 );
   
   getline( &line, &len, fp );
   CU_ASSERT( strcmp( line, "Exiting program.\n" ) == 0 );
   
   fclose( fp );
   free( line );
   
   command_line_handler_deep_dispose( &command_line_handler );

   string_deep_dispose( &help_string );
   string_deep_dispose( &usage_string );
   string_deep_dispose( &version_string );
   
   string_deep_dispose( &short_name );
   string_deep_dispose( &long_name );
   string_deep_dispose( &documentation );
   
   return;
}

int
add_test_execute( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_execute", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_execute_1
   add_test_to_suite( p_suite, test_execute_1, "test_execute_1" );

   // test_execute_2
   add_test_to_suite( p_suite, test_execute_2, "test_execute_2" );

   // test_execute_3
   add_test_to_suite( p_suite, test_execute_3, "test_execute_3" );

   // test_execute_4
   add_test_to_suite( p_suite, test_execute_4, "test_execute_4" );

   // test_execute_5
   add_test_to_suite( p_suite, test_execute_5, "test_execute_5" );

   // test_execute_6
   add_test_to_suite( p_suite, test_execute_6, "test_execute_6" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

