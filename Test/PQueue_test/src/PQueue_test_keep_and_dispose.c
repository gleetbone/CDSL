/**
 @file PQueue_test_keep_and_dispose.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for PQueue_put"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for PQueue_item_at.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "int_PQueue.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_keep_and_dispose_1
*/

void test_keep_and_dispose_1( void )
{
   int_pqueue_t *pqueue = NULL;

   pqueue = int_pqueue_make();

   int_pqueue_put( pqueue, 24 );

   CU_ASSERT( int_pqueue_count( pqueue ) == 1 );

   int_pqueue_keep_and_dispose( pqueue, 1 );

   CU_ASSERT( int_pqueue_count( pqueue ) == 1 );

   int_pqueue_keep_and_dispose( pqueue, 0 );

   CU_ASSERT( int_pqueue_count( pqueue ) == 0 );

   int_pqueue_dispose( pqueue );

   return;
}

/**
   test_keep_and_dispose_2
*/

void test_keep_and_dispose_2( void )
{
   int_pqueue_t *pqueue = NULL;

   pqueue = int_pqueue_make();

   int_pqueue_put( pqueue, 24 );

   int_pqueue_put( pqueue, 7 );

   CU_ASSERT( int_pqueue_count( pqueue ) == 2 );

   int_pqueue_keep_and_dispose( pqueue, 1 );

   CU_ASSERT( int_pqueue_count( pqueue ) == 1 );

   int_pqueue_dispose( pqueue );

   return;
}

/**
   test_keep_and_dispose_3
*/

void test_keep_and_dispose_3( void )
{
   int_pqueue_t *pqueue = NULL;

   pqueue = int_pqueue_make();

   int_pqueue_put( pqueue, 24 );

   int_pqueue_put( pqueue, 7 );

   int_pqueue_put( pqueue, 13 );

   CU_ASSERT( int_pqueue_count( pqueue ) == 3 );

   int_pqueue_keep_and_dispose( pqueue, 2 );

   CU_ASSERT( int_pqueue_count( pqueue ) == 2 );

   int_pqueue_dispose( pqueue );

   return;
}

int
add_test_keep_and_dispose( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_keep_and_dispose", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_keep_and_dispose_1
   add_test_to_suite( p_suite, test_keep_and_dispose_1, "test_keep_and_dispose_1" );

   // test_keep_and_dispose_2
   add_test_to_suite( p_suite, test_keep_and_dispose_2, "test_keep_and_dispose_2" );

   // test_keep_and_dispose_3
   add_test_to_suite( p_suite, test_keep_and_dispose_3, "test_keep_and_dispose_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

