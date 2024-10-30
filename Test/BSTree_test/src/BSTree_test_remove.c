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

 Unit tests for BSTree_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_BSTree.h"
#include "s_BSTree.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_remove_1
*/

void test_remove_1( void )
{
   i_bstree_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 1 );
   
   i_bstree_remove( bstree, 0 );
   
   CU_ASSERT( i_bstree_count( bstree ) == 0 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 0 );
 
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_remove_2
*/

void test_remove_2( void )
{
   i_bstree_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   
   i_bstree_start( bstree );
   i_bstree_forth( bstree );
   i_bstree_remove( bstree, 1 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 2 );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_remove_2a
*/

void test_remove_2a( void )
{
   i_bstree_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   
   i_bstree_remove( bstree, 0 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 2 );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_remove_2b
*/

void test_remove_2b( void )
{
   i_bstree_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   
   i_bstree_remove( bstree, 2 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 2 );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_remove_3
*/

void test_remove_3( void )
{
   i_bstree_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 1 );
   
   i_bstree_remove( bstree, 1 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 2 );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_remove_3a
*/

void test_remove_3a( void )
{
   i_bstree_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 1 );
   
   i_bstree_remove( bstree, 0 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 2 );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_remove_3b
*/

void test_remove_3b( void )
{
   i_bstree_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 1 );
   
   i_bstree_remove( bstree, 1 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 2 );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_remove_4
*/

void test_remove_4( void )
{
   i_bstree_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 3 );
   
   i_bstree_remove( bstree, 1 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 0 );
  
   CU_ASSERT( i_bstree_count( bstree ) == 2 );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_remove_4a
*/

void test_remove_4a( void )
{
   i_bstree_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 3 );
   
   i_bstree_remove( bstree, 1 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 0 );
  
   CU_ASSERT( i_bstree_count( bstree ) == 2 );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_remove_4b
*/

void test_remove_4b( void )
{
   i_bstree_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 3 );
   
   i_bstree_remove( bstree, 2 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 0 );
  
   CU_ASSERT( i_bstree_count( bstree ) == 2 );
   
   i_bstree_dispose( &bstree );

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
   i_bstree_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 5 );
   i_bstree_put( bstree, 7 );
   
   i_bstree_remove( bstree, 3 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 6 );
   
   i_bstree_dispose( &bstree );

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
   i_bstree_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 5 );
   i_bstree_put( bstree, 7 );
   
   i_bstree_remove( bstree, 0 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 6 );
   
   i_bstree_dispose( &bstree );

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
   i_bstree_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 5 );
   i_bstree_put( bstree, 7 );
   
   i_bstree_remove( bstree, 1 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 6 );
   
   i_bstree_dispose( &bstree );

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
   i_bstree_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 5 );
   i_bstree_put( bstree, 7 );
   
   i_bstree_remove( bstree, 2 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 6 );
   
   i_bstree_dispose( &bstree );

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
   i_bstree_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 5 );
   i_bstree_put( bstree, 7 );
   
   i_bstree_remove( bstree, 4 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 5 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 6 );
   
   i_bstree_dispose( &bstree );

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
   i_bstree_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 5 );
   i_bstree_put( bstree, 7 );
   
   i_bstree_remove( bstree, 5 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 6 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 6 );
   
   i_bstree_dispose( &bstree );

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
   i_bstree_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 5 );
   i_bstree_put( bstree, 7 );
   
   i_bstree_remove( bstree, 6 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 7 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 6 );
   
   i_bstree_dispose( &bstree );

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
   i_bstree_t *bstree = NULL;
   i_bstree_cursor_t *cursor = NULL;
   int32_t result = 0;

   bstree = i_bstree_make();
   cursor = i_bstree_cursor_make( bstree );

   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 5 );
   i_bstree_put( bstree, 7 );

   i_bstree_cursor_start( cursor );
   i_bstree_remove( bstree, 0 );

   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );

   result = i_bstree_has( bstree, 6 );
   CU_ASSERT( result == 1 );

   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 0 );

   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );

   result = i_bstree_has( bstree, 5 );
   CU_ASSERT( result == 1 );

   result = i_bstree_has( bstree, 7 );
   CU_ASSERT( result == 1 );

   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i_bstree_count( bstree ) == 6 );

   i_bstree_dispose( &bstree );

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
   i_bstree_t *bstree = NULL;
   int32_t result = 0;

   bstree = i_bstree_make();

   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );

   i_bstree_remove( bstree, 1 );

   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );

   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_bstree_count( bstree ) == 1 );

   i_bstree_dispose( &bstree );

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
   i_bstree_t *bstree = NULL;
   int32_t result = 0;

   bstree = i_bstree_make();

   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 8 );
   i_bstree_put( bstree, 7 );
   i_bstree_put( bstree, 6 );

   i_bstree_remove( bstree, 3 );

   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 1 );

   result = i_bstree_has( bstree, 6 );
   CU_ASSERT( result == 1 );

   result = i_bstree_has( bstree, 7 );
   CU_ASSERT( result == 1 );

   result = i_bstree_has( bstree, 8 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_bstree_count( bstree ) == 3 );

   i_bstree_dispose( &bstree );

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
   i_bstree_t *bstree = NULL;
   int32_t result = 0;

   bstree = i_bstree_make();

   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 3 );

   i_bstree_remove( bstree, 0 );

   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 0 );

   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );

   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );

   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i_bstree_count( bstree ) == 3 );

   i_bstree_dispose( &bstree );

   return;
}

