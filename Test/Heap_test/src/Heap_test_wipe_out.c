/**
 @file Heap_test_wipe_out.c
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
   test_wipe_out_1
*/

void test_wipe_out_1( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 1 );

   i_heap_wipe_out( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_2
*/

void test_wipe_out_2( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );

   i_heap_wipe_out( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_2a
*/

void test_wipe_out_2a( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );

   i_heap_wipe_out( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_2b
*/

void test_wipe_out_2b( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );
   i_heap_put( heap, 3 );

   i_heap_wipe_out( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_3
*/

void test_wipe_out_3( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 3 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );

   i_heap_wipe_out( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_3a
*/

void test_wipe_out_3a( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 3 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );

   i_heap_wipe_out( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_3b
*/

void test_wipe_out_3b( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 3 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 1 );

   i_heap_wipe_out( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_4
*/

void test_wipe_out_4( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 1 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 3 );

   i_heap_wipe_out( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_4a
*/

void test_wipe_out_4a( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 1 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 3 );

   i_heap_wipe_out( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_4b
*/

void test_wipe_out_4b( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 1 );
   i_heap_put( heap, 2 );
   i_heap_put( heap, 3 );

   i_heap_wipe_out( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_5
*/

void test_wipe_out_5( void )
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

   i_heap_wipe_out( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_5a
*/

void test_wipe_out_5a( void )
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

   i_heap_wipe_out( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_5b
*/

void test_wipe_out_5b( void )
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

   i_heap_wipe_out( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_5c
*/

void test_wipe_out_5c( void )
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

   i_heap_wipe_out( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_5d
*/

void test_wipe_out_5d( void )
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

   i_heap_wipe_out( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_5e
*/

void test_wipe_out_5e( void )
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

   i_heap_wipe_out( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_5f
*/

void test_wipe_out_5f( void )
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

   i_heap_wipe_out( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

/**
   test_wipe_out_6
*/

void test_wipe_out_6( void )
{
   i_heap_t *heap = NULL;

   heap = i_heap_make();

   i_heap_put( heap, 1 );

   i_heap_wipe_out( heap );

   CU_ASSERT( i_heap_count( heap ) == 0 );

   i_heap_dispose( &heap );

   return;
}

int
add_test_wipe_out( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_wipe_out", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_wipe_out_1
   add_test_to_suite( p_suite, test_wipe_out_1, "test_wipe_out_1" );

   // test_wipe_out_2
   add_test_to_suite( p_suite, test_wipe_out_2, "test_wipe_out_2" );
   add_test_to_suite( p_suite, test_wipe_out_2a, "test_wipe_out_2a" );
   add_test_to_suite( p_suite, test_wipe_out_2b, "test_wipe_out_2b" );

   // test_wipe_out_3
   add_test_to_suite( p_suite, test_wipe_out_3, "test_wipe_out_3" );
   add_test_to_suite( p_suite, test_wipe_out_3a, "test_wipe_out_3a" );
   add_test_to_suite( p_suite, test_wipe_out_3b, "test_wipe_out_3b" );

   // test_wipe_out_4
   add_test_to_suite( p_suite, test_wipe_out_4, "test_wipe_out_4" );
   add_test_to_suite( p_suite, test_wipe_out_4a, "test_wipe_out_4a" );
   add_test_to_suite( p_suite, test_wipe_out_4b, "test_wipe_out_4b" );

   // test_wipe_out_5
   add_test_to_suite( p_suite, test_wipe_out_5, "test_wipe_out_5" );
   add_test_to_suite( p_suite, test_wipe_out_5a, "test_wipe_out_5a" );
   add_test_to_suite( p_suite, test_wipe_out_5b, "test_wipe_out_5b" );
   add_test_to_suite( p_suite, test_wipe_out_5c, "test_wipe_out_5c" );
   add_test_to_suite( p_suite, test_wipe_out_5d, "test_wipe_out_5d" );
   add_test_to_suite( p_suite, test_wipe_out_5e, "test_wipe_out_5e" );
   add_test_to_suite( p_suite, test_wipe_out_5f, "test_wipe_out_5f" );

   // test_wipe_out_6
   add_test_to_suite( p_suite, test_wipe_out_6, "test_wipe_out_6" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

