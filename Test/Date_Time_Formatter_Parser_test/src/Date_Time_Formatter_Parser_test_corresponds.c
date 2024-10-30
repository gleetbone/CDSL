/**
 @file date_time_formatter_parser_test_corresponds.c
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
   test_corresponds_1
*/

void test_corresponds_1( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yyyy-mm-dd hh:mi:ss.[0]mls" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "2010-10-01 13:45:50.123" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_corresponds_2
*/

void test_corresponds_2( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yyyy-mm-dd hh:mi:ss.[0]mls" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "2010-10-01 13: 5:50.123" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_corresponds_3
*/

void test_corresponds_3( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yyyy-mm-dd" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "   0-01-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2000-01-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2004-01-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "1900-01-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2000-02-29" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2001-02-28" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2001-02-29" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2001-01-31" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2001-04-30" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_corresponds_4
*/

void test_corresponds_4( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yyyy-mm-dd" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "2345-01-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( " 345-01-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "  45-01-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "   5-01-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_corresponds_5
*/

void test_corresponds_5( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yy-mm-dd" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "45-01-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( " 5-01-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
 
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_corresponds_6
*/

void test_corresponds_6( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yyyy-mm-dd" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "2345-01-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2345- 1-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2001-13-29" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
 
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_corresponds_7
*/

void test_corresponds_7( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yyyy-[0]mm-dd" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "2345-01-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2345- 1-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2001-13-29" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2345-01- 1" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2345-01-32" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
 
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_corresponds_8
*/

void test_corresponds_8( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yyyy-mmm-dd" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "2345-Jan-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2345-Feb-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2345-Mar-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2345-Apr-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2345-May-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2345-Jun-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2345-Jul-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2345-Aug-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2345-Sep-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2345-Oct-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2345-Nov-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2345-Dec-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_corresponds_9
*/

void test_corresponds_9( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yyyy-mm-[0]dd" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "2345-01-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2345-01- 1" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2001-12-32" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
 
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_corresponds_10
*/

void test_corresponds_10( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yyyy-mm-dd ddd" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "2010-01-01 Fri" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2010-01-02 Sat" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2010-01-03 Sun" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2010-01-04 Mon" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2010-01-05 Tue" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2010-01-06 Wed" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2010-01-07 Thu" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_corresponds_11
*/

void test_corresponds_11( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yyyy-mm-dd hh" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "2010-01-01 11" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2010-01-02  7" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2010-01-03 26" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
 
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_corresponds_12
*/

void test_corresponds_12( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yyyy-mm-dd [0]hh" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "2010-01-01 11" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2010-01-02  7" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2010-01-03 26" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
 
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_corresponds_13
*/

void test_corresponds_13( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yyyy-mm-dd h1 md" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "2010-01-01 11 AM" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2010-01-02  7 PM" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2010-01-03 13 AM" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2010-01-03 26 PM" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
 
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_corresponds_14
*/

void test_corresponds_14( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yyyy-mm-dd [0]h1 md" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "2010-01-01 11 AM" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2010-01-02  7 PM" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2010-01-03 26 AM" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
 
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_corresponds_15
*/

void test_corresponds_15( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yyyy-mm-dd hh:mi" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "2010-01-01 11:25" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2010-01-02  7:61" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
  
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_corresponds_16
*/

void test_corresponds_16( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yyyy-mm-dd hh:[0]mi" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "2010-01-01 11:25" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2010-01-02  17: 1" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
  
   s = string_make_from_cstring( "2010-01-02  7:61" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
  
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_corresponds_17
*/

void test_corresponds_17( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yyyy-mm-dd hh:mi:ss" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "2010-01-01 11:25:20" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2010-01-01 11:25: 2" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2010-01-02  7:25:65" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
  
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_corresponds_18
*/

void test_corresponds_18( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yyyy-mm-dd hh:mi:[0]ss" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "2010-01-01 11:25:20" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2010-01-01 11:25: 2" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2010-01-02  7:25:65" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
  
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_corresponds_19
*/

void test_corresponds_19( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yyyy-mm-dd hh:mi:ss.[0]mls" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "2010-01-01 11:25:20.123" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2010-01-01 11:25:22. 23" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
 
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_corresponds_20
*/

void test_corresponds_20( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yy-mm-dd" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "20-01-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "2C-01-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
 
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_corresponds_21
*/

void test_corresponds_21( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yy-mmm-dd" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "20-Jan-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "20-Xub-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
 
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_corresponds_22
*/

void test_corresponds_22( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yy-mmm-dd ddd" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "10-Jan-01 Fri" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "10-Jan-01 Zgy" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
 
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_corresponds_23
*/

void test_corresponds_23( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yy-mmm-dd h1 md" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "10-Jan-01 12 AM" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "10-Jan-01 11 FM" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
 
   s = string_make_from_cstring( "10-Jan-01 11 PM" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 1 );
   string_deep_dispose( &s );
 
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_corresponds_24
*/

void test_corresponds_24( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yy-mmm-dd h1" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "10-Jan-01 12" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
  
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

/**
   test_corresponds_25
*/

void test_corresponds_25( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   string_t *s = NULL;
   
   format_string = string_make_from_cstring( "yy-mmm-dd hh md" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   s = string_make_from_cstring( "10-Jan-01 15 AM" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
  
   s = string_make_from_cstring( "10-Jan-01" );
   CU_ASSERT( date_time_formatter_parser_corresponds( date_time_formatter_parser, s ) == 0 );
   string_deep_dispose( &s );
  
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

int
add_test_corresponds( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_corresponds", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_corresponds_1
   add_test_to_suite( p_suite, test_corresponds_1, "test_corresponds_1" );

   // test_corresponds_2
   add_test_to_suite( p_suite, test_corresponds_2, "test_corresponds_2" );

   // test_corresponds_3
   add_test_to_suite( p_suite, test_corresponds_3, "test_corresponds_3" );

   // test_corresponds_4
   add_test_to_suite( p_suite, test_corresponds_4, "test_corresponds_4" );

   // test_corresponds_5
   add_test_to_suite( p_suite, test_corresponds_5, "test_corresponds_5" );

   // test_corresponds_6
   add_test_to_suite( p_suite, test_corresponds_6, "test_corresponds_6" );

   // test_corresponds_7
   add_test_to_suite( p_suite, test_corresponds_7, "test_corresponds_7" );

   // test_corresponds_8
   add_test_to_suite( p_suite, test_corresponds_8, "test_corresponds_8" );

   // test_corresponds_9
   add_test_to_suite( p_suite, test_corresponds_9, "test_corresponds_9" );

   // test_corresponds_10
   add_test_to_suite( p_suite, test_corresponds_10, "test_corresponds_10" );

   // test_corresponds_11
   add_test_to_suite( p_suite, test_corresponds_11, "test_corresponds_11" );

   // test_corresponds_12
   add_test_to_suite( p_suite, test_corresponds_12, "test_corresponds_12" );

   // test_corresponds_13
   add_test_to_suite( p_suite, test_corresponds_13, "test_corresponds_13" );

   // test_corresponds_14
   add_test_to_suite( p_suite, test_corresponds_14, "test_corresponds_14" );

   // test_corresponds_15
   add_test_to_suite( p_suite, test_corresponds_15, "test_corresponds_15" );

   // test_corresponds_16
   add_test_to_suite( p_suite, test_corresponds_16, "test_corresponds_16" );

   // test_corresponds_17
   add_test_to_suite( p_suite, test_corresponds_17, "test_corresponds_17" );

   // test_corresponds_18
   add_test_to_suite( p_suite, test_corresponds_18, "test_corresponds_18" );

   // test_corresponds_19
   add_test_to_suite( p_suite, test_corresponds_19, "test_corresponds_19" );

   // test_corresponds_20
   add_test_to_suite( p_suite, test_corresponds_20, "test_corresponds_20" );

   // test_corresponds_21
   add_test_to_suite( p_suite, test_corresponds_21, "test_corresponds_21" );

   // test_corresponds_22
   add_test_to_suite( p_suite, test_corresponds_22, "test_corresponds_22" );

   // test_corresponds_23
   add_test_to_suite( p_suite, test_corresponds_23, "test_corresponds_23" );

   // test_corresponds_24
   add_test_to_suite( p_suite, test_corresponds_24, "test_corresponds_24" );

   // test_corresponds_25
   add_test_to_suite( p_suite, test_corresponds_25, "test_corresponds_25" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

