/**
 @file Queue_test_prune.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for Queue_put"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Queue_item_at.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "int_Queue.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_prune_1
*/

void test_prune_1( void )
{
   int_queue_t *queue = NULL;

   queue = int_queue_make();

   int_queue_put( queue, 24 );

   CU_ASSERT( int_queue_count( queue ) == 1 );

   int_queue_prune( queue, 1 );

   CU_ASSERT( int_queue_count( queue ) == 0 );

   int_queue_dispose( queue );

   return;
}

/**
   test_prune_2
*/

void test_prune_2( void )
{
   int_queue_t *queue = NULL;

   queue = int_queue_make();

   int_queue_put( queue, 24 );

   int_queue_put( queue, 7 );

   CU_ASSERT( int_queue_count( queue ) == 2 );

   int_queue_prune( queue, 1 );

   CU_ASSERT( int_queue_count( queue ) == 1 );

   int_queue_dispose( queue );

   return;
}

/**
   test_prune_3
*/

void test_prune_3( void )
{
   int_queue_t *queue = NULL;

   queue = int_queue_make();

   int_queue_put( queue, 24 );

   int_queue_put( queue, 7 );

   int_queue_put( queue, 13 );

   CU_ASSERT( int_queue_count( queue ) == 3 );

   int_queue_prune( queue, 2 );

   CU_ASSERT( int_queue_count( queue ) == 1 );

   int_queue_dispose( queue );

   return;
}

int
add_test_prune( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_prune", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_prune_1
   add_test_to_suite( p_suite, test_prune_1, "test_prune_1" );

   // test_prune_2
   add_test_to_suite( p_suite, test_prune_2, "test_prune_2" );

   // test_prune_3
   add_test_to_suite( p_suite, test_prune_3, "test_prune_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

