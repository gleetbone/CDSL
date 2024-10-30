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
   test_format_cstring_1
*/

void test_format_cstring_1( void )
{
   date_time_duration_formatter_parser_t *date_time_duration_formatter_parser = NULL;
   string_t *start_format_string = NULL;
   string_t *end_format_string = NULL;
   string_t *separator = NULL;
   char_t *result = NULL;
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
        
   result = date_time_duration_formatter_parser_format_cstring( date_time_duration_formatter_parser, dtd );
      
   s = string_make_from_cstring( "2010-01-02 10:15:30.001 / 2010-01-03 09:16:31.021" );
   
   CU_ASSERT( string_is_equal_cstring( s, result ) == 1 );
   
   free( result );
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

int
add_test_format_cstring( void )
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

   // test_format_cstring_1
   add_test_to_suite( p_suite, test_format_cstring_1, "test_format_cstring_1" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

