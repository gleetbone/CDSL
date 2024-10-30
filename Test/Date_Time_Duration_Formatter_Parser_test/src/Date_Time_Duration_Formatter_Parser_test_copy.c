/**
 @file date_time_duration_formatter_parser_test_copy.c
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
   test_copy_1
*/

void test_copy_1( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser1 = NULL;
   string_t *s = NULL;
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_end_cstring
         ( 
            "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls", 
            "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls", 
            "//"
         );
   
   date_time_duration_formatter_parser1
      =  date_time_duration_formatter_parser_make_start_end_cstring
         ( 
            "", 
            "", 
            ",,"
         );
   
   date_time_duration_formatter_parser_copy
   (
      date_time_duration_formatter_parser1,
      date_time_duration_formatter_parser
   );
         
   CU_ASSERT( date_time_duration_formatter_parser1 != NULL );
   
   s = date_time_duration_formatter_parser_start_format_string( date_time_duration_formatter_parser1 );
   CU_ASSERT( string_is_equal_cstring( s, "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls" ) == 1 );
   string_deep_dispose( &s );
 
   s = date_time_duration_formatter_parser_end_format_string( date_time_duration_formatter_parser1 );
   CU_ASSERT( string_is_equal_cstring( s, "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls" ) == 1 );
   string_deep_dispose( &s );
 
   s = date_time_duration_formatter_parser_separator( date_time_duration_formatter_parser1 );
   CU_ASSERT( string_is_equal_cstring( s, "//" ) == 1 );
   string_deep_dispose( &s );
 
   s = date_time_duration_formatter_parser_last_error( date_time_duration_formatter_parser1 );
   CU_ASSERT( string_is_equal_cstring( s, "" ) == 1 );
   string_deep_dispose( &s );
 
   CU_ASSERT( date_time_duration_formatter_parser_base_century( date_time_duration_formatter_parser1 ) == 2000 );
   
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser1 );

   return;
}

/**
   test_copy_2
*/

void test_copy_2( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser1 = NULL;
   string_t *s = NULL;
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_duration_cstring
         ( 
            "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls", 
            "[0]HH:[0]MI:[0]SS.[0]MLS", 
            "//"
         );
   
   date_time_duration_formatter_parser1
      =  date_time_duration_formatter_parser_make_start_duration_cstring
         ( 
            "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls", 
            "HH:[0]MI:[0]SS.[0]MLS", 
            " ^ "
         );
   
   date_time_duration_formatter_parser_copy
   (
      date_time_duration_formatter_parser1,
      date_time_duration_formatter_parser
   );
         
   CU_ASSERT( date_time_duration_formatter_parser1 != NULL );
   
   s = date_time_duration_formatter_parser_start_format_string( date_time_duration_formatter_parser1 );
   CU_ASSERT( string_is_equal_cstring( s, "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls" ) == 1 );
   string_deep_dispose( &s );
 
   s = date_time_duration_formatter_parser_duration_format_string( date_time_duration_formatter_parser1 );
   CU_ASSERT( string_is_equal_cstring( s, "[0]HH:[0]MI:[0]SS.[0]MLS" ) == 1 );
   string_deep_dispose( &s );
 
   s = date_time_duration_formatter_parser_separator( date_time_duration_formatter_parser1 );
   CU_ASSERT( string_is_equal_cstring( s, "//" ) == 1 );
   string_deep_dispose( &s );
 
   s = date_time_duration_formatter_parser_last_error( date_time_duration_formatter_parser1 );
   CU_ASSERT( string_is_equal_cstring( s, "" ) == 1 );
   string_deep_dispose( &s );
 
   CU_ASSERT( date_time_duration_formatter_parser_base_century( date_time_duration_formatter_parser1 ) == 2000 );
   
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser1 );

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

   // test_copy_2
   add_test_to_suite( p_suite, test_copy_2, "test_copy_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

