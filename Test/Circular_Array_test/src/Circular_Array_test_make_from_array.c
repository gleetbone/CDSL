/**
 @file Circular_Array_test_make_from_array.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Circular_Array_make"
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
   test_make_from_array_1
*/

void test_make_from_array_1( void )
{
   i_circular_array_t *ca = NULL;
   int32_t array[3] = { 13, 24, 0 };
   
   ca = i_circular_array_make_from_array( array, 2, 4 );
   
   CU_ASSERT( ca != NULL );
   CU_ASSERT( i_circular_array_count( ca ) == 2 );
   CU_ASSERT( i_circular_array_capacity( ca ) == 4 );
   CU_ASSERT( i_circular_array_item( ca, 0 ) == 13 );
   CU_ASSERT( i_circular_array_item( ca, 1 ) == 24 );
 
   i_circular_array_deep_dispose( &ca );

   return;
}

/**
   test_make_from_array_2
*/

void test_make_from_array_2( void )
{
   s_circular_array_t *ca = NULL;
   string_t *array[3] = { NULL, NULL, NULL };
   
   string_t *s1 = string_make_from_cstring( "a" ); 
   string_t *s2 = string_make_from_cstring( "b" ); 
   array[0] = s1;
   array[1] = s2;
   
   ca = s_circular_array_make_from_array( array, 2, 4 );
   
   CU_ASSERT( ca != NULL );
   CU_ASSERT( s_circular_array_count( ca ) == 2 );
   CU_ASSERT( s_circular_array_capacity( ca ) == 4 );
   CU_ASSERT( s_circular_array_item( ca, 0 ) == s1 );
   CU_ASSERT( s_circular_array_item( ca, 1 ) == s2 );
   
   s_circular_array_deep_dispose( &ca );

   return;
}

int
add_test_make_from_array( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make_from_array", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_from_array_1
   add_test_to_suite( p_suite, test_make_from_array_1, "test_make_from_array_1" );

   // test_make_from_array_2
   add_test_to_suite( p_suite, test_make_from_array_2, "test_make_from_array_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

