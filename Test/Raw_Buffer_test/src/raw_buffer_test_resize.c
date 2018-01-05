/**
 @file raw_buffer_test_resize.c
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
   test_resize_1
*/

void test_resize_1( void )
{
   raw_buffer_t *raw_buffer = raw_buffer_make( 1 );
   
   CU_ASSERT( raw_buffer != NULL );

   CU_ASSERT( raw_buffer_count( raw_buffer ) == 1 );
   CU_ASSERT( raw_buffer_base( raw_buffer ) != NULL );

   raw_buffer_resize( raw_buffer, 16 );

   CU_ASSERT( raw_buffer_count( raw_buffer ) == 16 );
   
   raw_buffer_resize( raw_buffer, 4 );

   CU_ASSERT( raw_buffer_count( raw_buffer ) == 4 );
   
   raw_buffer_dispose_with_contents( raw_buffer );

   return;
}

/**
   test_resize_2
*/

void test_resize_2( void )
{
   raw_buffer_t *raw_buffer = raw_buffer_make( 16 );
   
   CU_ASSERT( raw_buffer != NULL );

   CU_ASSERT( raw_buffer_count( raw_buffer ) == 16 );
   
   raw_buffer_put_int32( raw_buffer, 123456, 0 );
   raw_buffer_put_int32( raw_buffer, 654321, 8 );

   raw_buffer_resize( raw_buffer, 32 );

   CU_ASSERT( raw_buffer_count( raw_buffer ) == 32 );
   
   CU_ASSERT( raw_buffer_read_int32( raw_buffer, 0 ) == 123456 );
   CU_ASSERT( raw_buffer_read_int32( raw_buffer, 8 ) == 654321 );
   CU_ASSERT( raw_buffer_read_int32( raw_buffer, 16 ) == 0 );
   CU_ASSERT( raw_buffer_read_int32( raw_buffer, 24 ) == 0 );
   
   raw_buffer_dispose_with_contents( raw_buffer );

   return;
}



int
add_test_resize( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_resize", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_resize_1
   add_test_to_suite( p_suite, test_resize_1, "test_resize_1" );

   // test_resize_2
   add_test_to_suite( p_suite, test_resize_2, "test_resize_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