/**
   test_remove_6d

            4
         2      6
       1   3  5   7
*/

void test_remove_6d( void )
{
   i_bstree_t *bstree = NULL;
   int32_t result = 0;

   bstree = i_bstree_make();

   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 3 );

   i_bstree_finish( bstree );
   i_bstree_remove( bstree, 0 );

   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 0 );

   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );

   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );

   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i_bstree_count( bstree ) == 3 );

   i_bstree_dispose( &bstree );

   return;
}

/**
   test_remove_7
*/

void test_remove_7( void )
{
   s_bstree_t *bstree = NULL;
   int32_t result = 0;

   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s3 = string_make_from_cstring( "3" );
   string_t *s4 = string_make_from_cstring( "4" );
   
   bstree = s_bstree_make();

   s_bstree_put( bstree, s4 );
   s_bstree_put( bstree, s1 );
   s_bstree_put( bstree, s2 );
   s_bstree_put( bstree, s3 );

   s_bstree_finish( bstree );
   s_bstree_remove( bstree, 0 );

   result = s_bstree_has( bstree, s1 );
   CU_ASSERT( result == 0 );

   result = s_bstree_has( bstree, s2 );
   CU_ASSERT( result == 1 );

   result = s_bstree_has( bstree, s3 );
   CU_ASSERT( result == 1 );

   result = s_bstree_has( bstree, s4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( s_bstree_count( bstree ) == 3 );

   string_deep_dispose( &s1 );
   
   s_bstree_deep_dispose( &bstree );

   return;
}

/**
   test_remove_7a
*/

void test_remove_7a( void )
{
   s_bstree_t *bstree = NULL;
   int32_t result = 0;

   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s3 = string_make_from_cstring( "3" );
   
   bstree = s_bstree_make();

   s_bstree_put( bstree, s2 );
   s_bstree_put( bstree, s1 );
   s_bstree_put( bstree, s3 );

   s_bstree_start( bstree );
   s_bstree_forth( bstree );
   s_bstree_remove( bstree, 1 );
 
   result = s_bstree_has( bstree, s1 );
   CU_ASSERT( result == 1 );
 
   result = s_bstree_has( bstree, s3 );
   CU_ASSERT( result == 1 );
 
   result = s_bstree_has( bstree, s2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( s_bstree_count( bstree ) == 2 );
   
   s_bstree_deep_dispose( &bstree );
   string_dispose( &s2 );

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
   add_test_to_suite( p_suite, test_remove_6d, "test_remove_6d" );

   // test_remove_7
   add_test_to_suite( p_suite, test_remove_7, "test_remove_7" );
   add_test_to_suite( p_suite, test_remove_7a, "test_remove_7a" );
   
   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

