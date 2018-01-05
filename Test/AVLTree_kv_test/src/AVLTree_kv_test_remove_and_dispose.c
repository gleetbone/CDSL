/**
 @file AVLTree_test_remove_and_dispose.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for AVLTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for AVLTree_make.

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_AVLTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_remove_and_dispose_1
*/

void test_remove_and_dispose_1( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 10, 1 );
   
   ii_avltree_kv_remove_and_dispose( avltree, 1 );
   
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 0 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 0 );
 
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_2
*/

void test_remove_and_dispose_2( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   ii_avltree_kv_remove_and_dispose( avltree, 2 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 2 );
   
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_2a
*/

void test_remove_and_dispose_2a( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   ii_avltree_kv_remove_and_dispose( avltree, 1 );
 
   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 2 );
   
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_2b
*/

void test_remove_and_dispose_2b( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   ii_avltree_kv_remove_and_dispose( avltree, 3 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 2 );
   
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_3
*/

void test_remove_and_dispose_3( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   
   ii_avltree_kv_remove_and_dispose( avltree, 2 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 2 );
   
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_3a
*/

void test_remove_and_dispose_3a( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   
   ii_avltree_kv_remove_and_dispose( avltree, 1 );
 
   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 2 );
   
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_3b
*/

void test_remove_and_dispose_3b( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   
   ii_avltree_kv_remove_and_dispose( avltree, 2 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 2 );
   
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_4
*/

void test_remove_and_dispose_4( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   ii_avltree_kv_remove_and_dispose( avltree, 2 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 0 );
  
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 2 );
   
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_4a
*/

void test_remove_and_dispose_4a( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   ii_avltree_kv_remove_and_dispose( avltree, 1 );
 
   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 0 );
  
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 2 );
   
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_4b
*/

void test_remove_and_dispose_4b( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   ii_avltree_kv_remove_and_dispose( avltree, 3 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 0 );
  
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 2 );
   
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_5
   
            4
         2      6
       1   3  5   7
*/

void test_remove_and_dispose_5( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 50, 5 );
   ii_avltree_kv_put( avltree, 70, 7 );
   
   ii_avltree_kv_remove_and_dispose( avltree, 4 );
 
   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 6 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 5 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 7 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 6 );
   
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_5a
   
            4
         2      6
       1   3  5   7
*/

void test_remove_and_dispose_5a( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 50, 5 );
   ii_avltree_kv_put( avltree, 70, 7 );
   
   ii_avltree_kv_remove_and_dispose( avltree, 1 );
 
   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 6 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 5 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 7 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 6 );
   
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_5b
   
            4
         2      6
       1   3  5   7
*/

void test_remove_and_dispose_5b( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 50, 5 );
   ii_avltree_kv_put( avltree, 70, 7 );
   
   ii_avltree_kv_remove_and_dispose( avltree, 2 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 6 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 5 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 7 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 6 );
   
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_5c
   
            4
         2      6
       1   3  5   7
*/

void test_remove_and_dispose_5c( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 50, 5 );
   ii_avltree_kv_put( avltree, 70, 7 );
   
   ii_avltree_kv_remove_and_dispose( avltree, 3 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 6 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 5 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 7 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 6 );
   
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_5d
   
            4
         2      6
       1   3  5   7
*/

void test_remove_and_dispose_5d( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 50, 5 );
   ii_avltree_kv_put( avltree, 70, 7 );
   
   ii_avltree_kv_remove_and_dispose( avltree, 5 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 6 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 7 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 5 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 6 );
   
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_5e
   
            4
         2      6
       1   3  5   7
*/

void test_remove_and_dispose_5e( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 50, 5 );
   ii_avltree_kv_put( avltree, 70, 7 );
   
   ii_avltree_kv_remove_and_dispose( avltree, 6 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 5 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 7 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 6 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 6 );
   
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_5f
   
            4
         2      6
       1   3  5   7
*/

void test_remove_and_dispose_5f( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 50, 5 );
   ii_avltree_kv_put( avltree, 70, 7 );
   
   ii_avltree_kv_remove_and_dispose( avltree, 7 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 5 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 6 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 7 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 6 );
   
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_6

            4
         2
       1   3
*/

void test_remove_and_dispose_6( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );

   ii_avltree_kv_remove_and_dispose( avltree, 4 );

   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_avltree_kv_count( avltree ) == 3 );

   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_6a

            4
         2
       1   3
