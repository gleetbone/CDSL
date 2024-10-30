/**
 @file BSTree_test_has_value.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BSTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for BSTree_kv_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_BSTree_kv.h"
#include "ss_BSTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_has_value_1
*/

void test_has_value_1( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 10, 1 );
   
   result = ii_bstree_kv_has_value( bstree, 10 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 0 );
   CU_ASSERT( result == 0 );
 
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_has_value_2
*/

void test_has_value_2( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   result = ii_bstree_kv_has_value( bstree, 20 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 10 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 30 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 0 );
   CU_ASSERT( result == 0 );
 
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_has_value_3
*/

void test_has_value_3( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   
   result = ii_bstree_kv_has_value( bstree, 20 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 10 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 30 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 0 );
   CU_ASSERT( result == 0 );
 
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_has_value_4
*/

void test_has_value_4( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   result = ii_bstree_kv_has_value( bstree, 20 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 10 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 30 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 0 );
   CU_ASSERT( result == 0 );
  
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_has_value_5
   
            4
         2      6
       1  
*/

void test_has_value_5( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 10, 1 );
   
   result = ii_bstree_kv_has_value( bstree, 40 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 20 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 60 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 10 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 0 );
   CU_ASSERT( result == 0 );
 
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_has_value_6
   
            4
         2      6
            3       
*/

void test_has_value_6( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   result = ii_bstree_kv_has_value( bstree, 40 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 20 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 60 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 30 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 0 );
   CU_ASSERT( result == 0 );
 
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_has_value_7
   
            4
         2      6
              5 
*/

void test_has_value_7( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 50, 5 );
   
   result = ii_bstree_kv_has_value( bstree, 40 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 20 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 60 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 50 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 0 );
   CU_ASSERT( result == 0 );
 
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_has_value_8
   
            4
         2      6
                  7   
*/

void test_has_value_8( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 70, 7 );
   
   result = ii_bstree_kv_has_value( bstree, 40 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 20 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 60 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 70 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has_value( bstree, 0 );
   CU_ASSERT( result == 0 );
 
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_has_value_9
*/
void test_has_value_9( void )
{
   ss_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   string_t *s0 = NULL;
   string_t *s00 = NULL;
   string_t *s2 = NULL;
   string_t *s20 = NULL;
   string_t *s4 = NULL;
   string_t *s40 = NULL;
   string_t *s6 = NULL;
   string_t *s60 = NULL;
   string_t *s7 = NULL;
   string_t *s70 = NULL;
   
   s0 = string_make_from_cstring( "0" );
   s00 = string_make_from_cstring( "00" );
   s2 = string_make_from_cstring( "2" );
   s20 = string_make_from_cstring( "20" );
   s4 = string_make_from_cstring( "4" );
   s40 = string_make_from_cstring( "40" );
   s6 = string_make_from_cstring( "6" );
   s60 = string_make_from_cstring( "6" );
   s7 = string_make_from_cstring( "7" );
   s70 = string_make_from_cstring( "70" );
   
   bstree = ss_bstree_kv_make();
   
   ss_bstree_kv_put( bstree, s40, s4 );
   ss_bstree_kv_put( bstree, s20, s2 );
   ss_bstree_kv_put( bstree, s60, s6 );
   ss_bstree_kv_put( bstree, s70, s7 );
   
   result = ss_bstree_kv_has_value( bstree, s40 );
   CU_ASSERT( result == 1 );
 
   result = ss_bstree_kv_has_value( bstree, s20 );
   CU_ASSERT( result == 1 );
 
   result = ss_bstree_kv_has_value( bstree, s60 );
   CU_ASSERT( result == 1 );
 
   result = ss_bstree_kv_has_value( bstree, s70 );
   CU_ASSERT( result == 1 );
 
   result = ss_bstree_kv_has_value( bstree, s00 );
   CU_ASSERT( result == 0 );
 
   ss_bstree_kv_deep_dispose( &bstree );
   string_deep_dispose( &s0 );
   string_deep_dispose( &s00 );
   
   return;
}

int
add_test_has_value( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_has_value", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_has_value_1
   add_test_to_suite( p_suite, test_has_value_1, "test_has_value_1" );

   // test_has_value_2
   add_test_to_suite( p_suite, test_has_value_2, "test_has_value_2" );

   // test_has_value_3
   add_test_to_suite( p_suite, test_has_value_3, "test_has_value_3" );

   // test_has_value_4
   add_test_to_suite( p_suite, test_has_value_4, "test_has_value_4" );

   // test_has_value_5
   add_test_to_suite( p_suite, test_has_value_5, "test_has_value_5" );

   // test_has_value_6
   add_test_to_suite( p_suite, test_has_value_6, "test_has_value_6" );

   // test_has_value_7
   add_test_to_suite( p_suite, test_has_value_7, "test_has_value_7" );

   // test_has_value_8
   add_test_to_suite( p_suite, test_has_value_8, "test_has_value_8" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

