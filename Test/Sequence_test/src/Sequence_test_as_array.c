/**
 @file Sequence_test_as_array.c
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
   test_as_array_1
*/

void test_as_array_1( void )
{
   int_sequence_t *sequence = NULL;
   int32_t *array = NULL;
   int32_t count = 0;
   
   sequence = int_sequence_make_n( 16 );
   
   int_sequence_set_count( sequence, 2 );
   int_sequence_put( sequence, 13, 0 );
   int_sequence_put( sequence, 24, 1 );
   
   array = int_sequence_as_array( sequence, &count );
   
   CU_ASSERT( count == 2 );
   CU_ASSERT( array[0] == 13 );
   CU_ASSERT( array[1] == 24 );
   
   free( array );
   int_sequence_dispose( &sequence );

   return;
}

/**
   test_as_array_2
*/

void test_as_array_2( void )
{
   s_sequence_t *sequence = NULL;
   string_t **array = NULL;
   int32_t count = 0;
   
   sequence = s_sequence_make_n( 16 );
   
   string_t *s1 = string_make_from_cstring( "a" );
   string_t *s2 = string_make_from_cstring( "b" );
   
   s_sequence_set_count( sequence, 2 );
   s_sequence_put( sequence, s1, 0 );
   s_sequence_put( sequence, s2, 1 );
   
   array = s_sequence_as_array( sequence, &count );
   
   CU_ASSERT( count == 2 );
   CU_ASSERT( array[0] == s1 );
   CU_ASSERT( array[1] == s2 );
   
   free( array );
   s_sequence_deep_dispose( &sequence );

   return;
}

int
add_test_as_array( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_as_array", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_as_array_1
   add_test_to_suite( p_suite, test_as_array_1, "test_as_array_1" );

   // test_as_array_2
   add_test_to_suite( p_suite, test_as_array_2, "test_as_array_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