*/

void test_remove_and_dispose_6a( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );

   ii_avltree_kv_remove_and_dispose( avltree, 2 );

   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 0 );

   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ii_avltree_kv_count( avltree ) == 3 );

   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_7

            4
                6
              5   7
*/

void test_remove_and_dispose_7( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 50, 5 );
   ii_avltree_kv_put( avltree, 70, 7 );

   ii_avltree_kv_remove_and_dispose( avltree, 4 );

   result = ii_avltree_kv_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 5 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_avltree_kv_count( avltree ) == 3 );

   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_8

               5
            4
         2
       1   3
*/

void test_remove_and_dispose_8( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 50, 5 );
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );

   ii_avltree_kv_remove_and_dispose( avltree, 5 );

   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 5 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_avltree_kv_count( avltree ) == 4 );

   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_9

         3
            4
                6
              5   7
*/

void test_remove_and_dispose_9( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 50, 5 );
   ii_avltree_kv_put( avltree, 70, 7 );

   ii_avltree_kv_remove_and_dispose( avltree, 3 );

   result = ii_avltree_kv_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 5 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_avltree_kv_count( avltree ) == 4 );

   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_10

                  6
               5
            4
         2
       1   3
*/

void test_remove_and_dispose_10( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 50, 5 );
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );

   ii_avltree_kv_remove_and_dispose( avltree, 6 );

   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 5 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 6 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_avltree_kv_count( avltree ) == 5 );

   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_11

      2
         3
            4
                6
              5   7
*/

void test_remove_and_dispose_11( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 50, 5 );
   ii_avltree_kv_put( avltree, 70, 7 );

   ii_avltree_kv_remove_and_dispose( avltree, 2 );

   result = ii_avltree_kv_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 5 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_avltree_kv_count( avltree ) == 5 );

   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_12

                  6
               5
            4
         2
       1   3
*/

void test_remove_and_dispose_12( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 50, 5 );
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );

   ii_avltree_kv_remove_and_dispose( avltree, 5 );

   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 5 );
   CU_ASSERT( result == 0 );

   result = ii_avltree_kv_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ii_avltree_kv_count( avltree ) == 5 );

   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_13

      2
         3
            4
                6
              5   7
*/

void test_remove_and_dispose_13( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 50, 5 );
   ii_avltree_kv_put( avltree, 70, 7 );

   ii_avltree_kv_remove_and_dispose( avltree, 3 );

   result = ii_avltree_kv_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 5 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 0 );

   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ii_avltree_kv_count( avltree ) == 5 );

   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_14

                  8
            4               12
         2       6      10       14
       1   3   5   7   9  11   13   15
*/

void test_remove_and_dispose_14( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 80, 8 );
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 120, 12 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 100, 10 );
   ii_avltree_kv_put( avltree, 140, 14 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 50, 5 );
   ii_avltree_kv_put( avltree, 70, 7 );
   ii_avltree_kv_put( avltree, 90, 9 );
   ii_avltree_kv_put( avltree, 110, 11 );
   ii_avltree_kv_put( avltree, 130, 13 );
   ii_avltree_kv_put( avltree, 150, 15 );

   ii_avltree_kv_remove_and_dispose( avltree, 4 );

   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 0 );

   result = ii_avltree_kv_has( avltree, 5 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 8 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 9 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 10 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 11 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 12 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 13 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 14 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 15 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ii_avltree_kv_count( avltree ) == 14 );

   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_14a

                  8
            4               12
         2       6      10       14
       1   3   5   7   9  11   13   15
*/

