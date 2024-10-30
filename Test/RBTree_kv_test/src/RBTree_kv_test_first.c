/**
 @file RBTree_test_first.c
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
   test_first_1
*/

void test_first_1( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 10, 1 );
   
   CU_ASSERT( ii_rbtree_kv_first( rbtree ) == 10 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_first_2
*/

void test_first_2( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   CU_ASSERT( ii_rbtree_kv_first( rbtree ) == 10 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_first_3
*/

void test_first_3( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   
   CU_ASSERT( ii_rbtree_kv_first( rbtree ) == 10 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_first_4
*/

void test_first_4( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   CU_ASSERT( ii_rbtree_kv_first( rbtree ) == 10 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_first_5
   
            4
         2      6
       1  
*/

void test_first_5( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   
   CU_ASSERT( ii_rbtree_kv_first( rbtree ) == 10 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_first_6
   
            4
         2      6
            3       
*/

void test_first_6( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   CU_ASSERT( ii_rbtree_kv_first( rbtree ) == 20 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_first_7
   
            4
         2      6
              5 
*/

void test_first_7( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 50, 5 );
   
   CU_ASSERT( ii_rbtree_kv_first( rbtree ) == 20 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_first_8
   
            4
         2      6
                  7   
*/

void test_first_8( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 70, 7 );
   
   CU_ASSERT( ii_rbtree_kv_first( rbtree ) == 20 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_first_9
*/

void test_first_9( void )
{
   ss_rbtree_kv_t *rbtree = NULL;
   
   string_t *s2 = NULL;
   string_t *s20 = NULL;
   string_t *s4 = NULL;
   string_t *s40 = NULL;
   string_t *s6 = NULL;
   string_t *s60 = NULL;
   string_t *s7 = NULL;
   string_t *s70 = NULL;
   
   s2 = string_make_from_cstring( "2" );
   s20 = string_make_from_cstring( "20" );
   s4 = string_make_from_cstring( "4" );
   s40 = string_make_from_cstring( "40" );
   s6 = string_make_from_cstring( "6" );
   s60 = string_make_from_cstring( "6" );
   s7 = string_make_from_cstring( "7" );
   s70 = string_make_from_cstring( "70" );
   
   rbtree = ss_rbtree_kv_make();
   
   ss_rbtree_kv_put( rbtree, s40, s4 );
   ss_rbtree_kv_put( rbtree, s20, s2 );
   ss_rbtree_kv_put( rbtree, s60, s6 );
   ss_rbtree_kv_put( rbtree, s70, s7 );
   
   CU_ASSERT( ss_rbtree_kv_first( rbtree ) == s20 );
   
   ss_rbtree_kv_deep_dispose( &rbtree );

   return;
}

int
add_test_first( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_first", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_first_1
   add_test_to_suite( p_suite, test_first_1, "test_first_1" );

   // test_first_2
   add_test_to_suite( p_suite, test_first_2, "test_first_2" );

   // test_first_3
   add_test_to_suite( p_suite, test_first_3, "test_first_3" );

   // test_first_4
   add_test_to_suite( p_suite, test_first_4, "test_first_4" );

   // test_first_5
   add_test_to_suite( p_suite, test_first_5, "test_first_5" );

   // test_first_6
   add_test_to_suite( p_suite, test_first_6, "test_first_6" );

   // test_first_7
   add_test_to_suite( p_suite, test_first_7, "test_first_7" );

   // test_first_8
   add_test_to_suite( p_suite, test_first_8, "test_first_8" );

   // test_first_9
   add_test_to_suite( p_suite, test_first_9, "test_first_9" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

