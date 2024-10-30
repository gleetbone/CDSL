/**
 @file Stack_test_keep.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Stack_keep"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Stack_keep.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "int_Stack.h"
#include "s_Stack.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_keep_1
*/

void test_keep_1( void )
{
   int_stack_t *stack = NULL;

   stack = int_stack_make();

   int_stack_put( stack, 24 );

   CU_ASSERT( int_stack_count( stack ) == 1 );

   int_stack_keep( stack, 1 );

   CU_ASSERT( int_stack_count( stack ) == 1 );

   int_stack_keep( stack, 0 );

   CU_ASSERT( int_stack_count( stack ) == 0 );

   int_stack_dispose( &stack );

   return;
}

/**
   test_keep_2
*/

void test_keep_2( void )
{
   int_stack_t *stack = NULL;

   stack = int_stack_make();

   int_stack_put( stack, 24 );

   int_stack_put( stack, 7 );

   CU_ASSERT( int_stack_count( stack ) == 2 );

   int_stack_keep( stack, 1 );

   CU_ASSERT( int_stack_count( stack ) == 1 );

   int_stack_dispose( &stack );

   return;
}

/**
   test_keep_3
*/

void test_keep_3( void )
{
   int_stack_t *stack = NULL;

   stack = int_stack_make();

   int_stack_put( stack, 24 );

   int_stack_put( stack, 7 );

   int_stack_put( stack, 13 );

   CU_ASSERT( int_stack_count( stack ) == 3 );

   int_stack_keep( stack, 2 );

   CU_ASSERT( int_stack_count( stack ) == 2 );

   int_stack_dispose( &stack );

   return;
}

/**
   test_keep_4
*/

void test_keep_4( void )
{
   s_stack_t *stack = NULL;
   string_t *s1 = NULL;
   string_t *s2 = NULL;
   string_t *s3 = NULL;

   stack = s_stack_make();
   s1 = string_make_from_cstring( "A" );
   s2 = string_make_from_cstring( "B" );
   s3 = string_make_from_cstring( "C" );

   s_stack_put( stack, s1 );

   s_stack_put( stack, s2 );

   s_stack_put( stack, s3 );

   CU_ASSERT( s_stack_count( stack ) == 3 );

   s_stack_keep( stack, 2 );

   CU_ASSERT( s_stack_count( stack ) == 2 );

   s_stack_dispose( &stack );
   string_deep_dispose( &s1 );
   string_deep_dispose( &s2 );
   string_deep_dispose( &s3 );

   return;
}

int
add_test_keep( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_keep", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_keep_1
   add_test_to_suite( p_suite, test_keep_1, "test_keep_1" );

   // test_keep_2
   add_test_to_suite( p_suite, test_keep_2, "test_keep_2" );

   // test_keep_3
   add_test_to_suite( p_suite, test_keep_3, "test_keep_3" );

   // test_keep_4
   add_test_to_suite( p_suite, test_keep_4, "test_keep_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

