/**
 @file RBTree_test_make_from_array.c
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
   test_make_from_array_1
*/

void test_make_from_array_1( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t array[3] = {13, 0, 0 };

   rbtree = i_rbtree_make_from_array( array, 1 );

   CU_ASSERT( rbtree != NULL );
   CU_ASSERT( i_rbtree_count( rbtree ) == 1 );
   CU_ASSERT( i_rbtree_has( rbtree, 13 ) == 1 );

   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_make_from_array_2
*/

void test_make_from_array_2( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t array[3] = { 13, 24, 7 };

   rbtree = i_rbtree_make_from_array( array, 2 );

   CU_ASSERT( rbtree != NULL );
   CU_ASSERT( i_rbtree_count( rbtree ) == 2 );
   CU_ASSERT( i_rbtree_has( rbtree, 13 ) == 1 );
   CU_ASSERT( i_rbtree_has( rbtree, 24 ) == 1 );
   CU_ASSERT( i_rbtree_has( rbtree, 7 ) == 0 );

   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_make_from_array_3
*/

void test_make_from_array_3( void )
{
   s_rbtree_t *rbtree = NULL;
   
   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s3 = string_make_from_cstring( "3" );
   
   string_t *array[3] = { s1, s2, s3 };

   rbtree = s_rbtree_make_from_array( array, 2 );

   CU_ASSERT( rbtree != NULL );
   CU_ASSERT( s_rbtree_count( rbtree ) == 2 );
   CU_ASSERT( s_rbtree_has( rbtree, s1 ) == 1 );
   CU_ASSERT( s_rbtree_has( rbtree, s2 ) == 1 );
   CU_ASSERT( s_rbtree_has( rbtree, s3 ) == 0 );

   string_deep_dispose( &s3 );
   s_rbtree_deep_dispose( &rbtree );

   return;
}

int
add_test_make_from_array( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make_from_array", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_from_array_1
   add_test_to_suite( p_suite, test_make_from_array_1, "test_make_from_array_1" );

   // test_make_from_array_2
   add_test_to_suite( p_suite, test_make_from_array_2, "test_make_from_array_2" );

   // test_make_from_array_3
   add_test_to_suite( p_suite, test_make_from_array_3, "test_make_from_array_3" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

