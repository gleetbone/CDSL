/**
 @file Circular_Array_test_copy.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Circular_Array_put_last"
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
   test_copy_1
*/

void test_copy_1( void )
{
   i_circular_array_t *ca = NULL;
   i_circular_array_t *ca1 = NULL;

   ca = i_circular_array_make( 4 );
   ca1 = i_circular_array_make( 4 );
   
   i_circular_array_put_last( ca1, 24 );

   i_circular_array_copy( ca, ca1 );
   CU_ASSERT( i_circular_array_is_equal( ca, ca1 ) == 1 );

   i_circular_array_dispose( &ca );
   i_circular_array_dispose( &ca1 );

   return;
}

/**
   test_copy_2
*/

void test_copy_2( void )
{
   i_circular_array_t *ca = NULL;
   i_circular_array_t *ca1 = NULL;

   ca = i_circular_array_make( 4 );
   ca1 = i_circular_array_make( 4 );
   
   i_circular_array_put_last( ca1, 24 );

   i_circular_array_deep_copy( ca, ca1 );
   CU_ASSERT( i_circular_array_is_deep_equal( ca, ca1 ) == 1 );

   i_circular_array_dispose( &ca );
   i_circular_array_dispose( &ca1 );

   return;
}

/**
   test_copy_3
*/

void test_copy_3( void )
{
   s_circular_array_t *ca = NULL;
   s_circular_array_t *ca1 = NULL;

   ca = s_circular_array_make( 4 );
   ca1 = s_circular_array_make( 4 );

   string_t *s1 = string_make_from_cstring( "a" ); 
   
   s_circular_array_put_last( ca1, s1 );

   s_circular_array_copy( ca, ca1 );
   CU_ASSERT( s_circular_array_is_equal( ca, ca1 ) == 1 );
   CU_ASSERT( s_circular_array_is_deep_equal( ca, ca1 ) == 1 );

   s_circular_array_wipe_out( ca );
   
   s_circular_array_deep_copy( ca, ca1 );
   CU_ASSERT( s_circular_array_is_equal( ca, ca1 ) == 0 );
   CU_ASSERT( s_circular_array_is_deep_equal( ca, ca1 ) == 1 );

   s_circular_array_deep_dispose( &ca );
   s_circular_array_deep_dispose( &ca1 );

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

   // test_copy_2
   add_test_to_suite( p_suite, test_copy_2, "test_copy_2" );

   // test_copy_3
   add_test_to_suite( p_suite, test_copy_3, "test_copy_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

