/**
 @file RBTree_test_has_eq_fn.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for RBTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for RBTree_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_RBTree.h"
#include "s_RBTree.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

static int32_t is_equal_int( int32_t i1, int32_t i2 )
{
   return ( i1 == i2 );
}

static int32_t is_equal_s( string_t *s1, string_t *s2 )
{
   return ( string_is_equal( s1, s2 ) == 1 );
}

/**
   test_has_eq_fn_1
*/

void test_has_eq_fn_1( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 1 );
   
   result = i_rbtree_has_eq_fn( rbtree, 1, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 0, is_equal_int );
   CU_ASSERT( result == 0 );
 
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_has_eq_fn_2
*/

void test_has_eq_fn_2( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   
   result = i_rbtree_has_eq_fn( rbtree, 2, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 1, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 3, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 0, is_equal_int );
   CU_ASSERT( result == 0 );
 
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_has_eq_fn_3
*/

void test_has_eq_fn_3( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   
   result = i_rbtree_has_eq_fn( rbtree, 2, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 1, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 3, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 0, is_equal_int );
   CU_ASSERT( result == 0 );
 
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_has_eq_fn_4
*/

void test_has_eq_fn_4( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 3 );
   
   result = i_rbtree_has_eq_fn( rbtree, 2, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 1, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 3, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 0, is_equal_int );
   CU_ASSERT( result == 0 );
  
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_has_eq_fn_5
   
            4
         2      6
       1  
*/

void test_has_eq_fn_5( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 1 );
   
   result = i_rbtree_has_eq_fn( rbtree, 4, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 2, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 6, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 1, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 0, is_equal_int );
   CU_ASSERT( result == 0 );
 
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_has_eq_fn_6
   
            4
         2      6
            3       
*/

void test_has_eq_fn_6( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 3 );
   
   result = i_rbtree_has_eq_fn( rbtree, 4, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 2, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 6, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 3, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 0, is_equal_int );
   CU_ASSERT( result == 0 );
 
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_has_eq_fn_7
   
            4
         2      6
              5 
*/

void test_has_eq_fn_7( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 5 );
   
   result = i_rbtree_has_eq_fn( rbtree, 4, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 2, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 6, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 5, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 0, is_equal_int );
   CU_ASSERT( result == 0 );
 
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_has_eq_fn_8
   
            4
         2      6
                  7   
*/

void test_has_eq_fn_8( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 7 );
   
   result = i_rbtree_has_eq_fn( rbtree, 4, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 2, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 6, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 7, is_equal_int );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has_eq_fn( rbtree, 0, is_equal_int );
   CU_ASSERT( result == 0 );
 
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_has_eq_fn_9
   
            4
         2      6
                  7   
*/

void test_has_eq_fn_9( void )
{
   s_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s4 = string_make_from_cstring( "4" );
   string_t *s6 = string_make_from_cstring( "6" );
   string_t *s7 = string_make_from_cstring( "7" );
   
   string_t *s0 = string_make_from_cstring( "0" );
   
   rbtree = s_rbtree_make();
   
   s_rbtree_put( rbtree, s4 );
   s_rbtree_put( rbtree, s2 );
   s_rbtree_put( rbtree, s6 );
   s_rbtree_put( rbtree, s7 );
   
   result = s_rbtree_has_eq_fn( rbtree, s4, is_equal_s );
   CU_ASSERT( result == 1 );
 
   result = s_rbtree_has_eq_fn( rbtree, s2, is_equal_s );
   CU_ASSERT( result == 1 );
 
   result = s_rbtree_has_eq_fn( rbtree, s6, is_equal_s );
   CU_ASSERT( result == 1 );
 
   result = s_rbtree_has_eq_fn( rbtree, s7, is_equal_s );
   CU_ASSERT( result == 1 );
 
   result = s_rbtree_has_eq_fn( rbtree, s0, is_equal_s );
   CU_ASSERT( result == 0 );
 
   string_deep_dispose( &s0 );
   s_rbtree_deep_dispose( &rbtree );

   return;
}

int
add_test_has_eq_fn( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_has_eq_fn", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_has_eq_fn_1
   add_test_to_suite( p_suite, test_has_eq_fn_1, "test_has_eq_fn_1" );

   // test_has_eq_fn_2
   add_test_to_suite( p_suite, test_has_eq_fn_2, "test_has_eq_fn_2" );

   // test_has_eq_fn_3
   add_test_to_suite( p_suite, test_has_eq_fn_3, "test_has_eq_fn_3" );

   // test_has_eq_fn_4
   add_test_to_suite( p_suite, test_has_eq_fn_4, "test_has_eq_fn_4" );

   // test_has_eq_fn_5
   add_test_to_suite( p_suite, test_has_eq_fn_5, "test_has_eq_fn_5" );

   // test_has_eq_fn_6
   add_test_to_suite( p_suite, test_has_eq_fn_6, "test_has_eq_fn_6" );

   // test_has_eq_fn_7
   add_test_to_suite( p_suite, test_has_eq_fn_7, "test_has_eq_fn_7" );

   // test_has_eq_fn_8
   add_test_to_suite( p_suite, test_has_eq_fn_8, "test_has_eq_fn_8" );

   // test_has_eq_fn_9
   add_test_to_suite( p_suite, test_has_eq_fn_9, "test_has_eq_fn_9" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

