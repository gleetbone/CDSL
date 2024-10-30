/**
 @file date_time_formatter_parser_test_parse.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for date_time_formatter_parser_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for date_time_formatter_parser_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include "CUnit/Basic.h"

#include "Date_Time_Formatter_Parser.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_parse_1
*/

void test_parse_1( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   date_time_t *dt = NULL;
   date_time_t *dt1 = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yyyy-mm-dd hh:mi:ss.[0]mls" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "2010-10-01 13:45:50.123" );
   dt = date_time_formatter_parser_parse( date_time_formatter_parser, s );
   string_deep_dispose( &s );
 
   dt1 = date_time_make( 2010, 10, 1, 13, 45, 50, 123 );
   
   CU_ASSERT( date_time_is_equal( dt, dt1 ) == 1 );
   
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );
   date_time_dispose( &dt );
   date_time_dispose( &dt1 );

   return;
}

/**
   test_parse_2
*/

void test_parse_2( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   date_time_t *dt = NULL;
   date_time_t *dt1 = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yyyy-mmm-dd hh:mi:ss.[0]mls" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "2010-Jan-01 13:45:50.123" );
   dt = date_time_formatter_parser_parse( date_time_formatter_parser, s );
   string_deep_dispose( &s );
   dt1 = date_time_make( 2010, 1, 1, 13, 45, 50, 123 );
   CU_ASSERT( date_time_is_equal( dt, dt1 ) == 1 );
   date_time_dispose( &dt );
   date_time_dispose( &dt1 );
   
   s = string_make_from_cstring( "2010-Feb-01 13:45:50.123" );
   dt = date_time_formatter_parser_parse( date_time_formatter_parser, s );
   string_deep_dispose( &s );
   dt1 = date_time_make( 2010, 2, 1, 13, 45, 50, 123 );
   CU_ASSERT( date_time_is_equal( dt, dt1 ) == 1 );
   date_time_dispose( &dt );
   date_time_dispose( &dt1 );
   
   s = string_make_from_cstring( "2010-Mar-01 13:45:50.123" );
   dt = date_time_formatter_parser_parse( date_time_formatter_parser, s );
   string_deep_dispose( &s );
   dt1 = date_time_make( 2010, 3, 1, 13, 45, 50, 123 );
   CU_ASSERT( date_time_is_equal( dt, dt1 ) == 1 );
   date_time_dispose( &dt );
   date_time_dispose( &dt1 );
   
   s = string_make_from_cstring( "2010-Apr-01 13:45:50.123" );
   dt = date_time_formatter_parser_parse( date_time_formatter_parser, s );
   string_deep_dispose( &s );
   dt1 = date_time_make( 2010, 4, 1, 13, 45, 50, 123 );
   CU_ASSERT( date_time_is_equal( dt, dt1 ) == 1 );
   date_time_dispose( &dt );
   date_time_dispose( &dt1 );
   
   s = string_make_from_cstring( "2010-May-01 13:45:50.123" );
   dt = date_time_formatter_parser_parse( date_time_formatter_parser, s );
   string_deep_dispose( &s );
   dt1 = date_time_make( 2010, 5, 1, 13, 45, 50, 123 );
   CU_ASSERT( date_time_is_equal( dt, dt1 ) == 1 );
   date_time_dispose( &dt );
   date_time_dispose( &dt1 );
   
   s = string_make_from_cstring( "2010-Jun-01 13:45:50.123" );
   dt = date_time_formatter_parser_parse( date_time_formatter_parser, s );
   string_deep_dispose( &s );
   dt1 = date_time_make( 2010, 6, 1, 13, 45, 50, 123 );
   CU_ASSERT( date_time_is_equal( dt, dt1 ) == 1 );
   date_time_dispose( &dt );
   date_time_dispose( &dt1 );
   
   s = string_make_from_cstring( "2010-Jul-01 13:45:50.123" );
   dt = date_time_formatter_parser_parse( date_time_formatter_parser, s );
   string_deep_dispose( &s );
   dt1 = date_time_make( 2010, 7, 1, 13, 45, 50, 123 );
   CU_ASSERT( date_time_is_equal( dt, dt1 ) == 1 );
   date_time_dispose( &dt );
   date_time_dispose( &dt1 );
   
   s = string_make_from_cstring( "2010-Aug-01 13:45:50.123" );
   dt = date_time_formatter_parser_parse( date_time_formatter_parser, s );
   string_deep_dispose( &s );
   dt1 = date_time_make( 2010, 8, 1, 13, 45, 50, 123 );
   CU_ASSERT( date_time_is_equal( dt, dt1 ) == 1 );
   date_time_dispose( &dt );
   date_time_dispose( &dt1 );
   
   s = string_make_from_cstring( "2010-Sep-01 13:45:50.123" );
   dt = date_time_formatter_parser_parse( date_time_formatter_parser, s );
   string_deep_dispose( &s );
   dt1 = date_time_make( 2010, 9, 1, 13, 45, 50, 123 );
   CU_ASSERT( date_time_is_equal( dt, dt1 ) == 1 );
   date_time_dispose( &dt );
   date_time_dispose( &dt1 );
   
   s = string_make_from_cstring( "2010-Oct-01 13:45:50.123" );
   dt = date_time_formatter_parser_parse( date_time_formatter_parser, s );
   string_deep_dispose( &s );
   dt1 = date_time_make( 2010, 10, 1, 13, 45, 50, 123 );
   CU_ASSERT( date_time_is_equal( dt, dt1 ) == 1 );
   date_time_dispose( &dt );
   date_time_dispose( &dt1 );
   
   s = string_make_from_cstring( "2010-Nov-01 13:45:50.123" );
   dt = date_time_formatter_parser_parse( date_time_formatter_parser, s );
   string_deep_dispose( &s );
   dt1 = date_time_make( 2010, 11, 1, 13, 45, 50, 123 );
   CU_ASSERT( date_time_is_equal( dt, dt1 ) == 1 );
   date_time_dispose( &dt );
   date_time_dispose( &dt1 );
   
   s = string_make_from_cstring( "2010-Dec-01 13:45:50.123" );
   dt = date_time_formatter_parser_parse( date_time_formatter_parser, s );
   string_deep_dispose( &s );
   dt1 = date_time_make( 2010, 12, 1, 13, 45, 50, 123 );
   CU_ASSERT( date_time_is_equal( dt, dt1 ) == 1 );
   date_time_dispose( &dt );
   date_time_dispose( &dt1 );
   
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_parse_3
*/

void test_parse_3( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   date_time_t *dt = NULL;
   date_time_t *dt1 = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yyyy-mm-dd h1 md" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "2010-01-01 11 AM" );
   dt = date_time_formatter_parser_parse( date_time_formatter_parser, s );
   string_deep_dispose( &s );
   dt1 = date_time_make( 2010, 1, 1, 11, 0, 0, 0 );
   CU_ASSERT( date_time_is_equal( dt, dt1 ) == 1 );
   date_time_dispose( &dt );
   date_time_dispose( &dt1 );
   
   s = string_make_from_cstring( "2010-01-01  1 PM" );
   dt = date_time_formatter_parser_parse( date_time_formatter_parser, s );
   string_deep_dispose( &s );
   dt1 = date_time_make( 2010, 1, 1, 13, 0, 0, 0 );
   CU_ASSERT( date_time_is_equal( dt, dt1 ) == 1 );
   date_time_dispose( &dt );
   date_time_dispose( &dt1 );
   
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_parse_4
*/

void test_parse_4( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   date_time_t *dt = NULL;
   date_time_t *dt1 = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yy-mm-dd" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "10-01-01" );
   dt = date_time_formatter_parser_parse( date_time_formatter_parser, s );
   string_deep_dispose( &s );
   dt1 = date_time_make( 2010, 1, 1, 0, 0, 0, 0 );
   CU_ASSERT( date_time_is_equal( dt, dt1 ) == 1 );
   date_time_dispose( &dt );
   date_time_dispose( &dt1 );
   
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_parse_5
*/

void test_parse_5( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   date_time_t *dt = NULL;
   date_time_t *dt1 = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yy-[0]mm-dd" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "10-01-01" );
   dt = date_time_formatter_parser_parse( date_time_formatter_parser, s );
   string_deep_dispose( &s );
   dt1 = date_time_make( 2010, 1, 1, 0, 0, 0, 0 );
   CU_ASSERT( date_time_is_equal( dt, dt1 ) == 1 );
   date_time_dispose( &dt );
   date_time_dispose( &dt1 );
   
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_parse_6
*/

void test_parse_6( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   date_time_t *dt = NULL;
   date_time_t *dt1 = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yy-mm-[0]dd" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "10-01-01" );
   dt = date_time_formatter_parser_parse( date_time_formatter_parser, s );
   string_deep_dispose( &s );
   dt1 = date_time_make( 2010, 1, 1, 0, 0, 0, 0 );
   CU_ASSERT( date_time_is_equal( dt, dt1 ) == 1 );
   date_time_dispose( &dt );
   date_time_dispose( &dt1 );
   
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_parse_7
*/

void test_parse_7( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   date_time_t *dt = NULL;
   date_time_t *dt1 = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yy-mm-dd [0]hh" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "10-01-01 01" );
   dt = date_time_formatter_parser_parse( date_time_formatter_parser, s );
   string_deep_dispose( &s );
   dt1 = date_time_make( 2010, 1, 1, 1, 0, 0, 0 );
   CU_ASSERT( date_time_is_equal( dt, dt1 ) == 1 );
   date_time_dispose( &dt );
   date_time_dispose( &dt1 );
   
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_parse_8
*/

void test_parse_8( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   date_time_t *dt = NULL;
   date_time_t *dt1 = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yy-mm-dd [0]h1" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "10-01-01 01" );
   dt = date_time_formatter_parser_parse( date_time_formatter_parser, s );
   string_deep_dispose( &s );
   dt1 = date_time_make( 2010, 1, 1, 1, 0, 0, 0 );
   CU_ASSERT( date_time_is_equal( dt, dt1 ) == 1 );
   date_time_dispose( &dt );
   date_time_dispose( &dt1 );
   
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_parse_9
*/

void test_parse_9( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   date_time_t *dt = NULL;
   date_time_t *dt1 = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yy-mm-dd hh:[0]mi" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "10-01-01 01:01" );
   dt = date_time_formatter_parser_parse( date_time_formatter_parser, s );
   string_deep_dispose( &s );
   dt1 = date_time_make( 2010, 1, 1, 1, 1, 0, 0 );
   CU_ASSERT( date_time_is_equal( dt, dt1 ) == 1 );
   date_time_dispose( &dt );
   date_time_dispose( &dt1 );
   
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_parse_10
*/

void test_parse_10( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   date_time_t *dt = NULL;
   date_time_t *dt1 = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yy-mm-dd hh:mi:[0]ss" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "10-01-01 01:01:01" );
   dt = date_time_formatter_parser_parse( date_time_formatter_parser, s );
   string_deep_dispose( &s );
   dt1 = date_time_make( 2010, 1, 1, 1, 1, 1, 0 );
   CU_ASSERT( date_time_is_equal( dt, dt1 ) == 1 );
   date_time_dispose( &dt );
   date_time_dispose( &dt1 );
   
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

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

   // test_parse_3
   add_test_to_suite( p_suite, test_parse_3, "test_parse_3" );

   // test_parse_4
   add_test_to_suite( p_suite, test_parse_4, "test_parse_4" );

   // test_parse_5
   add_test_to_suite( p_suite, test_parse_5, "test_parse_5" );

   // test_parse_6
   add_test_to_suite( p_suite, test_parse_6, "test_parse_6" );

   // test_parse_7
   add_test_to_suite( p_suite, test_parse_7, "test_parse_7" );

   // test_parse_8
   add_test_to_suite( p_suite, test_parse_8, "test_parse_8" );

   // test_parse_9
   add_test_to_suite( p_suite, test_parse_9, "test_parse_9" );

   // test_parse_10
   add_test_to_suite( p_suite, test_parse_10, "test_parse_10" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

