/**
 @file AVLTree_test_is_empty.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for AVLTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for AVLTree_kv_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_AVLTree_kv.h"
#include "ss_AVLTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_is_empty_1
*/

void test_is_empty_1( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   CU_ASSERT( ii_avltree_kv_is_empty( avltree ) == 1 );
   
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_is_empty_2
*/

void test_is_empty_2( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 20, 2 );
   
   CU_ASSERT( ii_avltree_kv_is_empty( avltree ) == 0 );
   
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_is_empty_3
*/

void test_is_empty_3( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   
   CU_ASSERT( ii_avltree_kv_is_empty( avltree ) == 0 );
   
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_is_empty_4
*/

void test_is_empty_4( void )
{
   ss_avltree_kv_t *avltree = NULL;
   
   string_t *s1 = NULL;
   string_t *s10 = NULL;
   string_t *s2 = NULL;
   string_t *s20 = NULL;
   string_t *s3 = NULL;
   string_t *s30 = NULL;
   
   s1 = string_make_from_cstring( "1" );
   s10 = string_make_from_cstring( "10" );
   s2 = string_make_from_cstring( "2" );
   s20 = string_make_from_cstring( "20" );
   s3 = string_make_from_cstring( "3" );
   s30 = string_make_from_cstring( "30" );
   
   avltree = ss_avltree_kv_make();
   
   ss_avltree_kv_put( avltree, s30, s3 );
   ss_avltree_kv_put( avltree, s20, s2 );
   ss_avltree_kv_put( avltree, s10, s1 );
   
   CU_ASSERT( ss_avltree_kv_is_empty( avltree ) == 0 );
   
   ss_avltree_kv_deep_dispose( &avltree );

   return;
}

int
add_test_is_empty( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_empty", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_empty_1
   add_test_to_suite( p_suite, test_is_empty_1, "test_is_empty_1" );

   // test_is_empty_2
   add_test_to_suite( p_suite, test_is_empty_2, "test_is_empty_2" );

   // test_is_empty_3
   add_test_to_suite( p_suite, test_is_empty_3, "test_is_empty_3" );

   // test_is_empty_4
   add_test_to_suite( p_suite, test_is_empty_4, "test_is_empty_4" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

