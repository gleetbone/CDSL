/**
 @file PQueue_test_wipe_out.c
 @author Greg Lee
 @version 2.0.0
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
   test_wipe_out_1
*/

void test_wipe_out_1( void )
{
   int_pqueue_t *pqueue = NULL;

   pqueue = int_pqueue_make();

   int_pqueue_put( pqueue, 24 );

   CU_ASSERT( int_pqueue_count( pqueue ) == 1 );

   int_pqueue_wipe_out( pqueue );

   CU_ASSERT( int_pqueue_count( pqueue ) == 0 );

   int_pqueue_dispose( &pqueue );

   return;
}

/**
   test_wipe_out_2
*/

void test_wipe_out_2( void )
{
   int_pqueue_t *pqueue = NULL;

   pqueue = int_pqueue_make();

   int_pqueue_put( pqueue, 24 );

   int_pqueue_put( pqueue, 7 );

   CU_ASSERT( int_pqueue_count( pqueue ) == 2 );

   int_pqueue_wipe_out( pqueue );

   CU_ASSERT( int_pqueue_count( pqueue ) == 0 );

   int_pqueue_dispose( &pqueue );

   return;
}

/**
   test_wipe_out_3
*/

void test_wipe_out_3( void )
{
   int_pqueue_t *pqueue = NULL;

   pqueue = int_pqueue_make();

   int_pqueue_put( pqueue, 24 );

   int_pqueue_put( pqueue, 7 );

   int_pqueue_put( pqueue, 13 );

   CU_ASSERT( int_pqueue_count( pqueue ) == 3 );

   int_pqueue_wipe_out( pqueue );

   CU_ASSERT( int_pqueue_count( pqueue ) == 0 );

   int_pqueue_dispose( &pqueue );

   return;
}

int
add_test_wipe_out( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_wipe_out", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_wipe_out_1
   add_test_to_suite( p_suite, test_wipe_out_1, "test_wipe_out_1" );

   // test_wipe_out_2
   add_test_to_suite( p_suite, test_wipe_out_2, "test_wipe_out_2" );

   // test_wipe_out_3
   add_test_to_suite( p_suite, test_wipe_out_3, "test_wipe_out_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

