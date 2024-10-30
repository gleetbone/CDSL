/**
 @file Heap_test_wipe_out.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Heap_kv_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)

 @section Description

 Unit tests for Heap_kv_t.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_Heap_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_wipe_out_1
*/

void test_wipe_out_1( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 10, 1 );

   ii_heap_kv_wipe_out( heap );

   CU_ASSERT( ii_heap_kv_count( heap ) == 0 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_wipe_out_2
*/

void test_wipe_out_2( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 30, 3 );

   ii_heap_kv_wipe_out( heap );

   CU_ASSERT( ii_heap_kv_count( heap ) == 0 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_wipe_out_2a
*/

void test_wipe_out_2a( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 30, 3 );

   ii_heap_kv_wipe_out( heap );

   CU_ASSERT( ii_heap_kv_count( heap ) == 0 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_wipe_out_2b
*/

void test_wipe_out_2b( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 30, 3 );

   ii_heap_kv_wipe_out( heap );

   CU_ASSERT( ii_heap_kv_count( heap ) == 0 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_wipe_out_3
*/

void test_wipe_out_3( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 30, 3 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 10, 1 );

   ii_heap_kv_wipe_out( heap );

   CU_ASSERT( ii_heap_kv_count( heap ) == 0 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_wipe_out_3a
*/

void test_wipe_out_3a( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 30, 3 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 10, 1 );

   ii_heap_kv_wipe_out( heap );

   CU_ASSERT( ii_heap_kv_count( heap ) == 0 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_wipe_out_3b
*/

void test_wipe_out_3b( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 30, 3 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 10, 1 );

   ii_heap_kv_wipe_out( heap );

   CU_ASSERT( ii_heap_kv_count( heap ) == 0 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_wipe_out_4
*/

void test_wipe_out_4( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 30, 3 );

   ii_heap_kv_wipe_out( heap );

   CU_ASSERT( ii_heap_kv_count( heap ) == 0 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_wipe_out_4a
*/

void test_wipe_out_4a( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 30, 3 );

   ii_heap_kv_wipe_out( heap );

   CU_ASSERT( ii_heap_kv_count( heap ) == 0 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_wipe_out_4b
*/

void test_wipe_out_4b( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 30, 3 );

   ii_heap_kv_wipe_out( heap );

   CU_ASSERT( ii_heap_kv_count( heap ) == 0 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_wipe_out_5

            4
         2      6
       1   3  5   7
*/

void test_wipe_out_5( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 40, 4 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 60, 6 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 30, 3 );
   ii_heap_kv_put( heap, 50, 5 );
   ii_heap_kv_put( heap, 70, 7 );

   ii_heap_kv_wipe_out( heap );

   CU_ASSERT( ii_heap_kv_count( heap ) == 0 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_wipe_out_5a

            4
         2      6
       1   3  5   7
*/

void test_wipe_out_5a( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 40, 4 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 60, 6 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 30, 3 );
   ii_heap_kv_put( heap, 50, 5 );
   ii_heap_kv_put( heap, 70, 7 );

   ii_heap_kv_wipe_out( heap );

   CU_ASSERT( ii_heap_kv_count( heap ) == 0 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_wipe_out_5b

            4
         2      6
       1   3  5   7
*/

void test_wipe_out_5b( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 40, 4 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 60, 6 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 30, 3 );
   ii_heap_kv_put( heap, 50, 5 );
   ii_heap_kv_put( heap, 70, 7 );

   ii_heap_kv_wipe_out( heap );

   CU_ASSERT( ii_heap_kv_count( heap ) == 0 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_wipe_out_5c

            4
         2      6
       1   3  5   7
*/

void test_wipe_out_5c( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 40, 4 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 60, 6 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 30, 3 );
   ii_heap_kv_put( heap, 50, 5 );
   ii_heap_kv_put( heap, 70, 7 );

   ii_heap_kv_wipe_out( heap );

   CU_ASSERT( ii_heap_kv_count( heap ) == 0 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_wipe_out_5d

            4
         2      6
       1   3  5   7
*/

void test_wipe_out_5d( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 40, 4 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 60, 6 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 30, 3 );
   ii_heap_kv_put( heap, 50, 5 );
   ii_heap_kv_put( heap, 70, 7 );

   ii_heap_kv_wipe_out( heap );

   CU_ASSERT( ii_heap_kv_count( heap ) == 0 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_wipe_out_5e

            4
         2      6
       1   3  5   7
*/

void test_wipe_out_5e( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 40, 4 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 60, 6 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 30, 3 );
   ii_heap_kv_put( heap, 50, 5 );
   ii_heap_kv_put( heap, 70, 7 );

   ii_heap_kv_wipe_out( heap );

   CU_ASSERT( ii_heap_kv_count( heap ) == 0 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_wipe_out_5f

            4
         2      6
       1   3  5   7
*/

void test_wipe_out_5f( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 40, 4 );
   ii_heap_kv_put( heap, 20, 2 );
   ii_heap_kv_put( heap, 60, 6 );
   ii_heap_kv_put( heap, 10, 1 );
   ii_heap_kv_put( heap, 30, 3 );
   ii_heap_kv_put( heap, 50, 5 );
   ii_heap_kv_put( heap, 70, 7 );

   ii_heap_kv_wipe_out( heap );

   CU_ASSERT( ii_heap_kv_count( heap ) == 0 );

   ii_heap_kv_dispose( &heap );

   return;
}

/**
   test_wipe_out_6
*/

void test_wipe_out_6( void )
{
   ii_heap_kv_t *heap = NULL;

   heap = ii_heap_kv_make();

   ii_heap_kv_put( heap, 10, 1 );

   ii_heap_kv_wipe_out( heap );

   CU_ASSERT( ii_heap_kv_count( heap ) == 0 );

   ii_heap_kv_dispose( &heap );

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

