/**
 @file BSTree_test_start.c
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

#include "ii_BSTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_start_1
*/

void test_start_1( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 10, 1 );
   
   ii_bstree_kv_start( bstree );
   
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 10 );
   CU_ASSERT( ii_bstree_kv_off( bstree ) == 0 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}

/**
   test_start_2
*/

void test_start_2( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   ii_bstree_kv_start( bstree );
   
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 10 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}

/**
   test_start_3
*/

void test_start_3( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   
   ii_bstree_kv_start( bstree );
   
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 10 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}

/**
   test_start_4
*/

void test_start_4( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   ii_bstree_kv_start( bstree );
   
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 10 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}

/**
   test_start_5
   
            4
         2      6
       1  
*/

void test_start_5( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 10, 1 );
   
   ii_bstree_kv_start( bstree );
   
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 10 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}

/**
   test_start_6
   
            4
         2      6
            3       
*/

void test_start_6( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   ii_bstree_kv_start( bstree );
   
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 20 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}


int
add_test_start( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_start", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_start_1
   add_test_to_suite( p_suite, test_start_1, "test_start_1" );

   // test_start_2
   add_test_to_suite( p_suite, test_start_2, "test_start_2" );

   // test_start_3
   add_test_to_suite( p_suite, test_start_3, "test_start_3" );

   // test_start_4
   add_test_to_suite( p_suite, test_start_4, "test_start_4" );

   // test_start_5
   add_test_to_suite( p_suite, test_start_5, "test_start_5" );

   // test_start_6
   add_test_to_suite( p_suite, test_start_6, "test_start_6" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

