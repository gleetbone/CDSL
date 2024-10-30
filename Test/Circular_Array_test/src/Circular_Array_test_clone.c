/**
 @file Circular_Array_test_clone.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Circular_Array_make_from"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Circular_Array_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_Circular_Array.h"
#include "s_Circular_Array.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_clone_1
*/

void test_clone_1( void )
{
   i_circular_array_t *ca = NULL;
   
   ca = i_circular_array_make( 4 );
   
   i_circular_array_t *ca_1 = i_circular_array_clone( ca );
   
   CU_ASSERT( ca_1 != NULL );
   CU_ASSERT( i_circular_array_count( ca_1 ) == 0 );
   CU_ASSERT( i_circular_array_is_empty( ca_1 ) == 1 );
  
   i_circular_array_dispose( &ca );
   i_circular_array_dispose( &ca_1 );

   return;
}

/**
   test_clone_2
*/

void test_clone_2( void )
{
   i_circular_array_t *ca = NULL;
   
   ca = i_circular_array_make( 4 );
   i_circular_array_put_last( ca, 24 );
   
   i_circular_array_t *ca_1 = i_circular_array_clone( ca );
   
   CU_ASSERT( ca_1 != NULL );
   CU_ASSERT( i_circular_array_count( ca_1 ) == 1 );
   CU_ASSERT( i_circular_array_is_empty( ca_1 ) == 0 );
   CU_ASSERT( i_circular_array_item( ca_1, 0 ) == 24 );
 
   i_circular_array_dispose( &ca );
   i_circular_array_dispose( &ca_1 );

   return;
}

/**
   test_clone_3
*/

void test_clone_3( void )
{
   s_circular_array_t *ca = NULL;
   s_circular_array_t *ca_1 = NULL;
   
   ca = s_circular_array_make( 4 );
   
   string_t *s1 = string_make_from_cstring( "a" ); 
   
   s_circular_array_put_last( ca, s1 );
   
   ca_1 = s_circular_array_clone( ca );
   
   CU_ASSERT( ca_1 != NULL );
   CU_ASSERT( s_circular_array_count( ca_1 ) == 1 );
   CU_ASSERT( s_circular_array_is_empty( ca_1 ) == 0 );
   CU_ASSERT( string_is_equal( s_circular_array_item( ca_1, 0 ), s1 ) == 1 );
 
   s_circular_array_dispose( &ca_1 );
   s_circular_array_deep_dispose( &ca );

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

   // test_clone_3
   add_test_to_suite( p_suite, test_clone_3, "test_clone_3" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

