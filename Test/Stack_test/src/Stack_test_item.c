/**
 @file Stack_test_item.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Stack_item"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Stack_item.

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
   test_item_1
*/

void test_item_1( void )
{
   int_stack_t *stack = NULL;

   stack = int_stack_make();

   int_stack_put( stack, 24 );

   CU_ASSERT( int_stack_item( stack ) == 24 );

   int_stack_dispose( &stack );

   return;
}

/**
   test_item_2
*/

void test_item_2( void )
{
   int_stack_t *stack = NULL;

   stack = int_stack_make();

   int_stack_put( stack, 24 );

   CU_ASSERT( int_stack_item( stack ) == 24 );

   int_stack_put( stack, 7 );

   CU_ASSERT( int_stack_item( stack ) == 7 );

   int_stack_remove( stack );

   CU_ASSERT( int_stack_item( stack ) == 24 );

   int_stack_dispose( &stack );

   return;
}

/**
   test_item_3
*/

void test_item_3( void )
{
   s_stack_t *stack = NULL;
   string_t *s1 = NULL;
   string_t *s2 = NULL;

   stack = s_stack_make();
   s1 = string_make_from_cstring( "A" );
   s2 = string_make_from_cstring( "B" );

   s_stack_put( stack, s1 );

   CU_ASSERT( s_stack_item( stack ) == s1 );

   s_stack_put( stack, s2 );

   CU_ASSERT( s_stack_item( stack ) == s2 );

   s_stack_remove( stack );

   CU_ASSERT( s_stack_item( stack ) == s1 );

   s_stack_dispose( &stack );
   string_deep_dispose( &s1 );
   string_deep_dispose( &s2 );

   return;
}

int
add_test_item( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_item", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_item_1
   add_test_to_suite( p_suite, test_item_1, "test_item_1" );

   // test_item_2
   add_test_to_suite( p_suite, test_item_2, "test_item_2" );

   // test_item_3
   add_test_to_suite( p_suite, test_item_3, "test_item_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

