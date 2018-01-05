/**
 @file test_sort.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for timer_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for soa_node_make_dict.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "Protocol_Base.h"
#include "i_Sequence.h"
#include "i_SelSorter.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

static
int32_t
func( int32_t a, int32_t b )
{
   int32_t result = 0;
   
   if ( a < b )
   {
      result = -1;
   }
   else if ( a == b )
   {
      result = 0;
   }
   else
   {
      result = 1;
   }
   
   return result;
}

void test_sort_0( void )
{

   i_sequence_t *seq = i_sequence_make_n( 1 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;
   
   i_sequence_ensure_count( seq, 1 );
   
   i_sequence_put( seq, 1, 0 );
   
   i_selsorter_sort( pb_seq, func );
 
   CU_ASSERT( i_sequence_item( seq, 0 ) == 1 );

   i_sequence_dispose( seq );

   return;
}

void test_sort_1( void )
{

   i_sequence_t *seq = i_sequence_make_n( 2 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;
   
   i_sequence_ensure_count( seq, 2 );
   
   i_sequence_put( seq, 1, 0 );
   i_sequence_put( seq, 2, 1 );
   
   i_selsorter_sort( pb_seq, func );
 
   
   CU_ASSERT( i_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i_sequence_item( seq, 1 ) == 2 );

   i_sequence_dispose( seq );

   return;
}

void test_sort_2( void )
{

   i_sequence_t *seq = i_sequence_make_n( 2 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;
   
   i_sequence_ensure_count( seq, 2 );
   
   i_sequence_put( seq, 2, 0 );
   i_sequence_put( seq, 1, 1 );
   
   i_selsorter_sort( pb_seq, func );
 
   
   CU_ASSERT( i_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i_sequence_item( seq, 1 ) == 2 );

   i_sequence_dispose( seq );

   return;
}

void test_sort_3a( void )
{

   i_sequence_t *seq = i_sequence_make_n( 3 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;
   
   i_sequence_ensure_count( seq, 3 );
   
   i_sequence_put( seq, 1, 0 );
   i_sequence_put( seq, 2, 1 );
   i_sequence_put( seq, 3, 2 );
   
   i_selsorter_sort( pb_seq, func );
 
   
   CU_ASSERT( i_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i_sequence_item( seq, 1 ) == 2 );
   CU_ASSERT( i_sequence_item( seq, 2 ) == 3 );

   i_sequence_dispose( seq );

   return;
}

void test_sort_3b( void )
{

   i_sequence_t *seq = i_sequence_make_n( 3 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;
   
   i_sequence_ensure_count( seq, 3 );
   
   i_sequence_put( seq, 3, 0 );
   i_sequence_put( seq, 1, 1 );
   i_sequence_put( seq, 2, 2 );
   
   i_selsorter_sort( pb_seq, func );
 
   
   CU_ASSERT( i_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i_sequence_item( seq, 1 ) == 2 );
   CU_ASSERT( i_sequence_item( seq, 2 ) == 3 );

   i_sequence_dispose( seq );

   return;
}

void test_sort_3c( void )
{

   i_sequence_t *seq = i_sequence_make_n( 3 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;
   
   i_sequence_ensure_count( seq, 3 );
   
   i_sequence_put( seq, 2, 0 );
   i_sequence_put( seq, 3, 1 );
   i_sequence_put( seq, 1, 2 );
   
   i_selsorter_sort( pb_seq, func );
 
   
   CU_ASSERT( i_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i_sequence_item( seq, 1 ) == 2 );
   CU_ASSERT( i_sequence_item( seq, 2 ) == 3 );

   i_sequence_dispose( seq );

   return;
}

void test_sort_3d( void )
{

   i_sequence_t *seq = i_sequence_make_n( 3 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;
   
   i_sequence_ensure_count( seq, 3 );
   
   i_sequence_put( seq, 3, 0 );
   i_sequence_put( seq, 2, 1 );
   i_sequence_put( seq, 1, 2 );
   
   i_selsorter_sort( pb_seq, func );
 
   
   CU_ASSERT( i_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i_sequence_item( seq, 1 ) == 2 );
   CU_ASSERT( i_sequence_item( seq, 2 ) == 3 );

   i_sequence_dispose( seq );

   return;
}

void test_sort_3e( void )
{

   i_sequence_t *seq = i_sequence_make_n( 3 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;
   
   i_sequence_ensure_count( seq, 3 );
   
   i_sequence_put( seq, 2, 0 );
   i_sequence_put( seq, 1, 1 );
   i_sequence_put( seq, 3, 2 );
   
   i_selsorter_sort( pb_seq, func );
 
   
   CU_ASSERT( i_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i_sequence_item( seq, 1 ) == 2 );
   CU_ASSERT( i_sequence_item( seq, 2 ) == 3 );

   i_sequence_dispose( seq );

   return;
}

void test_sort_3f( void )
{

   i_sequence_t *seq = i_sequence_make_n( 3 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;
   
   i_sequence_ensure_count( seq, 3 );
   
   i_sequence_put( seq, 1, 0 );
   i_sequence_put( seq, 3, 1 );
   i_sequence_put( seq, 2, 2 );
   
   i_selsorter_sort( pb_seq, func );
 
   
   CU_ASSERT( i_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i_sequence_item( seq, 1 ) == 2 );
   CU_ASSERT( i_sequence_item( seq, 2 ) == 3 );

   i_sequence_dispose( seq );

   return;
}

void test_sort_4( void )
{

   i_sequence_t *seq = i_sequence_make_n( 3 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;

   i_sequence_ensure_count( seq, 6 );

   i_sequence_put( seq, 6, 0 );
   i_sequence_put( seq, 5, 1 );
   i_sequence_put( seq, 4, 2 );
   i_sequence_put( seq, 3, 3 );
   i_sequence_put( seq, 2, 4 );
   i_sequence_put( seq, 1, 5 );

   i_selsorter_sort( pb_seq, func );


   CU_ASSERT( i_sequence_item( seq, 0 ) == 1 );
   CU_ASSERT( i_sequence_item( seq, 1 ) == 2 );
   CU_ASSERT( i_sequence_item( seq, 2 ) == 3 );
   CU_ASSERT( i_sequence_item( seq, 3 ) == 4 );
   CU_ASSERT( i_sequence_item( seq, 4 ) == 5 );
   CU_ASSERT( i_sequence_item( seq, 5 ) == 6 );

   i_sequence_dispose( seq );

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

   // test_sort_0
   add_test_to_suite( p_suite, test_sort_0, "test_sort_0" );

   // test_sort_1
   add_test_to_suite( p_suite, test_sort_1, "test_sort_1" );

   // test_sort_2
   add_test_to_suite( p_suite, test_sort_2, "test_sort_2" );

   // test_sort_3a
   add_test_to_suite( p_suite, test_sort_3a, "test_sort_3a" );

   // test_sort_3b
   add_test_to_suite( p_suite, test_sort_3b, "test_sort_3b" );

   // test_sort_3c
   add_test_to_suite( p_suite, test_sort_3c, "test_sort_3c" );

   // test_sort_3d
   add_test_to_suite( p_suite, test_sort_3d, "test_sort_3d" );

   // test_sort_3e
   add_test_to_suite( p_suite, test_sort_3e, "test_sort_3e" );

   // test_sort_3f
   add_test_to_suite( p_suite, test_sort_3f, "test_sort_3f" );

   // test_sort_4
   add_test_to_suite( p_suite, test_sort_4, "test_sort_4" );


   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

