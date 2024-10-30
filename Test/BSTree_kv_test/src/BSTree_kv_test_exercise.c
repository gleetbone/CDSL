/**
 @file BSTree_kv_test_exercise.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BSTree_kv_forth"
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

extern int32_t print_flag;

#define MAX_COUNT 100
#define MAX_VALUE 1000

/**
   test_exercise_1
*/

void test_exercise_1( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t count = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t n = 0;
   int32_t values[MAX_COUNT] = {0};

   bstree = ii_bstree_kv_make();

   srand( 101 );

   for( k=0; k<10000; k++ )
   {
      count = 0;

      while( count == 0 )
      {
         count = rand() % MAX_COUNT;
      }

      i = 0;
      while( i<count )
      {
         n = rand() % MAX_VALUE;
         if ( ii_bstree_kv_has( bstree, n ) == 0 )
         {
            ii_bstree_kv_put( bstree, n, n );
            values[i] = n;
            i = i + 1;
         }
      }

      ii_bstree_kv_balance( bstree );
      
      j = 0;
      while ( j< count/2 )
      {
         i = rand() % count;
         if ( ii_bstree_kv_has( bstree, values[i] ) == 1 )
         {
            ii_bstree_kv_remove( bstree, values[i] );
            j = j + 1;
         }
      }

      ii_bstree_kv_balance( bstree );
      
      ii_bstree_kv_wipe_out( bstree );
   }

   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_exercise_2
*/

void test_exercise_2( void )
{
   ss_bstree_kv_t *bstree = NULL;
   int32_t count = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t n = 0;
   string_t *key = NULL;
   string_t * keys[MAX_COUNT] = {NULL};
   string_t *value = NULL;
   string_t * values[MAX_COUNT] = {NULL};
   char str[8] = {0};

   bstree = ss_bstree_kv_make();

   srand( 101 );

   for( k=0; k<10000; k++ )
   {
      count = 0;

      while( count == 0 )
      {
         count = rand() % MAX_COUNT;
      }

      i = 0;
      while( i<count )
      {
         n = rand() % MAX_VALUE;
         str[0] = 0;
         sprintf( str, "%03d", n );
         
         key = string_make_from_cstring( str );
         value = string_make_from_cstring( str );
         
         if ( ss_bstree_kv_has( bstree, key ) == 0 )
         {
            ss_bstree_kv_put( bstree,value, key );
            keys[i] = key;
            values[i] = value;
            i = i + 1;
         }
         else
         {
            string_deep_dispose( &key );
            string_deep_dispose( &value );
         }
      }

      ss_bstree_kv_balance( bstree );
      
      j = 0;
      while ( j< count/2 )
      {
         i = rand() % count;
         if ( values[i] != NULL )
         {
            if ( ss_bstree_kv_has( bstree, keys[i] ) == 1 )
            {
               ss_bstree_kv_remove( bstree, keys[i] );
               string_dispose( &keys[i] );
               string_dispose( &values[i] );
               keys[i] = NULL;
               values[i] = NULL;
               j = j + 1;
            }
         }
      }

      ss_bstree_kv_balance( bstree );
      
      ss_bstree_kv_wipe_out( bstree );
      
      j = 0;
      while ( j < count )
      {
         if ( values[j] != NULL )
         {
            string_dispose( &keys[j] );
            keys[j] = NULL;
            string_dispose( &values[j] );
            values[j] = NULL;
         }
         j = j + 1;
      }
      
   }

   ss_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_exercise_3
*/

void test_exercise_3( void )
{
   ss_bstree_kv_t *bstree = NULL;
   int32_t count = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t n = 0;
   string_t *value = NULL;
   string_t * values[MAX_COUNT] = {NULL};
   string_t *key = NULL;
   string_t * keys[MAX_COUNT] = {NULL};
   char str[8] = {0};

   bstree = ss_bstree_kv_make();

   srand( 101 );

   for( k=0; k<10000; k++ )
   {
      count = 0;

      while( count == 0 )
      {
         count = rand() % MAX_COUNT;
      }

      i = 0;
      while( i<count )
      {
         n = rand() % MAX_VALUE;
         str[0] = 0;
         sprintf( str, "%03d", n );
         
         key = string_make_from_cstring( str );
         value = string_make_from_cstring( str );
         
         if ( ss_bstree_kv_has( bstree, key ) == 0 )
         {
            ss_bstree_kv_put( bstree, value, key );
            keys[i] = key;
            values[i] = value;
            i = i + 1;
         }
         else
         {
            string_deep_dispose( &key );
            string_deep_dispose( &value );
         }
      }

      ss_bstree_kv_balance( bstree );
      
      j = 0;
      while ( j< count/2 )
      {
         i = rand() % count;
         if ( values[i] != NULL )
         {
            if ( ss_bstree_kv_has( bstree, keys[i] ) == 1 )
            {
               ss_bstree_kv_remove_and_dispose( bstree, keys[i] );
               keys[i] = NULL;
               values[i] = NULL;
               j = j + 1;
            }
         }
      }

      ss_bstree_kv_balance( bstree );
      
      ss_bstree_kv_wipe_out_and_dispose( bstree );
            
   }

   ss_bstree_kv_dispose( &bstree );

   return;
}


int
add_test_exercise( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_exercise", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_exercise_1
   add_test_to_suite( p_suite, test_exercise_1, "test_exercise_1" );

   // test_exercise_2
   add_test_to_suite( p_suite, test_exercise_2, "test_exercise_2" );

   // test_exercise_3
   add_test_to_suite( p_suite, test_exercise_3, "test_exercise_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