void test_remove_and_dispose_14a( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 80, 8 );
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 120, 12 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 100, 10 );
   ii_avltree_kv_put( avltree, 140, 14 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 50, 5 );
   ii_avltree_kv_put( avltree, 70, 7 );
   ii_avltree_kv_put( avltree, 90, 9 );
   ii_avltree_kv_put( avltree, 110, 11 );
   ii_avltree_kv_put( avltree, 130, 13 );
   ii_avltree_kv_put( avltree, 150, 15 );

   ii_avltree_kv_remove_and_dispose( avltree, 12 );

   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 5 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 8 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 9 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 10 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 11 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 12 );
   CU_ASSERT( result == 0 );

   result = ii_avltree_kv_has( avltree, 13 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 14 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 15 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ii_avltree_kv_count( avltree ) == 14 );

   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_15

                             16
              8                              24
      4              12              20             28
  2       6      10      14      18      22      26      30
1   3   5   7   9  11  13  15  17  19  21  23  25  27  29  31
*/

void test_remove_and_dispose_15( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 160, 16 );
   ii_avltree_kv_put( avltree, 80, 8 );
   ii_avltree_kv_put( avltree, 240, 24 );
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 120, 12 );
   ii_avltree_kv_put( avltree, 200, 20 );
   ii_avltree_kv_put( avltree, 280, 28 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 100, 10 );
   ii_avltree_kv_put( avltree, 140, 14 );
   ii_avltree_kv_put( avltree, 180, 18 );
   ii_avltree_kv_put( avltree, 220, 22 );
   ii_avltree_kv_put( avltree, 260, 26 );
   ii_avltree_kv_put( avltree, 300, 30 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 50, 5 );
   ii_avltree_kv_put( avltree, 70, 7 );
   ii_avltree_kv_put( avltree, 90, 9 );
   ii_avltree_kv_put( avltree, 110, 11 );
   ii_avltree_kv_put( avltree, 130, 13 );
   ii_avltree_kv_put( avltree, 150, 15 );
   ii_avltree_kv_put( avltree, 170, 17 );
   ii_avltree_kv_put( avltree, 190, 19 );
   ii_avltree_kv_put( avltree, 210, 21 );
   ii_avltree_kv_put( avltree, 230, 23 );
   ii_avltree_kv_put( avltree, 250, 25 );
   ii_avltree_kv_put( avltree, 270, 27 );
   ii_avltree_kv_put( avltree, 290, 29 );
   ii_avltree_kv_put( avltree, 310, 31 );

   ii_avltree_kv_remove_and_dispose( avltree, 4 );

   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 0 );

   result = ii_avltree_kv_has( avltree, 5 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 8 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 9 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 10 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 11 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 12 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 13 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 14 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 15 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 16 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 17 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 18 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 19 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 20 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 21 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 22 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 23 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 24 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 25 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 26 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 27 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 28 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 29 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 30 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 31 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ii_avltree_kv_count( avltree ) == 30 );

   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_15a

                             16
              8                              24
      4              12              20             28
  2       6      10      14      18      22      26      30
1   3   5   7   9  11  13  15  17  19  21  23  25  27  29  31
*/

void test_remove_and_dispose_15a( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 160, 16 );
   ii_avltree_kv_put( avltree, 80, 8 );
   ii_avltree_kv_put( avltree, 120, 12 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 100, 10 );
   ii_avltree_kv_put( avltree, 140, 14 );
   ii_avltree_kv_put( avltree, 90, 9 );
   ii_avltree_kv_put( avltree, 110, 11 );
   ii_avltree_kv_put( avltree, 130, 13 );
   ii_avltree_kv_put( avltree, 150, 15 );

   ii_avltree_kv_remove_and_dispose( avltree, 8 );

   result = ii_avltree_kv_has( avltree, 16 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 8 );
   CU_ASSERT( result == 0 );

   result = ii_avltree_kv_has( avltree, 12 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 10 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 14 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 9 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 11 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 13 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 15 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ii_avltree_kv_count( avltree ) == 9 );

   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_15b

                             16
              8                              24
      4              12              20             28
  2       6      10      14      18      22      26      30
1   3   5   7   9  11  13  15  17  19  21  23  25  27  29  31
*/

