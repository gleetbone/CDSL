/**
 @file date_time_duration_formatter_parser_test_format.c
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
   test_format_1
*/

void test_format_1( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *end_format_string = NULL;
   string_t *separator = NULL;
   string_t *result = NULL;
   string_t *s = NULL;
   date_time_duration_t *dtd = NULL;
   date_time_t *dt1 = NULL;
   date_time_t *dt2 = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-[0]mm-[0]dd [0]hh:[0]mi:[0]ss.[0]mls" );
   end_format_string = string_make_from_cstring( "yyyy-[0]mm-[0]dd [0]hh:[0]mi:[0]ss.[0]mls" );
   separator = string_make_from_cstring( " / " );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_end
         ( 
            start_format_string, 
            end_format_string, 
            separator 
         );
   
   dt1 = date_time_make( 2010, 1, 2, 10, 15, 30, 1 );
   dt2 = date_time_make( 2010, 1, 3, 9, 16, 31, 21 );
   
   dtd = date_time_duration_make_start_end( dt1, dt2 );
        
   result = date_time_duration_formatter_parser_format( date_time_duration_formatter_parser, dtd );
      
   s = string_make_from_cstring( "2010-01-02 10:15:30.001 / 2010-01-03 09:16:31.021" );
   
   CU_ASSERT( string_is_equal( s, result ) == 1 );
   
   string_deep_dispose( &result );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &end_format_string );
   string_deep_dispose( &separator );
   date_time_dispose( &dt1 );
   date_time_dispose( &dt2 );
   date_time_duration_dispose( &dtd );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_format_2
*/

void test_format_2( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *end_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   string_t *result = NULL;
   date_time_duration_t *dtd = NULL;
   date_time_t *dt1 = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-[0]mm-[0]dd [0]hh:[0]mi:[0]ss.[0]mls" );
   end_format_string = string_make_from_cstring( "[0]HH:[0]MI:[0]SS.[0]MLS" );
   separator = string_make_from_cstring( " / " );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_end_time
         ( 
            start_format_string, 
            end_format_string, 
            separator 
         );
   
   dt1 = date_time_make( 2010, 1, 2, 10, 15, 0, 0 );
   dtd = date_time_duration_make_start_dhms( dt1, 0, 0, 15, 1, 2 );
   
   result = date_time_duration_formatter_parser_format( date_time_duration_formatter_parser, dtd );
   
   s = string_make_from_cstring( "2010-01-02 10:15:00.000 / 10:30:01.002" );
   
   CU_ASSERT( string_is_equal( s, result ) == 1 );
   
   string_deep_dispose( &result );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &end_format_string );
   string_deep_dispose( &separator );
   date_time_dispose( &dt1 );
   date_time_duration_dispose( &dtd );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_format_2a
*/

void test_format_2a( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *end_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   string_t *result = NULL;
   date_time_duration_t *dtd = NULL;
   date_time_t *dt1 = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-[0]mm-[0]dd [0]hh:[0]mi:[0]ss.[0]mls" );
   end_format_string = string_make_from_cstring( "[0]H1:[0]MI:[0]SS.[0]MLS MD" );
   separator = string_make_from_cstring( " / " );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_end_time
         ( 
            start_format_string, 
            end_format_string, 
            separator 
         );
   
   dt1 = date_time_make( 2010, 1, 2, 10, 15, 0, 0 );
   dtd = date_time_duration_make_start_dhms( dt1, 0, 0, 15, 1, 2 );
   
   result = date_time_duration_formatter_parser_format( date_time_duration_formatter_parser, dtd );
   
   s = string_make_from_cstring( "2010-01-02 10:15:00.000 / 10:30:01.002 AM" );
   
   CU_ASSERT( string_is_equal( s, result ) == 1 );
   
   string_deep_dispose( &result );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &end_format_string );
   string_deep_dispose( &separator );
   date_time_dispose( &dt1 );
   date_time_duration_dispose( &dtd );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_format_2b
*/

