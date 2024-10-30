/**
 @file date_time_duration_formatter_parser_test_parse.c
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
   test_parse_1
*/

void test_parse_1( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *end_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   date_time_duration_t *result = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls" );
   end_format_string = string_make_from_cstring( "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls" );
   separator = string_make_from_cstring( " / " );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_end
         ( 
            start_format_string, 
            end_format_string, 
            separator 
         );
   
   s = string_make_from_cstring( "2010-01-02 10:15:30.001 / 2010-01-03 09:16:31.021" );
   
   result = date_time_duration_formatter_parser_parse( date_time_duration_formatter_parser, s );
   CU_ASSERT( result != NULL );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &end_format_string );
   string_deep_dispose( &separator );
   date_time_duration_dispose( &result );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_parse_2
*/

void test_parse_2( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *end_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   date_time_duration_t *result = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls" );
   end_format_string = string_make_from_cstring( "[0]HH:[0]MI:[0]SS.[0]MLS" );
   separator = string_make_from_cstring( " / " );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_end_time
         ( 
            start_format_string, 
            end_format_string, 
            separator 
         );
   
   s = string_make_from_cstring( "2010-01-02 10:15:00.000 / 10:30:00.000" );
   
   result = date_time_duration_formatter_parser_parse( date_time_duration_formatter_parser, s );
   CU_ASSERT( result != NULL );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &end_format_string );
   string_deep_dispose( &separator );
   date_time_duration_dispose( &result );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_parse_2a
*/

void test_parse_2a( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *end_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   date_time_duration_t *result = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls" );
   end_format_string = string_make_from_cstring( "[0]H1:[0]MI:[0]SS.[0]MLS MD" );
   separator = string_make_from_cstring( " / " );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_end_time
         ( 
            start_format_string, 
            end_format_string, 
            separator 
         );
   
   s = string_make_from_cstring( "2010-01-02 10:15:00.000 / 10:30:00.000 AM" );
   
   result = date_time_duration_formatter_parser_parse( date_time_duration_formatter_parser, s );
   CU_ASSERT( result != NULL );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &end_format_string );
   string_deep_dispose( &separator );
   date_time_duration_dispose( &result );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_parse_2b
*/

void test_parse_2b( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *end_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   date_time_duration_t *result = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls" );
   end_format_string = string_make_from_cstring( "HHh MIm SSs MLSms" );
   separator = string_make_from_cstring( " / " );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_end_time
         ( 
            start_format_string, 
            end_format_string, 
            separator 
         );
   
   s = string_make_from_cstring( "2010-01-02 10:15:00.000 / 10h 30m 00s 000ms" );
   
   result = date_time_duration_formatter_parser_parse( date_time_duration_formatter_parser, s );
   CU_ASSERT( result != NULL );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &end_format_string );
   string_deep_dispose( &separator );
   date_time_duration_dispose( &result );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_parse_2c
*/

void test_parse_2c( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *end_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   date_time_duration_t *result = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls" );
   end_format_string = string_make_from_cstring( "H1h MIm SSs MLSms MD" );
   separator = string_make_from_cstring( " / " );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_end_time
         ( 
            start_format_string, 
            end_format_string, 
            separator 
         );
   
   s = string_make_from_cstring( "2010-01-02 10:15:00.000 / 10h 30m 00s 000ms PM" );
   
   result = date_time_duration_formatter_parser_parse( date_time_duration_formatter_parser, s );
   CU_ASSERT( result != NULL );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &end_format_string );
   string_deep_dispose( &separator );
   date_time_duration_dispose( &result );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_parse_2d
*/

void test_parse_2d( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *end_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   date_time_duration_t *result = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-mm-dd  ddd [0]hh:[0]mi" );
   end_format_string = string_make_from_cstring( "[0]HH:[0]MI" );
   separator = string_make_from_cstring( "-" );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_end_time
         ( 
            start_format_string, 
            end_format_string, 
            separator 
         );
   
   s = string_make_from_cstring( "2019-05-08 Wed 19:30-22:00" );
   
   result = date_time_duration_formatter_parser_parse( date_time_duration_formatter_parser, s );
   CU_ASSERT( result != NULL );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &end_format_string );
   string_deep_dispose( &separator );
   date_time_duration_dispose( &result );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_parse_2e
*/

void test_parse_2e( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *end_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   date_time_duration_t *result = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-mm-dd  ddd [0]hh:[0]mi" );
   end_format_string = string_make_from_cstring( "" );
   separator = string_make_from_cstring( "-" );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_end_time
         ( 
            start_format_string, 
            end_format_string, 
            separator 
         );
   
   s = string_make_from_cstring( "2019-05-08 Wed 19:30-" );
   
   result = date_time_duration_formatter_parser_parse( date_time_duration_formatter_parser, s );
   CU_ASSERT( result != NULL );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &end_format_string );
   string_deep_dispose( &separator );
   date_time_duration_dispose( &result );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_parse_3
*/

void test_parse_3( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *duration_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   date_time_duration_t *result = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls" );
   duration_format_string = string_make_from_cstring( "*DDdHHhMImSS.[0]MLSs" );
   separator = string_make_from_cstring( " / " );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_duration
         ( 
            start_format_string, 
            duration_format_string, 
            separator 
         );
   
   s = string_make_from_cstring( "2010-01-02 10:15:00.000 / 1d3h14m1.123s" );
   
   result = date_time_duration_formatter_parser_parse( date_time_duration_formatter_parser, s );
   CU_ASSERT( result != NULL );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &duration_format_string );
   string_deep_dispose( &separator );
   date_time_duration_dispose( &result );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_parse_3a
*/

