/**
 @file Deque_test_is_empty.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for Deque_put_first"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Deque_first_at.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_Deque.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_is_empty_1
*/

void test_is_empty_1( void )
{
   i_deque_t *deque = NULL;

   deque = i_deque_make();

   CU_ASSERT( i_deque_is_empty( deque ) == 1 );

   i_deque_put_first( deque, 24 );

   CU_ASSERT( i_deque_is_empty( deque ) == 0 );

   i_deque_dispose( deque );

   return;
}

void test_is_empty_2( void )
{
   i_deque_t *deque = NULL;

   deque = i_deque_make();

   CU_ASSERT( i_deque_is_empty( deque ) == 1 );

   i_deque_put_first( deque, 24 );

   CU_ASSERT( i_deque_is_empty( deque ) == 0 );

   i_deque_put_first( deque, 7 );

   CU_ASSERT( i_deque_is_empty( deque ) == 0 );

   i_deque_remove_first( deque );

   CU_ASSERT( i_deque_is_empty( deque ) == 0 );

   i_deque_remove_first( deque );

   CU_ASSERT( i_deque_is_empty( deque ) == 1 );

   i_deque_dispose( deque );

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

   // test_is_empty_2
   add_test_to_suite( p_suite, test_is_empty_2, "test_is_empty_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

