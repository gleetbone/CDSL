/**
 @file LSearcher_test_all.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for LSearcher_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for LSearcher_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_LSearcher.h"
#include "i_Searcher.h"
#include "i_Sequence.h"
#include "p_Basic.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_all_1
*/

void test_all_1( void )
{
   i_lsearcher_t *searcher = i_lsearcher_make();
   protocol_base_t *pb_searcher = ( protocol_base_t * ) searcher;
   i_sequence_t *seq = i_sequence_make_n( 1 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;
   int32_t result = 0;

   i_sequence_ensure_count( seq, 1 );

   i_sequence_put( seq, 1, 0 );
   
   result = i_searcher_search( pb_searcher, pb_seq, 1 );

   CU_ASSERT( result == 0 );

   i_sequence_dispose( &seq );
   p_basic_dispose( &pb_searcher );
 
   return;
}

/**
   test_all_2
*/

void test_all_2( void )
{
   i_lsearcher_t *searcher = i_lsearcher_make();
   protocol_base_t *pb_searcher = ( protocol_base_t * ) searcher;
   i_sequence_t *seq = i_sequence_make_n( 2 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;
   int32_t result = 0;

   i_sequence_ensure_count( seq, 2 );

   i_sequence_put( seq, 1, 0 );
   i_sequence_put( seq, 2, 1 );

   result = i_searcher_search( pb_searcher, pb_seq, 2 );

   CU_ASSERT( result == 1 );

   i_sequence_dispose( &seq );
   p_basic_dispose( &pb_searcher );

   return;
}

/**
   test_all_3
*/

void test_all_3( void )
{
   i_lsearcher_t *searcher = i_lsearcher_make();
   protocol_base_t *pb_searcher = ( protocol_base_t * ) searcher;
   i_sequence_t *seq = i_sequence_make_n( 2 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;
   int32_t result = 0;

   i_sequence_ensure_count( seq, 3 );

   i_sequence_put( seq, 3, 0 );
   i_sequence_put( seq, 2, 1 );
   i_sequence_put( seq, 1, 2 );

   result = i_searcher_search( pb_searcher, pb_seq, 2 );

   CU_ASSERT( result == 1 );

   i_sequence_dispose( &seq );
   p_basic_dispose( &pb_searcher );

   return;
}

/**
   test_all_4
*/

void test_all_4( void )
{
   i_lsearcher_t *searcher = i_lsearcher_make();
   protocol_base_t *pb_searcher = ( protocol_base_t * ) searcher;
   i_sequence_t *seq = i_sequence_make_n( 2 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;
   int32_t result = 0;

   i_sequence_ensure_count( seq, 6 );

   i_sequence_put( seq, 5, 0 );
   i_sequence_put( seq, 2, 1 );
   i_sequence_put( seq, 3, 2 );
   i_sequence_put( seq, 6, 3 );
   i_sequence_put( seq, 1, 4 );
   i_sequence_put( seq, 4, 5 );

   result = i_searcher_search( pb_searcher, pb_seq, 2 );

   CU_ASSERT( result == 1 );

   i_sequence_dispose( &seq );
   p_basic_dispose( &pb_searcher );

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

   // test_all_4
   add_test_to_suite( p_suite, test_all_4, "test_all_4" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

