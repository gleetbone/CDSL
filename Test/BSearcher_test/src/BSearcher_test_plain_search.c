/**
 @file BSearcher_test_plain_search.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BSearcher_t"
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
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "Protocol_Base.h"
#include "i32_Sequence.h"
#include "i_BSearcher.h"

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

void test_plain_search_0( void )
{

   i32_sequence_t *seq = i32_sequence_make_n( 1 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;
   int32_t result = 0;
   
   i32_sequence_ensure_count( seq, 1 );
   
   i32_sequence_put( seq, 1, 0 );
   
   result = i_bsearcher_search( pb_seq, func, 1 );
 
   CU_ASSERT( result == 0 );

   i32_sequence_dispose( &seq );

   return;
}

void test_plain_search_1( void )
{

   i32_sequence_t *seq = i32_sequence_make_n( 2 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;
   int32_t result = 0;
   
   i32_sequence_ensure_count( seq, 2 );
   
   i32_sequence_put( seq, 1, 0 );
   i32_sequence_put( seq, 2, 1 );
   
   result = i_bsearcher_search( pb_seq, func, 2 );
 
   CU_ASSERT( result == 1 );

   i32_sequence_dispose( &seq );

   return;
}

void test_plain_search_2( void )
{

   i32_sequence_t *seq = i32_sequence_make_n( 3 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;
   int32_t result = 0;
   
   i32_sequence_ensure_count( seq, 3 );
   
   i32_sequence_put( seq, 1, 0 );
   i32_sequence_put( seq, 2, 1 );
   i32_sequence_put( seq, 3, 2 );
   
   result = i_bsearcher_search( pb_seq, func, 2 );
 
   CU_ASSERT( result == 1 );

   i32_sequence_dispose( &seq );

   return;
}

void test_plain_search_3( void )
{

   i32_sequence_t *seq = i32_sequence_make_n( 3 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;
   int32_t result = 0;

   i32_sequence_ensure_count( seq, 6 );

   i32_sequence_put( seq, 1, 0 );
   i32_sequence_put( seq, 2, 1 );
   i32_sequence_put( seq, 3, 2 );
   i32_sequence_put( seq, 4, 3 );
   i32_sequence_put( seq, 5, 4 );
   i32_sequence_put( seq, 6, 5 );

   result = i_bsearcher_search( pb_seq, func, 2 );

   CU_ASSERT( result == 1 );

   i32_sequence_dispose( &seq );

   return;
}

int
add_test_plain_search( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_plain_search", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_plain_search_0
   add_test_to_suite( p_suite, test_plain_search_0, "test_plain_search_0" );

   // test_plain_search_1
   add_test_to_suite( p_suite, test_plain_search_1, "test_plain_search_1" );

   // test_plain_search_2
   add_test_to_suite( p_suite, test_plain_search_2, "test_plain_search_2" );

   // test_plain_search_3
   add_test_to_suite( p_suite, test_plain_search_3, "test_plain_search_3" );


   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

