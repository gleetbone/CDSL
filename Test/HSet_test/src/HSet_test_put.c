/**
 @file HSet_test_put.c
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
   test_put_1
*/

void test_put_1( void )
{
   i_hset_t *hset = NULL;

   hset = i_hset_make();

   i_hset_put( hset, 24 );

   CU_ASSERT( i_hset_count( hset ) == 1 );
   CU_ASSERT( i_hset_is_empty( hset ) == 0 );

   i_hset_dispose( &hset );

   return;
}

/**
   test_put_2
*/

void test_put_2( void )
{
   i_hset_t *hset = NULL;

   hset = i_hset_make();

   i_hset_put( hset, 24 );

   CU_ASSERT( i_hset_count( hset ) == 1 );
   CU_ASSERT( i_hset_is_empty( hset ) == 0 );

   i_hset_put( hset, 13 );

   CU_ASSERT( i_hset_count( hset ) == 2 );
   CU_ASSERT( i_hset_is_empty( hset ) == 0 );

   i_hset_dispose( &hset );

   return;
}

/**
   test_put_3
*/

void test_put_3( void )
{
   i_hset_t *hset = NULL;

   hset = i_hset_make();

   i_hset_put( hset, 24 );
   i_hset_put( hset, 25 );
   i_hset_put( hset, 26 );
   i_hset_put( hset, 27 );
   i_hset_put( hset, 28 );
   i_hset_put( hset, 29 );
   i_hset_put( hset, 30 );
   i_hset_put( hset, 31 );
   i_hset_put( hset, 32 );
   i_hset_put( hset, 33 );
   i_hset_put( hset, 34 );
   i_hset_put( hset, 35 );
   i_hset_put( hset, 36 );
   i_hset_put( hset, 37 );
   i_hset_put( hset, 38 );
   i_hset_put( hset, 39 );
   i_hset_put( hset, 40 );
   i_hset_put( hset, 41 );

   CU_ASSERT( i_hset_count( hset ) == 18 );
   CU_ASSERT( i_hset_is_empty( hset ) == 0 );

   i_hset_dispose( &hset );

   return;
}

/**
   test_put_4
*/

void test_put_4( void )
{
   s_hset_t *hset = NULL;

   hset = s_hset_make();

   string_t *s1 = string_make_from_cstring( "a" ); 
   string_t *s2 = string_make_from_cstring( "b" ); 
   string_t *s3 = string_make_from_cstring( "c" ); 
   string_t *s4 = string_make_from_cstring( "d" ); 
   string_t *s5 = string_make_from_cstring( "e" ); 
   string_t *s6 = string_make_from_cstring( "f" ); 
   string_t *s7 = string_make_from_cstring( "g" ); 
   string_t *s8 = string_make_from_cstring( "h" ); 
   string_t *s9 = string_make_from_cstring( "i" ); 
   string_t *s10 = string_make_from_cstring( "j" ); 
   string_t *s11 = string_make_from_cstring( "k" ); 
   string_t *s12 = string_make_from_cstring( "l" ); 
   string_t *s13 = string_make_from_cstring( "m" ); 
   string_t *s14 = string_make_from_cstring( "n" ); 
   string_t *s15 = string_make_from_cstring( "o" ); 
   string_t *s16 = string_make_from_cstring( "p" ); 
   string_t *s17 = string_make_from_cstring( "q" ); 
   string_t *s18 = string_make_from_cstring( "r" ); 
   
   s_hset_put( hset, s1 );
   s_hset_put( hset, s2 );
   s_hset_put( hset, s3 );
   s_hset_put( hset, s4 );
   s_hset_put( hset, s5);
   s_hset_put( hset, s6 );
   s_hset_put( hset, s7 );
   s_hset_put( hset, s8 );
   s_hset_put( hset, s9 );
   s_hset_put( hset, s10 );
   s_hset_put( hset, s11 );
   s_hset_put( hset, s12 );
   s_hset_put( hset, s13 );
   s_hset_put( hset, s14 );
   s_hset_put( hset, s15 );
   s_hset_put( hset, s16 );
   s_hset_put( hset, s17 );
   s_hset_put( hset, s18 );

   CU_ASSERT( s_hset_count( hset ) == 18 );
   CU_ASSERT( s_hset_is_empty( hset ) == 0 );

   s_hset_deep_dispose( &hset );

   return;
}

/**
   test_put_5
*/

void test_put_5( void )
{
   i_hset_t *hset = NULL;

   hset = i_hset_make();

   i_hset_put( hset, 24 );

   CU_ASSERT( i_hset_count( hset ) == 1 );
   CU_ASSERT( i_hset_is_empty( hset ) == 0 );

   i_hset_put( hset, 24 );

   CU_ASSERT( i_hset_count( hset ) == 1 );
   CU_ASSERT( i_hset_is_empty( hset ) == 0 );

   i_hset_dispose( &hset );

   return;
}

int
add_test_put( void )
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

   // test_make_1
   add_test_to_suite( p_suite, test_put_1, "test_put_1" );

   // test_make_2
   add_test_to_suite( p_suite, test_put_2, "test_put_2" );

   // test_make_3
   add_test_to_suite( p_suite, test_put_3, "test_put_3" );

   // test_make_4
   add_test_to_suite( p_suite, test_put_4, "test_put_4" );

   // test_make_5
   add_test_to_suite( p_suite, test_put_5, "test_put_5" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

