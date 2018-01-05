/**
 @file RBTree_test_make.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for BSTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for BSTree_make.

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_RBTree.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_make_1
*/

void test_make_1( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   CU_ASSERT( rbtree != NULL );
   CU_ASSERT( i_rbtree_count( rbtree ) == 0 );
   CU_ASSERT( i_rbtree_is_empty( rbtree ) == 1 );
 
   i_rbtree_dispose( rbtree );
   
   return;
}

/**
   test_make_2
*/

void test_make_2( void )
{
   i_rbtree_t *rbtree = NULL;
   i_rbtree_t *rbtree1 = NULL;
   
   rbtree = i_rbtree_make();
   i_rbtree_put( rbtree, 13 );
   
   rbtree1 = i_rbtree_make_duplicate_from( rbtree );
   
   CU_ASSERT( rbtree1 != NULL );
   CU_ASSERT( i_rbtree_count( rbtree1 ) == 1 );
   CU_ASSERT( i_rbtree_has( rbtree1, 13 ) == 1 );
 
   i_rbtree_dispose( rbtree );
   i_rbtree_dispose( rbtree1 );
   
   return;
}

/**
   test_make_3
*/

void test_make_3( void )
{
   i_rbtree_t *rbtree = NULL;
   i_rbtree_t *rbtree1 = NULL;
   
   rbtree = i_rbtree_make();
   i_rbtree_put( rbtree, 13 );
   
   rbtree1 = i_rbtree_make_from( rbtree );
   
   CU_ASSERT( rbtree1 != NULL );
   CU_ASSERT( i_rbtree_count( rbtree1 ) == 1 );
   CU_ASSERT( i_rbtree_has( rbtree1, 13 ) == 1 );
 
   i_rbtree_dispose( rbtree );
   i_rbtree_dispose( rbtree1 );
   
   return;
}

/**
   test_make_4
*/

void test_make_4( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t array[3] = {13, 0, 0 };

   rbtree = i_rbtree_make_from_array( array, 1 );

   CU_ASSERT( rbtree != NULL );
   CU_ASSERT( i_rbtree_count( rbtree ) == 1 );
   CU_ASSERT( i_rbtree_has( rbtree, 13 ) == 1 );

   i_rbtree_dispose( rbtree );

   return;
}

int
add_test_make( void )
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
   add_test_to_suite( p_suite, test_make_1, "test_make_1" );

   // test_make_2
   add_test_to_suite( p_suite, test_make_2, "test_make_2" );

   // test_make_3
   add_test_to_suite( p_suite, test_make_3, "test_make_3" );

   // test_make_4
   add_test_to_suite( p_suite, test_make_4, "test_make_4" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

