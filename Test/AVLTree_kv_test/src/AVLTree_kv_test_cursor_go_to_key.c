/**
 @file AVLTree_test_cursor_go_to_key.c
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
   test_cursor_go_to_key_1
*/

void test_cursor_go_to_key_1( void )
{
   ii_avltree_kv_t *avltree = NULL;
   ii_avltree_kv_cursor_t *cursor = NULL;
   
   avltree = ii_avltree_kv_make();
   cursor = ii_avltree_kv_cursor_make( avltree );
   
   ii_avltree_kv_cursor_go_to_key( cursor, 0 );
   
   CU_ASSERT( ii_avltree_kv_cursor_off( cursor ) == 1 );
   
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_cursor_go_to_key_1a
*/

void test_cursor_go_to_key_1a( void )
{
   ii_avltree_kv_t *avltree = NULL;
   ii_avltree_kv_cursor_t *cursor = NULL;
   
   avltree = ii_avltree_kv_make();
   cursor = ii_avltree_kv_cursor_make( avltree );
   
   ii_avltree_kv_put( avltree, 10, 1 );
   
   ii_avltree_kv_cursor_go_to_key( cursor, 0 );
   CU_ASSERT( ii_avltree_kv_cursor_off( cursor ) == 1 );
   
   ii_avltree_kv_cursor_go_to_key( cursor, 1 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 1 );
   
   ii_avltree_kv_cursor_go_to_key( cursor, 2 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 1 );
   
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_cursor_go_to_key_2
*/

void test_cursor_go_to_key_2( void )
{
   ii_avltree_kv_t *avltree = NULL;
   ii_avltree_kv_cursor_t *cursor = NULL;
   
   avltree = ii_avltree_kv_make();
   cursor = ii_avltree_kv_cursor_make( avltree );
   
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   ii_avltree_kv_cursor_go_to_key( cursor, 0 );
   CU_ASSERT( ii_avltree_kv_cursor_off( cursor ) == 1 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 1 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 1 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 2 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 2 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 3 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 3 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 4 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 3 );
 
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_cursor_go_to_key_3
*/

void test_cursor_go_to_key_3( void )
{
   ii_avltree_kv_t *avltree = NULL;
   ii_avltree_kv_cursor_t *cursor = NULL;
   
   avltree = ii_avltree_kv_make();
   cursor = ii_avltree_kv_cursor_make( avltree );
   
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   
   ii_avltree_kv_cursor_go_to_key( cursor, 0 );
   CU_ASSERT( ii_avltree_kv_cursor_off( cursor ) == 1 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 1 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 1 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 2 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 2 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 3 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 3 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 4 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 3 );
 
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_cursor_go_to_key_4
*/

void test_cursor_go_to_key_4( void )
{
   ii_avltree_kv_t *avltree = NULL;
   ii_avltree_kv_cursor_t *cursor = NULL;
   
   avltree = ii_avltree_kv_make();
   cursor = ii_avltree_kv_cursor_make( avltree );
   
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   ii_avltree_kv_cursor_go_to_key( cursor, 0 );
   CU_ASSERT( ii_avltree_kv_cursor_off( cursor ) == 1 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 1 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 1 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 2 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 2 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 3 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 3 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 4 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 3 );
 
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_cursor_go_to_key_5
   
            4
         2      6
       1  
*/

void test_cursor_go_to_key_5( void )
{
   ii_avltree_kv_t *avltree = NULL;
   ii_avltree_kv_cursor_t *cursor = NULL;
   
   avltree = ii_avltree_kv_make();
   cursor = ii_avltree_kv_cursor_make( avltree );
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 10, 1 );
   
   ii_avltree_kv_cursor_go_to_key( cursor, 0 );
   CU_ASSERT( ii_avltree_kv_cursor_off( cursor ) == 1 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 1 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 1 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 2 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 2 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 3 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 2 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 4 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 4 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 5 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 4 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 6 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 6 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 10 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 6 );
 
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_cursor_go_to_key_6
   
            4
         2      6
            3       
*/

void test_cursor_go_to_key_6( void )
{
   ii_avltree_kv_t *avltree = NULL;
   ii_avltree_kv_cursor_t *cursor = NULL;
   
   avltree = ii_avltree_kv_make();
   cursor = ii_avltree_kv_cursor_make( avltree );
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   ii_avltree_kv_cursor_go_to_key( cursor, 0 );
   CU_ASSERT( ii_avltree_kv_cursor_off( cursor ) == 1 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 1 );
   CU_ASSERT( ii_avltree_kv_cursor_off( cursor ) == 1 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 2 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 2 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 3 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 3 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 4 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 4 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 5 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 4 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 6 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 6 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 10 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 6 );
 
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_cursor_go_to_key_7
   
            4
         2      6
              5 
*/

void test_cursor_go_to_key_7( void )
{
   ii_avltree_kv_t *avltree = NULL;
   ii_avltree_kv_cursor_t *cursor = NULL;
   
   avltree = ii_avltree_kv_make();
   cursor = ii_avltree_kv_cursor_make( avltree );
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 50, 5 );
   
   ii_avltree_kv_cursor_go_to_key( cursor, 0 );
   CU_ASSERT( ii_avltree_kv_cursor_off( cursor ) == 1 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 1 );
   CU_ASSERT( ii_avltree_kv_cursor_off( cursor ) == 1 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 2 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 2 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 3 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 2 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 4 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 4 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 5 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 5 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 6 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 6 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 10 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 6 );
 
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_cursor_go_to_key_8
   
            4
         2      6
                  7   
*/

void test_cursor_go_to_key_8( void )
{
   ii_avltree_kv_t *avltree = NULL;
   ii_avltree_kv_cursor_t *cursor = NULL;
   
   avltree = ii_avltree_kv_make();
   cursor = ii_avltree_kv_cursor_make( avltree );
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 70, 7 );
   
   ii_avltree_kv_cursor_go_to_key( cursor, 0 );
   CU_ASSERT( ii_avltree_kv_cursor_off( cursor ) == 1 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 1 );
   CU_ASSERT( ii_avltree_kv_cursor_off( cursor ) == 1 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 2 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 2 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 3 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 2 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 4 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 4 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 5 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 4 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 6 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 6 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 7 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 7 );
 
   ii_avltree_kv_cursor_go_to_key( cursor, 10 );
   CU_ASSERT( ii_avltree_kv_cursor_key_at( cursor ) == 7 );
 
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_cursor_go_to_key_9
*/

void test_cursor_go_to_key_9( void )
{
   ss_avltree_kv_t *avltree = NULL;
   ss_avltree_kv_cursor_t *cursor = NULL;
   
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
   s60 = string_make_from_cstring( "60" );
   s7 = string_make_from_cstring( "7" );
   s70 = string_make_from_cstring( "70" );
   s9 = string_make_from_cstring( "9" );
   s90 = string_make_from_cstring( "90" );
   
   avltree = ss_avltree_kv_make();
   cursor = ss_avltree_kv_cursor_make( avltree );
   
   ss_avltree_kv_put( avltree, s40, s4 );
   ss_avltree_kv_put( avltree, s20, s2 );
   ss_avltree_kv_put( avltree, s60, s6 );
   ss_avltree_kv_put( avltree, s70, s7 );
   
   ss_avltree_kv_cursor_go_to_key( cursor, s0 );
   CU_ASSERT( ss_avltree_kv_cursor_off( cursor ) == 1 );
 
   ss_avltree_kv_cursor_go_to_key( cursor, s1 );
   CU_ASSERT( ss_avltree_kv_cursor_off( cursor ) == 1 );
 
   ss_avltree_kv_cursor_go_to_key( cursor, s2 );
   CU_ASSERT( ss_avltree_kv_cursor_key_at( cursor ) == s2 );
 
   ss_avltree_kv_cursor_go_to_key( cursor, s3 );
   CU_ASSERT( ss_avltree_kv_cursor_key_at( cursor ) == s2 );
 
   ss_avltree_kv_cursor_go_to_key( cursor, s4 );
   CU_ASSERT( ss_avltree_kv_cursor_key_at( cursor ) == s4 );
 
   ss_avltree_kv_cursor_go_to_key( cursor, s5 );
   CU_ASSERT( ss_avltree_kv_cursor_key_at( cursor ) == s4 );
 
   ss_avltree_kv_cursor_go_to_key( cursor, s6 );
   CU_ASSERT( ss_avltree_kv_cursor_key_at( cursor ) == s6 );
 
   ss_avltree_kv_cursor_go_to_key( cursor, s7 );
   CU_ASSERT( ss_avltree_kv_cursor_key_at( cursor ) == s7 );
 
   ss_avltree_kv_cursor_go_to_key( cursor, s9 );
   CU_ASSERT( ss_avltree_kv_cursor_key_at( cursor ) == s7 );
 
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
   
   ss_avltree_kv_deep_dispose( &avltree );

   return;
}

int
add_test_cursor_go_to_key( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_cursor_go_to_key", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_cursor_go_to_key_1
   add_test_to_suite( p_suite, test_cursor_go_to_key_1, "test_cursor_go_to_key_1" );

   // test_cursor_go_to_key_1a
   add_test_to_suite( p_suite, test_cursor_go_to_key_1a, "test_cursor_go_to_key_1a" );

   // test_cursor_go_to_key_2
   add_test_to_suite( p_suite, test_cursor_go_to_key_2, "test_cursor_go_to_key_2" );

   // test_cursor_go_to_key_3
   add_test_to_suite( p_suite, test_cursor_go_to_key_3, "test_cursor_go_to_key_3" );

   // test_cursor_go_to_key_4
   add_test_to_suite( p_suite, test_cursor_go_to_key_4, "test_cursor_go_to_key_4" );

   // test_cursor_go_to_key_5
   add_test_to_suite( p_suite, test_cursor_go_to_key_5, "test_cursor_go_to_key_5" );

   // test_cursor_go_to_key_6
   add_test_to_suite( p_suite, test_cursor_go_to_key_6, "test_cursor_go_to_key_6" );

   // test_cursor_go_to_key_7
   add_test_to_suite( p_suite, test_cursor_go_to_key_7, "test_cursor_go_to_key_7" );

   // test_cursor_go_to_key_8
   add_test_to_suite( p_suite, test_cursor_go_to_key_8, "test_cursor_go_to_key_8" );

   // test_cursor_go_to_key_9
   add_test_to_suite( p_suite, test_cursor_go_to_key_9, "test_cursor_go_to_key_9" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

