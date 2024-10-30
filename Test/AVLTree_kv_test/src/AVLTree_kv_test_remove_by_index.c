/**
 @file AVLTree_test_remove_by_index.c
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
   test_remove_by_index_1
*/

void test_remove_by_index_1( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 10, 1 );
   
   ii_avltree_kv_remove_by_index( avltree, 0 );
   
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 0 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 0 );
 
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_remove_by_index_2
*/

void test_remove_by_index_2( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   ii_avltree_kv_remove_by_index( avltree, 1 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 2 );
   
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_remove_by_index_2a
*/

void test_remove_by_index_2a( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   ii_avltree_kv_remove_by_index( avltree, 0 );
 
   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 2 );
   
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_remove_by_index_2b
*/

void test_remove_by_index_2b( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   ii_avltree_kv_remove_by_index( avltree, 2 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 2 );
   
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_remove_by_index_3
*/

void test_remove_by_index_3( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   
   ii_avltree_kv_remove_by_index( avltree, 1 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 2 );
   
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_remove_by_index_3a
*/

void test_remove_by_index_3a( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   
   ii_avltree_kv_remove_by_index( avltree, 0 );
 
   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 2 );
   
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_remove_by_index_3b
*/

void test_remove_by_index_3b( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   
   ii_avltree_kv_remove_by_index( avltree, 1 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 2 );
   
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_remove_by_index_4
*/

void test_remove_by_index_4( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   ii_avltree_kv_remove_by_index( avltree, 1 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 0 );
  
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 2 );
   
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_remove_by_index_4a
*/

void test_remove_by_index_4a( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   ii_avltree_kv_remove_by_index( avltree, 0 );
 
   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 0 );
  
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 2 );
   
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_remove_by_index_4b
*/

void test_remove_by_index_4b( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   ii_avltree_kv_remove_by_index( avltree, 2 );
 
   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 0 );
  
   CU_ASSERT( ii_avltree_kv_count( avltree ) == 2 );
   
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_remove_by_index_5
   
            4
         2      6
       1   3  5   7
*/

void test_remove_by_index_5( void )
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
   
   ii_avltree_kv_remove_by_index( avltree, 3 );
 
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
   
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_remove_by_index_5a
   
            4
         2      6
       1   3  5   7
*/

void test_remove_by_index_5a( void )
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
   
   ii_avltree_kv_remove_by_index( avltree, 0 );
 
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
   
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_remove_by_index_5b
   
            4
         2      6
       1   3  5   7
*/

void test_remove_by_index_5b( void )
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
   
   ii_avltree_kv_remove_by_index( avltree, 1 );
 
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
   
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_remove_by_index_5c
   
            4
         2      6
       1   3  5   7
*/

void test_remove_by_index_5c( void )
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
   
   ii_avltree_kv_remove_by_index( avltree, 2 );
 
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
   
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_remove_by_index_5d
   
            4
         2      6
       1   3  5   7
*/

void test_remove_by_index_5d( void )
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
   
   ii_avltree_kv_remove_by_index( avltree, 4 );
 
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
   
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_remove_by_index_5e
   
            4
         2      6
       1   3  5   7
*/

void test_remove_by_index_5e( void )
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
   
   ii_avltree_kv_remove_by_index( avltree, 5 );
 
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
   
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_remove_by_index_5f
   
            4
         2      6
       1   3  5   7
*/

void test_remove_by_index_5f( void )
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
   
   ii_avltree_kv_remove_by_index( avltree, 6 );
 
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
   
   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_remove_by_index_6

            4
         2      6
       1   3  5   7
*/

void test_remove_by_index_6( void )
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

   ii_avltree_kv_remove_by_index( avltree, 0 );

   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 0 );

   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 5 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ii_avltree_kv_count( avltree ) == 6 );

   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_remove_by_index_6a

            4
         2      6
       1   3  5   7
*/

void test_remove_by_index_6a( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );

   ii_avltree_kv_remove_by_index( avltree, 1 );

   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_avltree_kv_count( avltree ) == 1 );

   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_remove_by_index_6b

            4
         2      6
       1   3  5   7
*/

void test_remove_by_index_6b( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 80, 8 );
   ii_avltree_kv_put( avltree, 70, 7 );
   ii_avltree_kv_put( avltree, 60, 6 );

   ii_avltree_kv_remove_by_index( avltree, 3 );

   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 8 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_avltree_kv_count( avltree ) == 3 );

   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_remove_by_index_6c

            4
         2      6
       1   3  5   7
*/

