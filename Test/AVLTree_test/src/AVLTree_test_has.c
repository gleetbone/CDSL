/**
 @file AVLTree_test_has.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for AVLTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for AVLTree_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_AVLTree.h"
#include "s_AVLTree.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_has_1
*/

void test_has_1( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 1 );
   
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 0 );
   CU_ASSERT( result == 0 );
 
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_has_2
*/

void test_has_2( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 0 );
   CU_ASSERT( result == 0 );
 
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_has_3
*/

void test_has_3( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 0 );
   CU_ASSERT( result == 0 );
 
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_has_4
*/

void test_has_4( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 3 );
   
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 0 );
   CU_ASSERT( result == 0 );
  
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_has_5
   
            4
         2      6
       1  
*/

void test_has_5( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   
   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 0 );
   CU_ASSERT( result == 0 );
 
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_has_6
   
            4
         2      6
            3       
*/

void test_has_6( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 3 );
   
   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 0 );
   CU_ASSERT( result == 0 );
 
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_has_7
   
            4
         2      6
              5 
*/

void test_has_7( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 5 );
   
   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 0 );
   CU_ASSERT( result == 0 );
 
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_has_8
   
            4
         2      6
                  7   
*/

void test_has_8( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 7 );
   
   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 0 );
   CU_ASSERT( result == 0 );
 
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_has_9
   
            4
         2      6
                  7   
*/

void test_has_9( void )
{
   s_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s4 = string_make_from_cstring( "4" );
   string_t *s6 = string_make_from_cstring( "6" );
   string_t *s7 = string_make_from_cstring( "7" );
   
   string_t *s0 = string_make_from_cstring( "0" );
   
   avltree = s_avltree_make();
   
   s_avltree_put( avltree, s4 );
   s_avltree_put( avltree, s2 );
   s_avltree_put( avltree, s6 );
   s_avltree_put( avltree, s7 );
   
   result = s_avltree_has( avltree, s4 );
   CU_ASSERT( result == 1 );
 
   result = s_avltree_has( avltree, s2 );
   CU_ASSERT( result == 1 );
 
   result = s_avltree_has( avltree, s6 );
   CU_ASSERT( result == 1 );
 
   result = s_avltree_has( avltree, s7 );
   CU_ASSERT( result == 1 );
 
   result = s_avltree_has( avltree, s0 );
   CU_ASSERT( result == 0 );
 
   string_deep_dispose( &s0 );
   s_avltree_deep_dispose( &avltree );

   return;
}

int
add_test_has( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_has", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_has_1
   add_test_to_suite( p_suite, test_has_1, "test_has_1" );

   // test_has_2
   add_test_to_suite( p_suite, test_has_2, "test_has_2" );

   // test_has_3
   add_test_to_suite( p_suite, test_has_3, "test_has_3" );

   // test_has_4
   add_test_to_suite( p_suite, test_has_4, "test_has_4" );

   // test_has_5
   add_test_to_suite( p_suite, test_has_5, "test_has_5" );

   // test_has_6
   add_test_to_suite( p_suite, test_has_6, "test_has_6" );

   // test_has_7
   add_test_to_suite( p_suite, test_has_7, "test_has_7" );

   // test_has_8
   add_test_to_suite( p_suite, test_has_8, "test_has_8" );

   // test_has_9
   add_test_to_suite( p_suite, test_has_9, "test_has_9" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

