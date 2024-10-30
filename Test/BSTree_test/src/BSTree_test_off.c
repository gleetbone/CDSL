/**
 @file BSTree_test_off.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BSTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for BSTree_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_BSTree.h"
#include "s_BSTree.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_off_1
*/

void test_off_1( void )
{
   i_bstree_t *bstree = NULL;
   
   bstree = i_bstree_make();
   
   CU_ASSERT( i_bstree_off( bstree ) == 1 );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_off_2
*/

void test_off_2( void )
{
   i_bstree_t *bstree = NULL;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 1 );
   
   i_bstree_start( bstree );
   CU_ASSERT( i_bstree_off( bstree ) == 0 );
   
   i_bstree_forth( bstree );
   CU_ASSERT( i_bstree_off( bstree ) == 1 );
 
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_off_3
*/

void test_off_3( void )
{
   i_bstree_t *bstree = NULL;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   
   i_bstree_start( bstree );
   CU_ASSERT( i_bstree_item_at( bstree ) == 1 );
   CU_ASSERT( i_bstree_off( bstree ) == 0 );
 
   i_bstree_forth( bstree );
   CU_ASSERT( i_bstree_item_at( bstree ) == 2 );
   CU_ASSERT( i_bstree_off( bstree ) == 0 );
 
   i_bstree_forth( bstree );
   CU_ASSERT( i_bstree_item_at( bstree ) == 3 );
   CU_ASSERT( i_bstree_off( bstree ) == 0 );
 
   i_bstree_forth( bstree );
   CU_ASSERT( i_bstree_off( bstree ) == 1 );
 
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_off_4
*/

void test_off_4( void )
{
   s_bstree_t *bstree = NULL;
   
   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s3 = string_make_from_cstring( "3" );
   
   bstree = s_bstree_make();
   
   s_bstree_put( bstree, s2 );
   s_bstree_put( bstree, s1 );
   s_bstree_put( bstree, s3 );
   
   s_bstree_start( bstree );
   CU_ASSERT( s_bstree_item_at( bstree ) == s1 );
   CU_ASSERT( s_bstree_off( bstree ) == 0 );
 
   s_bstree_forth( bstree );
   CU_ASSERT( s_bstree_item_at( bstree ) == s2 );
   CU_ASSERT( s_bstree_off( bstree ) == 0 );
 
   s_bstree_forth( bstree );
   CU_ASSERT( s_bstree_item_at( bstree ) == s3 );
   CU_ASSERT( s_bstree_off( bstree ) == 0 );
 
   s_bstree_forth( bstree );
   CU_ASSERT( s_bstree_off( bstree ) == 1 );
 
   s_bstree_deep_dispose( &bstree );

   return;
}

int
add_test_off( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_off", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_off_1
   add_test_to_suite( p_suite, test_off_1, "test_off_1" );

   // test_off_2
   add_test_to_suite( p_suite, test_off_2, "test_off_2" );

   // test_off_3
   add_test_to_suite( p_suite, test_off_3, "test_off_3" );

   // test_off_4
   add_test_to_suite( p_suite, test_off_4, "test_off_4" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

