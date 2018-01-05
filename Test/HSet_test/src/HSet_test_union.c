/**
 @file HSet_test_union.c
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
   test_union_1
*/

void test_union_1( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   i_hset_t *result = NULL;
   
   result = i_hset_union( hset, other );
   
   CU_ASSERT( i_hset_count( result ) == 0 );
 
   i_hset_dispose( hset );
   i_hset_dispose( other );
   i_hset_dispose( result );

   return;
}

/**
   test_union_2
*/

void test_union_2( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   i_hset_t *result = NULL;
   
   i_hset_put( hset, 24 );
   
   result = i_hset_union( hset, other );
   
   CU_ASSERT( i_hset_count( result ) == 1 );
   CU_ASSERT( i_hset_has( result, 24 ) == 1 );
 
   i_hset_dispose( hset );
   i_hset_dispose( other );
   i_hset_dispose( result );

   return;
}

/**
   test_union_3
*/

void test_union_3( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   i_hset_t *result = NULL;
   
   i_hset_put( hset, 24 );
   i_hset_put( other, 24 );
   
   result = i_hset_union( hset, other );
   
   CU_ASSERT( i_hset_count( result ) == 1 );
   CU_ASSERT( i_hset_has( result, 24 ) == 1 );
 
   i_hset_dispose( hset );
   i_hset_dispose( other );
   i_hset_dispose( result );

   return;
}

/**
   test_union_4
*/

void test_union_4( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   i_hset_t *result = NULL;
   
   i_hset_put( other, 24 );
   
   result = i_hset_union( hset, other );
   
   CU_ASSERT( i_hset_count( result ) == 1 );
   CU_ASSERT( i_hset_has( result, 24 ) == 1 );
 
   i_hset_dispose( hset );
   i_hset_dispose( other );
   i_hset_dispose( result );

   return;
}

/**
   test_union_5
*/

void test_union_5( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   i_hset_t *result = NULL;
   
   i_hset_put( hset, 24 );
   i_hset_put( hset, 13 );
   i_hset_put( other, 24 );
   
   result = i_hset_union( hset, other );
   
   CU_ASSERT( i_hset_count( result ) == 2 );
   CU_ASSERT( i_hset_has( result, 24 ) == 1 );
   CU_ASSERT( i_hset_has( result, 13 ) == 1 );
 
   i_hset_dispose( hset );
   i_hset_dispose( other );
   i_hset_dispose( result );

   return;
}

/**
   test_union_6
*/

void test_union_6( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   i_hset_t *result = NULL;
   
   i_hset_put( hset, 24 );
   i_hset_put( other, 24 );
   i_hset_put( other, 13 );
   
   result = i_hset_union( hset, other );
   
   CU_ASSERT( i_hset_count( result ) == 2 );
   CU_ASSERT( i_hset_has( result, 24 ) == 1 );
   CU_ASSERT( i_hset_has( result, 13 ) == 1 );
 
   i_hset_dispose( hset );
   i_hset_dispose( other );
   i_hset_dispose( result );

   return;
}

/**
   test_union_7
*/

void test_union_7( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   i_hset_t *result = NULL;
   
   i_hset_put( hset, 24 );
   i_hset_put( hset, 13 );
   i_hset_put( other, 24 );
   i_hset_put( other, 13 );
   
   result = i_hset_union( hset, other );
   
   CU_ASSERT( i_hset_count( result ) == 2 );
   CU_ASSERT( i_hset_has( result, 24 ) == 1 );
   CU_ASSERT( i_hset_has( result, 13 ) == 1 );
 
   i_hset_dispose( hset );
   i_hset_dispose( other );
   i_hset_dispose( result );

   return;
}

/**
   test_union_8
*/

void test_union_8( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   i_hset_t *result = NULL;

   i_hset_put( hset, 24 );
   i_hset_put( hset, 24 );
   i_hset_put( other, 29 );
   i_hset_put( other, 7 );

   result = i_hset_union( hset, other );

   CU_ASSERT( i_hset_count( result ) == 3 );
   CU_ASSERT( i_hset_has( result, 24 ) == 1 );
   CU_ASSERT( i_hset_has( result, 29 ) == 1 );
   CU_ASSERT( i_hset_has( result, 7 ) == 1 );

   i_hset_dispose( hset );
   i_hset_dispose( other );
   i_hset_dispose( result );

   return;
}

int
add_test_union( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_union", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_union_1
   add_test_to_suite( p_suite, test_union_1, "test_union_1" );

   // test_union_2
   add_test_to_suite( p_suite, test_union_2, "test_union_2" );

   // test_union_3
   add_test_to_suite( p_suite, test_union_3, "test_union_3" );

   // test_union_4
   add_test_to_suite( p_suite, test_union_4, "test_union_4" );

   // test_union_5
   add_test_to_suite( p_suite, test_union_5, "test_union_5" );

   // test_union_6
   add_test_to_suite( p_suite, test_union_6, "test_union_6" );

   // test_union_7
   add_test_to_suite( p_suite, test_union_7, "test_union_7" );

   // test_union_8
   add_test_to_suite( p_suite, test_union_8, "test_union_8" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

