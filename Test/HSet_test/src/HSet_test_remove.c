/**
 @file HSet_test_remove.c
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
   test_remove_1
*/

void test_remove_1( void )
{
   i_hset_t *hset = NULL;

   hset = i_hset_make();

   i_hset_put( hset, 24 );

   CU_ASSERT( i_hset_has( hset, 24 ) == 1 );
   
   i_hset_remove( hset, 24 );

   CU_ASSERT( i_hset_has( hset, 24 ) == 0 );
   
   CU_ASSERT( i_hset_count( hset ) == 0 );
   
   i_hset_dispose( &hset );

   return;
}

/**
   test_remove_2
*/

void test_remove_2( void )
{
   i_hset_t *hset = NULL;

   hset = i_hset_make();

   i_hset_put( hset, 24 );
   i_hset_put( hset, 13 );

   CU_ASSERT( i_hset_has( hset, 24 ) == 1 );
   CU_ASSERT( i_hset_has( hset, 13 ) == 1 );

   i_hset_remove( hset, 13 );
   
   CU_ASSERT( i_hset_has( hset, 24 ) == 1 );
   CU_ASSERT( i_hset_has( hset, 13 ) == 0 );

   i_hset_remove( hset, 24 );
   
   CU_ASSERT( i_hset_has( hset, 24 ) == 0 );
   CU_ASSERT( i_hset_has( hset, 13 ) == 0 );

   i_hset_dispose( &hset );

   return;
}

/**
   test_remove_3
*/

void test_remove_3( void )
{
   i_hset_t *hset = NULL;
   i_hset_cursor_t *cursor = NULL;

   hset = i_hset_make();
   cursor = i_hset_cursor_make( hset );

   i_hset_put( hset, 24 );
   i_hset_put( hset, 13 );

   CU_ASSERT( i_hset_has( hset, 24 ) == 1 );
   CU_ASSERT( i_hset_has( hset, 13 ) == 1 );

   i_hset_cursor_start( cursor );

   i_hset_remove( hset, 24 );

   CU_ASSERT( i_hset_has( hset, 24 ) == 0 );
   CU_ASSERT( i_hset_has( hset, 13 ) == 1 );

   i_hset_dispose( &hset );

   return;
}

/**
   test_remove_4
*/

void test_remove_4( void )
{
   i_hset_t *hset = NULL;

   hset = i_hset_make();

   i_hset_put( hset, 24 );
   i_hset_put( hset, 13 );
   i_hset_put( hset, 7 );

   CU_ASSERT( i_hset_has( hset, 24 ) == 1 );
   CU_ASSERT( i_hset_has( hset, 13 ) == 1 );
   CU_ASSERT( i_hset_has( hset, 7 ) == 1 );

   i_hset_remove( hset, 7 );

   CU_ASSERT( i_hset_has( hset, 24 ) == 1 );
   CU_ASSERT( i_hset_has( hset, 13 ) == 1 );
   CU_ASSERT( i_hset_has( hset, 7 ) == 0 );

   i_hset_dispose( &hset );

   return;
}

/**
   test_remove_5
*/

void test_remove_5( void )
{
   i_hset_t *hset = NULL;

   hset = i_hset_make();

   i_hset_put( hset, 26 );
   i_hset_put( hset, 13 );
   i_hset_put( hset, 39 );

   CU_ASSERT( i_hset_has( hset, 26 ) == 1 );
   CU_ASSERT( i_hset_has( hset, 13 ) == 1 );
   CU_ASSERT( i_hset_has( hset, 39 ) == 1 );

   i_hset_remove( hset, 26 );

   CU_ASSERT( i_hset_has( hset, 26 ) == 0 );
   CU_ASSERT( i_hset_has( hset, 13 ) == 1 );
   CU_ASSERT( i_hset_has( hset, 39 ) == 1 );

   i_hset_dispose( &hset );

   return;
}

/**
   test_remove_6
*/

void test_remove_6( void )
{
   s_hset_t *hset = NULL;

   hset = s_hset_make();

   string_t *s1 = string_make_from_cstring( "a" ); 
   string_t *s2 = string_make_from_cstring( "b" ); 
   string_t *s3 = string_make_from_cstring( "c" ); 
   
   s_hset_put( hset, s1 );
   s_hset_put( hset, s2 );
   s_hset_put( hset, s3 );

   CU_ASSERT( s_hset_has( hset, s1 ) == 1 );
   CU_ASSERT( s_hset_has( hset, s2 ) == 1 );
   CU_ASSERT( s_hset_has( hset, s3 ) == 1 );

   s_hset_remove( hset, s1 );

   CU_ASSERT( s_hset_has( hset, s1 ) == 0 );
   CU_ASSERT( s_hset_has( hset, s2 ) == 1 );
   CU_ASSERT( s_hset_has( hset, s3 ) == 1 );

   string_deep_dispose( &s1 );
   s_hset_deep_dispose( &hset );

   return;
}

int
add_test_remove( void )
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
   add_test_to_suite( p_suite, test_remove_1, "test_remove_1" );

   // test_make_2
   add_test_to_suite( p_suite, test_remove_2, "test_remove_2" );

   // test_make_3
   add_test_to_suite( p_suite, test_remove_3, "test_remove_3" );

   // test_make_4
   add_test_to_suite( p_suite, test_remove_4, "test_remove_4" );

   // test_make_5
   add_test_to_suite( p_suite, test_remove_5, "test_remove_5" );

   // test_make_6
   add_test_to_suite( p_suite, test_remove_6, "test_remove_6" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

