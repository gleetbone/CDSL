/**
 @file date_time_formatter_parser_test_put_base_century.c
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
   test_put_base_century_1
*/

void test_put_base_century_1( void )
{
   date_time_formatter_parser_t *date_time_formatter_parser = NULL;
   string_t *format_string = NULL;
   
   format_string = string_make_from_cstring( "yyyy-mm-dd hh:mi:ss.[0]mls" );
   
   date_time_formatter_parser = date_time_formatter_parser_make( format_string );
   
   CU_ASSERT( date_time_formatter_parser != NULL );
   
   CU_ASSERT( date_time_formatter_parser_base_century( date_time_formatter_parser ) == 2000 );
   
   date_time_formatter_parser_put_base_century( date_time_formatter_parser, 1900 );
   
   CU_ASSERT( date_time_formatter_parser_base_century( date_time_formatter_parser ) == 1900 );
   
   string_deep_dispose( &format_string );
   date_time_formatter_parser_dispose( &date_time_formatter_parser );

   return;
}

int
add_test_put_base_century( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_put_base_century", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_put_base_century_1
   add_test_to_suite( p_suite, test_put_base_century_1, "test_put_base_century_1" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