void test_remove_and_dispose_15b( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 160, 16 );
   ii_avltree_kv_put( avltree, 80, 8 );
   ii_avltree_kv_put( avltree, 120, 12 );
   ii_avltree_kv_put( avltree, 100, 10 );
   ii_avltree_kv_put( avltree, 140, 14 );
   ii_avltree_kv_put( avltree, 90, 9 );
   ii_avltree_kv_put( avltree, 110, 11 );
   ii_avltree_kv_put( avltree, 130, 13 );
   ii_avltree_kv_put( avltree, 150, 15 );

   ii_avltree_kv_remove_and_dispose( avltree, 12 );

   result = ii_avltree_kv_has( avltree, 16 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 8 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 12 );
   CU_ASSERT( result == 0 );

   result = ii_avltree_kv_has( avltree, 10 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 14 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 9 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 11 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 13 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 15 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ii_avltree_kv_count( avltree ) == 8 );

   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_15c

                             16
              8                              24
      4              12              20             28
  2       6      10      14      18      22      26      30
1   3   5   7   9  11  13  15  17  19  21  23  25  27  29  31
*/

void test_remove_and_dispose_15c( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 160, 16 );
   ii_avltree_kv_put( avltree, 80, 8 );
   ii_avltree_kv_put( avltree, 120, 12 );
   ii_avltree_kv_put( avltree, 100, 10 );
   ii_avltree_kv_put( avltree, 140, 14 );
   ii_avltree_kv_put( avltree, 90, 9 );
   ii_avltree_kv_put( avltree, 110, 11 );
   ii_avltree_kv_put( avltree, 130, 13 );
   ii_avltree_kv_put( avltree, 150, 15 );

   ii_avltree_kv_remove_and_dispose( avltree, 10 );

   result = ii_avltree_kv_has( avltree, 16 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 8 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 12 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 10 );
   CU_ASSERT( result == 0 );

   result = ii_avltree_kv_has( avltree, 14 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 9 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 11 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 13 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 15 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ii_avltree_kv_count( avltree ) == 8 );

   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_15d

                             16
              8                              24
      4              12              20             28
  2       6      10      14      18      22      26      30
1   3   5   7   9  11  13  15  17  19  21  23  25  27  29  31
*/

void test_remove_and_dispose_15d( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 160, 16 );
   ii_avltree_kv_put( avltree, 80, 8 );
   ii_avltree_kv_put( avltree, 120, 12 );
   ii_avltree_kv_put( avltree, 100, 10 );
   ii_avltree_kv_put( avltree, 140, 14 );
   ii_avltree_kv_put( avltree, 90, 9 );
   ii_avltree_kv_put( avltree, 110, 11 );
   ii_avltree_kv_put( avltree, 130, 13 );
   ii_avltree_kv_put( avltree, 150, 15 );

   ii_avltree_kv_remove_and_dispose( avltree, 14 );

   result = ii_avltree_kv_has( avltree, 16 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 8 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 12 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 10 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 14 );
   CU_ASSERT( result == 0 );

   result = ii_avltree_kv_has( avltree, 9 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 11 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 13 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 15 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ii_avltree_kv_count( avltree ) == 8 );

   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_15e

                             16
              8                              24
      4              12              20             28
  2       6      10      14      18      22      26      30
1   3   5   7   9  11  13  15  17  19  21  23  25  27  29  31
*/

void test_remove_and_dispose_15e( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 160, 16 );
   ii_avltree_kv_put( avltree, 80, 8 );
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 50, 5 );
   ii_avltree_kv_put( avltree, 70, 7 );

   ii_avltree_kv_remove_and_dispose( avltree, 8 );

   result = ii_avltree_kv_has( avltree, 16 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 8 );
   CU_ASSERT( result == 0 );

   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 5 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 7 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ii_avltree_kv_count( avltree ) == 5 );

   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_16

                             16
              8                              24
      4              12              20             28
  2       6      10      14      18      22      26      30
1   3   5   7   9  11  13  15  17  19  21  23  25  27  29  31
*/

