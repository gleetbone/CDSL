/**
 @file RBTree_test_is_deep_equal.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for RBTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for RBTree_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_RBTree.h"
#include "s_RBTree.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_is_deep_equal_1
*/

void test_is_deep_equal_1( void )
{
   i_rbtree_t *rbtree = NULL;
   i_rbtree_t *rbtree1 = NULL;
   
   rbtree = i_rbtree_make();
   
   rbtree1 = i_rbtree_make();
   
   CU_ASSERT( i_rbtree_is_deep_equal( rbtree, rbtree1 ) == 1 );
 
   i_rbtree_dispose( &rbtree );
   i_rbtree_dispose( &rbtree1 );

   return;
}

/**
   test_is_deep_equal_2
*/

void test_is_deep_equal_2( void )
{
   i_rbtree_t *rbtree = NULL;
   i_rbtree_t *rbtree1 = NULL;
   
   rbtree = i_rbtree_make();
   i_rbtree_put( rbtree, 13 );
   
   rbtree1 = i_rbtree_make();
   i_rbtree_put( rbtree1, 13 );
   
   CU_ASSERT( i_rbtree_is_deep_equal( rbtree, rbtree1 ) == 1 );
 
   i_rbtree_dispose( &rbtree );
   i_rbtree_dispose( &rbtree1 );

   return;
}

/**
   test_is_deep_equal_3
*/

void test_is_deep_equal_3( void )
{
   s_rbtree_t *rbtree = NULL;
   s_rbtree_t *rbtree1 = NULL;
   
   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s1a = string_make_from_cstring( "1" );
   
   rbtree = s_rbtree_make();
   s_rbtree_put( rbtree, s1 );
   
   rbtree1 = s_rbtree_make();
   s_rbtree_put( rbtree1, s1a );
   
   CU_ASSERT( s_rbtree_is_deep_equal( rbtree, rbtree1 ) == 1 );
 
   s_rbtree_deep_dispose( &rbtree );
   s_rbtree_deep_dispose( &rbtree1 );

   return;
}

int
add_test_is_deep_equal( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_deep_equal", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_deep_equal_1
   add_test_to_suite( p_suite, test_is_deep_equal_1, "test_is_deep_equal_1" );

   // test_is_deep_equal_2
   add_test_to_suite( p_suite, test_is_deep_equal_2, "test_is_deep_equal_2" );

   // test_is_deep_equal_3
   add_test_to_suite( p_suite, test_is_deep_equal_3, "test_is_deep_equal_3" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

