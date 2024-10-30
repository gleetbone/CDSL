/**
 @file RBTree_test_as_string.c
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
#include "RBTree_kv_test_print_utility.h"

void convert_func( char_t *cstr, int32_t key, int32_t value )
{
   int32_t i = 0;
   char_t a[256] = {0};
   sprintf( a, "%d", value );

   for( i=0; a[i] != 0; i++ )
   {
      cstr[i] = a[i];
   }

   return;
}

void convert_func_s( char_t *cstr, string_t *key, string_t *value )
{
   int32_t i = 0;
   char_t a[256] = {0};
   strcpy( a, string_as_cstring( value ) );

   for( i=0; a[i] != 0; i++ )
   {
      cstr[i] = a[i];
   }

   return;
}

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_as_string_1
*/

void test_as_string_1( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   char_t **astr = NULL;

   rbtree = ii_rbtree_kv_make();

   ii_rbtree_kv_put( rbtree, 10, 1 );

   astr = test_print_utility_make_array( ii_rbtree_kv_height( rbtree ), 2 );

   CU_ASSERT( astr != NULL );

   ii_rbtree_kv_as_string( rbtree, astr, 2, convert_func );

   test_print_utility_print_array( astr );

   test_print_utility_dispose_array( astr );

   ii_rbtree_kv_dispose( &rbtree );
   
   return;
}

/**
   test_as_string_2
*/

void test_as_string_2( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   char_t **astr = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   astr = test_print_utility_make_array( ii_rbtree_kv_height( rbtree ), 2 );

   CU_ASSERT( astr != NULL );

   ii_rbtree_kv_as_string( rbtree, astr, 2, convert_func );

   test_print_utility_print_array( astr );

   test_print_utility_dispose_array( astr );
 
   ii_rbtree_kv_dispose( &rbtree );
   
   return;
}

/**
   test_as_string_3
*/

void test_as_string_3( void )
{
   ss_rbtree_kv_t *rbtree = NULL;
   char_t **astr = NULL;
   
   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s3 = string_make_from_cstring( "3" );
   string_t *s10 = string_make_from_cstring( "10" );
   string_t *s20 = string_make_from_cstring( "20" );
   string_t *s30 = string_make_from_cstring( "30" );
   
   rbtree = ss_rbtree_kv_make();
   
   ss_rbtree_kv_put( rbtree, s20, s2 );
   ss_rbtree_kv_put( rbtree, s10, s1 );
   ss_rbtree_kv_put( rbtree, s30, s3 );
   
   astr = test_print_utility_make_array( ss_rbtree_kv_height( rbtree ), 2 );

   CU_ASSERT( astr != NULL );

   ss_rbtree_kv_as_string( rbtree, astr, 2, convert_func_s );

   test_print_utility_print_array( astr );

   test_print_utility_dispose_array( astr );
 
   ss_rbtree_kv_deep_dispose( &rbtree );
   
   return;
}

int
add_test_as_string( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_as_string", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_as_string_1
   add_test_to_suite( p_suite, test_as_string_1, "test_as_string_1" );

   // test_as_string_2
   add_test_to_suite( p_suite, test_as_string_2, "test_as_string_2" );

   // test_as_string_3
   add_test_to_suite( p_suite, test_as_string_3, "test_as_string_3" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

