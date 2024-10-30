/**
 @file Sequence_test_protocol.c
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
#include "int_Indexable.h"
#include "int_Basic.h"
#include "s_Sequence.h"
#include "s_Indexable.h"
#include "s_Basic.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_protocol_1
*/

void test_protocol_1( void )
{
   int_sequence_t *sequence = NULL;
   protocol_base_t *indexable = NULL;
   protocol_base_t *basic = NULL;
   protocol_base_t *clone = NULL;

   sequence = int_sequence_make_n( 16 );
   indexable = ( protocol_base_t * ) sequence;
   basic = ( protocol_base_t * ) sequence;

   CU_ASSERT( int_indexable_count( indexable ) == 0 );

   clone = int_basic_clone( basic );
   CU_ASSERT( clone != NULL );

   int_sequence_dispose( &sequence );
   int_basic_dispose( &clone );

   return;
}

/**
   test_protocol_2
*/

void test_protocol_2( void )
{
   s_sequence_t *sequence = NULL;
   protocol_base_t *indexable = NULL;
   protocol_base_t *basic = NULL;
   protocol_base_t *clone = NULL;

   sequence = s_sequence_make_n( 16 );
   indexable = ( protocol_base_t * ) sequence;
   basic = ( protocol_base_t * ) sequence;

   CU_ASSERT( s_indexable_count( indexable ) == 0 );

   clone = s_basic_clone( basic );
   CU_ASSERT( clone != NULL );

   s_basic_dispose( &clone );
   s_sequence_deep_dispose( &sequence );

   return;
}

int
add_test_protocol( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_protocol", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_protocol_1
   add_test_to_suite( p_suite, test_protocol_1, "test_protocol_1" );

   // test_protocol_2
   add_test_to_suite( p_suite, test_protocol_2, "test_protocol_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

