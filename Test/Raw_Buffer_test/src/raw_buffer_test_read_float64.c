/**
 @file raw_buffer_test_read_float64.c
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
   test_read_float64_1
*/

void test_read_float64_1( void )
{
   raw_buffer_t *raw_buffer = raw_buffer_make( 16 );
   
   float64_t value = raw_buffer_read_float64( raw_buffer, 0 );

   CU_ASSERT( value == 0 );
      
   raw_buffer_dispose_with_contents( raw_buffer );

   return;
}

/**
   test_read_float64_2
*/

void test_read_float64_2( void )
{
   raw_buffer_t *raw_buffer = raw_buffer_make( 16 );
   float64_t value = 0;
   
   raw_buffer_put_float64( raw_buffer, 3.125, 0 );
   value = raw_buffer_read_float64( raw_buffer, 0 );

   CU_ASSERT( value == 3.125 );
   
   raw_buffer_put_float64( raw_buffer, 3.125, 7 );
   value = raw_buffer_read_float64( raw_buffer, 7 );

   CU_ASSERT( value == 3.125 );
   
   raw_buffer_dispose_with_contents( raw_buffer );

   return;
}



int
add_test_read_float64( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_read_float64", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_read_float64_1
   add_test_to_suite( p_suite, test_read_float64_1, "test_read_float64_1" );

   // test_read_float64_2
   add_test_to_suite( p_suite, test_read_float64_2, "test_read_float64_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

