/**
 @file Heap_test_wipe_out_and_dispose.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Heap_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)

 @section Description

 Unit tests for Heap_t

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_Heap.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_wipe_out_and_dispose_1
*/

void test_wipe_out_and_dispose_1( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 1 );

   i_heap_wipe_out_and_dispose( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_and_dispose_2
*/

void test_wipe_out_and_dispose_2( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );

   i_heap_wipe_out_and_dispose( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_and_dispose_2a
*/

void test_wipe_out_and_dispose_2a( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );

   i_heap_wipe_out_and_dispose( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_and_dispose_2b
*/

void test_wipe_out_and_dispose_2b( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );

   i_heap_wipe_out_and_dispose( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_and_dispose_3
*/

void test_wipe_out_and_dispose_3( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 3 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );

   i_heap_wipe_out_and_dispose( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_and_dispose_3a
*/

void test_wipe_out_and_dispose_3a( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 3 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );

   i_heap_wipe_out_and_dispose( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_and_dispose_3b
*/

void test_wipe_out_and_dispose_3b( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 3 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );

   i_heap_wipe_out_and_dispose( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_and_dispose_4
*/

void test_wipe_out_and_dispose_4( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 1 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 3 );

   i_heap_wipe_out_and_dispose( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_and_dispose_4a
*/

void test_wipe_out_and_dispose_4a( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 1 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 3 );

   i_heap_wipe_out_and_dispose( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_and_dispose_4b
*/

void test_wipe_out_and_dispose_4b( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 1 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 3 );

   i_heap_wipe_out_and_dispose( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_and_dispose_5

            4
         2      6
       1   3  5   7
*/

void test_wipe_out_and_dispose_5( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );
   i_heap_put( heap, 5 );
   i_heap_put( heap, 7 );

   i_heap_wipe_out_and_dispose( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_and_dispose_5a

            4
         2      6
       1   3  5   7
*/

void test_wipe_out_and_dispose_5a( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );
   i_heap_put( heap, 5 );
   i_heap_put( heap, 7 );

   i_heap_wipe_out_and_dispose( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_and_dispose_5b

            4
         2      6
       1   3  5   7
*/

void test_wipe_out_and_dispose_5b( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );
   i_heap_put( heap, 5 );
   i_heap_put( heap, 7 );

   i_heap_wipe_out_and_dispose( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_and_dispose_5c

            4
         2      6
       1   3  5   7
*/

void test_wipe_out_and_dispose_5c( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );
   i_heap_put( heap, 5 );
   i_heap_put( heap, 7 );

   i_heap_wipe_out_and_dispose( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_and_dispose_5d

            4
         2      6
       1   3  5   7
*/

void test_wipe_out_and_dispose_5d( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );
   i_heap_put( heap, 5 );
   i_heap_put( heap, 7 );

   i_heap_wipe_out_and_dispose( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_and_dispose_5e

            4
         2      6
       1   3  5   7
*/

void test_wipe_out_and_dispose_5e( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );
   i_heap_put( heap, 5 );
   i_heap_put( heap, 7 );

   i_heap_wipe_out_and_dispose( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_and_dispose_5f

            4
         2      6
       1   3  5   7
*/

void test_wipe_out_and_dispose_5f( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 4 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 6 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );
   i_heap_put( heap, 5 );
   i_heap_put( heap, 7 );

   i_heap_wipe_out_and_dispose( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_and_dispose_6
*/

void test_wipe_out_and_dispose_6( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 1 );

   i_heap_wipe_out_and_dispose( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

int
add_test_wipe_out_and_dispose( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_wipe_out_and_dispose", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_wipe_out_and_dispose_1
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_1, "test_wipe_out_and_dispose_1" );

   // test_wipe_out_and_dispose_2
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_2, "test_wipe_out_and_dispose_2" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_2a, "test_wipe_out_and_dispose_2a" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_2b, "test_wipe_out_and_dispose_2b" );

   // test_wipe_out_and_dispose_3
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_3, "test_wipe_out_and_dispose_3" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_3a, "test_wipe_out_and_dispose_3a" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_3b, "test_wipe_out_and_dispose_3b" );

   // test_wipe_out_and_dispose_4
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_4, "test_wipe_out_and_dispose_4" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_4a, "test_wipe_out_and_dispose_4a" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_4b, "test_wipe_out_and_dispose_4b" );

   // test_wipe_out_and_dispose_5
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_5, "test_wipe_out_and_dispose_5" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_5a, "test_wipe_out_and_dispose_5a" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_5b, "test_wipe_out_and_dispose_5b" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_5c, "test_wipe_out_and_dispose_5c" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_5d, "test_wipe_out_and_dispose_5d" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_5e, "test_wipe_out_and_dispose_5e" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_5f, "test_wipe_out_and_dispose_5f" );

   // test_wipe_out_and_dispose_6
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_6, "test_wipe_out_and_dispose_6" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */
