/**
 @file QSorter_test_all.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for QSorter_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for QSorter_t.

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_QSorter.h"
#include "i_Sorter.h"
#include "i_Sequence.h"
#include "p_Basic.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_all_1
*/

void test_all_1( void )
{
   i_qsorter_t *sorter = i_qsorter_make();
   protocol_base_t *pb_sorter = ( protocol_base_t * ) sorter;
   i_sequence_t *seq = i_sequence_make_n( 1 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;

   i_sequence_ensure_count( seq, 1 );

   i_sequence_put( seq, 1, 0 );
   
   i_sorter_sort( pb_sorter, pb_seq );

   CU_ASSERT( i_sequence_item( seq, 0 ) == 1 );

   p_basic_dispose( &pb_sorter );
   i_sequence_dispose( &seq );

   return;
}

/**
   test_all_2
*/

void test_all_2( void )
{
   i_qsorter_t *sorter = i_qsorter_make();
   protocol_base_t *pb_sorter = ( protocol_base_t * ) sorter;
   i_sequence_t *seq = i_sequence_make_n( 2 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;

   i_sequence_ensure_count( seq, 2 );

   i_sequence_put( seq, 1, 0 );
   i_sequence_put( seq, 2, 1 );

   i_sorter_sort( pb_sorter, pb_seq );

   CU_ASSERT( i_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i_sequence_item( seq, 1 ) == 2 );

   p_basic_dispose( &pb_sorter );
   i_sequence_dispose( &seq );

   return;
}

/**
   test_all_3
*/

void test_all_3( void )
{
   i_qsorter_t *sorter = i_qsorter_make();
   protocol_base_t *pb_sorter = ( protocol_base_t * ) sorter;
   i_sequence_t *seq = i_sequence_make_n( 2 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;

   i_sequence_ensure_count( seq, 2 );

   i_sequence_put( seq, 2, 0 );
   i_sequence_put( seq, 1, 1 );

   i_sorter_sort( pb_sorter, pb_seq );

   CU_ASSERT( i_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i_sequence_item( seq, 1 ) == 2 );

   p_basic_dispose( &pb_sorter );
   i_sequence_dispose( &seq );

   return;
}

/**
   test_all_4a
*/

void test_all_4a( void )
{
   i_qsorter_t *sorter = i_qsorter_make();
   protocol_base_t *pb_sorter = ( protocol_base_t * ) sorter;
   i_sequence_t *seq = i_sequence_make_n( 2 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;

   i_sequence_ensure_count( seq, 3 );

   i_sequence_put( seq, 1, 0 );
   i_sequence_put( seq, 2, 1 );
   i_sequence_put( seq, 3, 2 );

   i_sorter_sort( pb_sorter, pb_seq );

   CU_ASSERT( i_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i_sequence_item( seq, 1 ) == 2 );
   CU_ASSERT( i_sequence_item( seq, 2 ) == 3 );

   p_basic_dispose( &pb_sorter );
   i_sequence_dispose( &seq );

   return;
}

/**
   test_all_4b
*/

void test_all_4b( void )
{
   i_qsorter_t *sorter = i_qsorter_make();
   protocol_base_t *pb_sorter = ( protocol_base_t * ) sorter;
   i_sequence_t *seq = i_sequence_make_n( 2 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;

   i_sequence_ensure_count( seq, 3 );

   i_sequence_put( seq, 3, 0 );
   i_sequence_put( seq, 1, 1 );
   i_sequence_put( seq, 2, 2 );

   i_sorter_sort( pb_sorter, pb_seq );

   CU_ASSERT( i_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i_sequence_item( seq, 1 ) == 2 );
   CU_ASSERT( i_sequence_item( seq, 2 ) == 3 );

   p_basic_dispose( &pb_sorter );
   i_sequence_dispose( &seq );

   return;
}

/**
   test_all_4c
*/

void test_all_4c( void )
{
   i_qsorter_t *sorter = i_qsorter_make();
   protocol_base_t *pb_sorter = ( protocol_base_t * ) sorter;
   i_sequence_t *seq = i_sequence_make_n( 2 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;

   i_sequence_ensure_count( seq, 3 );

   i_sequence_put( seq, 2, 0 );
   i_sequence_put( seq, 3, 1 );
   i_sequence_put( seq, 1, 2 );

   i_sorter_sort( pb_sorter, pb_seq );

   CU_ASSERT( i_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i_sequence_item( seq, 1 ) == 2 );
   CU_ASSERT( i_sequence_item( seq, 2 ) == 3 );

   p_basic_dispose( &pb_sorter );
   i_sequence_dispose( &seq );

   return;
}

/**
   test_all_4d
*/

void test_all_4d( void )
{
   i_qsorter_t *sorter = i_qsorter_make();
   protocol_base_t *pb_sorter = ( protocol_base_t * ) sorter;
   i_sequence_t *seq = i_sequence_make_n( 2 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;

   i_sequence_ensure_count( seq, 3 );

   i_sequence_put( seq, 3, 0 );
   i_sequence_put( seq, 2, 1 );
   i_sequence_put( seq, 1, 2 );

   i_sorter_sort( pb_sorter, pb_seq );

   CU_ASSERT( i_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i_sequence_item( seq, 1 ) == 2 );
   CU_ASSERT( i_sequence_item( seq, 2 ) == 3 );

   p_basic_dispose( &pb_sorter );
   i_sequence_dispose( &seq );

   return;
}

/**
   test_all_4e
*/

void test_all_4e( void )
{
   i_qsorter_t *sorter = i_qsorter_make();
   protocol_base_t *pb_sorter = ( protocol_base_t * ) sorter;
   i_sequence_t *seq = i_sequence_make_n( 2 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;

   i_sequence_ensure_count( seq, 3 );

   i_sequence_put( seq, 2, 0 );
   i_sequence_put( seq, 1, 1 );
   i_sequence_put( seq, 3, 2 );

   i_sorter_sort( pb_sorter, pb_seq );

   CU_ASSERT( i_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i_sequence_item( seq, 1 ) == 2 );
   CU_ASSERT( i_sequence_item( seq, 2 ) == 3 );

   p_basic_dispose( &pb_sorter );
   i_sequence_dispose( &seq );

   return;
}

/**
   test_all_4f
*/

void test_all_4f( void )
{
   i_qsorter_t *sorter = i_qsorter_make();
   protocol_base_t *pb_sorter = ( protocol_base_t * ) sorter;
   i_sequence_t *seq = i_sequence_make_n( 2 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;

   i_sequence_ensure_count( seq, 3 );

   i_sequence_put( seq, 1, 0 );
   i_sequence_put( seq, 3, 1 );
   i_sequence_put( seq, 2, 2 );

   i_sorter_sort( pb_sorter, pb_seq );

   CU_ASSERT( i_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i_sequence_item( seq, 1 ) == 2 );
   CU_ASSERT( i_sequence_item( seq, 2 ) == 3 );

   p_basic_dispose( &pb_sorter );
   i_sequence_dispose( &seq );

   return;
}

/**
   test_all_5
*/

void test_all_5( void )
{
   i_qsorter_t *sorter = i_qsorter_make();
   protocol_base_t *pb_sorter = ( protocol_base_t * ) sorter;
   i_sequence_t *seq = i_sequence_make_n( 2 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;

   i_sequence_ensure_count( seq, 6 );

   i_sequence_put( seq, 6, 0 );
   i_sequence_put( seq, 5, 1 );
   i_sequence_put( seq, 4, 2 );
   i_sequence_put( seq, 3, 3 );
   i_sequence_put( seq, 2, 4 );
   i_sequence_put( seq, 1, 5 );

   i_sorter_sort( pb_sorter, pb_seq );

   CU_ASSERT( i_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i_sequence_item( seq, 1 ) == 2 );
   CU_ASSERT( i_sequence_item( seq, 2 ) == 3 );
   CU_ASSERT( i_sequence_item( seq, 3 ) == 4 );
   CU_ASSERT( i_sequence_item( seq, 4 ) == 5 );
   CU_ASSERT( i_sequence_item( seq, 5 ) == 6 );

   p_basic_dispose( &pb_sorter );
   i_sequence_dispose( &seq );

   return;
}

int
add_test_all( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_all", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_all_1
   add_test_to_suite( p_suite, test_all_1, "test_all_1" );

   // test_all_2
   add_test_to_suite( p_suite, test_all_2, "test_all_2" );

   // test_all_3
   add_test_to_suite( p_suite, test_all_3, "test_all_3" );

   // test_all_4a
   add_test_to_suite( p_suite, test_all_4a, "test_all_4a" );

   // test_all_4b
   add_test_to_suite( p_suite, test_all_4b, "test_all_4b" );

   // test_all_4c
   add_test_to_suite( p_suite, test_all_4c, "test_all_4c" );

   // test_all_4d
   add_test_to_suite( p_suite, test_all_4d, "test_all_4d" );

   // test_all_4e
   add_test_to_suite( p_suite, test_all_4e, "test_all_4e" );

   // test_all_4f
   add_test_to_suite( p_suite, test_all_4f, "test_all_4f" );

   // test_all_5
   add_test_to_suite( p_suite, test_all_5, "test_all_5" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