void test_parse_3a( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *duration_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   date_time_duration_t *result = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls" );
   duration_format_string = string_make_from_cstring( "*DDd HHh MIm SS.[0]MLS" );
   separator = string_make_from_cstring( " / " );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_duration
         ( 
            start_format_string, 
            duration_format_string, 
            separator 
         );
   
   s = string_make_from_cstring( "2010-01-02 10:15:00.000 / 1d 3h 14m 1.123" );
   
   result = date_time_duration_formatter_parser_parse( date_time_duration_formatter_parser, s );
   CU_ASSERT( result != NULL );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &duration_format_string );
   string_deep_dispose( &separator );
   date_time_duration_dispose( &result );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_parse_3b
*/

void test_parse_3b( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *duration_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   date_time_duration_t *result = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls" );
   duration_format_string = string_make_from_cstring( "*HHh MIm SS.[0]MLSs" );
   separator = string_make_from_cstring( " / " );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_duration
         ( 
            start_format_string, 
            duration_format_string, 
            separator 
         );
   
   s = string_make_from_cstring( "2010-01-02 10:15:00.000 / 3h 14m 1.123s" );
   
   result = date_time_duration_formatter_parser_parse( date_time_duration_formatter_parser, s );
   CU_ASSERT( result != NULL );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &duration_format_string );
   string_deep_dispose( &separator );
   date_time_duration_dispose( &result );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_parse_3c
*/

void test_parse_3c( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *duration_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   date_time_duration_t *result = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls" );
   duration_format_string = string_make_from_cstring( "*DDd [0]HHh [0]MIm [0]SS.[0]MLSs" );
   separator = string_make_from_cstring( " / " );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_duration
         ( 
            start_format_string, 
            duration_format_string, 
            separator 
         );
   
   s = string_make_from_cstring( "2010-01-02 10:15:00.000 / 1d 03h 14m 01.123s" );
   
   result = date_time_duration_formatter_parser_parse( date_time_duration_formatter_parser, s );
   CU_ASSERT( result != NULL );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &duration_format_string );
   string_deep_dispose( &separator );
   date_time_duration_dispose( &result );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_parse_3d
*/

void test_parse_3d( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *duration_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   date_time_duration_t *result = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls" );
   duration_format_string = string_make_from_cstring( "*MIm SS.[0]MLSs" );
   separator = string_make_from_cstring( " / " );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_duration
         ( 
            start_format_string, 
            duration_format_string, 
            separator 
         );
   
   s = string_make_from_cstring( "2010-01-02 10:15:00.000 / 14m 1.123s" );
   
   result = date_time_duration_formatter_parser_parse( date_time_duration_formatter_parser, s );
   CU_ASSERT( result != NULL );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &duration_format_string );
   string_deep_dispose( &separator );
   date_time_duration_dispose( &result );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_parse_3e
*/

void test_parse_3e( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *duration_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   date_time_duration_t *result = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls" );
   duration_format_string = string_make_from_cstring( "*SS.[0]MLSs" );
   separator = string_make_from_cstring( " / " );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_duration
         ( 
            start_format_string, 
            duration_format_string, 
            separator 
         );
   
   s = string_make_from_cstring( "2010-01-02 10:15:00.000 / 121.123s" );
   
   result = date_time_duration_formatter_parser_parse( date_time_duration_formatter_parser, s );
   CU_ASSERT( result != NULL );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &duration_format_string );
   string_deep_dispose( &separator );
   date_time_duration_dispose( &result );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_parse_4
*/

void test_parse_4( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *duration_format_string = NULL;
   string_t *s = NULL;
   date_time_duration_t *result = NULL;
   
   duration_format_string = string_make_from_cstring( "*DDd HHh MIm SS.[0]MLSs" );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_duration
         ( 
            duration_format_string
         );
   
   s = string_make_from_cstring( "1d 3h 14m 1.123s" );
   
   result = date_time_duration_formatter_parser_parse( date_time_duration_formatter_parser, s );
   CU_ASSERT( result != NULL );
   string_deep_dispose( &s );
 
   string_deep_dispose( &duration_format_string );
   date_time_duration_dispose( &result );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

int
add_test_parse( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_parse", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_parse_1
   add_test_to_suite( p_suite, test_parse_1, "test_parse_1" );

   // test_parse_2
   add_test_to_suite( p_suite, test_parse_2, "test_parse_2" );

   // test_parse_2a
   add_test_to_suite( p_suite, test_parse_2a, "test_parse_2a" );

   // test_parse_2b
   add_test_to_suite( p_suite, test_parse_2b, "test_parse_2b" );

   // test_parse_2c
   add_test_to_suite( p_suite, test_parse_2c, "test_parse_2c" );

   // test_parse_2d
   add_test_to_suite( p_suite, test_parse_2d, "test_parse_2d" );

   // test_parse_2e
   add_test_to_suite( p_suite, test_parse_2e, "test_parse_2e" );

   // test_parse_3
   add_test_to_suite( p_suite, test_parse_3, "test_parse_3" );

   // test_parse_3a
   add_test_to_suite( p_suite, test_parse_3a, "test_parse_3a" );

   // test_parse_3b
   add_test_to_suite( p_suite, test_parse_3b, "test_parse_3b" );

   // test_parse_3c
   add_test_to_suite( p_suite, test_parse_3c, "test_parse_3c" );

   // test_parse_3d
   add_test_to_suite( p_suite, test_parse_3d, "test_parse_3d" );

   // test_parse_3e
   add_test_to_suite( p_suite, test_parse_3e, "test_parse_3e" );

   // test_parse_4
   add_test_to_suite( p_suite, test_parse_4, "test_parse_4" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

