/**
 @file BSorter_test_sort.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BSorter_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for BSorter_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_BSorter.h"
#include "i_Sorter.h"
#include "i32_Sequence.h"
#include "p_Basic.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_sort_1
*/

void test_sort_1( void )
{
   i_bsorter_t *sorter = NULL;
   protocol_base_t *pb_sorter = NULL;
   i32_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;
   int32_t result = 0;

   sorter = i_bsorter_make();
   pb_sorter = ( protocol_base_t * ) sorter;
   
   seq = i32_sequence_make_n( 1 );
   pb_seq = ( protocol_base_t * ) seq;

   i32_sequence_ensure_count( seq, 1 );

   i32_sequence_put( seq, 1, 0 );
   
   i_bsorter_sort_predefined_comparison_function( sorter, pb_seq );

   CU_ASSERT( i32_sequence_item( seq, 0 ) == 1 );

   result = i_bsorter_is_sorted_predefined_comparison_function( sorter, pb_seq );
   CU_ASSERT( result == 1 );

   i32_sequence_dispose( &seq );
   p_basic_dispose( &pb_sorter );
 
   return;
}

/**
   test_sort_2
*/

void test_sort_2( void )
{
   i_bsorter_t *sorter = NULL;
   protocol_base_t *pb_sorter = NULL;
   i32_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;
   int32_t result = 0;

   sorter = i_bsorter_make();
   pb_sorter = ( protocol_base_t * ) sorter;
   seq = i32_sequence_make_n( 2 );
   pb_seq = ( protocol_base_t * ) seq;

   i32_sequence_ensure_count( seq, 2 );

   i32_sequence_put( seq, 1, 0 );
   i32_sequence_put( seq, 2, 1 );

   i_sorter_sort( pb_sorter, pb_seq );

   result = i_sorter_is_sorted( pb_sorter, pb_seq );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i32_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i32_sequence_item( seq, 1 ) == 2 );

   i32_sequence_dispose( &seq );
   i_bsorter_dispose( &sorter );

   return;
}

/**
   test_sort_3
*/

void test_sort_3( void )
{
   i_bsorter_t *sorter = NULL;
   protocol_base_t *pb_sorter = NULL;
   i32_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;
   int32_t result = 0;

   sorter = i_bsorter_make();
   pb_sorter = ( protocol_base_t * ) sorter;
   seq = i32_sequence_make_n( 2 );
   pb_seq = ( protocol_base_t * ) seq;

   i32_sequence_ensure_count( seq, 2 );

   i32_sequence_put( seq, 2, 0 );
   i32_sequence_put( seq, 1, 1 );

   i_sorter_sort( pb_sorter, pb_seq );

   result = i_sorter_is_sorted( pb_sorter, pb_seq );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i32_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i32_sequence_item( seq, 1 ) == 2 );

   i32_sequence_dispose( &seq );
   i_bsorter_dispose( &sorter );

   return;
}

/**
   test_sort_4a
*/

void test_sort_4a( void )
{
   i_bsorter_t *sorter = NULL;
   protocol_base_t *pb_sorter = NULL;
   i32_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;
   int32_t result = 0;

   sorter = i_bsorter_make();
   pb_sorter = ( protocol_base_t * ) sorter;
   seq = i32_sequence_make_n( 2 );
   pb_seq = ( protocol_base_t * ) seq;

   i32_sequence_ensure_count( seq, 3 );

   i32_sequence_put( seq, 1, 0 );
   i32_sequence_put( seq, 2, 1 );
   i32_sequence_put( seq, 3, 2 );

   i_sorter_sort( pb_sorter, pb_seq );

   result = i_sorter_is_sorted( pb_sorter, pb_seq );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i32_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i32_sequence_item( seq, 1 ) == 2 );
   CU_ASSERT( i32_sequence_item( seq, 2 ) == 3 );

   i32_sequence_dispose( &seq );
   i_bsorter_dispose( &sorter );

   return;
}

/**
   test_sort_4b
*/

