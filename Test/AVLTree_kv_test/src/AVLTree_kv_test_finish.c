/**
 @file AVLTree_test_finish.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for AVLTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for AVLTree_make.

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_AVLTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_finish_1
*/

void test_finish_1( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 10, 1 );
   
   ii_avltree_kv_finish( avltree );
   
   CU_ASSERT( ii_avltree_kv_item_at( avltree ) == 10 );
   CU_ASSERT( ii_avltree_kv_off( avltree ) == 0 );
 
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_finish_2
*/

void test_finish_2( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   ii_avltree_kv_finish( avltree );
   
   CU_ASSERT( ii_avltree_kv_item_at( avltree ) == 30 );
 
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_finish_3
*/

void test_finish_3( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   
   ii_avltree_kv_finish( avltree );
   
   CU_ASSERT( ii_avltree_kv_item_at( avltree ) == 30 );
 
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_finish_4
*/

void test_finish_4( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   ii_avltree_kv_finish( avltree );
   
   CU_ASSERT( ii_avltree_kv_item_at( avltree ) == 30 );
 
   ii_avltree_kv_dispose( avltree );

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
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 10, 1 );
   
   ii_avltree_kv_finish( avltree );
   
   CU_ASSERT( ii_avltree_kv_item_at( avltree ) == 60 );
 
   ii_avltree_kv_dispose( avltree );

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
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   ii_avltree_kv_finish( avltree );
   
   CU_ASSERT( ii_avltree_kv_item_at( avltree ) == 60 );
 
   ii_avltree_kv_dispose( avltree );

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

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

