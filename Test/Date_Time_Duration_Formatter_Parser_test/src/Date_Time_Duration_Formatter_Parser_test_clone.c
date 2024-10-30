/**
 @file date_time_duration_formatter_parser_test_clone.c
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
   test_clone_1
*/

void test_clone_1( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser1 = NULL;
   string_t *start_format_string = NULL;
   string_t *end_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls" );
   end_format_string = string_make_from_cstring( "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls" );
   separator = string_make_from_cstring( "//" );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_end
         ( 
            start_format_string, 
            end_format_string, 
            separator 
         );
   
   date_time_duration_formatter_parser1
      = date_time_duration_formatter_parser_clone
         (
            date_time_duration_formatter_parser
         );
         
   CU_ASSERT( date_time_duration_formatter_parser1 != NULL );
   
   s = date_time_duration_formatter_parser_start_format_string( date_time_duration_formatter_parser1 );
   CU_ASSERT( string_is_equal( start_format_string, s ) == 1 );
   string_deep_dispose( &s );
 
   s = date_time_duration_formatter_parser_end_format_string( date_time_duration_formatter_parser1 );
   CU_ASSERT( string_is_equal( end_format_string, s ) == 1 );
   string_deep_dispose( &s );
 
   s = date_time_duration_formatter_parser_separator( date_time_duration_formatter_parser1 );
   CU_ASSERT( string_is_equal( separator, s ) == 1 );
   string_deep_dispose( &s );
 
   s = date_time_duration_formatter_parser_last_error( date_time_duration_formatter_parser1 );
   CU_ASSERT( string_is_equal_cstring( s, "" ) == 1 );
   string_deep_dispose( &s );
 
   CU_ASSERT( date_time_duration_formatter_parser_base_century( date_time_duration_formatter_parser1 ) == 2000 );
   
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &end_format_string );
   string_deep_dispose( &separator );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser1 );

   return;
}

/**
   test_clone_2
*/

void test_clone_2( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser1 = NULL;
   string_t *start_format_string = NULL;
   string_t *duration_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls" );
   duration_format_string = string_make_from_cstring( "[0]HH:[0]MI:[0]SS.[0]MLS" );
   separator = string_make_from_cstring( "//" );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_duration
         ( 
            start_format_string, 
            duration_format_string, 
            separator 
         );
   
   date_time_duration_formatter_parser1
      = date_time_duration_formatter_parser_clone
         (
            date_time_duration_formatter_parser
         );
         
   CU_ASSERT( date_time_duration_formatter_parser1 != NULL );
   
   s = date_time_duration_formatter_parser_start_format_string( date_time_duration_formatter_parser1 );
   CU_ASSERT( string_is_equal( start_format_string, s ) == 1 );
   string_deep_dispose( &s );
 
   s = date_time_duration_formatter_parser_duration_format_string( date_time_duration_formatter_parser1 );
   CU_ASSERT( string_is_equal( duration_format_string, s ) == 1 );
   string_deep_dispose( &s );
 
   s = date_time_duration_formatter_parser_separator( date_time_duration_formatter_parser1 );
   CU_ASSERT( string_is_equal( separator, s ) == 1 );
   string_deep_dispose( &s );
 
   s = date_time_duration_formatter_parser_last_error( date_time_duration_formatter_parser1 );
   CU_ASSERT( string_is_equal_cstring( s, "" ) == 1 );
   string_deep_dispose( &s );
 
   CU_ASSERT( date_time_duration_formatter_parser_base_century( date_time_duration_formatter_parser1 ) == 2000 );
   
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &duration_format_string );
   string_deep_dispose( &separator );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser1 );

   return;
}

int
add_test_clone( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_clone", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_clone_1
   add_test_to_suite( p_suite, test_clone_1, "test_clone_1" );

   // test_clone_2
   add_test_to_suite( p_suite, test_clone_2, "test_clone_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */
