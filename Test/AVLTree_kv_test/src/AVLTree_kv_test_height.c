/**
 @file AVLTree_test_height.c
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
   test_height_1
*/

void test_height_1( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   CU_ASSERT( ii_avltree_kv_height( avltree ) == 0 );
 
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_height_2
*/

void test_height_2( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 10, 1 );
   
   CU_ASSERT( ii_avltree_kv_height( avltree ) == 1 );
 
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_height_3
*/

void test_height_3( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   CU_ASSERT( ii_avltree_kv_height( avltree ) == 2 );

   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_height_4
*/

void test_height_4( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   
   CU_ASSERT( ii_avltree_kv_height( avltree ) == 2 );
 
   ii_avltree_kv_dispose( avltree );

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
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 10, 1 );
   
   CU_ASSERT( ii_avltree_kv_height( avltree ) == 3 );
 
   ii_avltree_kv_dispose( avltree );

   return;
}


/**
   test_height_6
   
*/

void test_height_6( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 50, 5 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 70, 7 );
   
   CU_ASSERT( ii_avltree_kv_height( avltree ) == 3 );

   ii_avltree_kv_dispose( avltree );

   return;
}


/**
   test_height_7
   
*/

void test_height_7( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 70, 7 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 50, 5 );
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   
   CU_ASSERT( ii_avltree_kv_height( avltree ) == 3 );
 
   ii_avltree_kv_dispose( avltree );

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

   // test_height_7
   add_test_to_suite( p_suite, test_height_7, "test_height_7" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

