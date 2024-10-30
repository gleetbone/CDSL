/**
 @file Sequence_test_p_basic.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Sequence P_Clonable"
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
#include "int_Basic.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_p_basic_1
*/

void test_p_basic_1( void )
{
   int_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;
   
   seq = int_sequence_make();
   pb_seq = ( protocol_base_t * ) seq;
   
   CU_ASSERT( seq != NULL );
   CU_ASSERT( pb_seq != NULL );

   int_basic_dispose( &pb_seq );
 
   return;
}

/**
   test_p_basic_2
*/

void test_p_basic_2( void )
{
   int_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;

   seq = int_sequence_make();
   pb_seq = ( protocol_base_t * ) seq;

   CU_ASSERT( seq != NULL );
   CU_ASSERT( pb_seq != NULL );

   int_basic_deep_dispose( &pb_seq );

   return;
}

/**
   test_p_basic_3
*/

void test_p_basic_3( void )
{
   int_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;
   protocol_base_t *pb_seq1 = NULL;

   seq = int_sequence_make();
   pb_seq = ( protocol_base_t * ) seq;

   CU_ASSERT( seq != NULL );
   CU_ASSERT( pb_seq != NULL );

   pb_seq1 = int_basic_clone( pb_seq );
   CU_ASSERT( pb_seq1 != NULL );

   int_basic_dispose( &pb_seq );
   int_basic_dispose( &pb_seq1 );

   return;
}

/**
   test_p_basic_4
*/

void test_p_basic_4( void )
{
   int_sequence_t *seq = NULL;
   protocol_base_t *pb_seq = NULL;
   protocol_base_t *pb_seq1 = NULL;

   seq = int_sequence_make();
   pb_seq = ( protocol_base_t * ) seq;

   CU_ASSERT( seq != NULL );
   CU_ASSERT( pb_seq != NULL );

   pb_seq1 = int_basic_deep_clone( pb_seq );
   CU_ASSERT( pb_seq1 != NULL );

   int_basic_dispose( &pb_seq );
   int_basic_dispose( &pb_seq1 );

   return;
}

int
add_test_p_basic( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_p_basic", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_p_basic_1
   add_test_to_suite( p_suite, test_p_basic_1, "test_p_basic_1" );

   // test_p_basic_2
   add_test_to_suite( p_suite, test_p_basic_2, "test_p_basic_2" );

   // test_p_basic_3
   add_test_to_suite( p_suite, test_p_basic_3, "test_p_basic_3" );

   // test_p_basic_4
   add_test_to_suite( p_suite, test_p_basic_4, "test_p_basic_4" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

