/**
 @file HSet_test_replace.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for HSet_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for HSet_put.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_HSet.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_replace_1
*/

void test_replace_1( void )
{
   i_hset_t *hset = NULL;

   hset = i_hset_make();

   i_hset_put( hset, 24 );

   CU_ASSERT( i_hset_item( hset, 24 ) == 24 );
   
   i_hset_replace( hset, 24 );

   CU_ASSERT( i_hset_item( hset, 24 ) == 24 );
   
   i_hset_dispose( hset );

   return;
}

/**
   test_replace_2
*/

void test_replace_2( void )
{
   i_hset_t *hset = NULL;

   hset = i_hset_make();

   i_hset_put( hset, 24 );
   i_hset_put( hset, 13 );

   CU_ASSERT( i_hset_item( hset, 24 ) == 24 );
   CU_ASSERT( i_hset_item( hset, 13 ) == 13 );

   i_hset_replace( hset, 24 );
   
   CU_ASSERT( i_hset_item( hset, 24 ) == 24 );
   CU_ASSERT( i_hset_item( hset, 13 ) == 13 );

   i_hset_replace( hset, 13 );
   
   CU_ASSERT( i_hset_item( hset, 24 ) == 24 );
   CU_ASSERT( i_hset_item( hset, 13 ) == 13 );

   i_hset_dispose( hset );

   return;
}

/**
   test_replace_3
*/

void test_replace_3( void )
{
   i_hset_t *hset = NULL;

   hset = i_hset_make();

   i_hset_put( hset, 24 );
   i_hset_put( hset, 13 );

   CU_ASSERT( i_hset_item( hset, 24 ) == 24 );
   CU_ASSERT( i_hset_item( hset, 13 ) == 13 );

   i_hset_replace( hset, 24 );
   
   CU_ASSERT( i_hset_item( hset, 24 ) == 24 );
   CU_ASSERT( i_hset_item( hset, 13 ) == 13 );

   i_hset_replace( hset, 13 );
   
   CU_ASSERT( i_hset_item( hset, 24 ) == 24 );
   CU_ASSERT( i_hset_item( hset, 13 ) == 13 );

   i_hset_dispose( hset );

   return;
}

int
add_test_replace( void )
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
   add_test_to_suite( p_suite, test_replace_1, "test_replace_1" );

   // test_make_2
   add_test_to_suite( p_suite, test_replace_2, "test_replace_2" );

   // test_make_3
   add_test_to_suite( p_suite, test_replace_3, "test_replace_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

