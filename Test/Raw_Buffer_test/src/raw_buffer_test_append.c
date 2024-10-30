/**
 @file raw_buffer_test_append.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for raw_buffer_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for raw_buffer_t

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
   test_append_1
*/

void test_append_1( void )
{
   raw_buffer_t *raw_buffer1 = raw_buffer_make( 16 );
   raw_buffer_t *raw_buffer2 = raw_buffer_make( 16 );

   raw_buffer_append( raw_buffer1, raw_buffer2 );
   
   CU_ASSERT( raw_buffer_count( raw_buffer1 ) == 32 );
   
   raw_buffer_deep_dispose( &raw_buffer1 );
   raw_buffer_deep_dispose( &raw_buffer2 );

   return;
}


/**
   test_append_2
*/

void test_append_2( void )
{
   raw_buffer_t *raw_buffer1 = raw_buffer_make( 16 );
   raw_buffer_t *raw_buffer2 = raw_buffer_make( 16 );

   raw_buffer_put_int32( raw_buffer1, 654321, 0 );
   raw_buffer_put_int32( raw_buffer1, 123456, 8 );
   
   raw_buffer_put_int32( raw_buffer2, 7654321, 0 );
   raw_buffer_put_int32( raw_buffer2, 1234567, 8 );
   
   raw_buffer_append( raw_buffer1, raw_buffer2 );
   
   CU_ASSERT( raw_buffer_count( raw_buffer1 ) == 32 );
   CU_ASSERT( raw_buffer_read_int32( raw_buffer1, 0 ) == 654321 );
   CU_ASSERT( raw_buffer_read_int32( raw_buffer1, 8 ) == 123456 );
   CU_ASSERT( raw_buffer_read_int32( raw_buffer1, 16 ) == 7654321 );
   CU_ASSERT( raw_buffer_read_int32( raw_buffer1, 24 ) == 1234567 );
   
   raw_buffer_deep_dispose( &raw_buffer1 );
   raw_buffer_deep_dispose( &raw_buffer2 );

   return;
}



int
add_test_append( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_append", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_append_1
   add_test_to_suite( p_suite, test_append_1, "test_append_1" );

   // test_append_2
   add_test_to_suite( p_suite, test_append_2, "test_append_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