void test_remove_and_dispose_16( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 160, 16 );
   ii_avltree_kv_put( avltree, 80, 8 );
   ii_avltree_kv_put( avltree, 240, 24 );
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 120, 12 );
   ii_avltree_kv_put( avltree, 200, 20 );
   ii_avltree_kv_put( avltree, 280, 28 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 100, 10 );
   ii_avltree_kv_put( avltree, 140, 14 );
   ii_avltree_kv_put( avltree, 180, 18 );
   ii_avltree_kv_put( avltree, 220, 22 );
   ii_avltree_kv_put( avltree, 260, 26 );
   ii_avltree_kv_put( avltree, 300, 30 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 50, 5 );
   ii_avltree_kv_put( avltree, 70, 7 );
   ii_avltree_kv_put( avltree, 90, 9 );
   ii_avltree_kv_put( avltree, 110, 11 );
   ii_avltree_kv_put( avltree, 130, 13 );
   ii_avltree_kv_put( avltree, 150, 15 );
   ii_avltree_kv_put( avltree, 170, 17 );
   ii_avltree_kv_put( avltree, 190, 19 );
   ii_avltree_kv_put( avltree, 210, 21 );
   ii_avltree_kv_put( avltree, 230, 23 );
   ii_avltree_kv_put( avltree, 250, 25 );
   ii_avltree_kv_put( avltree, 270, 27 );
   ii_avltree_kv_put( avltree, 290, 29 );
   ii_avltree_kv_put( avltree, 310, 31 );

   ii_avltree_kv_remove_and_dispose( avltree, 4 );

   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 0 );

   result = ii_avltree_kv_has( avltree, 5 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 8 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 9 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 10 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 11 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 12 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 13 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 14 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 15 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 16 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 17 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 18 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 19 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 20 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 21 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 22 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 23 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 24 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 25 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 26 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 27 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 28 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 29 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 30 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 31 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ii_avltree_kv_count( avltree ) == 30 );

   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_16a

                             16
              8                              24
      4              12              20             28
  2       6      10      14      18      22      26      30
1   3   5   7   9  11  13  15  17  19  21  23  25  27  29  31
*/

void test_remove_and_dispose_16a( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 160, 16 );
   ii_avltree_kv_put( avltree, 240, 24 );
   ii_avltree_kv_put( avltree, 280, 28 );
   ii_avltree_kv_put( avltree, 260, 26 );
   ii_avltree_kv_put( avltree, 300, 30 );
   ii_avltree_kv_put( avltree, 250, 25 );
   ii_avltree_kv_put( avltree, 270, 27 );
   ii_avltree_kv_put( avltree, 290, 29 );
   ii_avltree_kv_put( avltree, 310, 31 );

   ii_avltree_kv_remove_and_dispose( avltree, 24 );

   result = ii_avltree_kv_has( avltree, 16 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 24 );
   CU_ASSERT( result == 0 );

   result = ii_avltree_kv_has( avltree, 28 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 26 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 30 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 25 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 27 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 29 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 31 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ii_avltree_kv_count( avltree ) == 8 );

   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_16b

                             16
              8                              24
      4              12              20             28
  2       6      10      14      18      22      26      30
1   3   5   7   9  11  13  15  17  19  21  23  25  27  29  31
*/

void test_remove_and_dispose_16b( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 160, 16 );
   ii_avltree_kv_put( avltree, 80, 8 );
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 30, 3 );

   ii_avltree_kv_remove_and_dispose( avltree, 16 );

   result = ii_avltree_kv_has( avltree, 16 );
   CU_ASSERT( result == 0 );

   result = ii_avltree_kv_has( avltree, 8 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );
   
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 4 );

   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_16c

                             16
              8                              24
      4              12              20             28
  2       6      10      14      18      22      26      30
1   3   5   7   9  11  13  15  17  19  21  23  25  27  29  31
*/

