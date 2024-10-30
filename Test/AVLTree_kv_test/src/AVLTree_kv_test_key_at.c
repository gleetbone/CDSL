/**
 @file AVLTree_test_key_at.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for AVLTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for AVLTree_kv_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_AVLTree_kv.h"
#include "ss_AVLTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_key_at_1
*/

void test_key_at_1( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 10, 1 );
   
   ii_avltree_kv_start( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 1 );
 
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_key_at_2
*/

void test_key_at_2( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   ii_avltree_kv_start( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 1 );

   ii_avltree_kv_forth( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 2 );

   ii_avltree_kv_forth( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 3 );
 
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_key_at_3
*/

void test_key_at_3( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   
   ii_avltree_kv_start( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 1 );

   ii_avltree_kv_forth( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 2 );

   ii_avltree_kv_forth( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 3 );
 
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_key_at_4
*/

void test_key_at_4( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   ii_avltree_kv_start( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 1 );

   ii_avltree_kv_forth( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 2 );

   ii_avltree_kv_forth( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 3 );
 
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_key_at_5
   
            4
         2      6
       1  
*/

void test_key_at_5( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 10, 1 );
   
   ii_avltree_kv_start( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 1 );

   ii_avltree_kv_forth( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 2 );

   ii_avltree_kv_forth( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 4 );

   ii_avltree_kv_forth( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 6 );
  
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_key_at_6
   
            4
         2      6
            3       
*/

void test_key_at_6( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   ii_avltree_kv_start( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 2 );

   ii_avltree_kv_forth( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 3 );

   ii_avltree_kv_forth( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 4 );

   ii_avltree_kv_forth( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 6 );
 
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_key_at_7
   
            4
         2      6
              5 
*/

void test_key_at_7( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 50, 5 );
   
   ii_avltree_kv_start( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 2 );

   ii_avltree_kv_forth( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 4 );

   ii_avltree_kv_forth( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 5 );

   ii_avltree_kv_forth( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 6 );
 
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_key_at_8
   
            4
         2      6
                  7   
*/

void test_key_at_8( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 70, 7 );
   
   ii_avltree_kv_start( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 2 );

   ii_avltree_kv_forth( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 4 );

   ii_avltree_kv_forth( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 6 );

   ii_avltree_kv_forth( avltree );
   CU_ASSERT( ii_avltree_kv_key_at( avltree ) == 7 );
 
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_key_at_9
*/

void test_key_at_9( void )
{
   ss_avltree_kv_t *avltree = NULL;
   
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
   s60 = string_make_from_cstring( "60" );
   s7 = string_make_from_cstring( "7" );
   s70 = string_make_from_cstring( "70" );
   
   avltree = ss_avltree_kv_make();
   
   ss_avltree_kv_put( avltree, s40, s4 );
   ss_avltree_kv_put( avltree, s20, s2 );
   ss_avltree_kv_put( avltree, s60, s6 );
   ss_avltree_kv_put( avltree, s70, s7 );
   
   ss_avltree_kv_start( avltree );
   CU_ASSERT( ss_avltree_kv_key_at( avltree ) == s2 );

   ss_avltree_kv_forth( avltree );
   CU_ASSERT( ss_avltree_kv_key_at( avltree ) == s4 );

   ss_avltree_kv_forth( avltree );
   CU_ASSERT( ss_avltree_kv_key_at( avltree ) == s6 );

   ss_avltree_kv_forth( avltree );
   CU_ASSERT( ss_avltree_kv_key_at( avltree ) == s7 );
 
   ss_avltree_kv_deep_dispose( &avltree );

   return;
}


int
add_test_key_at( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_key_at", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_key_at_1
   add_test_to_suite( p_suite, test_key_at_1, "test_key_at_1" );

   // test_key_at_2
   add_test_to_suite( p_suite, test_key_at_2, "test_key_at_2" );

   // test_key_at_3
   add_test_to_suite( p_suite, test_key_at_3, "test_key_at_3" );

   // test_key_at_4
   add_test_to_suite( p_suite, test_key_at_4, "test_key_at_4" );

   // test_key_at_5
   add_test_to_suite( p_suite, test_key_at_5, "test_key_at_5" );

   // test_key_at_6
   add_test_to_suite( p_suite, test_key_at_6, "test_key_at_6" );

   // test_key_at_7
   add_test_to_suite( p_suite, test_key_at_7, "test_key_at_7" );

   // test_key_at_8
   add_test_to_suite( p_suite, test_key_at_8, "test_key_at_8" );

   // test_key_at_9
   add_test_to_suite( p_suite, test_key_at_9, "test_key_at_9" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

