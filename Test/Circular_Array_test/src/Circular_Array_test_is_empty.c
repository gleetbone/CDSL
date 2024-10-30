/**
 @file Circular_Array_test_is_empty.c
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
   test_is_empty_1
*/

void test_is_empty_1( void )
{
   i_circular_array_t *ca = NULL;
   
   ca = i_circular_array_make( 4 );
   
   CU_ASSERT( i_circular_array_is_empty( ca ) == 1 );

   i_circular_array_put_last( ca, 24 );
   i_circular_array_put_first( ca, 13 );
   
   CU_ASSERT( i_circular_array_is_empty( ca ) == 0 );
      
   i_circular_array_dispose( &ca );

   return;
}

/**
   test_is_empty_2
*/

void test_is_empty_2( void )
{
   s_circular_array_t *ca = NULL;
   
   ca = s_circular_array_make( 4 );
   
   CU_ASSERT( s_circular_array_is_empty( ca ) == 1 );
   
   string_t *s1 = string_make_from_cstring( "a" ); 
   string_t *s2 = string_make_from_cstring( "b" ); 
   
   s_circular_array_put_last( ca, s1 );
   s_circular_array_put_first( ca, s2 );
   
   CU_ASSERT( s_circular_array_is_empty( ca ) == 0 );
 
   s_circular_array_deep_dispose( &ca );

   return;
}

int
add_test_is_empty( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_empty", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_empty_1
   add_test_to_suite( p_suite, test_is_empty_1, "test_is_empty_1" );

   // test_is_empty_2
   add_test_to_suite( p_suite, test_is_empty_2, "test_is_empty_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