void test_format_2b( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *end_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   string_t *result = NULL;
   date_time_duration_t *dtd = NULL;
   date_time_t *dt1 = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-[0]mm-[0]dd [0]hh:[0]mi:[0]ss.[0]mls" );
   end_format_string = string_make_from_cstring( "[0]H1:[0]MI:[0]SS.[0]MLS MD" );
   separator = string_make_from_cstring( " / " );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_end_time
         ( 
            start_format_string, 
            end_format_string, 
            separator 
         );
   
   dt1 = date_time_make( 2010, 1, 2, 10, 15, 0, 0 );
   dtd = date_time_duration_make_start_dhms( dt1, 0, 3, 15, 1, 2 );
   
   result = date_time_duration_formatter_parser_format( date_time_duration_formatter_parser, dtd );
   
   s = string_make_from_cstring( "2010-01-02 10:15:00.000 / 01:30:01.002 PM" );
   
   CU_ASSERT( string_is_equal( s, result ) == 1 );
   
   string_deep_dispose( &result );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &end_format_string );
   string_deep_dispose( &separator );
   date_time_dispose( &dt1 );
   date_time_duration_dispose( &dtd );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_format_2c
*/

void test_format_2c( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *end_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   string_t *result = NULL;
   date_time_duration_t *dtd = NULL;
   date_time_t *dt1 = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-[0]mm-[0]dd [0]hh:[0]mi:[0]ss.[0]mls" );
   end_format_string = string_make_from_cstring( "HHh MIm SSs MLSms" );
   separator = string_make_from_cstring( " / " );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_end_time
         ( 
            start_format_string, 
            end_format_string, 
            separator 
         );
   
   dt1 = date_time_make( 2010, 1, 2, 10, 15, 0, 0 );
   dtd = date_time_duration_make_start_dhms( dt1, 0, 3, 15, 1, 2 );
   
   result = date_time_duration_formatter_parser_format( date_time_duration_formatter_parser, dtd );
   
   s = string_make_from_cstring( "2010-01-02 10:15:00.000 / 13h 30m 1s 2ms" );
   
   CU_ASSERT( string_is_equal( s, result ) == 1 );
   
   string_deep_dispose( &result );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &end_format_string );
   string_deep_dispose( &separator );
   date_time_dispose( &dt1 );
   date_time_duration_dispose( &dtd );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_format_2d
*/

void test_format_2d( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *end_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   string_t *result = NULL;
   date_time_duration_t *dtd = NULL;
   date_time_t *dt1 = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-[0]mm-[0]dd [0]hh:[0]mi:[0]ss.[0]mls" );
   end_format_string = string_make_from_cstring( "H1h MIm SSs MLSms MD" );
   separator = string_make_from_cstring( " / " );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_end_time
         ( 
            start_format_string, 
            end_format_string, 
            separator 
         );
   
   dt1 = date_time_make( 2010, 1, 2, 10, 15, 0, 0 );
   dtd = date_time_duration_make_start_dhms( dt1, 0, 3, 15, 1, 2 );
   
   result = date_time_duration_formatter_parser_format( date_time_duration_formatter_parser, dtd );
   
   s = string_make_from_cstring( "2010-01-02 10:15:00.000 / 1h 30m 1s 2ms PM" );
   
   CU_ASSERT( string_is_equal( s, result ) == 1 );
   
   string_deep_dispose( &result );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &end_format_string );
   string_deep_dispose( &separator );
   date_time_dispose( &dt1 );
   date_time_duration_dispose( &dtd );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_format_2e
*/

void test_format_2e( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *end_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   string_t *result = NULL;
   date_time_duration_t *dtd = NULL;
   date_time_t *dt1 = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-[0]mm-[0]dd  ddd [0]hh:[0]mi" );
   end_format_string = string_make_from_cstring( "[0]HH:[0]MI" );
   separator = string_make_from_cstring( "-" );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_end_time
         ( 
            start_format_string, 
            end_format_string, 
            separator 
         );
   
   dt1 = date_time_make( 2010, 1, 2, 10, 15, 0, 0 );
   dtd = date_time_duration_make_start_dhms( dt1, 0, 3, 15, 1, 2 );
   
   result = date_time_duration_formatter_parser_format( date_time_duration_formatter_parser, dtd );
   
   s = string_make_from_cstring( "2010-01-02  Sat 10:15-13:30" );
   
   CU_ASSERT( string_is_equal( s, result ) == 1 );
   
   string_deep_dispose( &result );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &end_format_string );
   string_deep_dispose( &separator );
   date_time_dispose( &dt1 );
   date_time_duration_dispose( &dtd );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_format_2f
