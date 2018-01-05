/**
 @file Sequence_test_clone.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for Sequence_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Sequence_make.

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "int_Sequence.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_clone_1
*/

void test_clone_1( void )
{
   int_sequence_t *sequence = NULL;
   int_sequence_t *sequence1 = NULL;
   int32_t array[4] = { 13, 17, 19, 23 };
   
   sequence = int_sequence_make_from_array( array, 4, 4 );
   
   sequence1 = int_sequence_clone( sequence );
   CU_ASSERT( sequence != NULL );
   CU_ASSERT( sequence1 != NULL );
   CU_ASSERT( int_sequence_count( sequence ) == 4 );
   CU_ASSERT( int_sequence_count( sequence1 ) == 4 );
   CU_ASSERT( int_sequence_capacity( sequence ) == 4 );
   CU_ASSERT( int_sequence_capacity( sequence1 ) == 4 );
   CU_ASSERT( int_sequence_is_empty( sequence ) == 0 );
   CU_ASSERT( int_sequence_is_empty( sequence1 ) == 0 );

   CU_ASSERT( int_sequence_item( sequence1, 0 ) == 13 );
   CU_ASSERT( int_sequence_item( sequence1, 1 ) == 17 );
   CU_ASSERT( int_sequence_item( sequence1, 2 ) == 19 );
   CU_ASSERT( int_sequence_item( sequence1, 3 ) == 23 );
 
   int_sequence_dispose( sequence );
   int_sequence_dispose( sequence1 );

   return;
}

int
add_test_clone( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_clone", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_clone_1
   add_test_to_suite( p_suite, test_clone_1, "test_clone_1" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

