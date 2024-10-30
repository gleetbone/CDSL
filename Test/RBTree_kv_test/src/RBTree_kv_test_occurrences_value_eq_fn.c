/**
 @file RBTree_test_occurrences_value_eq_fn.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for RBTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for RBTree_kv_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_RBTree_kv.h"
#include "ss_RBTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

static int32_t is_equal_int( int32_t i1, int32_t i2 )
{
   return ( i1 == i2 );
}

static int32_t is_equal_s( string_t *s1, string_t *s2 )
{
   return ( string_is_deep_equal( s1, s2 ) == 1 );
}

/**
   test_occurrences_value_eq_fn_1
*/

void test_occurrences_value_eq_fn_1( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   CU_ASSERT( ii_rbtree_kv_occurrences_value_eq_fn( rbtree, 10, is_equal_int ) == 0 );
 
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_occurrences_value_eq_fn_2
*/

void test_occurrences_value_eq_fn_2( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 10, 1 );
   
   CU_ASSERT( ii_rbtree_kv_occurrences_value_eq_fn( rbtree, 10, is_equal_int ) == 1 );
              
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_occurrences_value_eq_fn_3
*/

void test_occurrences_value_eq_fn_3( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   
   CU_ASSERT( ii_rbtree_kv_occurrences_value_eq_fn( rbtree, 10, is_equal_int ) == 1 );
   CU_ASSERT( ii_rbtree_kv_occurrences_value_eq_fn( rbtree, 20, is_equal_int ) == 2 );
   CU_ASSERT( ii_rbtree_kv_occurrences_value_eq_fn( rbtree, 30, is_equal_int ) == 1 );
 
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_occurrences_value_eq_fn_4
*/

void test_occurrences_value_eq_fn_4( void )
{
   ss_rbtree_kv_t *rbtree = NULL;
   
   string_t *s1 = NULL;
   string_t *s10 = NULL;
   string_t *s2 = NULL;
   string_t *s20 = NULL;
   string_t *s2a = NULL;
   string_t *s20a = NULL;
   string_t *s3 = NULL;
   string_t *s30 = NULL;
   
   s1 = string_make_from_cstring( "1" );
   s10 = string_make_from_cstring( "10" );
   s2 = string_make_from_cstring( "2" );
   s20 = string_make_from_cstring( "20" );
   s2a = string_make_from_cstring( "2" );
   s20a = string_make_from_cstring( "20" );
   s3 = string_make_from_cstring( "3" );
   s30 = string_make_from_cstring( "30" );
   
   rbtree = ss_rbtree_kv_make();
   
   ss_rbtree_kv_put( rbtree, s30, s3 );
   ss_rbtree_kv_put( rbtree, s20, s2 );
   ss_rbtree_kv_put( rbtree, s10, s1 );
   ss_rbtree_kv_put( rbtree, s20a, s2a );
   
   CU_ASSERT( ss_rbtree_kv_occurrences_value_eq_fn( rbtree, s10, is_equal_s ) == 1 );
   CU_ASSERT( ss_rbtree_kv_occurrences_value_eq_fn( rbtree, s20, is_equal_s ) == 2 );
   CU_ASSERT( ss_rbtree_kv_occurrences_value_eq_fn( rbtree, s30, is_equal_s ) == 1 );
 
   ss_rbtree_kv_deep_dispose( &rbtree );

   return;
}

int
add_test_occurrences_value_eq_fn( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_occurrences_value_eq_fn", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_occurrences_value_eq_fn_1
   add_test_to_suite( p_suite, test_occurrences_value_eq_fn_1, "test_occurrences_value_eq_fn_1" );

   // test_occurrences_value_eq_fn_2
   add_test_to_suite( p_suite, test_occurrences_value_eq_fn_2, "test_occurrences_value_eq_fn_2" );

   // test_occurrences_value_eq_fn_3
   add_test_to_suite( p_suite, test_occurrences_value_eq_fn_3, "test_occurrences_value_eq_fn_3" );

   // test_occurrences_value_eq_fn_4
   add_test_to_suite( p_suite, test_occurrences_value_eq_fn_4, "test_occurrences_value_eq_fn_4" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */
