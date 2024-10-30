/**
 @file RBTree_test_cursor_go_to_key.c
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
   test_go_to_key_1
*/

void test_go_to_key_1( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_go_to_key( rbtree, 0 );
   
   CU_ASSERT( ii_rbtree_kv_off( rbtree ) == 1 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_go_to_key_1a
*/

void test_go_to_key_1a( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 10, 1 );
   
   ii_rbtree_kv_go_to_key( rbtree , 0 );
   CU_ASSERT( ii_rbtree_kv_off( rbtree ) == 1 );
   
   ii_rbtree_kv_go_to_key( rbtree , 1 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 1 );
   
   ii_rbtree_kv_go_to_key( rbtree , 2 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 1 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_go_to_key_2
*/

void test_go_to_key_2( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   ii_rbtree_kv_go_to_key( rbtree , 0 );
   CU_ASSERT( ii_rbtree_kv_off( rbtree ) == 1 );
 
   ii_rbtree_kv_go_to_key( rbtree , 1 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 1 );
 
   ii_rbtree_kv_go_to_key( rbtree , 2 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 2 );
 
   ii_rbtree_kv_go_to_key( rbtree , 3 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 3 );
 
   ii_rbtree_kv_go_to_key( rbtree , 4 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 3 );
 
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_go_to_key_3
*/

void test_go_to_key_3( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   
   ii_rbtree_kv_go_to_key( rbtree , 0 );
   CU_ASSERT( ii_rbtree_kv_off( rbtree ) == 1 );
 
   ii_rbtree_kv_go_to_key( rbtree , 1 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 1 );
 
   ii_rbtree_kv_go_to_key( rbtree , 2 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 2 );
 
   ii_rbtree_kv_go_to_key( rbtree , 3 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 3 );
 
   ii_rbtree_kv_go_to_key( rbtree , 4 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 3 );
 
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_go_to_key_4
*/

void test_go_to_key_4( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   ii_rbtree_kv_go_to_key( rbtree , 0 );
   CU_ASSERT( ii_rbtree_kv_off( rbtree ) == 1 );
 
   ii_rbtree_kv_go_to_key( rbtree , 1 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 1 );
 
   ii_rbtree_kv_go_to_key( rbtree , 2 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 2 );
 
   ii_rbtree_kv_go_to_key( rbtree , 3 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 3 );
 
   ii_rbtree_kv_go_to_key( rbtree , 4 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 3 );
 
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_go_to_key_5
   
            4
         2      6
       1  
*/

void test_go_to_key_5( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   
   ii_rbtree_kv_go_to_key( rbtree , 0 );
   CU_ASSERT( ii_rbtree_kv_off( rbtree ) == 1 );
 
   ii_rbtree_kv_go_to_key( rbtree , 1 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 1 );
 
   ii_rbtree_kv_go_to_key( rbtree , 2 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 2 );
 
   ii_rbtree_kv_go_to_key( rbtree , 3 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 2 );
 
   ii_rbtree_kv_go_to_key( rbtree , 4 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 4 );
 
   ii_rbtree_kv_go_to_key( rbtree , 5 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 4 );
 
   ii_rbtree_kv_go_to_key( rbtree , 6 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 6 );
 
   ii_rbtree_kv_go_to_key( rbtree , 10 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 6 );
 
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_go_to_key_6
   
            4
         2      6
            3       
*/

void test_go_to_key_6( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   ii_rbtree_kv_go_to_key( rbtree , 0 );
   CU_ASSERT( ii_rbtree_kv_off( rbtree ) == 1 );
 
   ii_rbtree_kv_go_to_key( rbtree , 1 );
   CU_ASSERT( ii_rbtree_kv_off( rbtree ) == 1 );
 
   ii_rbtree_kv_go_to_key( rbtree , 2 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 2 );
 
   ii_rbtree_kv_go_to_key( rbtree , 3 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 3 );
 
   ii_rbtree_kv_go_to_key( rbtree , 4 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 4 );
 
   ii_rbtree_kv_go_to_key( rbtree , 5 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 4 );
 
   ii_rbtree_kv_go_to_key( rbtree , 6 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 6 );
 
   ii_rbtree_kv_go_to_key( rbtree , 10 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 6 );
 
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_go_to_key_7
   
            4
         2      6
              5 
*/

void test_go_to_key_7( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 50, 5 );
   
   ii_rbtree_kv_go_to_key( rbtree , 0 );
   CU_ASSERT( ii_rbtree_kv_off( rbtree ) == 1 );
 
   ii_rbtree_kv_go_to_key( rbtree , 1 );
   CU_ASSERT( ii_rbtree_kv_off( rbtree ) == 1 );
 
   ii_rbtree_kv_go_to_key( rbtree , 2 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 2 );
 
   ii_rbtree_kv_go_to_key( rbtree , 3 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 2 );
 
   ii_rbtree_kv_go_to_key( rbtree , 4 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 4 );
 
   ii_rbtree_kv_go_to_key( rbtree , 5 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 5 );
 
   ii_rbtree_kv_go_to_key( rbtree , 6 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 6 );
 
   ii_rbtree_kv_go_to_key( rbtree , 10 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 6 );
 
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_go_to_key_8
   
            4
         2      6
                  7   
*/

void test_go_to_key_8( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 70, 7 );
   
   ii_rbtree_kv_go_to_key( rbtree , 0 );
   CU_ASSERT( ii_rbtree_kv_off( rbtree ) == 1 );
 
   ii_rbtree_kv_go_to_key( rbtree , 1 );
   CU_ASSERT( ii_rbtree_kv_off( rbtree ) == 1 );
 
   ii_rbtree_kv_go_to_key( rbtree , 2 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 2 );
 
   ii_rbtree_kv_go_to_key( rbtree , 3 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 2 );
 
   ii_rbtree_kv_go_to_key( rbtree , 4 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 4 );
 
   ii_rbtree_kv_go_to_key( rbtree , 5 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 4 );
 
   ii_rbtree_kv_go_to_key( rbtree , 6 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 6 );
 
   ii_rbtree_kv_go_to_key( rbtree , 7 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 7 );
 
   ii_rbtree_kv_go_to_key( rbtree , 10 );
   CU_ASSERT( ii_rbtree_kv_key_at( rbtree ) == 7 );
 
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_go_to_key_9
*/

void test_go_to_key_9( void )
{
   ss_rbtree_kv_t *rbtree = NULL;
   
   string_t *s0 = NULL;
   string_t *s00 = NULL;
   string_t *s1 = NULL;
   string_t *s10 = NULL;
   string_t *s2 = NULL;
   string_t *s20 = NULL;
   string_t *s3 = NULL;
   string_t *s30 = NULL;
   string_t *s4 = NULL;
   string_t *s40 = NULL;
   string_t *s5 = NULL;
   string_t *s50 = NULL;
   string_t *s6 = NULL;
   string_t *s60 = NULL;
   string_t *s7 = NULL;
   string_t *s70 = NULL;
   string_t *s9 = NULL;
   string_t *s90 = NULL;
   
   s0 = string_make_from_cstring( "0" );
   s00 = string_make_from_cstring( "00" );
   s1 = string_make_from_cstring( "1" );
   s10 = string_make_from_cstring( "10" );
   s2 = string_make_from_cstring( "2" );
   s20 = string_make_from_cstring( "20" );
   s3 = string_make_from_cstring( "3" );
   s30 = string_make_from_cstring( "30" );
   s4 = string_make_from_cstring( "4" );
   s40 = string_make_from_cstring( "40" );
   s5 = string_make_from_cstring( "5" );
   s50 = string_make_from_cstring( "50" );
   s6 = string_make_from_cstring( "6" );
   s60 = string_make_from_cstring( "6" );
   s7 = string_make_from_cstring( "7" );
   s70 = string_make_from_cstring( "70" );
   s9 = string_make_from_cstring( "9" );
   s90 = string_make_from_cstring( "90" );
   
   rbtree = ss_rbtree_kv_make();
   
   ss_rbtree_kv_put( rbtree, s40, s4 );
   ss_rbtree_kv_put( rbtree, s20, s2 );
   ss_rbtree_kv_put( rbtree, s60, s6 );
   ss_rbtree_kv_put( rbtree, s70, s7 );
   
   ss_rbtree_kv_go_to_key( rbtree , s0 );
   CU_ASSERT( ss_rbtree_kv_off( rbtree ) == 1 );
 
   ss_rbtree_kv_go_to_key( rbtree , s1 );
   CU_ASSERT( ss_rbtree_kv_off( rbtree ) == 1 );
 
   ss_rbtree_kv_go_to_key( rbtree , s2 );
   CU_ASSERT( ss_rbtree_kv_key_at( rbtree ) == s2 );
 
   ss_rbtree_kv_go_to_key( rbtree , s3 );
   CU_ASSERT( ss_rbtree_kv_key_at( rbtree ) == s2 );
 
   ss_rbtree_kv_go_to_key( rbtree , s4 );
   CU_ASSERT( ss_rbtree_kv_key_at( rbtree ) == s4 );
 
   ss_rbtree_kv_go_to_key( rbtree , s5 );
   CU_ASSERT( ss_rbtree_kv_key_at( rbtree ) == s4 );
 
   ss_rbtree_kv_go_to_key( rbtree , s6 );
   CU_ASSERT( ss_rbtree_kv_key_at( rbtree ) == s6 );
 
   ss_rbtree_kv_go_to_key( rbtree , s7 );
   CU_ASSERT( ss_rbtree_kv_key_at( rbtree ) == s7 );
 
   ss_rbtree_kv_go_to_key( rbtree , s9 );
   CU_ASSERT( ss_rbtree_kv_key_at( rbtree ) == s7 );
 
   ss_rbtree_kv_deep_dispose( &rbtree );
   
   string_deep_dispose( &s0 );
   string_deep_dispose( &s00 );
   string_deep_dispose( &s1 );
   string_deep_dispose( &s10 );
   string_deep_dispose( &s3 );
   string_deep_dispose( &s30 );
   string_deep_dispose( &s5 );
   string_deep_dispose( &s50 );
   string_deep_dispose( &s9 );
   string_deep_dispose( &s90 );
   
   return;
}

int
add_test_go_to_key( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_go_to_key", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_go_to_key_1
   add_test_to_suite( p_suite, test_go_to_key_1, "test_go_to_key_1" );

   // test_go_to_key_1a
   add_test_to_suite( p_suite, test_go_to_key_1a, "test_go_to_key_1a" );

   // test_go_to_key_2
   add_test_to_suite( p_suite, test_go_to_key_2, "test_go_to_key_2" );

   // test_go_to_key_3
   add_test_to_suite( p_suite, test_go_to_key_3, "test_go_to_key_3" );

   // test_go_to_key_4
   add_test_to_suite( p_suite, test_go_to_key_4, "test_go_to_key_4" );

   // test_go_to_key_5
   add_test_to_suite( p_suite, test_go_to_key_5, "test_go_to_key_5" );

   // test_go_to_key_6
   add_test_to_suite( p_suite, test_go_to_key_6, "test_go_to_key_6" );

   // test_go_to_key_7
   add_test_to_suite( p_suite, test_go_to_key_7, "test_go_to_key_7" );

   // test_go_to_key_8
   add_test_to_suite( p_suite, test_go_to_key_8, "test_go_to_key_8" );

   // test_go_to_key_9
   add_test_to_suite( p_suite, test_go_to_key_9, "test_go_to_key_9" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

