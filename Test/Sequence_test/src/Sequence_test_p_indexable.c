/**
 @file Sequence_test_p_indexable.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Sequence P_Indexable"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Sequence_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "int_Sequence.h"
#include "Protocol_Base.h"
#include "int_Indexable.h"
#include "s_Sequence.h"
#include "s_Indexable.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_p_indexable_1
*/

void test_p_indexable_1( void )
{
   int_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;
   
   seq = int_sequence_make_n( 4 );
   pb_seq = ( protocol_base_t * ) seq;
   
   CU_ASSERT( seq != NULL );
   CU_ASSERT( pb_seq != NULL );

   int_sequence_dispose( &seq );
 
   return;
}

/**
   test_p_indexable_2
*/

void test_p_indexable_2( void )
{
   int_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;

   seq = int_sequence_make_n( 4 );
   pb_seq = ( protocol_base_t * ) seq;

   CU_ASSERT( seq != NULL );
   CU_ASSERT( pb_seq != NULL );

   int_sequence_deep_dispose( &seq );

   return;
}

/**
   test_p_indexable_3
*/

void test_p_indexable_3( void )
{
   int_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;

   seq = int_sequence_make_n( 4 );
   pb_seq = ( protocol_base_t * ) seq;

   CU_ASSERT( seq != NULL );
   CU_ASSERT( pb_seq != NULL );

   int_sequence_ensure_count( seq, 4 );
   int_sequence_put( seq, 24, 0 );

   CU_ASSERT( int_indexable_count( pb_seq ) == 4 );

   int_sequence_dispose( &seq );

   return;
}

/**
   test_p_indexable_4
*/

void test_p_indexable_4( void )
{
   int_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;

   seq = int_sequence_make_n( 4 );
   pb_seq = ( protocol_base_t * ) seq;

   CU_ASSERT( seq != NULL );
   CU_ASSERT( pb_seq != NULL );

   int_sequence_ensure_count( seq, 4 );
   int_sequence_put( seq, 24, 0 );

   CU_ASSERT( int_indexable_item( pb_seq, 0 ) == 24 );


   int_sequence_dispose( &seq );

   return;
}

/**
   test_p_indexable_4a
*/

void test_p_indexable_4a( void )
{
   s_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;

   seq = s_sequence_make_n( 4 );
   pb_seq = ( protocol_base_t * ) seq;

   string_t *s1 = string_make_from_cstring( "a" );
   
   CU_ASSERT( seq != NULL );
   CU_ASSERT( pb_seq != NULL );

   s_sequence_ensure_count( seq, 4 );
   s_sequence_put( seq, s1, 0 );

   CU_ASSERT( s_indexable_item( pb_seq, 0 ) == s1 );

   s_sequence_deep_dispose( &seq );

   return;
}

/**
   test_p_indexable_5
*/

void test_p_indexable_5( void )
{
   int_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;

   seq = int_sequence_make_n( 4 );
   pb_seq = ( protocol_base_t * ) seq;

   CU_ASSERT( seq != NULL );
   CU_ASSERT( pb_seq != NULL );

   int_sequence_ensure_count( seq, 4 );
   int_sequence_put( seq, 24, 0 );

   CU_ASSERT( int_indexable_item( pb_seq, 0 ) == 24 );

   int_indexable_put( pb_seq, 23, 0 );

   CU_ASSERT( int_indexable_item( pb_seq, 0 ) == 23 );

   int_sequence_dispose( &seq );

   return;
}

/**
   test_p_indexable_6
*/

void test_p_indexable_6( void )
{
   int_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;

   seq = int_sequence_make_n( 4 );
   pb_seq = ( protocol_base_t * ) seq;

   CU_ASSERT( seq != NULL );
   CU_ASSERT( pb_seq != NULL );

   int_sequence_ensure_count( seq, 4 );
   int_sequence_put( seq, 24, 0 );

   CU_ASSERT( int_indexable_item( pb_seq, 0 ) == 24 );

   int_indexable_put_and_dispose( pb_seq, 23, 0 );

   CU_ASSERT( int_indexable_item( pb_seq, 0 ) == 23 );

   int_sequence_dispose( &seq );

   return;
}

/**
   test_p_indexable_7
*/

void test_p_indexable_7( void )
{
   s_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;

   seq = s_sequence_make_n( 4 );
   pb_seq = ( protocol_base_t * ) seq;

   string_t *s1 = string_make_from_cstring( "a" );
   string_t *s2 = string_make_from_cstring( "b" );
   
   CU_ASSERT( seq != NULL );
   CU_ASSERT( pb_seq != NULL );

   s_sequence_ensure_count( seq, 4 );
   s_sequence_put( seq, s1, 0 );

   CU_ASSERT( s_indexable_item( pb_seq, 0 ) == s1 );

   s_indexable_put_and_dispose( pb_seq, s2, 0 );

   CU_ASSERT( s_indexable_item( pb_seq, 0 ) == s2 );

   s_sequence_deep_dispose( &seq );

   return;
}

int
add_test_p_indexable( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_p_indexable", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_p_indexable_1
   add_test_to_suite( p_suite, test_p_indexable_1, "test_p_indexable_1" );

   // test_p_indexable_2
   add_test_to_suite( p_suite, test_p_indexable_2, "test_p_indexable_2" );

   // test_p_indexable_3
   add_test_to_suite( p_suite, test_p_indexable_3, "test_p_indexable_3" );

   // test_p_indexable_4
   add_test_to_suite( p_suite, test_p_indexable_4, "test_p_indexable_4" );

   // test_p_indexable_4a
   add_test_to_suite( p_suite, test_p_indexable_4a, "test_p_indexable_4a" );

   // test_p_indexable_5
   add_test_to_suite( p_suite, test_p_indexable_5, "test_p_indexable_5" );

   // test_p_indexable_6
   add_test_to_suite( p_suite, test_p_indexable_6, "test_p_indexable_6" );

   // test_p_indexable_7
   add_test_to_suite( p_suite, test_p_indexable_7, "test_p_indexable_7" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

