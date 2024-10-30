/**
 @file Circular_Array_test_replace.c
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
   test_replace_1
*/

void test_replace_1( void )
{
   i_circular_array_t *ca = NULL;
   
   ca = i_circular_array_make( 4 );
   i_circular_array_put_last( ca, 24 );
   i_circular_array_put_first( ca, 13 );
   
   i_circular_array_replace( ca, 17, 0 );
   
   CU_ASSERT( i_circular_array_item( ca, 0 ) == 17 );
   CU_ASSERT( i_circular_array_item( ca, 1 ) == 24 );
      
   i_circular_array_dispose( &ca );

   return;
}

/**
   test_replace_1a
*/

void test_replace_1a( void )
{
   i_circular_array_t *ca = NULL;
   
   ca = i_circular_array_make( 4 );
   i_circular_array_put_last( ca, 24 );
   i_circular_array_put_first( ca, 13 );
   
   i_circular_array_replace( ca, 17, 1 );
   
   CU_ASSERT( i_circular_array_item( ca, 0 ) == 13 );
   CU_ASSERT( i_circular_array_item( ca, 1 ) == 17 );
      
   i_circular_array_dispose( &ca );

   return;
}

/**
   test_replace_2
*/

void test_replace_2( void )
{
   s_circular_array_t *ca = NULL;
   
   ca = s_circular_array_make( 4 );
   
   string_t *s1 = string_make_from_cstring( "a" ); 
   string_t *s2 = string_make_from_cstring( "b" ); 
   string_t *s3 = string_make_from_cstring( "c" ); 
   
   s_circular_array_put_last( ca, s1 );
   s_circular_array_put_first( ca, s2 );
   
   s_circular_array_replace( ca, s3, 0 );
   
   CU_ASSERT( s_circular_array_item( ca, 0 ) == s3 );
   CU_ASSERT( s_circular_array_item( ca, 1 ) == s1 );
 
   string_deep_dispose( &s2 );
   s_circular_array_deep_dispose( &ca );

   return;
}

int
add_test_replace( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_replace", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_replace_1
   add_test_to_suite( p_suite, test_replace_1, "test_replace_1" );

   // test_replace_1a
   add_test_to_suite( p_suite, test_replace_1a, "test_replace_1a" );

   // test_replace_2
   add_test_to_suite( p_suite, test_replace_2, "test_replace_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */
