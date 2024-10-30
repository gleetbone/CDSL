/**
 @file Queue_test_copy.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Queue_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Queue_t

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "int_Queue.h"
#include "s_Queue.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_copy_1
*/

void test_copy_1( void )
{
   int_queue_t *list = NULL;
   int_queue_t *list1 = NULL;

   list = int_queue_make();
   list1 = int_queue_make();
   
   int_queue_put( list, 24 );

   int_queue_copy( list, list1 );
   CU_ASSERT( int_queue_is_equal( list, list1 ) == 1 );

   int_queue_dispose( &list );
   int_queue_dispose( &list1 );

   return;
}

/**
   test_copy_1a
*/

void test_copy_1a( void )
{
   int_queue_t *list = NULL;
   int_queue_t *list1 = NULL;

   list = int_queue_make();
   list1 = int_queue_make();
   
   int_queue_put( list1, 24 );

   int_queue_copy( list, list1 );
   CU_ASSERT( int_queue_is_equal( list, list1 ) == 1 );

   int_queue_dispose( &list );
   int_queue_dispose( &list1 );

   return;
}

/**
   test_copy_2
*/

void test_copy_2( void )
{
   int_queue_t *list = NULL;
   int_queue_t *list1 = NULL;

   list = int_queue_make();
   list1 = int_queue_make();
   
   int_queue_put( list1, 24 );

   int_queue_copy( list, list1 );
   CU_ASSERT( int_queue_is_equal( list, list1 ) == 1 );

   int_queue_dispose( &list );
   int_queue_dispose( &list1 );

   return;
}

/**
   test_copy_2a
*/

void test_copy_2a( void )
{
   int_queue_t *list = NULL;
   int_queue_t *list1 = NULL;

   list = int_queue_make();
   list1 = int_queue_make();
   
   int_queue_put( list, 24 );

   int_queue_copy( list, list1 );
   CU_ASSERT( int_queue_is_equal( list, list1 ) == 1 );
   CU_ASSERT( int_queue_is_deep_equal( list, list1 ) == 1 );

   int_queue_dispose( &list );
   int_queue_dispose( &list1 );

   return;
}

/**
   test_copy_3
*/

void test_copy_3( void )
{
   s_queue_t *list = s_queue_make();
   s_queue_t *list1 = s_queue_make();

   string_t *s1 = string_make_from_cstring( "a" ); 
   
   s_queue_put( list1, s1 );

   s_queue_copy( list, list1 );
   CU_ASSERT( s_queue_is_equal( list, list1 ) == 1 );
   CU_ASSERT( s_queue_is_deep_equal( list, list1 ) == 1 );

   s_queue_wipe_out( list );
   
   s_queue_deep_copy( list, list1 );
   CU_ASSERT( s_queue_is_equal( list, list1 ) == 0 );
   CU_ASSERT( s_queue_is_deep_equal( list, list1 ) == 1 );

   s_queue_deep_dispose( &list );
   s_queue_deep_dispose( &list1 );

   return;
}

int
add_test_copy( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_copy", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_copy_1
   add_test_to_suite( p_suite, test_copy_1, "test_copy_1" );

   // test_copy_1a
   add_test_to_suite( p_suite, test_copy_1a, "test_copy_1a" );

   // test_copy_2
   add_test_to_suite( p_suite, test_copy_2, "test_copy_2" );

   // test_copy_2a
   add_test_to_suite( p_suite, test_copy_2a, "test_copy_2a" );

   // test_copy_3
   add_test_to_suite( p_suite, test_copy_3, "test_copy_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