*/

void test_format_2f( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *end_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   string_t *result = NULL;
   date_time_duration_t *dtd = NULL;
   date_time_t *dt1 = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-[0]mm-[0]dd  ddd [0]hh:[0]mi" );
   end_format_string = string_make_from_cstring( "" );
   separator = string_make_from_cstring( "-" );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_end_time
         ( 
            start_format_string, 
            end_format_string, 
            separator 
         );
   
   dt1 = date_time_make( 2010, 1, 2, 10, 15, 0, 0 );
   dtd = date_time_duration_make_start_dhms( dt1, 0, 3, 15, 1, 2 );
   
   result = date_time_duration_formatter_parser_format( date_time_duration_formatter_parser, dtd );
   
   s = string_make_from_cstring( "2010-01-02  Sat 10:15-" );
   
   CU_ASSERT( string_is_equal( s, result ) == 1 );
   
   string_deep_dispose( &result );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &end_format_string );
   string_deep_dispose( &separator );
   date_time_dispose( &dt1 );
   date_time_duration_dispose( &dtd );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_format_3
*/

void test_format_3( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *duration_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   string_t *result = NULL;
   date_time_duration_t *dtd = NULL;
   date_time_t *dt1 = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-[0]mm-[0]dd [0]hh:[0]mi:[0]ss.[0]mls" );
   duration_format_string = string_make_from_cstring( "*DDdHHhMImSS.[0]MLSs" );
   separator = string_make_from_cstring( " / " );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_duration
         ( 
            start_format_string, 
            duration_format_string, 
            separator 
         );
   
   dt1 = date_time_make( 2010, 1, 2, 10, 15, 0, 0 );
   dtd = date_time_duration_make_start_dhms( dt1, 0, 0, 15, 0, 0 );
   
   result = date_time_duration_formatter_parser_format( date_time_duration_formatter_parser, dtd );

   s = string_make_from_cstring( "2010-01-02 10:15:00.000 / 0d0h15m0.000s" );
   
   CU_ASSERT( string_is_equal( s, result ) == 1 );
   
   string_deep_dispose( &result );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &duration_format_string );
   string_deep_dispose( &separator );
   date_time_dispose( &dt1 );
   date_time_duration_dispose( &dtd );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_format_3a
*/

void test_format_3a( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *duration_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   string_t *result = NULL;
   date_time_duration_t *dtd = NULL;
   date_time_t *dt1 = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-[0]mm-[0]dd [0]hh:[0]mi:[0]ss.[0]mls" );
   duration_format_string = string_make_from_cstring( "*HHhMImSS.[0]MLSs" );
   separator = string_make_from_cstring( " / " );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_duration
         ( 
            start_format_string, 
            duration_format_string, 
            separator 
         );
   
   dt1 = date_time_make( 2010, 1, 2, 10, 15, 0, 0 );
   dtd = date_time_duration_make_start_dhms( dt1, 0, 0, 15, 0, 0 );
   
   result = date_time_duration_formatter_parser_format( date_time_duration_formatter_parser, dtd );

   s = string_make_from_cstring( "2010-01-02 10:15:00.000 / 0h15m0.000s" );
   
   CU_ASSERT( string_is_equal( s, result ) == 1 );
   
   string_deep_dispose( &result );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &duration_format_string );
   string_deep_dispose( &separator );
   date_time_dispose( &dt1 );
   date_time_duration_dispose( &dtd );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_format_3b
*/

