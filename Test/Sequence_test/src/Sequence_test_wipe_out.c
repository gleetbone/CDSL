/**
 @file Sequence_test_wipe_out.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Sequence_make"
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
#include "s_Sequence.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_wipe_out_1
*/

void test_wipe_out_1( void )
{
   int_sequence_t *sequence = NULL;
   
   sequence = int_sequence_make_n( 16 );
   
   int_sequence_set_count( sequence, 1 );
   int_sequence_wipe_out( sequence );
   
   CU_ASSERT( int_sequence_count( sequence ) == 0 );
   
   CU_ASSERT( int_sequence_is_empty( sequence ) == 1 );
   
   int_sequence_dispose( &sequence );

   return;
}

/**
   test_wipe_out_2
*/

void test_wipe_out_2( void )
{
   int_sequence_t *sequence = NULL;
   
   sequence = int_sequence_make_n( 16 );
   
   int_sequence_set_count( sequence, 2 );
   int_sequence_wipe_out( sequence );
   
   CU_ASSERT( int_sequence_count( sequence ) == 0 );
   CU_ASSERT( int_sequence_is_empty( sequence ) == 1 );
   
   int_sequence_dispose( &sequence );

   return;
}

/**
   test_wipe_out_3
*/

void test_wipe_out_3( void )
{
   int_sequence_t *sequence = NULL;
   
   sequence = int_sequence_make_n( 16 );
   
   int_sequence_set_count( sequence, 12 );
   int_sequence_wipe_out( sequence );
   
   CU_ASSERT( int_sequence_count( sequence ) == 0 );
   
   int_sequence_dispose( &sequence );

   return;
}

/**
   test_wipe_out_4
*/

void test_wipe_out_4( void )
{
   s_sequence_t *sequence = NULL;
   
   sequence = s_sequence_make_n( 16 );
   
   string_t *s1 = string_make_from_cstring( "a" );
   
   s_sequence_set_count( sequence, 12 );
   s_sequence_put( sequence, s1, 0 );
   s_sequence_wipe_out( sequence );
   
   CU_ASSERT( s_sequence_count( sequence ) == 0 );
   
   string_deep_dispose( &s1 );
   s_sequence_dispose( &sequence );

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

   // test_wipe_out_3
   add_test_to_suite( p_suite, test_wipe_out_3, "test_wipe_out_3" );

   // test_wipe_out_4
   add_test_to_suite( p_suite, test_wipe_out_4, "test_wipe_out_4" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

