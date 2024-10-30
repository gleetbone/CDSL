/**
 @file HSet_test_set_bucket_count.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for HSet_make"
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
   test_set_bucket_count_1
*/

void test_set_bucket_count_1( void )
{
   i_hset_t *hset = NULL;

   hset = i_hset_make();

   CU_ASSERT( i_hset_bucket_count( hset ) == 13 );

   i_hset_set_bucket_count( hset, 23 );

   CU_ASSERT( i_hset_bucket_count( hset ) == 23 );

   i_hset_dispose( &hset );

   return;
}

/**
   test_set_bucket_count_2
*/

void test_set_bucket_count_2( void )
{
   i_hset_t *hset = NULL;

   hset = i_hset_make_n( 23 );

   CU_ASSERT( i_hset_bucket_count( hset ) == 23 );

   i_hset_set_bucket_count( hset, 37 );

   CU_ASSERT( i_hset_bucket_count( hset ) == 37 );

   i_hset_dispose( &hset );

   return;
}

/**
   test_set_bucket_count_3
*/

void test_set_bucket_count_3( void )
{
   i_hset_t *hset = NULL;

   hset = i_hset_make_n( 23 );
   i_hset_put( hset, 24 );
   i_hset_put( hset, 13 );

   CU_ASSERT( i_hset_bucket_count( hset ) == 23 );

   i_hset_set_bucket_count( hset, 37 );

   CU_ASSERT( i_hset_bucket_count( hset ) == 37 );

   i_hset_dispose( &hset );

   return;
}

/**
   test_set_bucket_count_4
*/

void test_set_bucket_count_4( void )
{
   s_hset_t *hset = NULL;

   hset = s_hset_make_n( 23 );
   
   string_t *s1 = string_make_from_cstring( "a" ); 
   string_t *s2 = string_make_from_cstring( "b" ); 
   
   s_hset_put( hset, s1 );
   s_hset_put( hset, s2 );

   CU_ASSERT( s_hset_bucket_count( hset ) == 23 );

   s_hset_set_bucket_count( hset, 37 );

   CU_ASSERT( s_hset_bucket_count( hset ) == 37 );

   s_hset_deep_dispose( &hset );

   return;
}

int
add_test_set_bucket_count( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_set_bucket_count_1
   add_test_to_suite( p_suite, test_set_bucket_count_1, "test_set_bucket_count_1" );

   // test_set_bucket_count_2
   add_test_to_suite( p_suite, test_set_bucket_count_2, "test_set_bucket_count_2" );

   // test_set_bucket_count_3
   add_test_to_suite( p_suite, test_set_bucket_count_3, "test_set_bucket_count_3" );

   // test_set_bucket_count_4
   add_test_to_suite( p_suite, test_set_bucket_count_4, "test_set_bucket_count_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

