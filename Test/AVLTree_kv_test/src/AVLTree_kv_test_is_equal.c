/**
 @file AVLTree_test_is_equal.c
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
   test_is_equal_1
*/

void test_is_equal_1( void )
{
   ii_avltree_kv_t *avltree = NULL;
   ii_avltree_kv_t *avltree1 = NULL;
   
   avltree = ii_avltree_kv_make();
   
   avltree1 = ii_avltree_kv_make();
   
   ii_avltree_kv_deep_copy( avltree1, avltree );
   
   CU_ASSERT( ii_avltree_kv_is_equal( avltree1, avltree ) == 1 );
 
   ii_avltree_kv_dispose( &avltree );
   ii_avltree_kv_dispose( &avltree1 );

   return;
}

/**
   test_is_equal_2
*/

void test_is_equal_2( void )
{
   ii_avltree_kv_t *avltree = NULL;
   ii_avltree_kv_t *avltree1 = NULL;
   
   avltree = ii_avltree_kv_make();
   ii_avltree_kv_put( avltree, 130, 13 );
   
   avltree1 = ii_avltree_kv_make();
   ii_avltree_kv_put( avltree1, 130, 13 );
   
   CU_ASSERT( ii_avltree_kv_is_equal( avltree, avltree1 ) == 1 );
 
   ii_avltree_kv_dispose( &avltree );
   ii_avltree_kv_dispose( &avltree1 );

   return;
}

/**
   test_is_equal_2a
*/

void test_is_equal_2a( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   ii_avltree_kv_put( avltree, 130, 13 );
   
   CU_ASSERT( ii_avltree_kv_is_equal( avltree, avltree ) == 1 );
 
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_is_equal_3
*/

void test_is_equal_3( void )
{
   ss_avltree_kv_t *avltree = NULL;
   ss_avltree_kv_t *avltree1 = NULL;
   
   string_t *s1 = NULL;
   string_t *s10 = NULL;
   
   s1 = string_make_from_cstring( "1" );
   s10 = string_make_from_cstring( "10" );
   
   avltree = ss_avltree_kv_make();
   ss_avltree_kv_put( avltree, s10, s1 );
   
   avltree1 = ss_avltree_kv_make();
   ss_avltree_kv_put( avltree1, s10, s1 );
   
   CU_ASSERT( ss_avltree_kv_is_equal( avltree, avltree1 ) == 1 );
   CU_ASSERT( ss_avltree_kv_is_deep_equal( avltree, avltree1 ) == 1 );
 
   ss_avltree_kv_deep_dispose( &avltree );
   ss_avltree_kv_dispose( &avltree1 );

   return;
}

/**
   test_is_equal_4
*/

void test_is_equal_4( void )
{
   ss_avltree_kv_t *avltree = NULL;
   ss_avltree_kv_t *avltree1 = NULL;
   
   string_t *s1 = NULL;
   string_t *s10 = NULL;
   string_t *s1a = NULL;
   string_t *s10a = NULL;
   
   s1 = string_make_from_cstring( "1" );
   s10 = string_make_from_cstring( "10" );
   s1a = string_make_from_cstring( "1" );
   s10a = string_make_from_cstring( "10" );
   
   avltree = ss_avltree_kv_make();
   ss_avltree_kv_put( avltree, s10, s1 );
   
   avltree1 = ss_avltree_kv_make();
   ss_avltree_kv_put( avltree1, s10a, s1a );
   
   CU_ASSERT( ss_avltree_kv_is_equal( avltree, avltree1 ) == 0 );
   CU_ASSERT( ss_avltree_kv_is_deep_equal( avltree, avltree1 ) == 1 );
 
   ss_avltree_kv_deep_dispose( &avltree );
   ss_avltree_kv_deep_dispose( &avltree1 );

   return;
}

int
add_test_is_equal( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_equal", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_equal_1
   add_test_to_suite( p_suite, test_is_equal_1, "test_is_equal_1" );

   // test_is_equal_2
   add_test_to_suite( p_suite, test_is_equal_2, "test_is_equal_2" );

   // test_is_equal_2a
   add_test_to_suite( p_suite, test_is_equal_2a, "test_is_equal_2a" );

   // test_is_equal_3
   add_test_to_suite( p_suite, test_is_equal_3, "test_is_equal_3" );

   // test_is_equal_4
   add_test_to_suite( p_suite, test_is_equal_4, "test_is_equal_4" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