void test_remove_and_dispose_16c( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 160, 16 );
   ii_avltree_kv_put( avltree, 240, 24 );
   ii_avltree_kv_put( avltree, 200, 20 );
   ii_avltree_kv_put( avltree, 220, 22 );
   ii_avltree_kv_put( avltree, 180, 18 );
   ii_avltree_kv_put( avltree, 230, 23 );
   ii_avltree_kv_put( avltree, 210, 21 );
   ii_avltree_kv_put( avltree, 190, 19 );
   ii_avltree_kv_put( avltree, 170, 17 );

   ii_avltree_kv_remove_and_dispose( avltree, 20 );

   result = ii_avltree_kv_has( avltree, 16 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 24 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 20 );
   CU_ASSERT( result == 0 );

   result = ii_avltree_kv_has( avltree, 22 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 18 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 23 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 21 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 19 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 17 );
   CU_ASSERT( result == 1 );
   
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 8 );

   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_16d

                             16
              8                              24
      4              12              20             28
  2       6      10      14      18      22      26      30
1   3   5   7   9  11  13  15  17  19  21  23  25  27  29  31
*/

void test_remove_and_dispose_16d( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 160, 16 );
   ii_avltree_kv_put( avltree, 240, 24 );
   ii_avltree_kv_put( avltree, 200, 20 );
   ii_avltree_kv_put( avltree, 180, 18 );
   ii_avltree_kv_put( avltree, 220, 22 );
   ii_avltree_kv_put( avltree, 230, 23 );
   ii_avltree_kv_put( avltree, 210, 21 );
   ii_avltree_kv_put( avltree, 190, 19 );
   ii_avltree_kv_put( avltree, 170, 17 );

   ii_avltree_kv_remove_and_dispose( avltree, 18 );

   result = ii_avltree_kv_has( avltree, 16 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 24 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 20 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 18 );
   CU_ASSERT( result == 0 );

   result = ii_avltree_kv_has( avltree, 22 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 23 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 21 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 19 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 17 );
   CU_ASSERT( result == 1 );
   
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 8 );

   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_remove_and_dispose_16e

                             16
              8                              24
      4              12              20             28
  2       6      10      14      18      22      26      30
1   3   5   7   9  11  13  15  17  19  21  23  25  27  29  31
*/

void test_remove_and_dispose_16e( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 160, 16 );
   ii_avltree_kv_put( avltree, 80, 8 );
   ii_avltree_kv_put( avltree, 120, 12 );
   ii_avltree_kv_put( avltree, 100, 10 );
   ii_avltree_kv_put( avltree, 140, 14 );
   ii_avltree_kv_put( avltree, 90, 9 );
   ii_avltree_kv_put( avltree, 110, 11 );
   ii_avltree_kv_put( avltree, 130, 13 );
   ii_avltree_kv_put( avltree, 150, 15 );

   ii_avltree_kv_remove_and_dispose( avltree, 13 );

   result = ii_avltree_kv_has( avltree, 16 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 8 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 12 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 10 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 14 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 9 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 11 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 13 );
   CU_ASSERT( result == 0 );

   result = ii_avltree_kv_has( avltree, 15 );
   CU_ASSERT( result == 1 );
   
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 8 );

   ii_avltree_kv_dispose( avltree );

   return;
}

