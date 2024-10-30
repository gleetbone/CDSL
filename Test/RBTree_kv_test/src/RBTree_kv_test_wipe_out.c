/**
 @file RBTree_test_wipe_out.c
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
   test_wipe_out_1
*/

void test_wipe_out_1( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 10, 1 );
   
   ii_rbtree_kv_wipe_out( rbtree );
   
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 0 );
  
   ii_rbtree_kv_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_2
*/

void test_wipe_out_2( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   ii_rbtree_kv_wipe_out( rbtree );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 0 );
   
   ii_rbtree_kv_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_2a
*/

void test_wipe_out_2a( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   ii_rbtree_kv_wipe_out( rbtree );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 0 );
   
   ii_rbtree_kv_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_2b
*/

void test_wipe_out_2b( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   ii_rbtree_kv_wipe_out( rbtree );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 0 );
   
   ii_rbtree_kv_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_3
*/

void test_wipe_out_3( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   
   ii_rbtree_kv_wipe_out( rbtree );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 0 );
   
   ii_rbtree_kv_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_3a
*/

void test_wipe_out_3a( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   
   ii_rbtree_kv_wipe_out( rbtree );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 0 );
   
   ii_rbtree_kv_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_3b
*/

void test_wipe_out_3b( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   
   ii_rbtree_kv_wipe_out( rbtree );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 0 );
   
   ii_rbtree_kv_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_4
*/

void test_wipe_out_4( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   ii_rbtree_kv_wipe_out( rbtree );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 0 );
   
   ii_rbtree_kv_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_4a
*/

void test_wipe_out_4a( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   ii_rbtree_kv_wipe_out( rbtree );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 0 );
   
   ii_rbtree_kv_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_4b
*/

void test_wipe_out_4b( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   ii_rbtree_kv_wipe_out( rbtree );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 0 );
   
   ii_rbtree_kv_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_5
   
            4
         2      6
       1   3  5   7
*/

void test_wipe_out_5( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 50, 5 );
   ii_rbtree_kv_put( rbtree, 70, 7 );
   
   ii_rbtree_kv_wipe_out( rbtree );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 0 );
   
   ii_rbtree_kv_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_5a
   
            4
         2      6
       1   3  5   7
*/

void test_wipe_out_5a( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 50, 5 );
   ii_rbtree_kv_put( rbtree, 70, 7 );
   
   ii_rbtree_kv_wipe_out( rbtree );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 0 );
   
   ii_rbtree_kv_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_5b
   
            4
         2      6
       1   3  5   7
*/

void test_wipe_out_5b( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 50, 5 );
   ii_rbtree_kv_put( rbtree, 70, 7 );
   
   ii_rbtree_kv_wipe_out( rbtree );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 0 );
   
   ii_rbtree_kv_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_5c
   
            4
         2      6
       1   3  5   7
*/

void test_wipe_out_5c( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 50, 5 );
   ii_rbtree_kv_put( rbtree, 70, 7 );
   
   ii_rbtree_kv_wipe_out( rbtree );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 0 );
   
   ii_rbtree_kv_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_5d
   
            4
         2      6
       1   3  5   7
*/

void test_wipe_out_5d( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 50, 5 );
   ii_rbtree_kv_put( rbtree, 70, 7 );
   
   ii_rbtree_kv_wipe_out( rbtree );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 0 );
   
   ii_rbtree_kv_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_5e
   
            4
         2      6
       1   3  5   7
*/

void test_wipe_out_5e( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 50, 5 );
   ii_rbtree_kv_put( rbtree, 70, 7 );
   
   ii_rbtree_kv_wipe_out( rbtree );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 0 );
   
   ii_rbtree_kv_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_5f
   
            4
         2      6
       1   3  5   7
*/

void test_wipe_out_5f( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 50, 5 );
   ii_rbtree_kv_put( rbtree, 70, 7 );
   
   ii_rbtree_kv_wipe_out( rbtree );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 0 );
   
   ii_rbtree_kv_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_6
*/

void test_wipe_out_6( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   ii_rbtree_kv_cursor_t *cursor = NULL;

   rbtree = ii_rbtree_kv_make();
   cursor = ii_rbtree_kv_cursor_make( rbtree );

   ii_rbtree_kv_put( rbtree, 10, 1 );

   ii_rbtree_kv_wipe_out( rbtree );

   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 0 );

   ii_rbtree_kv_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_7
*/

void test_wipe_out_7( void )
{
   ss_rbtree_kv_t *rbtree = NULL;
   ss_rbtree_kv_cursor_t *cursor = NULL;

   string_t *s1 = NULL;
   string_t *s10 = NULL;
   
   s1 = string_make_from_cstring( "1" );
   s10 = string_make_from_cstring( "10" );
   
   rbtree = ss_rbtree_kv_make();
   cursor = ss_rbtree_kv_cursor_make( rbtree );

   ss_rbtree_kv_put( rbtree, s10, s1 );

   ss_rbtree_kv_wipe_out( rbtree );

   CU_ASSERT( ss_rbtree_kv_count( rbtree ) == 0 );

   string_deep_dispose( &s1 );
   string_deep_dispose( &s10 );
   ss_rbtree_kv_dispose( &rbtree );

   return;
}

int
add_test_wipe_out( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_wipe_out", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_wipe_out_1
   add_test_to_suite( p_suite, test_wipe_out_1, "test_wipe_out_1" );

   // test_wipe_out_2
   add_test_to_suite( p_suite, test_wipe_out_2, "test_wipe_out_2" );
   add_test_to_suite( p_suite, test_wipe_out_2a, "test_wipe_out_2a" );
   add_test_to_suite( p_suite, test_wipe_out_2b, "test_wipe_out_2b" );

   // test_wipe_out_3
   add_test_to_suite( p_suite, test_wipe_out_3, "test_wipe_out_3" );
   add_test_to_suite( p_suite, test_wipe_out_3a, "test_wipe_out_3a" );
   add_test_to_suite( p_suite, test_wipe_out_3b, "test_wipe_out_3b" );

   // test_wipe_out_4
   add_test_to_suite( p_suite, test_wipe_out_4, "test_wipe_out_4" );
   add_test_to_suite( p_suite, test_wipe_out_4a, "test_wipe_out_4a" );
   add_test_to_suite( p_suite, test_wipe_out_4b, "test_wipe_out_4b" );

   // test_wipe_out_5
   add_test_to_suite( p_suite, test_wipe_out_5, "test_wipe_out_5" );
   add_test_to_suite( p_suite, test_wipe_out_5a, "test_wipe_out_5a" );
   add_test_to_suite( p_suite, test_wipe_out_5b, "test_wipe_out_5b" );
   add_test_to_suite( p_suite, test_wipe_out_5c, "test_wipe_out_5c" );
   add_test_to_suite( p_suite, test_wipe_out_5d, "test_wipe_out_5d" );
   add_test_to_suite( p_suite, test_wipe_out_5e, "test_wipe_out_5e" );
   add_test_to_suite( p_suite, test_wipe_out_5f, "test_wipe_out_5f" );

   // test_wipe_out_6
   add_test_to_suite( p_suite, test_wipe_out_6, "test_wipe_out_6" );

   // test_wipe_out_7
   add_test_to_suite( p_suite, test_wipe_out_7, "test_wipe_out_7" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

