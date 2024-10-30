/**
 @file date_time_duration_formatter_parser_test_is_equal.c
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
   test_is_equal_1
*/

void test_is_equal_1( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser1 = NULL;
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser2 = NULL;
   int32_t result = 0;
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_end_cstring
         ( 
            "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls", 
            "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls", 
            "//"
         );
   
   date_time_duration_formatter_parser1
      = date_time_duration_formatter_parser_clone
         (
            date_time_duration_formatter_parser
         );
         
   date_time_duration_formatter_parser2
      =  date_time_duration_formatter_parser_make_start_end_cstring
         ( 
            "yyyy-mm-dd [0]hh:[0]mi:[0]ss", 
            "yyyy-mm-dd [0]hh:[0]mi:[0]ss", 
            " ^ "
         );
   
   result 
      =  date_time_duration_formatter_parser_is_equal
         (
            date_time_duration_formatter_parser,
            date_time_duration_formatter_parser1
         );
         
   CU_ASSERT( result == 1 );
   
   result 
      =  date_time_duration_formatter_parser_is_equal
         (
            date_time_duration_formatter_parser,
            date_time_duration_formatter_parser2
         );
         
   CU_ASSERT( result == 0 );
   
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser1 );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser2 );

   return;
}

/**
   test_is_equal_2
*/

void test_is_equal_2( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser1 = NULL;
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser2 = NULL;
   int32_t result = 0;
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_duration_cstring
         ( 
            "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls", 
            "[0]HH:[0]MI:[0]SS.[0]MLS", 
            "//"
         );
   
   date_time_duration_formatter_parser1
      = date_time_duration_formatter_parser_clone
         (
            date_time_duration_formatter_parser
         );
         
   date_time_duration_formatter_parser2
      =  date_time_duration_formatter_parser_make_start_duration_cstring
         ( 
            "yyyy-mm-dd [0]hh:[0]mi:[0]ss", 
            "HH:[0]MI:[0]SS.[0]MLS", 
            " ^ "
         );
   date_time_duration_formatter_parser_put_base_century( date_time_duration_formatter_parser2, 1900 );
   
   result 
      =  date_time_duration_formatter_parser_is_equal
         (
            date_time_duration_formatter_parser,
            date_time_duration_formatter_parser1
         );
         
   CU_ASSERT( result == 1 );
   
   result 
      =  date_time_duration_formatter_parser_is_equal
         (
            date_time_duration_formatter_parser,
            date_time_duration_formatter_parser2
         );
         
   CU_ASSERT( result == 0 );
   
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser1 );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser2 );

   return;
}

/**
   test_is_equal_3
*/

void test_is_equal_3( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser1 = NULL;
   int32_t result = 0;
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_end_cstring
         ( 
            "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls", 
            "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls", 
            "//"
         );
   
   date_time_duration_formatter_parser1
      =  date_time_duration_formatter_parser_make_duration_cstring
         ( 
            "HH:[0]MI:[0]SS.[0]MLS"
         );
   
   result 
      =  date_time_duration_formatter_parser_is_equal
         (
            date_time_duration_formatter_parser,
            date_time_duration_formatter_parser1
         );
         
   CU_ASSERT( result == 0 );
   
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser1 );

   return;
}

/**
   test_is_equal_4
*/

void test_is_equal_4( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser1 = NULL;
   int32_t result = 0;
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_end_cstring
         ( 
            "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls", 
            "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls", 
            "//"
         );
   
   date_time_duration_formatter_parser1
      =  date_time_duration_formatter_parser_make_start_end_time_cstring
         ( 
            "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls", 
            "HH:[0]MI:[0]SS.[0]MLS",
            "//"
         );
   
   result 
      =  date_time_duration_formatter_parser_is_equal
         (
            date_time_duration_formatter_parser,
            date_time_duration_formatter_parser1
         );
         
   CU_ASSERT( result == 0 );
   
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser1 );

   return;
}

/**
   test_is_equal_5
*/

void test_is_equal_5( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   int32_t result = 0;
   
   date_time_duration_formatter_parser 
      =  date_time_duration_formatter_parser_make_start_end_cstring
         ( 
            "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls", 
            "yyyy-mm-dd [0]hh:[0]mi:[0]ss.[0]mls", 
            "//"
         );
   
   result 
      =  date_time_duration_formatter_parser_is_equal
         (
            date_time_duration_formatter_parser,
            date_time_duration_formatter_parser
         );
         
   CU_ASSERT( result == 1 );
   
   date_time_duration_formatter_parser_dispose( &date_time_duration_formatter_parser );

   return;
}

int
add_test_is_equal( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_equal", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_equal_1
   add_test_to_suite( p_suite, test_is_equal_1, "test_is_equal_1" );

   // test_is_equal_2
   add_test_to_suite( p_suite, test_is_equal_2, "test_is_equal_2" );

   // test_is_equal_3
   add_test_to_suite( p_suite, test_is_equal_3, "test_is_equal_3" );

   // test_is_equal_4
   add_test_to_suite( p_suite, test_is_equal_4, "test_is_equal_4" );

   // test_is_equal_5
   add_test_to_suite( p_suite, test_is_equal_5, "test_is_equal_5" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

