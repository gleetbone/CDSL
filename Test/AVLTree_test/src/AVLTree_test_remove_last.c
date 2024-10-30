/**
 @file AVLTree_test_remove_last.c
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
   test_remove_last_1
*/

void test_remove_last_1( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 1 );
   
   i_avltree_remove_last( avltree );
   
   CU_ASSERT( i_avltree_count( avltree ) == 0 );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 0 );
 
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_last_2
*/

void test_remove_last_2( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_remove_last( avltree );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 0 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 2 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_last_2a
*/

void test_remove_last_2a( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_remove_last( avltree );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 0 );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 2 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_last_2b
*/

void test_remove_last_2b( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_remove_last( avltree );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 2 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_last_3
*/

void test_remove_last_3( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   
   i_avltree_remove_last( avltree );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 0 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 2 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_last_3a
*/

void test_remove_last_3a( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   
   i_avltree_remove_last( avltree );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 0 );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 2 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_last_3b
*/

void test_remove_last_3b( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   
   i_avltree_remove_last( avltree );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 0 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 2 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_last_4
*/

void test_remove_last_4( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_remove_last( avltree );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 0 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
  
   CU_ASSERT( i_avltree_count( avltree ) == 2 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_last_4a
*/

void test_remove_last_4a( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_remove_last( avltree );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 0 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
  
   CU_ASSERT( i_avltree_count( avltree ) == 2 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_last_4b
*/

void test_remove_last_4b( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_remove_last( avltree );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 0 );
  
   CU_ASSERT( i_avltree_count( avltree ) == 2 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_last_5
   
            4
         2      6
       1   3  5   7
*/

void test_remove_last_5( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_remove_last( avltree );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 0 );
 
   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 6 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_last_5a
   
            4
         2      6
       1   3  5   7
*/

void test_remove_last_5a( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_remove_last( avltree );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 0 );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 6 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_last_5b
   
            4
         2      6
       1   3  5   7
*/

void test_remove_last_5b( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_remove_last( avltree );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 0 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 6 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_last_5c
   
            4
         2      6
       1   3  5   7
*/

void test_remove_last_5c( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_remove_last( avltree );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 0 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 6 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_last_5d
   
            4
         2      6
       1   3  5   7
*/

void test_remove_last_5d( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_remove_last( avltree );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 0 );
 
   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 6 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_last_5e
   
            4
         2      6
       1   3  5   7
*/

void test_remove_last_5e( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_remove_last( avltree );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 0 );
 
   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 6 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_last_5f
   
            4
         2      6
       1   3  5   7
*/

void test_remove_last_5f( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_remove_last( avltree );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 6 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_last_6

            4
         2      6
       1   3  5   7
*/

void test_remove_last_6( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );

   i_avltree_remove_last( avltree );

   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 0 );

   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i_avltree_count( avltree ) == 6 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_last_6a

            4
         2      6
       1   3  5   7
*/

void test_remove_last_6a( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );

   i_avltree_remove_last( avltree );

   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_avltree_count( avltree ) == 1 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_last_6b

            4
         2      6
       1   3  5   7
*/

void test_remove_last_6b( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 8 );
   i_avltree_put( avltree, 7 );
   i_avltree_put( avltree, 6 );

   i_avltree_remove_last( avltree );

   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 8 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_avltree_count( avltree ) == 3 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_last_6c

            4
         2      6
       1   3  5   7
*/

void test_remove_last_6c( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 3 );

   i_avltree_remove_last( avltree );

   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_avltree_count( avltree ) == 3 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_last_7
*/

void test_remove_last_7( void )
{
   s_avltree_t *avltree = NULL;
   int32_t result = 0;

   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s3 = string_make_from_cstring( "3" );
   string_t *s4 = string_make_from_cstring( "4" );
   
   avltree = s_avltree_make();

   s_avltree_put( avltree, s4 );
   s_avltree_put( avltree, s1 );
   s_avltree_put( avltree, s2 );
   s_avltree_put( avltree, s3 );

   s_avltree_remove_last( avltree );

   result = s_avltree_has( avltree, s1 );
   CU_ASSERT( result == 1 );

   result = s_avltree_has( avltree, s2 );
   CU_ASSERT( result == 1 );

   result = s_avltree_has( avltree, s3 );
   CU_ASSERT( result == 1 );

   result = s_avltree_has( avltree, s4 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( s_avltree_count( avltree ) == 3 );

   string_deep_dispose( &s4 );
   s_avltree_deep_dispose( &avltree );

   return;
}

int
add_test_remove_last( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_remove_last", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_remove_last_1
   add_test_to_suite( p_suite, test_remove_last_1, "test_remove_last_1" );

   // test_remove_last_2
   add_test_to_suite( p_suite, test_remove_last_2, "test_remove_last_2" );
   add_test_to_suite( p_suite, test_remove_last_2a, "test_remove_last_2a" );
   add_test_to_suite( p_suite, test_remove_last_2b, "test_remove_last_2b" );

   // test_remove_last_3
   add_test_to_suite( p_suite, test_remove_last_3, "test_remove_last_3" );
   add_test_to_suite( p_suite, test_remove_last_3a, "test_remove_last_3a" );
   add_test_to_suite( p_suite, test_remove_last_3b, "test_remove_last_3b" );

   // test_remove_last_4
   add_test_to_suite( p_suite, test_remove_last_4, "test_remove_last_4" );
   add_test_to_suite( p_suite, test_remove_last_4a, "test_remove_last_4a" );
   add_test_to_suite( p_suite, test_remove_last_4b, "test_remove_last_4b" );

   // test_remove_last_5
   add_test_to_suite( p_suite, test_remove_last_5, "test_remove_last_5" );
   add_test_to_suite( p_suite, test_remove_last_5a, "test_remove_last_5a" );
   add_test_to_suite( p_suite, test_remove_last_5b, "test_remove_last_5b" );
   add_test_to_suite( p_suite, test_remove_last_5c, "test_remove_last_5c" );
   add_test_to_suite( p_suite, test_remove_last_5d, "test_remove_last_5d" );
   add_test_to_suite( p_suite, test_remove_last_5e, "test_remove_last_5e" );
   add_test_to_suite( p_suite, test_remove_last_5f, "test_remove_last_5f" );

   // test_remove_last_6
   add_test_to_suite( p_suite, test_remove_last_6, "test_remove_last_6" );
   add_test_to_suite( p_suite, test_remove_last_6a, "test_remove_last_6a" );
   add_test_to_suite( p_suite, test_remove_last_6b, "test_remove_last_6b" );
   add_test_to_suite( p_suite, test_remove_last_6c, "test_remove_last_6c" );

   // test_remove_last_7
   add_test_to_suite( p_suite, test_remove_last_7, "test_remove_last_7" );
   
   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