void test_format_3b( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *duration_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   string_t *result = NULL;
   date_time_duration_t *dtd = NULL;
   date_time_t *dt1 = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-[0]mm-[0]dd [0]hh:[0]mi:[0]ss.[0]mls" );
   duration_format_string = string_make_from_cstring( "*MImSS.[0]MLSs" );
   separator = string_make_from_cstring( " / " );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_duration
         ( 
            start_format_string, 
            duration_format_string, 
            separator 
         );
   
   dt1 = date_time_make( 2010, 1, 2, 10, 15, 0, 0 );
   dtd = date_time_duration_make_start_dhms( dt1, 0, 0, 15, 0, 0 );
   
   result = date_time_duration_formatter_parser_format( date_time_duration_formatter_parser, dtd );

   s = string_make_from_cstring( "2010-01-02 10:15:00.000 / 15m0.000s" );
   
   CU_ASSERT( string_is_equal( s, result ) == 1 );
   
   string_deep_dispose( &result );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &duration_format_string );
   string_deep_dispose( &separator );
   date_time_dispose( &dt1 );
   date_time_duration_dispose( &dtd );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_format_3c
*/

void test_format_3c( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *duration_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   string_t *result = NULL;
   date_time_duration_t *dtd = NULL;
   date_time_t *dt1 = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-[0]mm-[0]dd [0]hh:[0]mi:[0]ss.[0]mls" );
   duration_format_string = string_make_from_cstring( "*SS.[0]MLSs" );
   separator = string_make_from_cstring( " / " );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_duration
         ( 
            start_format_string, 
            duration_format_string, 
            separator 
         );
   
   dt1 = date_time_make( 2010, 1, 2, 10, 15, 0, 0 );
   dtd = date_time_duration_make_start_dhms( dt1, 0, 0, 0, 2, 0 );
   
   result = date_time_duration_formatter_parser_format( date_time_duration_formatter_parser, dtd );

   s = string_make_from_cstring( "2010-01-02 10:15:00.000 / 2.000s" );
   
   CU_ASSERT( string_is_equal( s, result ) == 1 );
   
   string_deep_dispose( &result );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &duration_format_string );
   string_deep_dispose( &separator );
   date_time_dispose( &dt1 );
   date_time_duration_dispose( &dtd );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_format_3d
*/

void test_format_3d( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *duration_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   string_t *result = NULL;
   date_time_duration_t *dtd = NULL;
   date_time_t *dt1 = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-[0]mm-[0]dd [0]hh:[0]mi:[0]ss.[0]mls" );
   duration_format_string = string_make_from_cstring( "*MLSms" );
   separator = string_make_from_cstring( " / " );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_duration
         ( 
            start_format_string, 
            duration_format_string, 
            separator 
         );
   
   dt1 = date_time_make( 2010, 1, 2, 10, 15, 0, 0 );
   dtd = date_time_duration_make_start_dhms( dt1, 0, 0, 0, 0, 12 );
   
   result = date_time_duration_formatter_parser_format( date_time_duration_formatter_parser, dtd );

   s = string_make_from_cstring( "2010-01-02 10:15:00.000 / 12ms" );
   
   CU_ASSERT( string_is_equal( s, result ) == 1 );
   
   string_deep_dispose( &result );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &duration_format_string );
   string_deep_dispose( &separator );
   date_time_dispose( &dt1 );
   date_time_duration_dispose( &dtd );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_format_3e
*/

void test_format_3e( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *duration_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   string_t *result = NULL;
   date_time_duration_t *dtd = NULL;
   date_time_t *dt1 = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-[0]mm-[0]dd [0]hh:[0]mi:[0]ss.[0]mls" );
   duration_format_string = string_make_from_cstring( "*SSs MLSms" );
   separator = string_make_from_cstring( " / " );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_duration
         ( 
            start_format_string, 
            duration_format_string, 
            separator 
         );
   
   dt1 = date_time_make( 2010, 1, 2, 10, 15, 0, 0 );
   dtd = date_time_duration_make_start_dhms( dt1, 0, 0, 0, 2, 0 );
   
   result = date_time_duration_formatter_parser_format( date_time_duration_formatter_parser, dtd );

   s = string_make_from_cstring( "2010-01-02 10:15:00.000 / 2s 0ms" );
   
   CU_ASSERT( string_is_equal( s, result ) == 1 );
   
   string_deep_dispose( &result );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &duration_format_string );
   string_deep_dispose( &separator );
   date_time_dispose( &dt1 );
   date_time_duration_dispose( &dtd );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_format_3f
