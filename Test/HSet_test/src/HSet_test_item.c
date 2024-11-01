/**
 @file HSet_test_item.c
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
   test_item_1
*/

void test_item_1( void )
{
   i_hset_t *hset = NULL;

   hset = i_hset_make();

   i_hset_put( hset, 24 );

   CU_ASSERT( i_hset_item( hset, 24 ) == 24 );

   i_hset_dispose( &hset );

   return;
}

/**
   test_item_2
*/

void test_item_2( void )
{
   i_hset_t *hset = NULL;

   hset = i_hset_make();

   i_hset_put( hset, 24 );
   i_hset_put( hset, 13 );

   CU_ASSERT( i_hset_item( hset, 24 ) == 24 );
   CU_ASSERT( i_hset_item( hset, 13 ) == 13 );

   i_hset_dispose( &hset );

   return;
}

/**
   test_item_3
*/

void test_item_3( void )
{
   i_hset_t *hset = NULL;

   hset = i_hset_make();

   i_hset_put( hset, 24 );
   i_hset_put( hset, 13 );

   CU_ASSERT( i_hset_item( hset, 24 ) == 24 );
   CU_ASSERT( i_hset_item( hset, 13 ) == 13 );

   i_hset_dispose( &hset );

   return;
}

/**
   test_item_4
*/

void test_item_4( void )
{
   i_hset_t *hset = NULL;

   hset = i_hset_make();

   i_hset_put( hset, 26 );
   i_hset_put( hset, 13 );

   CU_ASSERT( i_hset_item( hset, 26 ) == 26 );
   CU_ASSERT( i_hset_item( hset, 13 ) == 13 );

   i_hset_dispose( &hset );

   return;
}

/**
   test_item_5
*/

void test_item_5( void )
{
   s_hset_t *hset = NULL;

   hset = s_hset_make();

   string_t *s1 = string_make_from_cstring( "a" ); 
   string_t *s2 = string_make_from_cstring( "b" ); 
   
   s_hset_put( hset, s1 );
   s_hset_put( hset, s2 );

   CU_ASSERT( s_hset_item( hset, s1 ) == s1 );
   CU_ASSERT( s_hset_item( hset, s2 ) == s2 );

   s_hset_deep_dispose( &hset );

   return;
}

int
add_test_item( void )
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
   add_test_to_suite( p_suite, test_item_1, "test_item_1" );

   // test_make_2
   add_test_to_suite( p_suite, test_item_2, "test_item_2" );

   // test_make_3
   add_test_to_suite( p_suite, test_item_3, "test_item_3" );

   // test_make_4
   add_test_to_suite( p_suite, test_item_4, "test_item_4" );

   // test_make_5
   add_test_to_suite( p_suite, test_item_5, "test_item_5" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

