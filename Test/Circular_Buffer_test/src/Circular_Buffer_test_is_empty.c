/**
 @file Circular_Buffer_test_is_empty.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Circular_Buffer_put"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Circular_Buffer_t

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
   test_is_empty_1
*/

void test_is_empty_1( void )
{
   i_circular_buffer_t *circular_buffer = NULL;

   circular_buffer = i_circular_buffer_make( 4 );

   CU_ASSERT( i_circular_buffer_is_empty( circular_buffer ) == 1 );

   i_circular_buffer_put( circular_buffer, 24 );

   CU_ASSERT( i_circular_buffer_is_empty( circular_buffer ) == 0 );

   i_circular_buffer_forth( circular_buffer );

   CU_ASSERT( i_circular_buffer_is_empty( circular_buffer ) == 1 );

   i_circular_buffer_dispose( &circular_buffer );

   return;
}

int
add_test_is_empty( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_empty", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_empty_1
   add_test_to_suite( p_suite, test_is_empty_1, "test_is_empty_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

