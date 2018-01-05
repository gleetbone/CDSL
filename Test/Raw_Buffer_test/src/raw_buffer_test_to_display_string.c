/**
 @file raw_buffer_test_to_display_string.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for soa_node_iterator_make_str"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for soa_node_iterator_make_str.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "Raw_Buffer.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );


/**
   test_to_display_string_1
*/

void test_to_display_string_1( void )
{
   raw_buffer_t *raw_buffer = raw_buffer_make( 16 );
   raw_buffer_put_char( raw_buffer, 'A', 0 );
   raw_buffer_put_char( raw_buffer, 'B', 1 );
   raw_buffer_put_char( raw_buffer, 'C', 2 );
   raw_buffer_put_char( raw_buffer, 'D', 3 );

   raw_buffer_put_char( raw_buffer, 'E', 4 );
   raw_buffer_put_char( raw_buffer, 'F', 5 );
   raw_buffer_put_char( raw_buffer, 'G', 6 );
   raw_buffer_put_char( raw_buffer, 'H', 7 );

   raw_buffer_put_char( raw_buffer, 'I', 8 );
   raw_buffer_put_char( raw_buffer, 'J', 9 );
   raw_buffer_put_char( raw_buffer, 'K', 10 );
   raw_buffer_put_char( raw_buffer, 'L', 11 );

   raw_buffer_put_char( raw_buffer, 'M', 12 );
   raw_buffer_put_char( raw_buffer, 'N', 13 );
   raw_buffer_put_char( raw_buffer, 'O', 14 );
   raw_buffer_put_char( raw_buffer, 'P', 15 );
   
   string_t *string = raw_buffer_to_display_string( raw_buffer, 0, 16 );

   CU_ASSERT
   ( 
      string_is_equal_cstring
      ( 
         string, 
         "000: 41 42 43 44  45 46 47 48   49 4A 4B 4C  4D 4E 4F 50  ABCDEFGHIJKLMNOP\n" 
      ) == 1 
   );
      
   raw_buffer_dispose_with_contents( raw_buffer );
   string_dispose_with_contents( string );

   return;
}

/**
   test_to_display_string_2
*/

void test_to_display_string_2( void )
{
   raw_buffer_t *raw_buffer = raw_buffer_make( 80 );
   raw_buffer_put_char( raw_buffer, 'A', 0 );
   raw_buffer_put_char( raw_buffer, 'B', 1 );
   raw_buffer_put_char( raw_buffer, 'C', 2 );
   raw_buffer_put_char( raw_buffer, 'D', 3 );

   raw_buffer_put_char( raw_buffer, 'E', 4 );
   raw_buffer_put_char( raw_buffer, 'F', 5 );
   raw_buffer_put_char( raw_buffer, 'G', 6 );
   raw_buffer_put_char( raw_buffer, 'H', 7 );

   raw_buffer_put_char( raw_buffer, 'I', 8 );
   raw_buffer_put_char( raw_buffer, 'J', 9 );
   raw_buffer_put_char( raw_buffer, 'K', 10 );
   raw_buffer_put_char( raw_buffer, 'L', 11 );

   raw_buffer_put_char( raw_buffer, 'M', 12 );
   raw_buffer_put_char( raw_buffer, 'N', 13 );
   raw_buffer_put_char( raw_buffer, 'O', 14 );
   raw_buffer_put_char( raw_buffer, 'P', 15 );
   
   string_t *string = raw_buffer_to_display_string( raw_buffer, 0, 79 );

   CU_ASSERT( string_has_substring_cstring( string, " \n\n040:" ) == 1 );
   
   raw_buffer_dispose_with_contents( raw_buffer );
   string_dispose_with_contents( string );

   return;
}


int
add_test_to_display_string( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_to_display_string", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_to_display_string_1
   add_test_to_suite( p_suite, test_to_display_string_1, "test_to_display_string_1" );

   // test_to_display_string_2
   add_test_to_suite( p_suite, test_to_display_string_2, "test_to_display_string_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

