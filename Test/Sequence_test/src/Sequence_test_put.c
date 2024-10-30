/**
 @file Sequence_test_put.c
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
   test_put_1
*/

void test_put_1( void )
{
   int_sequence_t *sequence = NULL;
   
   sequence = int_sequence_make_n( 16 );
   
   int_sequence_set_count( sequence, 1 );
   int_sequence_put( sequence, 13, 0 );
   
   CU_ASSERT( int_sequence_item( sequence, 0 ) == 13 );
   
   int_sequence_dispose( &sequence );

   return;
}

/**
   test_put_2
*/

void test_put_2( void )
{
   int_sequence_t *sequence = NULL;
   
   sequence = int_sequence_make_n( 16 );
   
   int_sequence_set_count( sequence, 2 );
   int_sequence_put( sequence, 13, 0 );
   int_sequence_put( sequence, 24, 1 );
   
   CU_ASSERT( int_sequence_item( sequence, 0 ) == 13 );
   CU_ASSERT( int_sequence_item( sequence, 1 ) == 24 );
   
   int_sequence_put( sequence, 7, 1 );
   
   CU_ASSERT( int_sequence_item( sequence, 1 ) == 7 );
   
   int_sequence_dispose( &sequence );

   return;
}

/**
   test_put_3
*/

void test_put_3( void )
{
   int_sequence_t *sequence = NULL;
   
   sequence = int_sequence_make_n( 16 );
   
   int_sequence_set_count( sequence, 12 );
   int_sequence_put( sequence, 13, 0 );
   int_sequence_put( sequence, 24, 11 );
   
   CU_ASSERT( int_sequence_item( sequence, 0 ) == 13 );
   CU_ASSERT( int_sequence_item( sequence, 11 ) == 24 );
   
   int_sequence_put( sequence, 7, 11 );
   
   CU_ASSERT( int_sequence_item( sequence, 11 ) == 7 );
   
   int_sequence_dispose( &sequence );

   return;
}

/**
   test_put_4
*/

void test_put_4( void )
{
   s_sequence_t *sequence = NULL;
   
   sequence = s_sequence_make_n( 16 );
   
   string_t *s1 = string_make_from_cstring( "a" );
   string_t *s2 = string_make_from_cstring( "b" );
   string_t *s3 = string_make_from_cstring( "c" );
   
   s_sequence_set_count( sequence, 12 );
   
   s_sequence_put( sequence, s1, 0 );
   s_sequence_put( sequence, s2, 11 );
   
   CU_ASSERT( s_sequence_item( sequence, 0 ) == s1 );
   CU_ASSERT( s_sequence_item( sequence, 11 ) == s2 );
   
   s_sequence_put( sequence, s3, 11 );
   
   CU_ASSERT( s_sequence_item( sequence, 11 ) == s3 );
   
   string_deep_dispose( &s2 );
   s_sequence_deep_dispose( &sequence );

   return;
}

int
add_test_put( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_put", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_put_1
   add_test_to_suite( p_suite, test_put_1, "test_put_1" );

   // test_put_2
   add_test_to_suite( p_suite, test_put_2, "test_put_2" );

   // test_put_3
   add_test_to_suite( p_suite, test_put_3, "test_put_3" );

   // test_put_4
   add_test_to_suite( p_suite, test_put_4, "test_put_4" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

