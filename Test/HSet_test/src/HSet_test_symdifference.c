/**
 @file HSet_test_symdifference.c
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
   test_symdifference_1
*/

void test_symdifference_1( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   i_hset_t *result = NULL;
   
   result = i_hset_symdifference( hset, other );
   
   CU_ASSERT( i_hset_count( result ) == 0 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );
   i_hset_dispose( &result );

   return;
}

/**
   test_symdifference_2
*/

void test_symdifference_2( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   i_hset_t *result = NULL;
   
   i_hset_put( hset, 24 );
   
   result = i_hset_symdifference( hset, other );
   
   CU_ASSERT( i_hset_count( result ) == 1 );
   CU_ASSERT( i_hset_has( result, 24 ) == 1 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );
   i_hset_dispose( &result );

   return;
}

/**
   test_symdifference_3
*/

void test_symdifference_3( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   i_hset_t *result = NULL;
   
   i_hset_put( hset, 24 );
   i_hset_put( other, 24 );
   
   result = i_hset_symdifference( hset, other );
   
   CU_ASSERT( i_hset_count( result ) == 0 );
   CU_ASSERT( i_hset_has( result, 24 ) == 0 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );
   i_hset_dispose( &result );

   return;
}

/**
   test_symdifference_4
*/

void test_symdifference_4( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   i_hset_t *result = NULL;
   
   i_hset_put( other, 24 );
   
   result = i_hset_symdifference( hset, other );
   
   CU_ASSERT( i_hset_count( result ) == 1 );
   CU_ASSERT( i_hset_has( result, 24 ) == 1 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );
   i_hset_dispose( &result );

   return;
}

/**
   test_symdifference_5
*/

void test_symdifference_5( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   i_hset_t *result = NULL;
   
   i_hset_put( hset, 24 );
   i_hset_put( hset, 13 );
   i_hset_put( other, 24 );
   
   result = i_hset_symdifference( hset, other );
   
   CU_ASSERT( i_hset_count( result ) == 1 );
   CU_ASSERT( i_hset_has( result, 24 ) == 0 );
   CU_ASSERT( i_hset_has( result, 13 ) == 1 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );
   i_hset_dispose( &result );

   return;
}

/**
   test_symdifference_6
*/

void test_symdifference_6( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   i_hset_t *result = NULL;
   
   i_hset_put( hset, 24 );
   i_hset_put( other, 24 );
   i_hset_put( other, 13 );
   
   result = i_hset_symdifference( hset, other );
   
   CU_ASSERT( i_hset_count( result ) == 1 );
   CU_ASSERT( i_hset_has( result, 24 ) == 0 );
   CU_ASSERT( i_hset_has( result, 13 ) == 1 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );
   i_hset_dispose( &result );

   return;
}

/**
   test_symdifference_7
*/

void test_symdifference_7( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   i_hset_t *result = NULL;
   
   i_hset_put( hset, 24 );
   i_hset_put( hset, 13 );
   i_hset_put( other, 24 );
   i_hset_put( other, 13 );
   
   result = i_hset_symdifference( hset, other );
   
   CU_ASSERT( i_hset_count( result ) == 0 );
   CU_ASSERT( i_hset_has( result, 24 ) == 0 );
   CU_ASSERT( i_hset_has( result, 13 ) == 0 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );
   i_hset_dispose( &result );

   return;
}

/**
   test_symdifference_8
*/

void test_symdifference_8( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   i_hset_t *result = NULL;

   i_hset_put( hset, 24 );
   i_hset_put( other, 24 );
   i_hset_put( other, 29 );
   i_hset_put( other, 7 );

   result = i_hset_symdifference( hset, other );

   CU_ASSERT( i_hset_count( result ) == 2 );
   CU_ASSERT( i_hset_has( result, 24 ) == 0 );
   CU_ASSERT( i_hset_has( result, 29 ) == 1 );
   CU_ASSERT( i_hset_has( result, 7 ) == 1 );

   i_hset_dispose( &hset );
   i_hset_dispose( &other );
   i_hset_dispose( &result );

   return;
}

/**
   test_symdifference_9
*/

void test_symdifference_9( void )
{
   s_hset_t *hset = s_hset_make();
   s_hset_t *other = s_hset_make();
   s_hset_t *result = NULL;

   string_t *s1 = string_make_from_cstring( "a" ); 
   string_t *s2 = string_make_from_cstring( "a" ); 
   string_t *s3 = string_make_from_cstring( "b" ); 
   string_t *s4 = string_make_from_cstring( "c" ); 
   
   s_hset_put( hset, s1 );
   s_hset_put( other, s2 );
   s_hset_put( other, s3 );
   s_hset_put( other, s4 );

   result = s_hset_symdifference( hset, other );

   CU_ASSERT( s_hset_count( result ) == 2 );
   CU_ASSERT( s_hset_has( result, s1 ) == 0 );
   CU_ASSERT( s_hset_has( result, s2 ) == 0 );
   CU_ASSERT( s_hset_has( result, s3 ) == 1 );
   CU_ASSERT( s_hset_has( result, s4 ) == 1 );

   s_hset_dispose( &result );
   s_hset_deep_dispose( &hset );
   s_hset_deep_dispose( &other );

   return;
}

int
add_test_symdifference( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_symdifference", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_symdifference_1
   add_test_to_suite( p_suite, test_symdifference_1, "test_symdifference_1" );

   // test_symdifference_2
   add_test_to_suite( p_suite, test_symdifference_2, "test_symdifference_2" );

   // test_symdifference_3
   add_test_to_suite( p_suite, test_symdifference_3, "test_symdifference_3" );

   // test_symdifference_4
   add_test_to_suite( p_suite, test_symdifference_4, "test_symdifference_4" );

   // test_symdifference_5
   add_test_to_suite( p_suite, test_symdifference_5, "test_symdifference_5" );

   // test_symdifference_6
   add_test_to_suite( p_suite, test_symdifference_6, "test_symdifference_6" );

   // test_symdifference_7
   add_test_to_suite( p_suite, test_symdifference_7, "test_symdifference_7" );

   // test_symdifference_8
   add_test_to_suite( p_suite, test_symdifference_8, "test_symdifference_8" );

   // test_symdifference_9
   add_test_to_suite( p_suite, test_symdifference_9, "test_symdifference_9" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