int
add_test_remove_and_dispose( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_remove_and_dispose", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_remove_and_dispose_1
   add_test_to_suite( p_suite, test_remove_and_dispose_1, "test_remove_and_dispose_1" );

   // test_remove_and_dispose_2
   add_test_to_suite( p_suite, test_remove_and_dispose_2, "test_remove_and_dispose_2" );
   add_test_to_suite( p_suite, test_remove_and_dispose_2a, "test_remove_and_dispose_2a" );
   add_test_to_suite( p_suite, test_remove_and_dispose_2b, "test_remove_and_dispose_2b" );

   // test_remove_and_dispose_3
   add_test_to_suite( p_suite, test_remove_and_dispose_3, "test_remove_and_dispose_3" );
   add_test_to_suite( p_suite, test_remove_and_dispose_3a, "test_remove_and_dispose_3a" );
   add_test_to_suite( p_suite, test_remove_and_dispose_3b, "test_remove_and_dispose_3b" );

   // test_remove_and_dispose_4
   add_test_to_suite( p_suite, test_remove_and_dispose_4, "test_remove_and_dispose_4" );
   add_test_to_suite( p_suite, test_remove_and_dispose_4a, "test_remove_and_dispose_4a" );
   add_test_to_suite( p_suite, test_remove_and_dispose_4b, "test_remove_and_dispose_4b" );

   // test_remove_and_dispose_5
   add_test_to_suite( p_suite, test_remove_and_dispose_5, "test_remove_and_dispose_5" );
   add_test_to_suite( p_suite, test_remove_and_dispose_5a, "test_remove_and_dispose_5a" );
   add_test_to_suite( p_suite, test_remove_and_dispose_5b, "test_remove_and_dispose_5b" );
   add_test_to_suite( p_suite, test_remove_and_dispose_5c, "test_remove_and_dispose_5c" );
   add_test_to_suite( p_suite, test_remove_and_dispose_5d, "test_remove_and_dispose_5d" );
   add_test_to_suite( p_suite, test_remove_and_dispose_5e, "test_remove_and_dispose_5e" );
   add_test_to_suite( p_suite, test_remove_and_dispose_5f, "test_remove_and_dispose_5f" );

   // test_remove_and_dispose_6
   add_test_to_suite( p_suite, test_remove_and_dispose_6, "test_remove_and_dispose_6" );
   add_test_to_suite( p_suite, test_remove_and_dispose_6a, "test_remove_and_dispose_6a" );

   // test_remove_and_dispose_7
   add_test_to_suite( p_suite, test_remove_and_dispose_7, "test_remove_and_dispose_7" );

   // test_remove_and_dispose_8
   add_test_to_suite( p_suite, test_remove_and_dispose_8, "test_remove_and_dispose_8" );

   // test_remove_and_dispose_9
   add_test_to_suite( p_suite, test_remove_and_dispose_9, "test_remove_and_dispose_9" );

   // test_remove_and_dispose_10
   add_test_to_suite( p_suite, test_remove_and_dispose_10, "test_remove_and_dispose_10" );

   // test_remove_and_dispose_11
   add_test_to_suite( p_suite, test_remove_and_dispose_11, "test_remove_and_dispose_11" );

   // test_remove_and_dispose_12
   add_test_to_suite( p_suite, test_remove_and_dispose_12, "test_remove_and_dispose_12" );

   // test_remove_and_dispose_13
   add_test_to_suite( p_suite, test_remove_and_dispose_13, "test_remove_and_dispose_13" );

   // test_remove_and_dispose_14
   add_test_to_suite( p_suite, test_remove_and_dispose_14, "test_remove_and_dispose_14" );
   add_test_to_suite( p_suite, test_remove_and_dispose_14a, "test_remove_and_dispose_14a" );

   // test_remove_and_dispose_15
   add_test_to_suite( p_suite, test_remove_and_dispose_15, "test_remove_and_dispose_15" );
   add_test_to_suite( p_suite, test_remove_and_dispose_15a, "test_remove_and_dispose_15a" );
   add_test_to_suite( p_suite, test_remove_and_dispose_15b, "test_remove_and_dispose_15b" );
   add_test_to_suite( p_suite, test_remove_and_dispose_15c, "test_remove_and_dispose_15c" );
   add_test_to_suite( p_suite, test_remove_and_dispose_15d, "test_remove_and_dispose_15d" );
   add_test_to_suite( p_suite, test_remove_and_dispose_15e, "test_remove_and_dispose_15e" );

   // test_remove_and_dispose_16
   add_test_to_suite( p_suite, test_remove_and_dispose_16, "test_remove_and_dispose_16" );
   add_test_to_suite( p_suite, test_remove_and_dispose_16a, "test_remove_and_dispose_16a" );
   add_test_to_suite( p_suite, test_remove_and_dispose_16b, "test_remove_and_dispose_16b" );
   add_test_to_suite( p_suite, test_remove_and_dispose_16c, "test_remove_and_dispose_16c" );
   add_test_to_suite( p_suite, test_remove_and_dispose_16d, "test_remove_and_dispose_16d" );
   add_test_to_suite( p_suite, test_remove_and_dispose_16e, "test_remove_and_dispose_16e" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