void test_sort_4b( void )
{
   i_bsorter_t *sorter = NULL;
   protocol_base_t *pb_sorter = NULL;
   i32_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;
   int32_t result = 0;

   sorter = i_bsorter_make();
   pb_sorter = ( protocol_base_t * ) sorter;
   seq = i32_sequence_make_n( 2 );
   pb_seq = ( protocol_base_t * ) seq;

   i32_sequence_ensure_count( seq, 3 );

   result = i_sorter_is_sorted( pb_sorter, pb_seq );
   CU_ASSERT( result == 1 );

   i32_sequence_put( seq, 3, 0 );
   i32_sequence_put( seq, 1, 1 );
   i32_sequence_put( seq, 2, 2 );

   result = i_sorter_is_sorted( pb_sorter, pb_seq );
   CU_ASSERT( result == 0 );

   i_sorter_sort( pb_sorter, pb_seq );

   CU_ASSERT( i32_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i32_sequence_item( seq, 1 ) == 2 );
   CU_ASSERT( i32_sequence_item( seq, 2 ) == 3 );

   i32_sequence_dispose( &seq );
   i_bsorter_dispose( &sorter );

   return;
}

/**
   test_sort_4c
*/

void test_sort_4c( void )
{
   i_bsorter_t *sorter = NULL;
   protocol_base_t *pb_sorter = NULL;
   i32_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;
   int32_t result = 0;

   sorter = i_bsorter_make();
   pb_sorter = ( protocol_base_t * ) sorter;
   seq = i32_sequence_make_n( 2 );
   pb_seq = ( protocol_base_t * ) seq;

   i32_sequence_ensure_count( seq, 3 );

   i32_sequence_put( seq, 2, 0 );
   i32_sequence_put( seq, 3, 1 );
   i32_sequence_put( seq, 1, 2 );

   i_sorter_sort( pb_sorter, pb_seq );

   result = i_sorter_is_sorted( pb_sorter, pb_seq );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i32_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i32_sequence_item( seq, 1 ) == 2 );
   CU_ASSERT( i32_sequence_item( seq, 2 ) == 3 );

   i32_sequence_dispose( &seq );
   i_bsorter_dispose( &sorter );

   return;
}

/**
   test_sort_4d
*/

void test_sort_4d( void )
{
   i_bsorter_t *sorter = NULL;
   protocol_base_t *pb_sorter = NULL;
   i32_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;
   int32_t result = 0;

   sorter = i_bsorter_make();
   pb_sorter = ( protocol_base_t * ) sorter;
   seq = i32_sequence_make_n( 2 );
   pb_seq = ( protocol_base_t * ) seq;

   i32_sequence_ensure_count( seq, 3 );

   i32_sequence_put( seq, 3, 0 );
   i32_sequence_put( seq, 2, 1 );
   i32_sequence_put( seq, 1, 2 );

   i_sorter_sort( pb_sorter, pb_seq );

   result = i_sorter_is_sorted( pb_sorter, pb_seq );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i32_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i32_sequence_item( seq, 1 ) == 2 );
   CU_ASSERT( i32_sequence_item( seq, 2 ) == 3 );

   i32_sequence_dispose( &seq );
   i_bsorter_dispose( &sorter );

   return;
}

/**
   test_sort_4e
*/

void test_sort_4e( void )
{
   i_bsorter_t *sorter = NULL;
   protocol_base_t *pb_sorter = NULL;
   i32_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;
   int32_t result = 0;

   sorter = i_bsorter_make();
   pb_sorter = ( protocol_base_t * ) sorter;
   seq = i32_sequence_make_n( 2 );
   pb_seq = ( protocol_base_t * ) seq;

   i32_sequence_ensure_count( seq, 3 );

   i32_sequence_put( seq, 2, 0 );
   i32_sequence_put( seq, 1, 1 );
   i32_sequence_put( seq, 3, 2 );

   i_sorter_sort( pb_sorter, pb_seq );

   result = i_sorter_is_sorted( pb_sorter, pb_seq );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i32_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i32_sequence_item( seq, 1 ) == 2 );
   CU_ASSERT( i32_sequence_item( seq, 2 ) == 3 );

   i32_sequence_dispose( &seq );
   i_bsorter_dispose( &sorter );

   return;
}

/**
   test_sort_4f
*/

void test_sort_4f( void )
{
   i_bsorter_t *sorter = NULL;
   protocol_base_t *pb_sorter = NULL;
   i32_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;
   int32_t result = 0;

   sorter = i_bsorter_make();
   pb_sorter = ( protocol_base_t * ) sorter;
   seq = i32_sequence_make_n( 2 );
   pb_seq = ( protocol_base_t * ) seq;

   i32_sequence_ensure_count( seq, 3 );

   i32_sequence_put( seq, 1, 0 );
   i32_sequence_put( seq, 3, 1 );
   i32_sequence_put( seq, 2, 2 );

   i_sorter_sort( pb_sorter, pb_seq );

   result = i_sorter_is_sorted( pb_sorter, pb_seq );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i32_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i32_sequence_item( seq, 1 ) == 2 );
   CU_ASSERT( i32_sequence_item( seq, 2 ) == 3 );

   i32_sequence_dispose( &seq );
   i_bsorter_dispose( &sorter );

   return;
}

