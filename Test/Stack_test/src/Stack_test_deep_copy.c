/**
 @file Stack_test_deep_copy.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Stack_deep_copy"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Stack_deep_copy.

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
   test_deep_copy_1
*/

void test_deep_copy_1( void )
{
   int_stack_t *list = NULL;
   int_stack_t *list1 = NULL;

   list = int_stack_make();
   list1 = int_stack_make();
   
   int_stack_put( list, 24 );

   int_stack_deep_copy( list, list1 );
   CU_ASSERT( int_stack_is_equal( list, list1 ) == 1 );

   int_stack_dispose( &list );
   int_stack_dispose( &list1 );

   return;
}

/**
   test_deep_copy_1a
*/

void test_deep_copy_1a( void )
{
   int_stack_t *list = NULL;
   int_stack_t *list1 = NULL;

   list = int_stack_make();
   list1 = int_stack_make();
   
   int_stack_put( list1, 24 );

   int_stack_deep_copy( list, list1 );
   CU_ASSERT( int_stack_is_equal( list, list1 ) == 1 );

   int_stack_dispose( &list );
   int_stack_dispose( &list1 );

   return;
}

/**
   test_deep_copy_2
*/

void test_deep_copy_2( void )
{
   int_stack_t *list = NULL;
   int_stack_t *list1 = NULL;

   list = int_stack_make();
   list1 = int_stack_make();
   
   int_stack_put( list1, 24 );

   int_stack_deep_copy( list, list1 );
   CU_ASSERT( int_stack_is_deep_equal( list, list1 ) == 1 );

   int_stack_dispose( &list );
   int_stack_dispose( &list1 );

   return;
}

/**
   test_deep_copy_2a
*/

void test_deep_copy_2a( void )
{
   int_stack_t *list = NULL;
   int_stack_t *list1 = NULL;

   list = int_stack_make();
   list1 = int_stack_make();
   
   int_stack_put( list, 24 );

   int_stack_deep_copy( list, list1 );
   CU_ASSERT( int_stack_is_deep_equal( list, list1 ) == 1 );

   int_stack_dispose( &list );
   int_stack_dispose( &list1 );

   return;
}

/**
   test_deep_copy_3
*/

void test_deep_copy_3( void )
{
   s_stack_t *list = s_stack_make();
   s_stack_t *list1 = s_stack_make();

   string_t *s1 = string_make_from_cstring( "a" ); 
   
   s_stack_put( list1, s1 );

   s_stack_copy( list, list1 );
   CU_ASSERT( s_stack_is_equal( list, list1 ) == 1 );
   CU_ASSERT( s_stack_is_deep_equal( list, list1 ) == 1 );

   s_stack_wipe_out( list );
   
   s_stack_deep_copy( list, list1 );
   CU_ASSERT( s_stack_is_equal( list, list1 ) == 0 );
   CU_ASSERT( s_stack_is_deep_equal( list, list1 ) == 1 );

   s_stack_deep_dispose( &list );
   s_stack_deep_dispose( &list1 );

   return;
}

int
add_test_deep_copy( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_deep_copy", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_deep_copy_1
   add_test_to_suite( p_suite, test_deep_copy_1, "test_deep_copy_1" );

   // test_deep_copy_1a
   add_test_to_suite( p_suite, test_deep_copy_1a, "test_deep_copy_1a" );

   // test_deep_copy_2
   add_test_to_suite( p_suite, test_deep_copy_2, "test_deep_copy_2" );

   // test_deep_copy_2a
   add_test_to_suite( p_suite, test_deep_copy_2a, "test_deep_copy_2a" );

   // test_deep_copy_3
   add_test_to_suite( p_suite, test_deep_copy_3, "test_deep_copy_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

