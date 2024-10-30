/**
 @file BSTree_test_remove.c
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
   test_remove_1
*/

void test_remove_1( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 10, 1 );
   
   ii_bstree_kv_remove( bstree, 1 );
   
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 0 );
 
   result = ii_bstree_kv_has( bstree, 1 );
   CU_ASSERT( result == 0 );
 
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_remove_2
*/

void test_remove_2( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   ii_bstree_kv_remove( bstree, 2 );
 
   result = ii_bstree_kv_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 2 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_remove_2a
*/

void test_remove_2a( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   ii_bstree_kv_remove( bstree, 1 );
 
   result = ii_bstree_kv_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 1 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 2 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_remove_2b
*/

void test_remove_2b( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   ii_bstree_kv_remove( bstree, 3 );
 
   result = ii_bstree_kv_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 3 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 2 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_remove_3
*/

void test_remove_3( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   
   ii_bstree_kv_remove( bstree, 2 );
 
   result = ii_bstree_kv_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 2 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_remove_3a
*/

void test_remove_3a( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   
   ii_bstree_kv_remove( bstree, 1 );
 
   result = ii_bstree_kv_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 1 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 2 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_remove_3b
*/

void test_remove_3b( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   
   ii_bstree_kv_remove( bstree, 2 );
 
   result = ii_bstree_kv_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 2 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_remove_4
*/

void test_remove_4( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   ii_bstree_kv_remove( bstree, 2 );
 
   result = ii_bstree_kv_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 2 );
   CU_ASSERT( result == 0 );
  
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 2 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_remove_4a
*/

void test_remove_4a( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   ii_bstree_kv_remove( bstree, 1 );
 
   result = ii_bstree_kv_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 1 );
   CU_ASSERT( result == 0 );
  
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 2 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_remove_4b
*/

void test_remove_4b( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   ii_bstree_kv_remove( bstree, 3 );
 
   result = ii_bstree_kv_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 3 );
   CU_ASSERT( result == 0 );
  
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 2 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_remove_5
   
            4
         2      6
       1   3  5   7
*/

void test_remove_5( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 50, 5 );
   ii_bstree_kv_put( bstree, 70, 7 );
   
   ii_bstree_kv_remove( bstree, 4 );
 
   result = ii_bstree_kv_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 6 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 5 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 7 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 4 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 6 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_remove_5a
   
            4
         2      6
       1   3  5   7
*/

void test_remove_5a( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 50, 5 );
   ii_bstree_kv_put( bstree, 70, 7 );
   
   ii_bstree_kv_remove( bstree, 1 );
 
   result = ii_bstree_kv_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 6 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 4 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 5 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 7 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 1 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 6 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_remove_5b
   
            4
         2      6
       1   3  5   7
*/

void test_remove_5b( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 50, 5 );
   ii_bstree_kv_put( bstree, 70, 7 );
   
   ii_bstree_kv_remove( bstree, 2 );
 
   result = ii_bstree_kv_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 6 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 4 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 5 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 7 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 6 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_remove_5c
   
            4
         2      6
       1   3  5   7
*/

void test_remove_5c( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 50, 5 );
   ii_bstree_kv_put( bstree, 70, 7 );
   
   ii_bstree_kv_remove( bstree, 3 );
 
   result = ii_bstree_kv_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 6 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 4 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 5 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 7 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 3 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 6 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_remove_5d
   
            4
         2      6
       1   3  5   7
*/

void test_remove_5d( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 50, 5 );
   ii_bstree_kv_put( bstree, 70, 7 );
   
   ii_bstree_kv_remove( bstree, 5 );
 
   result = ii_bstree_kv_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 6 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 4 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 7 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 5 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 6 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_remove_5e
   
            4
         2      6
       1   3  5   7
*/

void test_remove_5e( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 50, 5 );
   ii_bstree_kv_put( bstree, 70, 7 );
   
   ii_bstree_kv_remove( bstree, 6 );
 
   result = ii_bstree_kv_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 5 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 4 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 7 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 6 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 6 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_remove_5f
   
            4
         2      6
       1   3  5   7
*/

void test_remove_5f( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 50, 5 );
   ii_bstree_kv_put( bstree, 70, 7 );
   
   ii_bstree_kv_remove( bstree, 7 );
 
   result = ii_bstree_kv_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 5 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 4 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 6 );
   CU_ASSERT( result == 1 );
 
   result = ii_bstree_kv_has( bstree, 7 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 6 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_remove_6

            4
         2      6
       1   3  5   7
*/

void test_remove_6( void )
{
   ii_bstree_kv_t *bstree = NULL;
   ii_bstree_kv_cursor_t *cursor = NULL;
   int32_t result = 0;

   bstree = ii_bstree_kv_make();
   cursor = ii_bstree_kv_cursor_make( bstree );

   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 50, 5 );
   ii_bstree_kv_put( bstree, 70, 7 );

   ii_bstree_kv_cursor_start( cursor );
   ii_bstree_kv_remove( bstree, 1 );

   result = ii_bstree_kv_has( bstree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_bstree_kv_has( bstree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_bstree_kv_has( bstree, 1 );
   CU_ASSERT( result == 0 );

   result = ii_bstree_kv_has( bstree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_bstree_kv_has( bstree, 5 );
   CU_ASSERT( result == 1 );

   result = ii_bstree_kv_has( bstree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_bstree_kv_has( bstree, 4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ii_bstree_kv_count( bstree ) == 6 );

   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_remove_6a

            4
         2      6
       1   3  5   7
*/

void test_remove_6a( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;

   bstree = ii_bstree_kv_make();

   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );

   ii_bstree_kv_remove( bstree, 4 );

   result = ii_bstree_kv_has( bstree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_bstree_kv_has( bstree, 4 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_bstree_kv_count( bstree ) == 1 );

   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_remove_6b

            4
         2      6
       1   3  5   7
*/

void test_remove_6b( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;

   bstree = ii_bstree_kv_make();

   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 80, 8 );
   ii_bstree_kv_put( bstree, 70, 7 );
   ii_bstree_kv_put( bstree, 60, 6 );

   ii_bstree_kv_remove( bstree, 8 );

   result = ii_bstree_kv_has( bstree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_bstree_kv_has( bstree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_bstree_kv_has( bstree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_bstree_kv_has( bstree, 8 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_bstree_kv_count( bstree ) == 3 );

   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_remove_6c

            4
         2      6
       1   3  5   7
*/

void test_remove_6c( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t result = 0;

   bstree = ii_bstree_kv_make();

   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 30, 3 );

   ii_bstree_kv_remove( bstree, 1 );

   result = ii_bstree_kv_has( bstree, 1 );
   CU_ASSERT( result == 0 );

   result = ii_bstree_kv_has( bstree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_bstree_kv_has( bstree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_bstree_kv_has( bstree, 4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ii_bstree_kv_count( bstree ) == 3 );

   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_remove_7
*/

void test_remove_7( void )
{
   ss_bstree_kv_t *bstree = NULL;
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
   
   bstree = ss_bstree_kv_make();

   ss_bstree_kv_put( bstree, s40, s4 );
   ss_bstree_kv_put( bstree, s10, s1 );
   ss_bstree_kv_put( bstree, s20, s2 );
   ss_bstree_kv_put( bstree, s30, s3 );

   ss_bstree_kv_remove( bstree, s1 );

   result = ss_bstree_kv_has( bstree, s1 );
   CU_ASSERT( result == 0 );

   result = ss_bstree_kv_has( bstree, s2 );
   CU_ASSERT( result == 1 );

   result = ss_bstree_kv_has( bstree, s3 );
   CU_ASSERT( result == 1 );

   result = ss_bstree_kv_has( bstree, s4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ss_bstree_kv_count( bstree ) == 3 );

   ss_bstree_kv_deep_dispose( &bstree );
   string_deep_dispose( &s1 );
   string_deep_dispose( &s10 );
   

   return;
}

int
add_test_remove( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_remove", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_remove_1
   add_test_to_suite( p_suite, test_remove_1, "test_remove_1" );

   // test_remove_2
   add_test_to_suite( p_suite, test_remove_2, "test_remove_2" );
   add_test_to_suite( p_suite, test_remove_2a, "test_remove_2a" );
   add_test_to_suite( p_suite, test_remove_2b, "test_remove_2b" );

   // test_remove_3
   add_test_to_suite( p_suite, test_remove_3, "test_remove_3" );
   add_test_to_suite( p_suite, test_remove_3a, "test_remove_3a" );
   add_test_to_suite( p_suite, test_remove_3b, "test_remove_3b" );

   // test_remove_4
   add_test_to_suite( p_suite, test_remove_4, "test_remove_4" );
   add_test_to_suite( p_suite, test_remove_4a, "test_remove_4a" );
   add_test_to_suite( p_suite, test_remove_4b, "test_remove_4b" );

   // test_remove_5
   add_test_to_suite( p_suite, test_remove_5, "test_remove_5" );
   add_test_to_suite( p_suite, test_remove_5a, "test_remove_5a" );
   add_test_to_suite( p_suite, test_remove_5b, "test_remove_5b" );
   add_test_to_suite( p_suite, test_remove_5c, "test_remove_5c" );
   add_test_to_suite( p_suite, test_remove_5d, "test_remove_5d" );
   add_test_to_suite( p_suite, test_remove_5e, "test_remove_5e" );
   add_test_to_suite( p_suite, test_remove_5f, "test_remove_5f" );

   // test_remove_6
   add_test_to_suite( p_suite, test_remove_6, "test_remove_6" );
   add_test_to_suite( p_suite, test_remove_6a, "test_remove_6a" );
   add_test_to_suite( p_suite, test_remove_6b, "test_remove_6b" );
   add_test_to_suite( p_suite, test_remove_6c, "test_remove_6c" );

   // test_remove_7
   add_test_to_suite( p_suite, test_remove_7, "test_remove_7" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

