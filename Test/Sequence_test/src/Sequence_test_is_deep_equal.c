/**
 @file Sequence_test_is_deep_equal.c
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
   test_is_deep_equal_1
*/

void test_is_deep_equal_1( void )
{
   int_sequence_t *sequence = NULL;
   int_sequence_t *sequence1 = NULL;
   
   sequence = int_sequence_make_n( 16 );
   sequence1 = int_sequence_make_n( 16 );
   
   CU_ASSERT( int_sequence_is_deep_equal( sequence1, sequence ) == 1 );
   
   int_sequence_set_count( sequence, 1 );
   
   CU_ASSERT( int_sequence_is_deep_equal( sequence, sequence1 ) == 0 );
   
   int_sequence_set_count( sequence1, 1 );
   
   int_sequence_put( sequence, 13, 0 );
   int_sequence_put( sequence1, 17, 0 );
      
   CU_ASSERT( int_sequence_is_deep_equal( sequence, sequence1 ) == 0 );
   
   int_sequence_put( sequence1, 13, 0 );
   
   CU_ASSERT( int_sequence_is_deep_equal( sequence, sequence1 ) == 1 );
   
   int_sequence_dispose( &sequence );
   int_sequence_dispose( &sequence1 );

   return;
}

/**
   test_is_deep_equal_2
*/

void test_is_deep_equal_2( void )
{
   s_sequence_t *sequence = NULL;
   s_sequence_t *sequence1 = NULL;
   
   sequence = s_sequence_make_n( 16 );
   sequence1 = s_sequence_make_n( 16 );
   
   string_t *s1 = string_make_from_cstring( "a" );
   string_t *s1a = string_make_from_cstring( "a" );
   string_t *s2 = string_make_from_cstring( "b" );
   
   CU_ASSERT( s_sequence_is_deep_equal( sequence1, sequence ) == 1 );
   
   s_sequence_set_count( sequence, 1 );
   
   CU_ASSERT( s_sequence_is_deep_equal( sequence, sequence1 ) == 0 );
   
   s_sequence_set_count( sequence1, 1 );
   
   s_sequence_put( sequence, s1, 0 );
   s_sequence_put( sequence1, s2, 0 );
      
   CU_ASSERT( s_sequence_is_deep_equal( sequence, sequence1 ) == 0 );
   
   s_sequence_put( sequence1, s1a, 0 );
   
   CU_ASSERT( s_sequence_is_deep_equal( sequence, sequence1 ) == 1 );
   
   string_deep_dispose( &s2 );
   
   s_sequence_deep_dispose( &sequence );
   s_sequence_deep_dispose( &sequence1 );

   return;
}

int
add_test_is_deep_equal( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_deep_equal", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_deep_equal_1
   add_test_to_suite( p_suite, test_is_deep_equal_1, "test_is_deep_equal_1" );

   // test_is_deep_equal_2
   add_test_to_suite( p_suite, test_is_deep_equal_2, "test_is_deep_equal_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