void test_remove_by_index_6c( void )
{
   ii_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   avltree = ii_avltree_kv_make();

   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 30, 3 );

   ii_avltree_kv_remove_by_index( avltree, 0 );

   result = ii_avltree_kv_has( avltree, 1 );
   CU_ASSERT( result == 0 );

   result = ii_avltree_kv_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_avltree_kv_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ii_avltree_kv_count( avltree ) == 3 );

   ii_avltree_kv_dispose( &avltree );

   return;
}

/**
   test_remove_by_index_7
*/

void test_remove_by_index_7( void )
{
   ss_avltree_kv_t *avltree = NULL;
   int32_t result = 0;

   string_t *s1 = NULL;
   string_t *s10 = NULL;
   string_t *s2 = NULL;
   string_t *s20 = NULL;
   string_t *s3 = NULL;
   string_t *s30 = NULL;
   string_t *s4 = NULL;
   string_t *s40 = NULL;
   
   s1 = string_make_from_cstring( "1" );
   s10 = string_make_from_cstring( "10" );
   s2 = string_make_from_cstring( "2" );
   s20 = string_make_from_cstring( "20" );
   s3 = string_make_from_cstring( "3" );
   s30 = string_make_from_cstring( "30" );
   s4 = string_make_from_cstring( "4" );
   s40 = string_make_from_cstring( "40" );
   
   avltree = ss_avltree_kv_make();

   ss_avltree_kv_put( avltree, s40, s4 );
   ss_avltree_kv_put( avltree, s10, s1 );
   ss_avltree_kv_put( avltree, s20, s2 );
   ss_avltree_kv_put( avltree, s30, s3 );

   ss_avltree_kv_remove_by_index( avltree, 0 );

   result = ss_avltree_kv_has( avltree, s1 );
   CU_ASSERT( result == 0 );

   result = ss_avltree_kv_has( avltree, s2 );
   CU_ASSERT( result == 1 );

   result = ss_avltree_kv_has( avltree, s3 );
   CU_ASSERT( result == 1 );

   result = ss_avltree_kv_has( avltree, s4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ss_avltree_kv_count( avltree ) == 3 );

   ss_avltree_kv_deep_dispose( &avltree );
   string_deep_dispose( &s1 );
   string_deep_dispose( &s10 );
   

   return;
}

int
add_test_remove_by_index( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_remove_by_index", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_remove_by_index_1
   add_test_to_suite( p_suite, test_remove_by_index_1, "test_remove_by_index_1" );

   // test_remove_by_index_2
   add_test_to_suite( p_suite, test_remove_by_index_2, "test_remove_by_index_2" );
   add_test_to_suite( p_suite, test_remove_by_index_2a, "test_remove_by_index_2a" );
   add_test_to_suite( p_suite, test_remove_by_index_2b, "test_remove_by_index_2b" );

   // test_remove_by_index_3
   add_test_to_suite( p_suite, test_remove_by_index_3, "test_remove_by_index_3" );
   add_test_to_suite( p_suite, test_remove_by_index_3a, "test_remove_by_index_3a" );
   add_test_to_suite( p_suite, test_remove_by_index_3b, "test_remove_by_index_3b" );

   // test_remove_by_index_4
   add_test_to_suite( p_suite, test_remove_by_index_4, "test_remove_by_index_4" );
   add_test_to_suite( p_suite, test_remove_by_index_4a, "test_remove_by_index_4a" );
   add_test_to_suite( p_suite, test_remove_by_index_4b, "test_remove_by_index_4b" );

   // test_remove_by_index_5
   add_test_to_suite( p_suite, test_remove_by_index_5, "test_remove_by_index_5" );
   add_test_to_suite( p_suite, test_remove_by_index_5a, "test_remove_by_index_5a" );
   add_test_to_suite( p_suite, test_remove_by_index_5b, "test_remove_by_index_5b" );
   add_test_to_suite( p_suite, test_remove_by_index_5c, "test_remove_by_index_5c" );
   add_test_to_suite( p_suite, test_remove_by_index_5d, "test_remove_by_index_5d" );
   add_test_to_suite( p_suite, test_remove_by_index_5e, "test_remove_by_index_5e" );
   add_test_to_suite( p_suite, test_remove_by_index_5f, "test_remove_by_index_5f" );

   // test_remove_by_index_6
   add_test_to_suite( p_suite, test_remove_by_index_6, "test_remove_by_index_6" );
   add_test_to_suite( p_suite, test_remove_by_index_6a, "test_remove_by_index_6a" );
   add_test_to_suite( p_suite, test_remove_by_index_6b, "test_remove_by_index_6b" );
   add_test_to_suite( p_suite, test_remove_by_index_6c, "test_remove_by_index_6c" );

   // test_remove_by_index_7
   add_test_to_suite( p_suite, test_remove_by_index_7, "test_remove_by_index_7" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

