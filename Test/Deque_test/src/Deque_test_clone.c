/**
 @file Deque_test_clone.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Deque_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Deque_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_Deque.h"
#include "s_Deque.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_clone_1
*/

void test_clone_1( void )
{
   i_deque_t *deque = NULL;
   i_deque_t *d1 = NULL;
   
   deque = i_deque_make();
   
   CU_ASSERT( deque != NULL );
   CU_ASSERT( i_deque_count( deque ) == 0 );
   CU_ASSERT( i_deque_is_empty( deque ) == 1 );
 
   i_deque_put_first( deque, 24 );
   i_deque_put_first( deque, 13 );

   CU_ASSERT( i_deque_first( deque ) == 13 );

   CU_ASSERT( i_deque_count( deque ) == 2 );

   d1 = i_deque_clone( deque );
   
   CU_ASSERT( i_deque_first( d1 ) == 13 );

   CU_ASSERT( i_deque_count( d1 ) == 2 );

   i_deque_dispose( &deque );
   i_deque_dispose( &d1 );

   return;
}

/**
   test_clone_2
*/

void test_clone_2( void )
{
   s_deque_t *deque = NULL;
   s_deque_t *d1 = NULL;
   string_t *s1 = NULL;
   string_t *s2 = NULL;
   
   deque = s_deque_make();
   
   CU_ASSERT( deque != NULL );
   CU_ASSERT( s_deque_count( deque ) == 0 );
   CU_ASSERT( s_deque_is_empty( deque ) == 1 );
 
   s1 = string_make_from_cstring( "1" );
   s2 = string_make_from_cstring( "2" );
   
   s_deque_put_first( deque, s1 );
   s_deque_put_first( deque, s2 );

   CU_ASSERT( s_deque_first( deque ) == s2 );

   CU_ASSERT( s_deque_count( deque ) == 2 );

   d1 = s_deque_clone( deque );
   
   CU_ASSERT( s_deque_first( d1 ) == s2 );

   CU_ASSERT( s_deque_count( d1 ) == 2 );

   s_deque_dispose( &deque );
   s_deque_dispose( &d1 );

   string_dispose( &s1 );
   string_dispose( &s2 );
   
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

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */
