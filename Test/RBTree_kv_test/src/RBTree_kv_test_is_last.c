/**
 @file RBTree_kv_test_is_last.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for RBTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for RBTree_kv_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_RBTree_kv.h"
#include "ss_RBTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_is_last_1
*/

void test_is_last_1( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_start( rbtree );
   
   CU_ASSERT( ii_rbtree_kv_is_last( rbtree ) == 0 );
 
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_is_last_1a
*/

void test_is_last_1a( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 10, 1 );
   
   ii_rbtree_kv_start( rbtree );
   
   CU_ASSERT( ii_rbtree_kv_is_last( rbtree ) == 1 );
 
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_is_last_2
*/

void test_is_last_2( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   ii_rbtree_kv_start( rbtree );
   
   CU_ASSERT( ii_rbtree_kv_is_last( rbtree ) == 0 );
 
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_is_last_3
*/

void test_is_last_3( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   
   ii_rbtree_kv_start( rbtree );
   
   CU_ASSERT( ii_rbtree_kv_is_last( rbtree ) == 0 );
 
   ii_rbtree_kv_finish( rbtree );
   
   CU_ASSERT( ii_rbtree_kv_is_last( rbtree ) == 1 );
 
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_is_last_4
*/

void test_is_last_4( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   ii_rbtree_kv_start( rbtree );
   
   CU_ASSERT( ii_rbtree_kv_is_last( rbtree ) == 0 );
 
   ii_rbtree_kv_finish( rbtree );
   
   CU_ASSERT( ii_rbtree_kv_is_last( rbtree ) == 1 );
 
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_is_last_5
   
            4
         2      6
       1  
*/

void test_is_last_5( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   
   ii_rbtree_kv_start( rbtree );
   
   CU_ASSERT( ii_rbtree_kv_is_last( rbtree ) == 0 );
 
   ii_rbtree_kv_finish( rbtree );
   
   CU_ASSERT( ii_rbtree_kv_is_last( rbtree ) == 1 );
 
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_is_last_6
   
            4
         2      6
            3       
*/

void test_is_last_6( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   ii_rbtree_kv_start( rbtree );
   
   CU_ASSERT( ii_rbtree_kv_is_last( rbtree ) == 0 );
 
   ii_rbtree_kv_finish( rbtree );
   
   CU_ASSERT( ii_rbtree_kv_is_last( rbtree ) == 1 );
 
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_is_last_7
*/

void test_is_last_7( void )
{
   ss_rbtree_kv_t *rbtree = NULL;
   
   string_t *s2 = NULL;
   string_t *s20 = NULL;
   string_t *s3 = NULL;
   string_t *s30 = NULL;
   string_t *s4 = NULL;
   string_t *s40 = NULL;
   string_t *s6 = NULL;
   string_t *s60 = NULL;
   
   s2 = string_make_from_cstring( "2" );
   s20 = string_make_from_cstring( "20" );
   s3 = string_make_from_cstring( "3" );
   s30 = string_make_from_cstring( "30" );
   s4 = string_make_from_cstring( "4" );
   s40 = string_make_from_cstring( "40" );
   s6 = string_make_from_cstring( "6" );
   s60 = string_make_from_cstring( "60" );
   
   rbtree = ss_rbtree_kv_make();
   
   ss_rbtree_kv_put( rbtree, s40, s4 );
   ss_rbtree_kv_put( rbtree, s20, s2 );
   ss_rbtree_kv_put( rbtree, s60, s6 );
   ss_rbtree_kv_put( rbtree, s30, s3 );
   
   ss_rbtree_kv_start( rbtree );
   
   CU_ASSERT( ss_rbtree_kv_is_last( rbtree ) == 0 );
 
   ss_rbtree_kv_finish( rbtree );
   
   CU_ASSERT( ss_rbtree_kv_is_last( rbtree ) == 1 );
 
   ss_rbtree_kv_deep_dispose( &rbtree );

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

   // test_is_last_1a
   add_test_to_suite( p_suite, test_is_last_1a, "test_is_last_1a" );

   // test_is_last_2
   add_test_to_suite( p_suite, test_is_last_2, "test_is_last_2" );

   // test_is_last_3
   add_test_to_suite( p_suite, test_is_last_3, "test_is_last_3" );

   // test_is_last_4
   add_test_to_suite( p_suite, test_is_last_4, "test_is_last_4" );

   // test_is_last_5
   add_test_to_suite( p_suite, test_is_last_5, "test_is_last_5" );

   // test_is_last_6
   add_test_to_suite( p_suite, test_is_last_6, "test_is_last_6" );

   // test_is_last_7
   add_test_to_suite( p_suite, test_is_last_7, "test_is_last_7" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

