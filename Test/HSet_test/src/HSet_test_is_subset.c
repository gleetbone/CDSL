/**
 @file HSet_test_is_subset.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for HSet_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for HSet_make.

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
   test_is_subset_1
*/

void test_is_subset_1( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   
   int flag = i_hset_is_subset( hset, other );
   
   CU_ASSERT( flag == 1 );
 
   i_hset_dispose( hset );
   i_hset_dispose( other );

   return;
}

/**
   test_is_subset_2
*/

void test_is_subset_2( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   
   i_hset_put( hset, 24 );
   
   int flag = i_hset_is_subset( hset, other );
   
   CU_ASSERT( flag == 0 );
 
   i_hset_dispose( hset );
   i_hset_dispose( other );

   return;
}

/**
   test_is_subset_3
*/

void test_is_subset_3( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   
   i_hset_put( hset, 24 );
   i_hset_put( other, 24 );
   
   int flag = i_hset_is_subset( hset, other );
   
   CU_ASSERT( flag == 1 );
 
   i_hset_dispose( hset );
   i_hset_dispose( other );

   return;
}

/**
   test_is_subset_4
*/

void test_is_subset_4( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   
   i_hset_put( other, 24 );
   
   int flag = i_hset_is_subset( hset, other );
   
   CU_ASSERT( flag == 1 );
 
   i_hset_dispose( hset );
   i_hset_dispose( other );

   return;
}

/**
   test_is_subset_5
*/

void test_is_subset_5( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   
   i_hset_put( hset, 24 );
   i_hset_put( hset, 13 );
   i_hset_put( other, 24 );
   
   int flag = i_hset_is_subset( hset, other );
   
   CU_ASSERT( flag == 0 );
 
   i_hset_dispose( hset );
   i_hset_dispose( other );

   return;
}

/**
   test_is_subset_6
*/

void test_is_subset_6( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   
   i_hset_put( hset, 24 );
   i_hset_put( other, 24 );
   i_hset_put( other, 13 );
   
   int flag = i_hset_is_subset( hset, other );
   
   CU_ASSERT( flag == 1 );
 
   i_hset_dispose( hset );
   i_hset_dispose( other );

   return;
}

/**
   test_is_subset_7
*/

void test_is_subset_7( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   
   i_hset_put( hset, 24 );
   i_hset_put( hset, 13 );
   i_hset_put( other, 24 );
   i_hset_put( other, 13 );
   
   int flag = i_hset_is_subset( hset, other );
   
   CU_ASSERT( flag == 1 );
 
   i_hset_dispose( hset );
   i_hset_dispose( other );

   return;
}

int
add_test_is_subset( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_subset", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_subset_1
   add_test_to_suite( p_suite, test_is_subset_1, "test_is_subset_1" );

   // test_is_subset_2
   add_test_to_suite( p_suite, test_is_subset_2, "test_is_subset_2" );

   // test_is_subset_3
   add_test_to_suite( p_suite, test_is_subset_3, "test_is_subset_3" );

   // test_is_subset_4
   add_test_to_suite( p_suite, test_is_subset_4, "test_is_subset_4" );

   // test_is_subset_5
   add_test_to_suite( p_suite, test_is_subset_5, "test_is_subset_5" );

   // test_is_subset_6
   add_test_to_suite( p_suite, test_is_subset_6, "test_is_subset_6" );

   // test_is_subset_7
   add_test_to_suite( p_suite, test_is_subset_7, "test_is_subset_7" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

