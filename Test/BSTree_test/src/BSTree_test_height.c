/**
 @file BSTree_test_height.c
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
   test_height_1
*/

void test_height_1( void )
{
   i_bstree_t *bstree = NULL;
   
   bstree = i_bstree_make();
   
   CU_ASSERT( i_bstree_height( bstree ) == 0 );
 
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_height_2
*/

void test_height_2( void )
{
   i_bstree_t *bstree = NULL;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 1 );
   
   CU_ASSERT( i_bstree_height( bstree ) == 1 );
 
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_height_3
*/

void test_height_3( void )
{
   i_bstree_t *bstree = NULL;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   
   CU_ASSERT( i_bstree_height( bstree ) == 2 );
 
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_height_4
*/

void test_height_4( void )
{
   i_bstree_t *bstree = NULL;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 1 );
   
   CU_ASSERT( i_bstree_height( bstree ) == 3 );
 
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_height_5
   
            4
         2      6
       1  
*/

void test_height_5( void )
{
   i_bstree_t *bstree = NULL;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 1 );
   
   CU_ASSERT( i_bstree_height( bstree ) == 3 );

   i_bstree_dispose( &bstree );

   return;
}

/**
   test_height_6
   
            4
         2      6
       1  
*/

void test_height_6( void )
{
   s_bstree_t *bstree = NULL;
   
   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s4 = string_make_from_cstring( "4" );
   string_t *s6 = string_make_from_cstring( "6" );
   
   bstree = s_bstree_make();
   
   s_bstree_put( bstree, s4 );
   s_bstree_put( bstree, s2 );
   s_bstree_put( bstree, s6 );
   s_bstree_put( bstree, s1 );
   
   CU_ASSERT( s_bstree_height( bstree ) == 3 );

   s_bstree_deep_dispose( &bstree );

   return;
}


int
add_test_height( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_height", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_height_1
   add_test_to_suite( p_suite, test_height_1, "test_height_1" );

   // test_height_2
   add_test_to_suite( p_suite, test_height_2, "test_height_2" );

   // test_height_3
   add_test_to_suite( p_suite, test_height_3, "test_height_3" );

   // test_height_4
   add_test_to_suite( p_suite, test_height_4, "test_height_4" );

   // test_height_5
   add_test_to_suite( p_suite, test_height_5, "test_height_5" );

   // test_height_6
   add_test_to_suite( p_suite, test_height_6, "test_height_6" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

