/**
 @file Circular_Buffer_test_put.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for Circular_Buffer_put"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Circular_Buffer_item_at.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_Circular_Buffer.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_put_1
*/

void test_put_1( void )
{
   i_circular_buffer_t *circular_buffer = NULL;

   circular_buffer = i_circular_buffer_make( 4 );

   i_circular_buffer_put( circular_buffer, 24 );

   CU_ASSERT( i_circular_buffer_item( circular_buffer ) == 24 );

   CU_ASSERT( i_circular_buffer_count( circular_buffer ) == 1 );

   i_circular_buffer_dispose( circular_buffer );

   return;
}

void test_put_2( void )
{
   i_circular_buffer_t *circular_buffer = NULL;

   circular_buffer = i_circular_buffer_make( 4 );

   i_circular_buffer_put( circular_buffer, 24 );

   CU_ASSERT( i_circular_buffer_count( circular_buffer ) == 1 );

   CU_ASSERT( i_circular_buffer_item( circular_buffer ) == 24 );

   i_circular_buffer_put( circular_buffer, 7 );

   CU_ASSERT( i_circular_buffer_count( circular_buffer ) == 2 );

   CU_ASSERT( i_circular_buffer_item( circular_buffer ) == 24 );

   i_circular_buffer_forth( circular_buffer );

   CU_ASSERT( i_circular_buffer_item( circular_buffer ) == 7 );
   CU_ASSERT( i_circular_buffer_count( circular_buffer ) == 1 );

   i_circular_buffer_dispose( circular_buffer );

   return;
}

int
add_test_put( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_put", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_put_1
   add_test_to_suite( p_suite, test_put_1, "test_put_1" );

   // test_put_2
   add_test_to_suite( p_suite, test_put_2, "test_put_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

