/**
 @file BSearcher_test_search.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BSearcher_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for BSearcher_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_BSearcher.h"
#include "i_Searcher.h"
#include "i32_Sequence.h"
#include "p_Basic.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_search_1
*/

void test_search_1( void )
{
   i_bsearcher_t *searcher = NULL;
   i32_sequence_t *seq = NULL;
   protocol_base_t *pb_searcher = NULL;
   protocol_base_t *pb_seq = NULL;
   int32_t result = 0;

   searcher = i_bsearcher_make();
   pb_searcher = ( protocol_base_t * ) searcher;
   
   seq = i32_sequence_make_n( 1 );
   pb_seq = ( protocol_base_t * ) seq;
   
   i32_sequence_ensure_count( seq, 1 );

   i32_sequence_put( seq, 1, 0 );
   
   result = i_bsearcher_search_predefined_comparison_function( searcher, pb_seq, 1 );

   CU_ASSERT( result == 0 );

   p_basic_dispose( &pb_searcher );
   i32_sequence_dispose( &seq );
 
   return;
}

/**
   test_search_2
*/

void test_search_2( void )
{
   i_bsearcher_t *searcher = NULL;
   protocol_base_t *pb_searcher = NULL;
   i32_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;
   int32_t result = 0;

   searcher = i_bsearcher_make();
   pb_searcher = ( protocol_base_t * ) searcher;
   
   seq = i32_sequence_make_n( 2 );
   pb_seq = ( protocol_base_t * ) seq;
   
   i32_sequence_ensure_count( seq, 2 );

   i32_sequence_put( seq, 1, 0 );
   i32_sequence_put( seq, 2, 1 );

   result = i_searcher_search( pb_searcher, pb_seq, 2 );

   CU_ASSERT( result == 1 );

   i32_sequence_dispose( &seq );
   i_bsearcher_dispose( &searcher );

   return;
}

/**
   test_search_3
*/

void test_search_3( void )
{
   i_bsearcher_t *searcher = NULL;
   protocol_base_t *pb_searcher = NULL;
   i32_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;
   int32_t result = 0;

   searcher = i_bsearcher_make();
   pb_searcher = ( protocol_base_t * ) searcher;
   seq = i32_sequence_make_n( 2 );
   pb_seq = ( protocol_base_t * ) seq;
   
   i32_sequence_ensure_count( seq, 3 );

   i32_sequence_put( seq, 1, 0 );
   i32_sequence_put( seq, 2, 1 );
   i32_sequence_put( seq, 3, 2 );

   result = i_searcher_search( pb_searcher, pb_seq, 2 );

   CU_ASSERT( result == 1 );

   i32_sequence_dispose( &seq );
   i_bsearcher_dispose( &searcher );

   return;
}

/**
   test_search_4
*/

void test_search_4( void )
{
   i_bsearcher_t *searcher = NULL;
   protocol_base_t *pb_searcher = NULL;
   i32_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;
   int32_t result = 0;

   searcher = i_bsearcher_make();
   pb_searcher = ( protocol_base_t * ) searcher;
   seq = i32_sequence_make_n( 2 );
   pb_seq = ( protocol_base_t * ) seq;
   
   i32_sequence_ensure_count( seq, 6 );

   i32_sequence_put( seq, 1, 0 );
   i32_sequence_put( seq, 2, 1 );
   i32_sequence_put( seq, 3, 2 );
   i32_sequence_put( seq, 4, 3 );
   i32_sequence_put( seq, 5, 4 );
   i32_sequence_put( seq, 6, 5 );

   result = i_searcher_search( pb_searcher, pb_seq, 2 );

   CU_ASSERT( result == 1 );

   i32_sequence_dispose( &seq );
   i_bsearcher_dispose( &searcher );

   return;
}

int
add_test_search( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_search", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_search_1
   add_test_to_suite( p_suite, test_search_1, "test_search_1" );

   // test_search_2
   add_test_to_suite( p_suite, test_search_2, "test_search_2" );

   // test_search_3
   add_test_to_suite( p_suite, test_search_3, "test_search_3" );

   // test_search_4
   add_test_to_suite( p_suite, test_search_4, "test_search_4" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

