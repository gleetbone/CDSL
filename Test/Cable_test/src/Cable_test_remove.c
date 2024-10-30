/**
 @file Cable_test_remove.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BSTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for BSTree_make.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "CUnit/Basic.h"

#include "Cable.h"

cable_t *
cable_make_capacity( int32_t capacity );

cable_t *
cable_make_capacity_from_cstring( char_t *str, int32_t capacity );

int32_t
cable_capacity( cable_t *cable );

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_remove_1
*/

void test_remove_1( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_remove( cable, 0 );

   CU_ASSERT( cable_is_equal_cstring( cable, "bcd" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_remove_2
*/

void test_remove_2( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_remove( cable, 1 );

   CU_ASSERT( cable_is_equal_cstring( cable, "acd" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_remove_3
*/

void test_remove_3( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_remove( cable, 2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abd" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_remove_4
*/

void test_remove_4( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_remove( cable, 3 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abc" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_remove_5
*/

void test_remove_5( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_remove( cable, 4 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdfghij" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_remove_6
*/

void test_remove_6( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_remove( cable, 5 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdeghij" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_remove_7
*/

void test_remove_7( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_remove( cable, 6 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefhij" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_remove_8
*/

void test_remove_8( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_remove( cable, 7 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefgij" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_remove_9
*/

#define MAX_CSTRING_COUNT 8
#define MAX_COUNT 100

static
char_t *
random_cstring( void )
{
   char_t *cp = NULL;
   int32_t n = 0;
   int32_t i = 0;

   while( n == 0 )
   {
	   n = rand() % MAX_CSTRING_COUNT;
   }

   cp = ( char_t * ) calloc( n + 1, sizeof( char_t ) );

   for( i=0; i<n; i++ )
   {
      cp[i] = 'a' + i;
   }

   return cp;
}

void test_remove_9( void )
{
   cable_t *cable = NULL;
   int32_t count = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   char_t *cp = NULL;
   int32_t start_index = 0;
   int32_t end_index = 0;

   cable = cable_make_capacity( 4 );

   CU_ASSERT( cable != NULL );

   srand( 100 );

   for( k=0; k<10000; k++ )
   {
      count = 0;

      while( count == 0 )
      {
         count = rand() % MAX_COUNT;
      }

      i = 0;
      while ( i < count )
      {
         cp = random_cstring();
         start_index = rand() % ( cable_count( cable ) + 1 );
         cable_insert_cstring( cable, cp, start_index );
         free( cp );
         i = i + 1;
      }

      j = 0;
      while ( ( j < count/2 ) && ( cable_count( cable ) > 0 ) )
      {
         start_index = rand() % ( cable_count( cable ) );

         if ( start_index < ( cable_count( cable ) - 1 ) )
         {
            end_index = start_index + ( rand() % ( cable_count( cable ) - start_index ) );
         }
         else
         {
            end_index = start_index;
         }

         cable_remove_substring( cable, start_index, end_index );
         j = j + 1;
      }

      cable_wipe_out( cable );
   }

   cable_dispose( &cable );

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

   // test_remove_3
   add_test_to_suite( p_suite, test_remove_3, "test_remove_3" );

   // test_remove_4
   add_test_to_suite( p_suite, test_remove_4, "test_remove_4" );

   // test_remove_5
   add_test_to_suite( p_suite, test_remove_5, "test_remove_5" );

   // test_remove_6
   add_test_to_suite( p_suite, test_remove_6, "test_remove_6" );

   // test_remove_7
   add_test_to_suite( p_suite, test_remove_7, "test_remove_7" );

   // test_remove_8
   add_test_to_suite( p_suite, test_remove_8, "test_remove_8" );

   // test_remove_9
   add_test_to_suite( p_suite, test_remove_9, "test_remove_9" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

