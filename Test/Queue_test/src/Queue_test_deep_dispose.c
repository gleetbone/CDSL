/**
 @file Queue_test_deep_dispose.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Queue_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Queue_make.

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
   test_deep_dispose_1
*/

void test_deep_dispose_1( void )
{
   int_queue_t *queue = NULL;
   
   queue = int_queue_make();
   int_queue_put( queue, 24 );

   CU_ASSERT( queue != NULL );
   CU_ASSERT( int_queue_count( queue ) == 1 );
   CU_ASSERT( int_queue_is_empty( queue ) == 0 );
 
   int_queue_deep_dispose( &queue );

   return;
}

int
add_test_deep_dispose( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_deep_dispose", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_deep_dispose_1
   add_test_to_suite( p_suite, test_deep_dispose_1, "test_deep_dispose_1" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

