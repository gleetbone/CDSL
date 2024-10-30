/**
 @file AVLTree_test_is_last.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for AVLTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for AVLTree_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_AVLTree.h"
#include "s_AVLTree.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_is_last_1
*/

void test_is_last_1( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   CU_ASSERT( i_avltree_is_last( avltree ) == 0 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_is_last_2
*/

void test_is_last_2( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 1 );
   
   CU_ASSERT( i_avltree_is_last( avltree ) == 0 );
   
   i_avltree_start( avltree );
   CU_ASSERT( i_avltree_is_last( avltree ) == 1 );
   
   i_avltree_forth( avltree );
   CU_ASSERT( i_avltree_is_last( avltree ) == 0 );
 
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_is_last_3
*/

void test_is_last_3( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   
   CU_ASSERT( i_avltree_is_last( avltree ) == 0 );

   i_avltree_start( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 1 );
   CU_ASSERT( i_avltree_is_last( avltree ) == 0 );
 
   i_avltree_forth( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 2 );
   CU_ASSERT( i_avltree_is_last( avltree ) == 0 );
 
   i_avltree_forth( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 3 );
   CU_ASSERT( i_avltree_is_last( avltree ) == 1 );
 
   i_avltree_forth( avltree );
   CU_ASSERT( i_avltree_is_last( avltree ) == 0 );
 
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_is_last_4
*/

void test_is_last_4( void )
{
   s_avltree_t *avltree = NULL;
   
   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s3 = string_make_from_cstring( "3" );
   
   avltree = s_avltree_make();
   
   s_avltree_put( avltree, s2 );
   s_avltree_put( avltree, s1 );
   s_avltree_put( avltree, s3 );
   
   CU_ASSERT( s_avltree_is_last( avltree ) == 0 );

   s_avltree_start( avltree );
   CU_ASSERT( s_avltree_item_at( avltree ) == s1 );
   CU_ASSERT( s_avltree_is_last( avltree ) == 0 );
 
   s_avltree_forth( avltree );
   CU_ASSERT( s_avltree_item_at( avltree ) == s2 );
   CU_ASSERT( s_avltree_is_last( avltree ) == 0 );
 
   s_avltree_forth( avltree );
   CU_ASSERT( s_avltree_item_at( avltree ) == s3 );
   CU_ASSERT( s_avltree_is_last( avltree ) == 1 );
 
   s_avltree_forth( avltree );
   CU_ASSERT( s_avltree_is_last( avltree ) == 0 );
 
   s_avltree_deep_dispose( &avltree );

   return;
}

int
add_test_is_last( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_last", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_last_1
   add_test_to_suite( p_suite, test_is_last_1, "test_is_last_1" );

   // test_is_last_2
   add_test_to_suite( p_suite, test_is_last_2, "test_is_last_2" );

   // test_is_last_3
   add_test_to_suite( p_suite, test_is_last_3, "test_is_last_3" );

   // test_is_last_4
   add_test_to_suite( p_suite, test_is_last_4, "test_is_last_4" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */
