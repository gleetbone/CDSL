/**
 @file Lsqline_test_dispose.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for raw_buffer_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for raw_buffer_t.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "Lsqline.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );


/**
   test_dispose_1
*/

void test_dispose_1( void )
{
   lsqline_t *lsqline = NULL;
   
   lsqline = lsqline_make( 4 );
   
   CU_ASSERT( lsqline != NULL );

   CU_ASSERT( lsqline_capacity( lsqline ) == 4 );

   lsqline_dispose( &lsqline );

   return;
}

/**
   test_dispose_2
*/

void test_dispose_2( void )
{
   lsqline_t *lsqline = NULL;
   
   lsqline = lsqline_make( 5 );
   
   CU_ASSERT( lsqline != NULL );

   CU_ASSERT( lsqline_capacity( lsqline ) == 5 );

   lsqline_dispose( &lsqline );

   return;
}



int
add_test_dispose( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_dispose", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_dispose_1
   add_test_to_suite( p_suite, test_dispose_1, "test_dispose_1" );

   // test_dispose_2
   add_test_to_suite( p_suite, test_dispose_2, "test_dispose_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

