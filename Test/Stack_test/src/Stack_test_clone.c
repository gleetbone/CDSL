/**
 @file Stack_test_clone.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Stack_clone"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Stack_clone.

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
   test_clone_1
*/

void test_clone_1( void )
{
   int_stack_t *list = NULL;
   
   list = int_stack_make();
   
   int_stack_t *list_1 = int_stack_clone( list );
   
   CU_ASSERT( list_1 != NULL );
   CU_ASSERT( int_stack_count( list_1 ) == 0 );
   CU_ASSERT( int_stack_is_empty( list_1 ) == 1 );
  
   int_stack_dispose( &list );
   int_stack_dispose( &list_1 );

   return;
}

/**
   test_clone_2
*/

void test_clone_2( void )
{
   int_stack_t *list = NULL;
   
   list = int_stack_make();
   int_stack_put( list, 24 );
   
   int_stack_t *list_1 = int_stack_clone( list );
   
   CU_ASSERT( list_1 != NULL );
   CU_ASSERT( int_stack_count( list_1 ) == 1 );
   CU_ASSERT( int_stack_is_empty( list_1 ) == 0 );
   CU_ASSERT( int_stack_item( list_1 ) == 24 );
 
   int_stack_dispose( &list );
   int_stack_dispose( &list_1 );

   return;
}

/**
   test_clone_2a
*/

void test_clone_2a( void )
{
   int_stack_t *list = NULL;
   
   list = int_stack_make();
   int_stack_put( list, 24 );
   int_stack_put( list, 7 );
   int_stack_put( list, 13 );
   
   int_stack_t *list_1 = int_stack_clone( list );
   
   CU_ASSERT( list_1 != NULL );
   CU_ASSERT( int_stack_count( list_1 ) == 3 );
   CU_ASSERT( int_stack_is_empty( list_1 ) == 0 );
   CU_ASSERT( int_stack_item( list_1 ) == 13 );
 
   int_stack_dispose( &list );
   int_stack_dispose( &list_1 );

   return;
}

/**
   test_clone_3
*/

void test_clone_3( void )
{
   s_stack_t *list = NULL;
   
   string_t *s1 = string_make_from_cstring( "1" );
   
   list = s_stack_make();
   s_stack_put( list, s1 );
   
   s_stack_t *list_1 = s_stack_clone( list );
   
   CU_ASSERT( list_1 != NULL );
   CU_ASSERT( s_stack_count( list_1 ) == 1 );
   CU_ASSERT( s_stack_is_empty( list_1 ) == 0 );
   CU_ASSERT( s_stack_item( list_1 ) == s1 );
 
   s_stack_dispose( &list_1 );
   s_stack_deep_dispose( &list );

   return;
}

int
add_test_clone( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_clone", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_clone_1
   add_test_to_suite( p_suite, test_clone_1, "test_clone_1" );

   // test_clone_2
   add_test_to_suite( p_suite, test_clone_2, "test_clone_2" );

   // test_clone_2a
   add_test_to_suite( p_suite, test_clone_2a, "test_clone_2a" );

   // test_clone_3
   add_test_to_suite( p_suite, test_clone_3, "test_clone_3" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

