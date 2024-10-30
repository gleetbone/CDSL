/**
 @file HSet_test_intersect.c
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
   test_intersect_1
*/

void test_intersect_1( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   
   i_hset_intersect( hset, other );
   
   CU_ASSERT( i_hset_count( hset ) == 0 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );

   return;
}

/**
   test_intersect_2
*/

void test_intersect_2( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   
   i_hset_put( hset, 24 );
   
   i_hset_intersect( hset, other );
   
   CU_ASSERT( i_hset_count( hset ) == 0 );
   CU_ASSERT( i_hset_has( hset, 24 ) == 0 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );

   return;
}

/**
   test_intersect_3
*/

void test_intersect_3( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   
   i_hset_put( hset, 24 );
   i_hset_put( other, 24 );
   
   i_hset_intersect( hset, other );
   
   CU_ASSERT( i_hset_count( hset ) == 1 );
   CU_ASSERT( i_hset_has( hset, 24 ) == 1 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );

   return;
}

/**
   test_intersect_4
*/

void test_intersect_4( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   
   i_hset_put( other, 24 );
   
   i_hset_intersect( hset, other );
   
   CU_ASSERT( i_hset_count( hset ) == 0 );
   CU_ASSERT( i_hset_has( hset, 24 ) == 0 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );

   return;
}

/**
   test_intersect_5
*/

void test_intersect_5( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   
   i_hset_put( hset, 24 );
   i_hset_put( hset, 13 );
   i_hset_put( other, 24 );
   
   i_hset_intersect( hset, other );
   
   CU_ASSERT( i_hset_count( hset ) == 1 );
   CU_ASSERT( i_hset_has( hset, 24 ) == 1 );
   CU_ASSERT( i_hset_has( hset, 13 ) == 0 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );

   return;
}

/**
   test_intersect_6
*/

void test_intersect_6( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   
   i_hset_put( hset, 24 );
   i_hset_put( other, 24 );
   i_hset_put( other, 13 );
   
   i_hset_intersect( hset, other );
   
   CU_ASSERT( i_hset_count( hset ) == 1 );
   CU_ASSERT( i_hset_has( hset, 24 ) == 1 );
   CU_ASSERT( i_hset_has( hset, 13 ) == 0 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );

   return;
}

/**
   test_intersect_7
*/

void test_intersect_7( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   
   i_hset_put( hset, 24 );
   i_hset_put( hset, 13 );
   i_hset_put( other, 24 );
   i_hset_put( other, 13 );
   
   i_hset_intersect( hset, other );
   
   CU_ASSERT( i_hset_count( hset ) == 2 );
   CU_ASSERT( i_hset_has( hset, 24 ) == 1 );
   CU_ASSERT( i_hset_has( hset, 13 ) == 1 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );

   return;
}

/**
   test_intersect_8
*/

void test_intersect_8( void )
{
   s_hset_t *hset = s_hset_make();
   s_hset_t *other = s_hset_make();
   
   string_t *s1 = string_make_from_cstring( "a" ); 
   string_t *s2 = string_make_from_cstring( "b" ); 
   string_t *s3 = string_make_from_cstring( "a" ); 
   string_t *s4 = string_make_from_cstring( "b" ); 
   
   s_hset_put( hset, s1 );
   s_hset_put( hset, s2 );
   s_hset_put( other, s3 );
   s_hset_put( other, s4 );
   
   s_hset_intersect( hset, other );
   
   CU_ASSERT( s_hset_count( hset ) == 2 );
   CU_ASSERT( s_hset_has( hset, s1 ) == 1 );
   CU_ASSERT( s_hset_has( hset, s2 ) == 1 );
   CU_ASSERT( s_hset_has( hset, s3 ) == 1 );
   CU_ASSERT( s_hset_has( hset, s4 ) == 1 );
 
   s_hset_deep_dispose( &hset );
   s_hset_deep_dispose( &other );

   return;
}

int
add_test_intersect( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_intersect", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_intersect_1
   add_test_to_suite( p_suite, test_intersect_1, "test_intersect_1" );

   // test_intersect_2
   add_test_to_suite( p_suite, test_intersect_2, "test_intersect_2" );

   // test_intersect_3
   add_test_to_suite( p_suite, test_intersect_3, "test_intersect_3" );

   // test_intersect_4
   add_test_to_suite( p_suite, test_intersect_4, "test_intersect_4" );

   // test_intersect_5
   add_test_to_suite( p_suite, test_intersect_5, "test_intersect_5" );

   // test_intersect_6
   add_test_to_suite( p_suite, test_intersect_6, "test_intersect_6" );

   // test_intersect_7
   add_test_to_suite( p_suite, test_intersect_7, "test_intersect_7" );

   // test_intersect_8
   add_test_to_suite( p_suite, test_intersect_8, "test_intersect_8" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

