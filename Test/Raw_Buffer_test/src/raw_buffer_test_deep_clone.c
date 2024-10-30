/**
 @file raw_buffer_test_deep_clone.c
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
   test_deep_clone_1
*/

void test_deep_clone_1( void )
{
   raw_buffer_t *raw_buffer = raw_buffer_make( 1 );
   
   raw_buffer_t *rb1 = raw_buffer_deep_clone( raw_buffer );
   
   CU_ASSERT( rb1 != NULL );

   CU_ASSERT( raw_buffer_count( rb1 ) == 1 );
   CU_ASSERT( raw_buffer_base( rb1 ) != NULL );

   raw_buffer_deep_dispose( &raw_buffer );
   raw_buffer_deep_dispose( &rb1 );

   return;
}

/**
   test_deep_clone_2
*/

void test_deep_clone_2( void )
{
   raw_buffer_t *raw_buffer = raw_buffer_make( 16 );

   raw_buffer_put_int32( raw_buffer, 123456, 0 );
   
   raw_buffer_t *rb1 = raw_buffer_deep_clone( raw_buffer );
   
   CU_ASSERT( rb1 != NULL );

   CU_ASSERT( raw_buffer_count( rb1 ) == 16 );
   CU_ASSERT( raw_buffer_base( rb1 ) != NULL );

   CU_ASSERT( raw_buffer_read_int32( rb1, 0 ) == 123456 );
   CU_ASSERT( raw_buffer_read_int32( rb1, 8 ) == 0 );

   raw_buffer_deep_dispose( &raw_buffer );
   raw_buffer_deep_dispose( &rb1 );

   return;
}



int
add_test_deep_clone( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_deep_clone", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_deep_clone_1
   add_test_to_suite( p_suite, test_deep_clone_1, "test_deep_clone_1" );

   // test_deep_clone_2
   add_test_to_suite( p_suite, test_deep_clone_2, "test_deep_clone_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

