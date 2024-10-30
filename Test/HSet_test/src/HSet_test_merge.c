/**
 @file HSet_test_merge.c
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
   test_merge_1
*/

void test_merge_1( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   
   i_hset_merge( hset, other );
   
   CU_ASSERT( i_hset_count( hset ) == 0 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );

   return;
}

/**
   test_merge_2
*/

void test_merge_2( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   
   i_hset_put( hset, 24 );
   
   i_hset_merge( hset, other );
   
   CU_ASSERT( i_hset_count( hset ) == 1 );
   CU_ASSERT( i_hset_has( hset, 24 ) == 1 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );

   return;
}

/**
   test_merge_3
*/

void test_merge_3( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   
   i_hset_put( hset, 24 );
   i_hset_put( other, 24 );
   
   i_hset_merge( hset, other );
   
   CU_ASSERT( i_hset_count( hset ) == 1 );
   CU_ASSERT( i_hset_has( hset, 24 ) == 1 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );

   return;
}

/**
   test_merge_4
*/

void test_merge_4( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   
   i_hset_put( other, 24 );
   
   i_hset_merge( hset, other );
   
   CU_ASSERT( i_hset_count( hset ) == 1 );
   CU_ASSERT( i_hset_has( hset, 24 ) == 1 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );

   return;
}

/**
   test_merge_5
*/

void test_merge_5( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   
   i_hset_put( hset, 24 );
   i_hset_put( hset, 13 );
   i_hset_put( other, 24 );
   
   i_hset_merge( hset, other );
   
   CU_ASSERT( i_hset_count( hset ) == 2 );
   CU_ASSERT( i_hset_has( hset, 24 ) == 1 );
   CU_ASSERT( i_hset_has( hset, 13 ) == 1 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );

   return;
}

/**
   test_merge_6
*/

void test_merge_6( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   
   i_hset_put( hset, 24 );
   i_hset_put( other, 24 );
   i_hset_put( other, 13 );
   
   i_hset_merge( hset, other );
   
   CU_ASSERT( i_hset_count( hset ) == 2 );
   CU_ASSERT( i_hset_has( hset, 24 ) == 1 );
   CU_ASSERT( i_hset_has( hset, 13 ) == 1 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );

   return;
}

/**
   test_merge_7
*/

void test_merge_7( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   
   i_hset_put( hset, 24 );
   i_hset_put( hset, 13 );
   i_hset_put( other, 24 );
   i_hset_put( other, 13 );
   
   i_hset_merge( hset, other );
   
   CU_ASSERT( i_hset_count( hset ) == 2 );
   CU_ASSERT( i_hset_has( hset, 24 ) == 1 );
   CU_ASSERT( i_hset_has( hset, 13 ) == 1 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );

   return;
}

/**
   test_merge_8
*/

void test_merge_8( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();

   i_hset_put( hset, 24 );
   i_hset_put( other, 24 );
   i_hset_put( other, 29 );
   i_hset_put( other, 7 );

   i_hset_merge( hset, other );

   CU_ASSERT( i_hset_count( hset ) == 3 );
   CU_ASSERT( i_hset_has( hset, 24 ) == 1 );
   CU_ASSERT( i_hset_has( hset, 29 ) == 1 );
   CU_ASSERT( i_hset_has( hset, 7 ) == 1 );

   i_hset_dispose( &hset );
   i_hset_dispose( &other );

   return;
}

/**
   test_merge_9
*/

void test_merge_9( void )
{
   s_hset_t *hset = s_hset_make();
   s_hset_t *other = s_hset_make();

   string_t *s1 = string_make_from_cstring( "a" ); 
   string_t *s2 = string_make_from_cstring( "a" ); 
   string_t *s3 = string_make_from_cstring( "b" ); 
   string_t *s4 = string_make_from_cstring( "c" ); 
   
   s_hset_put( hset, s1 );
   s_hset_put( other, s2 );
   s_hset_put( other, s3 );
   s_hset_put( other, s4 );

   s_hset_merge( hset, other );

   CU_ASSERT( s_hset_count( hset ) == 3 );
   CU_ASSERT( s_hset_has( hset, s1 ) == 1 );
   CU_ASSERT( s_hset_has( hset, s1 ) == 1 );
   CU_ASSERT( s_hset_has( hset, s3 ) == 1 );
   CU_ASSERT( s_hset_has( hset, s4 ) == 1 );

   s_hset_deep_dispose( &hset );
   s_hset_dispose( &other );
   string_deep_dispose( &s2 );

   return;
}

int
add_test_merge( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_merge", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_merge_1
   add_test_to_suite( p_suite, test_merge_1, "test_merge_1" );

   // test_merge_2
   add_test_to_suite( p_suite, test_merge_2, "test_merge_2" );

   // test_merge_3
   add_test_to_suite( p_suite, test_merge_3, "test_merge_3" );

   // test_merge_4
   add_test_to_suite( p_suite, test_merge_4, "test_merge_4" );

   // test_merge_5
   add_test_to_suite( p_suite, test_merge_5, "test_merge_5" );

   // test_merge_6
   add_test_to_suite( p_suite, test_merge_6, "test_merge_6" );

   // test_merge_7
   add_test_to_suite( p_suite, test_merge_7, "test_merge_7" );

   // test_merge_8
   add_test_to_suite( p_suite, test_merge_8, "test_merge_8" );

   // test_merge_9
   add_test_to_suite( p_suite, test_merge_9, "test_merge_9" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

