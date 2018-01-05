/**
 @file raw_buffer_test_clear.c
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
   test_clear_1
*/

void test_clear_1( void )
{
   raw_buffer_t *raw_buffer = raw_buffer_make( 16 );

   raw_buffer_put_int32( raw_buffer, 654321, 0 );
   raw_buffer_put_int32( raw_buffer, 123456, 8 );
   
   raw_buffer_clear( raw_buffer );
   
   CU_ASSERT( raw_buffer_read_int32( raw_buffer, 0 ) == 0 );
   CU_ASSERT( raw_buffer_read_int32( raw_buffer, 8 ) == 0 );

   raw_buffer_dispose_with_contents( raw_buffer );

   return;
}



int
add_test_clear( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_clear", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_clear_1
   add_test_to_suite( p_suite, test_clear_1, "test_clear_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

