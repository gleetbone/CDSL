/**
 @file Circular_Array_test_deep_dispose.c
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
   test_deep_dispose_1
*/

void test_deep_dispose_1( void )
{
   i_circular_array_t *ca = NULL;
   
   ca = i_circular_array_make( 4 );
   
   i_circular_array_t *ca_1 = i_circular_array_deep_clone( ca );
   
   CU_ASSERT( ca_1 != NULL );
  
   i_circular_array_deep_dispose( &ca );
   i_circular_array_deep_dispose( &ca_1 );

   return;
}

/**
   test_deep_dispose_2
*/

void test_deep_dispose_2( void )
{
   i_circular_array_t *ca = NULL;
   
   ca = i_circular_array_make( 4 );
   i_circular_array_put_last( ca, 24 );
   
   i_circular_array_t *ca_1 = i_circular_array_deep_clone( ca );
   
   CU_ASSERT( ca_1 != NULL );
 
   i_circular_array_deep_dispose( &ca );
   i_circular_array_deep_dispose( &ca_1 );

   return;
}

/**
   test_deep_dispose_3
*/

void test_deep_dispose_3( void )
{
   s_circular_array_t *ca = NULL;
   s_circular_array_t *ca_1 = NULL;
   
   ca = s_circular_array_make( 4 );
   
   string_t *s1 = string_make_from_cstring( "a" ); 
   
   s_circular_array_put_last( ca, s1 );
   
   ca_1 = s_circular_array_deep_clone( ca );
   
   CU_ASSERT( ca_1 != NULL );
 
   s_circular_array_deep_dispose( &ca_1 );
   s_circular_array_deep_dispose( &ca );

   return;
}

int
add_test_deep_dispose( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_deep_dispose", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_deep_dispose_1
   add_test_to_suite( p_suite, test_deep_dispose_1, "test_deep_dispose_1" );

   // test_deep_dispose_2
   add_test_to_suite( p_suite, test_deep_dispose_2, "test_deep_dispose_2" );

   // test_deep_dispose_3
   add_test_to_suite( p_suite, test_deep_dispose_3, "test_deep_dispose_3" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

