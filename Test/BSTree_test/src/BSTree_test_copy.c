/**
 @file BSTree_test_copy.c
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
   test_copy_1
*/

void test_copy_1( void )
{
   i_bstree_t *bstree = NULL;
   i_bstree_t *bstree1 = NULL;
   
   bstree = i_bstree_make();
   bstree1 = i_bstree_make();
   
   i_bstree_copy( bstree1, bstree );
   
   CU_ASSERT( bstree1 != NULL );
   CU_ASSERT( i_bstree_count( bstree1 ) == 0 );
 
   i_bstree_dispose( &bstree );
   i_bstree_dispose( &bstree1 );

   return;
}

/**
   test_copy_2
*/

void test_copy_2( void )
{
   i_bstree_t *bstree = NULL;
   i_bstree_t *bstree1 = NULL;
   
   bstree = i_bstree_make();
   i_bstree_put( bstree, 13 );
   
   bstree1 = i_bstree_make();
   
   i_bstree_copy( bstree1, bstree );
   
   CU_ASSERT( bstree1 != NULL );
   CU_ASSERT( i_bstree_count( bstree1 ) == 1 );
   CU_ASSERT( i_bstree_has( bstree1, 13 ) == 1 );
 
   i_bstree_dispose( &bstree );
   i_bstree_dispose( &bstree1 );

   return;
}

/**
   test_copy_3
*/

void test_copy_3( void )
{
   i_bstree_t *bstree = NULL;
   i_bstree_t *bstree1 = NULL;
   
   bstree = i_bstree_make();
   i_bstree_put( bstree, 13 );
   
   bstree1 = i_bstree_make();
   i_bstree_put( bstree1, 7 );
   
   i_bstree_copy( bstree1, bstree );
   
   CU_ASSERT( bstree1 != NULL );
   CU_ASSERT( i_bstree_count( bstree1 ) == 1 );
   CU_ASSERT( i_bstree_has( bstree1, 13 ) == 1 );
 
   i_bstree_dispose( &bstree );
   i_bstree_dispose( &bstree1 );

   return;
}

/**
   test_copy_4
*/

void test_copy_4( void )
{
   s_bstree_t *bstree = NULL;
   s_bstree_t *bstree1 = NULL;
   
   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   
   bstree = s_bstree_make();
   s_bstree_put( bstree, s1 );
   
   bstree1 = s_bstree_make();
   s_bstree_put( bstree1, s2 );
   
   s_bstree_copy( bstree1, bstree );
   
   CU_ASSERT( bstree1 != NULL );
   CU_ASSERT( s_bstree_count( bstree1 ) == 1 );
   CU_ASSERT( s_bstree_has( bstree1, s1 ) == 1 );
 
   s_bstree_deep_dispose( &bstree );
   s_bstree_dispose( &bstree1 );

   return;
}

int
add_test_copy( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_copy", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_copy_1
   add_test_to_suite( p_suite, test_copy_1, "test_copy_1" );

   // test_copy_2
   add_test_to_suite( p_suite, test_copy_2, "test_copy_2" );

   // test_copy_3
   add_test_to_suite( p_suite, test_copy_3, "test_copy_3" );

   // test_copy_4
   add_test_to_suite( p_suite, test_copy_4, "test_copy_4" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

