/**
 @file RBTree_test_put.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for RBTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for RBTree_make.

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_RBTree.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_put_1
*/

void test_put_1( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 1 );
   
   CU_ASSERT( i_rbtree_count( rbtree ) == 1 );
   CU_ASSERT( i_rbtree_is_empty( rbtree ) == 0 );
 
   i_rbtree_dispose( rbtree );
   
   return;
}

/**
   test_put_2
*/

void test_put_2( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   
   CU_ASSERT( i_rbtree_count( rbtree ) == 3 );
 
   i_rbtree_dispose( rbtree );
   
   return;
}

/**
   test_put_3
*/

void test_put_3( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   
   CU_ASSERT( i_rbtree_count( rbtree ) == 3 );
 
   i_rbtree_dispose( rbtree );
   
   return;
}

/**
   test_put_4
*/

void test_put_4( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 3 );
   
   CU_ASSERT( i_rbtree_count( rbtree ) == 3 );
 
   i_rbtree_dispose( rbtree );
   
   return;
}

/**
   test_put_4a
*/

void test_put_4a( void )
{
   i_rbtree_t *rbtree = NULL;

   rbtree = i_rbtree_make();

   i_rbtree_put( rbtree, 8 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 3 );

   CU_ASSERT( i_rbtree_count( rbtree ) == 3 );

   i_rbtree_dispose( rbtree );
   
   return;
}

/**
   test_put_5
   
            4
         2      6
       1  
*/

void test_put_5( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 1 );
   
   CU_ASSERT( i_rbtree_count( rbtree ) == 4 );
 
   i_rbtree_dispose( rbtree );
   
   return;
}

/**
   test_put_6
   
            4
         2      6
            3       
*/

void test_put_6( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 3 );
   
   CU_ASSERT( i_rbtree_count( rbtree ) == 4 );
 
   i_rbtree_dispose( rbtree );
   
   return;
}

/**
   test_put_7
   
            4
         2      6
              5 
*/

void test_put_7( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 5 );
   
   CU_ASSERT( i_rbtree_count( rbtree ) == 4 );
 
   i_rbtree_dispose( rbtree );
   
   return;
}

/**
   test_put_8
   
            4
         2      6
                  7   
*/

void test_put_8( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 7 );
   
   CU_ASSERT( i_rbtree_count( rbtree ) == 4 );
 
   i_rbtree_dispose( rbtree );
   
   return;
}

int
add_test_put( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_put", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_put_1
   add_test_to_suite( p_suite, test_put_1, "test_put_1" );

   // test_put_2
   add_test_to_suite( p_suite, test_put_2, "test_put_2" );

   // test_put_3
   add_test_to_suite( p_suite, test_put_3, "test_put_3" );

   // test_put_4
   add_test_to_suite( p_suite, test_put_4, "test_put_4" );
   add_test_to_suite( p_suite, test_put_4a, "test_put_4a" );

   // test_put_5
   add_test_to_suite( p_suite, test_put_5, "test_put_5" );

   // test_put_6
   add_test_to_suite( p_suite, test_put_6, "test_put_6" );

   // test_put_7
   add_test_to_suite( p_suite, test_put_7, "test_put_7" );

   // test_put_8
   add_test_to_suite( p_suite, test_put_8, "test_put_8" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

