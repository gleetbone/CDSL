/**
 @file date_time_duration_formatter_parser_test_is_time_duration.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for date_time_duration_formatter_parser_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for date_time_duration_formatter_parser_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include "CUnit/Basic.h"

#include "Date_Time_Duration_Formatter_Parser.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_is_time_duration_1
*/

void test_is_time_duration_1( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *end_format_string = NULL;
   string_t *separator = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls" );
   end_format_string = string_make_from_cstring( "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls" );
   separator = string_make_from_cstring( "//" );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_end_time
         ( 
            start_format_string, 
            end_format_string, 
            separator 
         );
   
   CU_ASSERT( date_time_duration_formatter_parser_is_time_duration( date_time_duration_formatter_parser ) == 1 );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &end_format_string );
   string_deep_dispose( &separator );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

int
add_test_is_time_duration( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_time_duration", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_time_duration_1
   add_test_to_suite( p_suite, test_is_time_duration_1, "test_is_time_duration_1" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */
