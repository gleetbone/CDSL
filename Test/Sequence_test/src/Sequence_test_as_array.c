/**
 @file Sequence_test_as_array.c
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
   int_sequence_dispose( sequence );

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

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

