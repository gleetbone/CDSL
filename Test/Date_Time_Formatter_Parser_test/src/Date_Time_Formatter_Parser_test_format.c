/**
 @file date_time_formatter_parser_test_format.c
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
   test_format_1
*/

void test_format_1( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   date_time_t *dt = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yyyy-[0]mm-[0]dd [0]hh:[0]mi:[0]ss.[0]mls" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   dt = date_time_make( 2010, 10, 1, 13, 45, 50, 123 );
   
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   
   CU_ASSERT( string_is_equal_cstring( s, "2010-10-01 13:45:50.123" ) == 1 );
   
   string_deep_dispose( &format_string );
   string_deep_dispose( &s );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );
   date_time_dispose( &dt );

   return;
}

/**
   test_format_2
*/

void test_format_2( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   date_time_t *dt = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yyyy-mmm-[0]dd [0]hh:[0]mi:[0]ss.[0]mls" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   dt = date_time_make( 2010, 1, 1, 13, 45, 50, 123 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "2010-Jan-01 13:45:50.123" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   dt = date_time_make( 2010, 2, 1, 13, 45, 50, 123 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "2010-Feb-01 13:45:50.123" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   dt = date_time_make( 2010, 3, 1, 13, 45, 50, 123 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "2010-Mar-01 13:45:50.123" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   dt = date_time_make( 2010, 4, 1, 13, 45, 50, 123 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "2010-Apr-01 13:45:50.123" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   dt = date_time_make( 2010, 5, 1, 13, 45, 50, 123 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "2010-May-01 13:45:50.123" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   dt = date_time_make( 2010, 6, 1, 13, 45, 50, 123 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "2010-Jun-01 13:45:50.123" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   dt = date_time_make( 2010, 7, 1, 13, 45, 50, 123 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "2010-Jul-01 13:45:50.123" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   dt = date_time_make( 2010, 8, 1, 13, 45, 50, 123 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "2010-Aug-01 13:45:50.123" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   dt = date_time_make( 2010, 9, 1, 13, 45, 50, 123 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "2010-Sep-01 13:45:50.123" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   dt = date_time_make( 2010, 10, 1, 13, 45, 50, 123 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "2010-Oct-01 13:45:50.123" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   dt = date_time_make( 2010, 11, 1, 13, 45, 50, 123 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "2010-Nov-01 13:45:50.123" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   dt = date_time_make( 2010, 12, 1, 13, 45, 50, 123 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "2010-Dec-01 13:45:50.123" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_format_3
*/

void test_format_3( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   date_time_t *dt = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yyyy-[0]mm-[0]dd ddd" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   dt = date_time_make( 2010, 1, 1, 13, 45, 50, 123 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "2010-01-01 Fri" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   dt = date_time_make( 2010, 1, 2, 13, 45, 50, 123 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "2010-01-02 Sat" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   dt = date_time_make( 2010, 1, 3, 13, 45, 50, 123 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "2010-01-03 Sun" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   dt = date_time_make( 2010, 1, 4, 13, 45, 50, 123 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "2010-01-04 Mon" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   dt = date_time_make( 2010, 1, 5, 13, 45, 50, 123 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "2010-01-05 Tue" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   dt = date_time_make( 2010, 1, 6, 13, 45, 50, 123 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "2010-01-06 Wed" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   dt = date_time_make( 2010, 1, 7, 13, 45, 50, 123 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "2010-01-07 Thu" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_format_4
*/

void test_format_4( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   date_time_t *dt = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yyyy-[0]mm-[0]dd h1 md" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   dt = date_time_make( 2010, 1, 1, 11, 0, 0, 0 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "2010-01-01 11 AM" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   dt = date_time_make( 2010, 1, 1, 13, 0, 0, 0 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "2010-01-01  1 PM" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_format_5
*/

void test_format_5( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   date_time_t *dt = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yy-mm-dd" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   dt = date_time_make( 10, 1, 1, 0, 0, 0, 0 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "10- 1- 1" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_format_6
*/

void test_format_6( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   date_time_t *dt = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yy-mm-dd hh" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   dt = date_time_make( 10, 1, 1, 0, 0, 0, 0 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "10- 1- 1  0" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_format_7
*/

void test_format_7( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   date_time_t *dt = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yy-mm-dd [0]h1" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   dt = date_time_make( 10, 1, 1, 0, 0, 0, 0 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "10- 1- 1 00" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_format_8
*/

void test_format_8( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   date_time_t *dt = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yy-mm-dd hh:mi" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   dt = date_time_make( 10, 1, 1, 0, 0, 0, 0 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "10- 1- 1  0: 0" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_format_9
*/

void test_format_9( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   date_time_t *dt = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yy-mm-dd hh:mi:ss" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   dt = date_time_make( 10, 1, 1, 0, 0, 0, 0 );
   s = date_time_formatter_parser_format( date_time_formatter_parser, dt );
   CU_ASSERT( string_is_equal_cstring( s, "10- 1- 1  0: 0: 0" ) == 1 );
   string_deep_dispose( &s );
   date_time_dispose( &dt );
   
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

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

   // test_format_3
   add_test_to_suite( p_suite, test_format_3, "test_format_3" );

   // test_format_4
   add_test_to_suite( p_suite, test_format_4, "test_format_4" );

   // test_format_5
   add_test_to_suite( p_suite, test_format_5, "test_format_5" );

   // test_format_6
   add_test_to_suite( p_suite, test_format_6, "test_format_6" );

   // test_format_7
   add_test_to_suite( p_suite, test_format_7, "test_format_7" );

   // test_format_8
   add_test_to_suite( p_suite, test_format_8, "test_format_8" );

   // test_format_9
   add_test_to_suite( p_suite, test_format_9, "test_format_9" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