*/

void test_format_3f( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *duration_format_string = NULL;
   string_t *separator = NULL;
   string_t *s = NULL;
   string_t *result = NULL;
   date_time_duration_t *dtd = NULL;
   date_time_t *dt1 = NULL;
   
   start_format_string = string_make_from_cstring( "yyyy-[0]mm-[0]dd [0]hh:[0]mi:[0]ss.[0]mls" );
   duration_format_string = string_make_from_cstring( "*MLSms" );
   separator = string_make_from_cstring( " / " );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_duration
         ( 
            start_format_string, 
            duration_format_string, 
            separator 
         );
   
   dt1 = date_time_make( 2010, 1, 2, 10, 15, 0, 0 );
   dtd = date_time_duration_make_start_dhms( dt1, 0, 0, 0, 2, 0 );
   
   result = date_time_duration_formatter_parser_format( date_time_duration_formatter_parser, dtd );

   s = string_make_from_cstring( "2010-01-02 10:15:00.000 / 2000ms" );
   
   CU_ASSERT( string_is_equal( s, result ) == 1 );
   
   string_deep_dispose( &result );
   string_deep_dispose( &s );
 
   string_deep_dispose( &start_format_string );
   string_deep_dispose( &duration_format_string );
   string_deep_dispose( &separator );
   date_time_dispose( &dt1 );
   date_time_duration_dispose( &dtd );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

/**
   test_format_4
*/

void test_format_4( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *duration_format_string = NULL;
   string_t *s = NULL;
   string_t *result = NULL;
   date_time_duration_t *dtd = NULL;
   
   duration_format_string = string_make_from_cstring( "*DDd HHh MIm SS.[0]MLSs" );
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_duration
         ( 
            duration_format_string
         );
   
   dtd = date_time_duration_make_dhms( 1, 3, 14, 1, 123 );
   
   result = date_time_duration_formatter_parser_format( date_time_duration_formatter_parser, dtd );
   
   s = string_make_from_cstring( "1d 3h 14m 1.123s" );
   
   CU_ASSERT( string_is_equal( s, result ) == 1 );
   
   string_deep_dispose( &result );
   string_deep_dispose( &s );
 
   string_deep_dispose( &duration_format_string );
   date_time_duration_dispose( &dtd );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}


int
add_test_format( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_format", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_format_1
   add_test_to_suite( p_suite, test_format_1, "test_format_1" );

   // test_format_2
   add_test_to_suite( p_suite, test_format_2, "test_format_2" );

   // test_format_2a
   add_test_to_suite( p_suite, test_format_2a, "test_format_2a" );

   // test_format_2b
   add_test_to_suite( p_suite, test_format_2b, "test_format_2b" );

   // test_format_2c
   add_test_to_suite( p_suite, test_format_2c, "test_format_2c" );

   // test_format_2d
   add_test_to_suite( p_suite, test_format_2d, "test_format_2d" );

   // test_format_2e
   add_test_to_suite( p_suite, test_format_2e, "test_format_2e" );

   // test_format_2f
   add_test_to_suite( p_suite, test_format_2f, "test_format_2f" );

   // test_format_3
   add_test_to_suite( p_suite, test_format_3, "test_format_3" );

   // test_format_3a
   add_test_to_suite( p_suite, test_format_3a, "test_format_3a" );

   // test_format_3b
   add_test_to_suite( p_suite, test_format_3b, "test_format_3b" );

   // test_format_3c
   add_test_to_suite( p_suite, test_format_3c, "test_format_3c" );

   // test_format_3d
   add_test_to_suite( p_suite, test_format_3d, "test_format_3d" );

   // test_format_3e
   add_test_to_suite( p_suite, test_format_3e, "test_format_3e" );

   // test_format_3f
   add_test_to_suite( p_suite, test_format_3f, "test_format_3f" );

   // test_format_4
   add_test_to_suite( p_suite, test_format_4, "test_format_4" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

