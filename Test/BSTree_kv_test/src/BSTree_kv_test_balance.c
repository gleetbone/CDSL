/**
 @file BSTree_test_balance.c
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
   test_balance_1
*/

void test_balance_1( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 10, 1 );
   
   ii_bstree_kv_balance( bstree );
   
   CU_ASSERT( ii_bstree_kv_height( bstree ) == 1 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}

/**
   test_balance_2
*/

void test_balance_2( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   ii_bstree_kv_balance( bstree );
   
   CU_ASSERT( ii_bstree_kv_height( bstree ) == 2 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}

/**
   test_balance_3
*/

void test_balance_3( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   
   ii_bstree_kv_balance( bstree );
   
   CU_ASSERT( ii_bstree_kv_height( bstree ) == 2 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}

/**
   test_balance_4
*/

void test_balance_4( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   ii_bstree_kv_balance( bstree );
   
   CU_ASSERT( ii_bstree_kv_height( bstree ) == 2 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}

/**
   test_balance_5
   
*/

void test_balance_5( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   
   ii_bstree_kv_balance( bstree );
   
   CU_ASSERT( ii_bstree_kv_height( bstree ) == 3 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}

/**
   test_balance_6
*/

void test_balance_6( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 40, 4 );
   
   ii_bstree_kv_balance( bstree );
   
   CU_ASSERT( ii_bstree_kv_height( bstree ) == 3 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}

/**
   test_balance_7
*/

void test_balance_7( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 70, 7 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 50, 5 );
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   
   ii_bstree_kv_balance( bstree );
   
   CU_ASSERT( ii_bstree_kv_height( bstree ) == 3 );

   ii_bstree_kv_dispose( bstree );

   return;
}

/**
   test_balance_8
   
            4
         2      6
                  7   
*/

void test_balance_8( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 50, 5 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 70, 7 );
   
   ii_bstree_kv_balance( bstree );
   
   CU_ASSERT( ii_bstree_kv_height( bstree ) == 3 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}

int
add_test_balance( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_balance", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_balance_1
   add_test_to_suite( p_suite, test_balance_1, "test_balance_1" );

   // test_balance_2
   add_test_to_suite( p_suite, test_balance_2, "test_balance_2" );

   // test_balance_3
   add_test_to_suite( p_suite, test_balance_3, "test_balance_3" );

   // test_balance_4
   add_test_to_suite( p_suite, test_balance_4, "test_balance_4" );

   // test_balance_5
   add_test_to_suite( p_suite, test_balance_5, "test_balance_5" );

   // test_balance_6
   add_test_to_suite( p_suite, test_balance_6, "test_balance_6" );

   // test_balance_7
   add_test_to_suite( p_suite, test_balance_7, "test_balance_7" );

   // test_balance_8
   add_test_to_suite( p_suite, test_balance_8, "test_balance_8" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