/**
   test_sort_5
*/

void test_sort_5( void )
{
   i_bsorter_t *sorter = NULL;
   protocol_base_t *pb_sorter = NULL;
   i32_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;
   int32_t result = 0;

   sorter = i_bsorter_make();
   pb_sorter = ( protocol_base_t * ) sorter;
   seq = i32_sequence_make_n( 2 );
   pb_seq = ( protocol_base_t * ) seq;

   i32_sequence_ensure_count( seq, 6 );

   i32_sequence_put( seq, 6, 0 );
   i32_sequence_put( seq, 5, 1 );
   i32_sequence_put( seq, 4, 2 );
   i32_sequence_put( seq, 3, 3 );
   i32_sequence_put( seq, 2, 4 );
   i32_sequence_put( seq, 1, 5 );

   i_sorter_sort( pb_sorter, pb_seq );

   result = i_sorter_is_sorted( pb_sorter, pb_seq );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i32_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i32_sequence_item( seq, 1 ) == 2 );
   CU_ASSERT( i32_sequence_item( seq, 2 ) == 3 );
   CU_ASSERT( i32_sequence_item( seq, 3 ) == 4 );
   CU_ASSERT( i32_sequence_item( seq, 4 ) == 5 );
   CU_ASSERT( i32_sequence_item( seq, 5 ) == 6 );

   i32_sequence_dispose( &seq );
   i_bsorter_dispose( &sorter );

   return;
}

/**
   test_sort_6
*/

void test_sort_6( void )
{
   i_bsorter_t *sorter = NULL;
   protocol_base_t *pb_sorter = NULL;
   i32_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;
   int32_t result = 0;

   sorter = i_bsorter_make();
   pb_sorter = ( protocol_base_t * ) sorter;
   seq = i32_sequence_make_n( 2 );
   pb_seq = ( protocol_base_t * ) seq;

   i32_sequence_ensure_count( seq, 6 );

   i32_sequence_put( seq, 6, 0 );
   i32_sequence_put( seq, 5, 1 );
   i32_sequence_put( seq, 3, 2 );
   i32_sequence_put( seq, 3, 3 );
   i32_sequence_put( seq, 2, 4 );
   i32_sequence_put( seq, 1, 5 );

   i_sorter_sort( pb_sorter, pb_seq );

   result = i_sorter_is_sorted( pb_sorter, pb_seq );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i32_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i32_sequence_item( seq, 1 ) == 2 );
   CU_ASSERT( i32_sequence_item( seq, 2 ) == 3 );
   CU_ASSERT( i32_sequence_item( seq, 3 ) == 3 );
   CU_ASSERT( i32_sequence_item( seq, 4 ) == 5 );
   CU_ASSERT( i32_sequence_item( seq, 5 ) == 6 );

   i32_sequence_dispose( &seq );
   i_bsorter_dispose( &sorter );

   return;
}

int
add_test_sort( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_sort", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_sort_1
   add_test_to_suite( p_suite, test_sort_1, "test_sort_1" );

   // test_sort_2
   add_test_to_suite( p_suite, test_sort_2, "test_sort_2" );

   // test_sort_3
   add_test_to_suite( p_suite, test_sort_3, "test_sort_3" );

   // test_sort_4a
   add_test_to_suite( p_suite, test_sort_4a, "test_sort_4a" );

   // test_sort_4b
   add_test_to_suite( p_suite, test_sort_4b, "test_sort_4b" );

   // test_sort_4c
   add_test_to_suite( p_suite, test_sort_4c, "test_sort_4c" );

   // test_sort_4d
   add_test_to_suite( p_suite, test_sort_4d, "test_sort_4d" );

   // test_sort_4e
   add_test_to_suite( p_suite, test_sort_4e, "test_sort_4e" );

   // test_sort_4f
   add_test_to_suite( p_suite, test_sort_4f, "test_sort_4f" );

   // test_sort_5
   add_test_to_suite( p_suite, test_sort_5, "test_sort_5" );

   // test_sort_6
   add_test_to_suite( p_suite, test_sort_6, "test_sort_6" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

