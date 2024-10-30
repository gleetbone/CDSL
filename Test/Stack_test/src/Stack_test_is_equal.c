/**
 @file Stack_test_is_equal.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Stack_is_equal"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Stack_is_equal.

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
   test_is_equal_1
*/

void test_is_equal_1( void )
{
   int_stack_t *list = NULL;
   int_stack_t *list1 = NULL;

   list = int_stack_make();
   list1 = int_stack_make();
   
   int_stack_put( list, 24 );
   int_stack_put( list1, 24 );

   CU_ASSERT( int_stack_is_equal( list, list1 ) == 1 );

   int_stack_dispose( &list );
   int_stack_dispose( &list1 );

   return;
}

/**
   test_is_equal_2
*/

void test_is_equal_2( void )
{
   int_stack_t *list = NULL;
   int_stack_t *list1 = NULL;

   list = int_stack_make();
   list1 = int_stack_make();
   
   int_stack_put( list, 24 );
   int_stack_put( list1, 24 );

   CU_ASSERT( int_stack_is_equal( list, list1 ) == 1 );

   int_stack_dispose( &list );
   int_stack_dispose( &list1 );

   return;
}

/**
   test_is_equal_3
*/

void test_is_equal_3( void )
{
   int_stack_t *list = NULL;
   int_stack_t *list1 = NULL;

   list = int_stack_make();
   list1 = int_stack_make();
   
   int_stack_put( list1, 24 );

   CU_ASSERT( int_stack_is_equal( list, list1 ) == 0 );

   int_stack_put( list, 23 );
   
   CU_ASSERT( int_stack_is_equal( list, list1 ) == 0 );

   int_stack_dispose( &list );
   int_stack_dispose( &list1 );

   return;
}

/**
   test_is_equal_4
*/

void test_is_equal_4( void )
{
   int_stack_t *list = NULL;
   int_stack_t *list1 = NULL;

   list = int_stack_make();
   list1 = int_stack_make();
   
   int_stack_put( list1, 24 );

   CU_ASSERT( int_stack_is_equal( list, list1 ) == 0 );

   int_stack_put( list, 23 );
   
   CU_ASSERT( int_stack_is_equal( list, list1 ) == 0 );

   int_stack_dispose( &list );
   int_stack_dispose( &list1 );

   return;
}

/**
   test_is_equal_5
*/

void test_is_equal_5( void )
{
   s_stack_t *list = NULL;
   s_stack_t *list1 = NULL;
   s_stack_t *list2 = NULL;

   list = s_stack_make();
   list1 = s_stack_make();
   list2 = s_stack_make();
   
   string_t *s1 = string_make_from_cstring( "a" ); 
   string_t *s2 = string_make_from_cstring( "a" );
   
   s_stack_put( list, s1 );
   s_stack_put( list1, s1 );
   s_stack_put( list2, s2 );

   CU_ASSERT( s_stack_is_equal( list, list1 ) == 1 );
   CU_ASSERT( s_stack_is_equal( list, list2 ) == 0 );

   CU_ASSERT( s_stack_is_equal( list, list1 ) == 1 );
   CU_ASSERT( s_stack_is_equal( list, list2 ) == 0 );

   s_stack_deep_dispose( &list );
   s_stack_dispose( &list1 );
   s_stack_deep_dispose( &list2 );

   return;
}

int
add_test_is_equal( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_equal", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_equal_1
   add_test_to_suite( p_suite, test_is_equal_1, "test_is_equal_1" );

   // test_is_equal_2
   add_test_to_suite( p_suite, test_is_equal_2, "test_is_equal_2" );

   // test_is_equal_3
   add_test_to_suite( p_suite, test_is_equal_3, "test_is_equal_3" );

   // test_is_equal_4
   add_test_to_suite( p_suite, test_is_equal_4, "test_is_equal_4" );

   // test_is_equal_5
   add_test_to_suite( p_suite, test_is_equal_5, "test_is_equal_5" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

