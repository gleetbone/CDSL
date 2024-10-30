/**
 @file HSet_test_make_from_array.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for HSet_make_from_array"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for HSet_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_HSet.h"
#include "s_HSet.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_make_from_array_1
*/

void test_make_from_array_1( void )
{
   i_hset_t *hset = NULL;
   int32_t array[3] = { 13, 0, 0 };
   
   hset = i_hset_make_from_array( array, 1 );
   
   CU_ASSERT( hset != NULL );
   CU_ASSERT( i_hset_count( hset ) == 1 );
   CU_ASSERT( i_hset_is_empty( hset ) == 0 );
   CU_ASSERT( i_hset_has( hset, 13 ) == 1 );
 
   i_hset_dispose( &hset );

   return;
}

/**
   test_make_from_array_2
*/

void test_make_from_array_2( void )
{
   s_hset_t *hset = NULL;
   string_t *array[3] = { NULL, NULL, NULL };
   
   string_t *s1 = string_make_from_cstring( "a" ); 
   string_t *s2 = string_make_from_cstring( "b" ); 
   string_t *s3 = string_make_from_cstring( "c" ); 
   
   array[0] = s1;
   array[1] = s2;
   array[2] = s3;
   
   hset = s_hset_make_from_array( array, 1 );
   
   CU_ASSERT( hset != NULL );
   CU_ASSERT( s_hset_count( hset ) == 1 );
   CU_ASSERT( s_hset_is_empty( hset ) == 0 );
   CU_ASSERT( s_hset_has( hset, s1 ) == 1 );
 
   string_deep_dispose( &s2 );
   string_deep_dispose( &s3 );
   
   s_hset_deep_dispose( &hset );

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

