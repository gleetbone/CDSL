/**
 @file LSearcher_test_search.c
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
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "Protocol_Base.h"
#include "i_Sequence.h"
#include "i_LSearcher.h"

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

void test_search_0( void )
{

   i_sequence_t *seq = i_sequence_make_n( 1 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;
   int32_t result = 0;
   
   i_sequence_ensure_count( seq, 1 );
   
   i_sequence_put( seq, 1, 0 );
   
   result = i_lsearcher_search( pb_seq, func, 1 );
 
   CU_ASSERT( result == 0 );

   i_sequence_dispose( &seq );

   return;
}

void test_search_1( void )
{

   i_sequence_t *seq = i_sequence_make_n( 2 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;
   int32_t result = 0;
   
   i_sequence_ensure_count( seq, 2 );
   
   i_sequence_put( seq, 1, 0 );
   i_sequence_put( seq, 2, 1 );
   
   result = i_lsearcher_search( pb_seq, func, 2 );
 
   CU_ASSERT( result == 1 );

   i_sequence_dispose( &seq );

   return;
}

void test_search_2( void )
{

   i_sequence_t *seq = i_sequence_make_n( 3 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;
   int32_t result = 0;
   
   i_sequence_ensure_count( seq, 3 );
   
   i_sequence_put( seq, 3, 0 );
   i_sequence_put( seq, 2, 1 );
   i_sequence_put( seq, 1, 2 );
   
   result = i_lsearcher_search( pb_seq, func, 2 );
 
   CU_ASSERT( result == 1 );

   i_sequence_dispose( &seq );

   return;
}

void test_search_3( void )
{

   i_sequence_t *seq = i_sequence_make_n( 3 );
   protocol_base_t *pb_seq = ( protocol_base_t * ) seq;
   int32_t result = 0;

   i_sequence_ensure_count( seq, 6 );

   i_sequence_put( seq, 6, 0 );
   i_sequence_put( seq, 2, 1 );
   i_sequence_put( seq, 4, 2 );
   i_sequence_put( seq, 3, 3 );
   i_sequence_put( seq, 5, 4 );
   i_sequence_put( seq, 1, 5 );

   result = i_lsearcher_search( pb_seq, func, 2 );

   CU_ASSERT( result == 1 );

   i_sequence_dispose( &seq );

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

   // test_search_0
   add_test_to_suite( p_suite, test_search_0, "test_search_0" );

   // test_search_1
   add_test_to_suite( p_suite, test_search_1, "test_search_1" );

   // test_search_2
   add_test_to_suite( p_suite, test_search_2, "test_search_2" );

   // test_search_3
   add_test_to_suite( p_suite, test_search_3, "test_search_3" );


   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

