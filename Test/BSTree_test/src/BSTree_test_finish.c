/**
 @file BSTree_test_finish.c
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
   test_finish_1
*/

void test_finish_1( void )
{
   i_bstree_t *bstree = NULL;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 1 );
   
   i_bstree_finish( bstree );
   
   CU_ASSERT( i_bstree_item_at( bstree ) == 1 );
   CU_ASSERT( i_bstree_off( bstree ) == 0 );
 
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_finish_2
*/

void test_finish_2( void )
{
   i_bstree_t *bstree = NULL;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   
   i_bstree_finish( bstree );
   
   CU_ASSERT( i_bstree_item_at( bstree ) == 3 );
 
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_finish_3
*/

void test_finish_3( void )
{
   i_bstree_t *bstree = NULL;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 1 );
   
   i_bstree_finish( bstree );
   
   CU_ASSERT( i_bstree_item_at( bstree ) == 3 );
 
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_finish_4
*/

void test_finish_4( void )
{
   i_bstree_t *bstree = NULL;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 3 );
   
   i_bstree_finish( bstree );
   
   CU_ASSERT( i_bstree_item_at( bstree ) == 3 );
 
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_finish_5
   
            4
         2      6
       1  
*/

void test_finish_5( void )
{
   i_bstree_t *bstree = NULL;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 1 );
   
   i_bstree_finish( bstree );
   
   CU_ASSERT( i_bstree_item_at( bstree ) == 6 );
 
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_finish_6
   
            4
         2      6
            3       
*/

void test_finish_6( void )
{
   i_bstree_t *bstree = NULL;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 3 );
   
   i_bstree_finish( bstree );
   
   CU_ASSERT( i_bstree_item_at( bstree ) == 6 );
 
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_finish_7
   
            4
         2      6
            3       
*/

void test_finish_7( void )
{
   s_bstree_t *bstree = NULL;
   
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s3 = string_make_from_cstring( "3" );
   string_t *s4 = string_make_from_cstring( "4" );
   string_t *s6 = string_make_from_cstring( "6" );
   
   bstree = s_bstree_make();
   
   s_bstree_put( bstree, s4 );
   s_bstree_put( bstree, s2 );
   s_bstree_put( bstree, s6 );
   s_bstree_put( bstree, s3 );
   
   s_bstree_finish( bstree );
   
   CU_ASSERT( s_bstree_item_at( bstree ) == s6 );
 
   s_bstree_deep_dispose( &bstree );

   return;
}


int
add_test_finish( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_finish", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_finish_1
   add_test_to_suite( p_suite, test_finish_1, "test_finish_1" );

   // test_finish_2
   add_test_to_suite( p_suite, test_finish_2, "test_finish_2" );

   // test_finish_3
   add_test_to_suite( p_suite, test_finish_3, "test_finish_3" );

   // test_finish_4
   add_test_to_suite( p_suite, test_finish_4, "test_finish_4" );

   // test_finish_5
   add_test_to_suite( p_suite, test_finish_5, "test_finish_5" );

   // test_finish_6
   add_test_to_suite( p_suite, test_finish_6, "test_finish_6" );

   // test_finish_7
   add_test_to_suite( p_suite, test_finish_7, "test_finish_7" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

