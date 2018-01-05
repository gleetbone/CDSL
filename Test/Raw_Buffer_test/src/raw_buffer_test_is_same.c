/**
 @file raw_buffer_test_is_same.c
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
   test_is_same_1
*/

void test_is_same_1( void )
{
   raw_buffer_t *raw_buffer1 = raw_buffer_make( 1 );
   raw_buffer_t *raw_buffer2 = raw_buffer_make( 1 );
   
   CU_ASSERT( raw_buffer_is_same( raw_buffer1, raw_buffer2 ) == 0 );

   raw_buffer_dispose_with_contents( raw_buffer1 );
   raw_buffer_dispose_with_contents( raw_buffer2 );

   return;
}

/**
   test_is_same_2
*/

void test_is_same_2( void )
{
   raw_buffer_t *raw_buffer1 = raw_buffer_make( 101 );
   
   raw_buffer_t *raw_buffer2 
      =  raw_buffer_make_from_pointer
         ( 
               raw_buffer_base( raw_buffer1 ), 
               raw_buffer_count( raw_buffer1 ) 
         );
   
   CU_ASSERT( raw_buffer_is_same( raw_buffer1, raw_buffer2 ) == 1 );

   raw_buffer_dispose_with_contents( raw_buffer1 );
   raw_buffer_dispose( raw_buffer2 );

   return;
}



int
add_test_is_same( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_same", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_same_1
   add_test_to_suite( p_suite, test_is_same_1, "test_is_same_1" );

   // test_is_same_2
   add_test_to_suite( p_suite, test_is_same_2, "test_is_same_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

