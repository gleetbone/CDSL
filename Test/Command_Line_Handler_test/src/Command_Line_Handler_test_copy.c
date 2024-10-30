/**
 @file command_line_handler_test_copy.c
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

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_copy_1
*/

void test_copy_1( void )
{
   command_line_handler_t *command_line_handler = NULL;
   command_line_handler_t *command_line_handler1 = NULL;
   string_t *help_string = NULL;
   string_t *usage_string = NULL;
   string_t *version_string = NULL;
   string_t *help_string1 = NULL;
   string_t *usage_string1 = NULL;
   string_t *version_string1 = NULL;
   
   help_string = string_make_from_cstring( "Help String." );
   usage_string = string_make_from_cstring( "Usage String." );
   version_string = string_make_from_cstring( "Version String." );

   help_string1 = string_make_from_cstring( "Help String 1." );
   usage_string1 = string_make_from_cstring( "Usage String 1." );
   version_string1 = string_make_from_cstring( "Version String 1." );

   command_line_handler 
      =  command_line_handler_make
         (
            stdin,
            stdout,
            help_string,
            usage_string,
            version_string
         );
   
   CU_ASSERT( command_line_handler != NULL );
   
   command_line_handler1
      =  command_line_handler_make
         (
            stdin,
            stdout,
            help_string1,
            usage_string1,
            version_string1
         );
   
   CU_ASSERT( command_line_handler1 != NULL );
   
   command_line_handler_copy( command_line_handler1, command_line_handler );
   
   command_line_handler_dispose( &command_line_handler1 );
   command_line_handler_deep_dispose( &command_line_handler );

   string_deep_dispose( &help_string );
   string_deep_dispose( &usage_string );
   string_deep_dispose( &version_string );
   
   string_deep_dispose( &help_string1 );
   string_deep_dispose( &usage_string1 );
   string_deep_dispose( &version_string1 );
   
   return;
}

int
add_test_copy( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_copy", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_copy_1
   add_test_to_suite( p_suite, test_copy_1, "test_copy_1" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

