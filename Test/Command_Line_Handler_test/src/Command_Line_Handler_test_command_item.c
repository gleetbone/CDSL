/**
 @file command_line_handler_test_command_item.c
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
   test_command_item_1
*/

void test_command_item_1( void )
{
   command_line_handler_t *command_line_handler = NULL;
   string_t *help_string = NULL;
   string_t *usage_string = NULL;
   string_t *version_string = NULL;
   string_t *short_name = NULL;
   string_t *long_name = NULL;
   string_t *documentation = NULL;
   string_t *s = NULL;
   string_t *argument = NULL;
   FILE *fp_in = NULL;
   FILE *fp_out = NULL;
   command_t *command = NULL;
   command_t *c1 = NULL;
   command_t *c2 = NULL;
   option_t *option = NULL;
   option_t *o1 = NULL;
   option_t *o2 = NULL;
   protocol_base_t *p_command = NULL;
   protocol_base_t *p_command1 = NULL;
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
   
   fclose( fp_in );
   fclose( fp_out );

   c1 = command_clone( command );
   CU_ASSERT( command_is_equal( c1, c1 ) == 1 );
   CU_ASSERT( command_is_equal( c1, command ) == 1 );
   c2 = command_deep_clone( command );
   command_copy( c2, c1 );
   CU_ASSERT( command_is_equal( c1, c2 ) == 1 );
   command_dispose( &c1 );
   
   argument = string_make_from_cstring( "123" );
   command_add_argument( c2, argument );
   s = command_argument_item( c2, 0 );
   CU_ASSERT( s == argument );
   
   string_dispose( &argument );
   
   command_dispose( &c2 );
   
   c1 = command_deep_clone( command );
   CU_ASSERT( command_is_deep_equal( c1, c1 ) == 1 );
   CU_ASSERT( command_is_deep_equal( c1, command ) == 1 );
   c2 = command_clone( command );
   command_deep_copy( c2, c1 );
   CU_ASSERT( command_is_equal( c1, c2 ) == 1 );
   command_dispose( &c1 );
   command_dispose( &c2 );
   
   s = command_documentation( command );
   CU_ASSERT( string_is_equal_cstring( s, "c [arg]" ) == 1 );
   string_dispose( &s );
   
   CU_ASSERT( command_num_required_arguments( command ) == 0 );
   CU_ASSERT( command_num_arguments( command ) == 0 );
   
   o1 = option_make( short_name, long_name, documentation, 0 );
   command_add_option( command, ( protocol_base_t * ) o1 );
   
   o2 = option_clone( o1 );
   CU_ASSERT( option_is_equal( o1, o1 ) == 1 );
   CU_ASSERT( option_is_equal( o1, o2 ) == 1 );
   option_dispose( &o2 );
   
   o2 = option_deep_clone( option );
   option_copy( o2, o1 );
   CU_ASSERT( option_is_equal( o1, o2 ) == 1 );
   option_dispose( &o2 );
   
   o2 = option_clone( option );
   option_deep_copy( o2, o1 );
   CU_ASSERT( option_is_deep_equal( o1, o2 ) == 1 );
   option_dispose( &o2 );
   
   o2 = option_deep_clone( o1 );
   CU_ASSERT( option_is_deep_equal( o1, o1 ) == 1 );
   CU_ASSERT( option_is_deep_equal( o1, o2 ) == 1 );
   option_deep_dispose( &o2 );
   
   o2 = ( option_t * ) command_option_item( command, 0 );
   CU_ASSERT( command_num_options( command ) == 1 );
   CU_ASSERT( o1 == o2 );
   
   s = option_documentation( o1 );
   CU_ASSERT( string_is_equal( s, documentation ) == 1 );
   string_dispose( &s );
   
   CU_ASSERT( option_num_required_arguments( option ) == 0 );
   
   p_command1 = command_line_handler_command_item( command_line_handler, 0 );
   CU_ASSERT( p_command1 == p_command );

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
add_test_command_item( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_command_item", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_command_item_1
   add_test_to_suite( p_suite, test_command_item_1, "test_command_item_1" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

