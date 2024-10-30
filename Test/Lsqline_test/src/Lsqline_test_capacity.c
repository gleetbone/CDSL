/**
 @file Lsqline_test_capacity.c
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
   test_capacity_1
*/

void test_capacity_1( void )
{
   lsqline_t *lsqline = NULL;
   
   lsqline = lsqline_make( 4 );
   
   CU_ASSERT( lsqline != NULL );

   CU_ASSERT( lsqline_capacity( lsqline ) == 4 );

   lsqline_put( lsqline, 1.0, 1.0 );
   lsqline_put( lsqline, 2.0, 2.0 );
   lsqline_put( lsqline, 3.0, 3.0 );
   lsqline_put( lsqline, 4.0, 4.0 );
   lsqline_put( lsqline, 5.0, 5.0 );
                                       
   lsqline_put( lsqline, 9.0, 9.0 );
   lsqline_put( lsqline, 6.0, 6.0 );
   lsqline_put( lsqline, 7.0, 7.0 );
   lsqline_put( lsqline, 8.0, 8.0 );
   
   CU_ASSERT( lsqline_capacity( lsqline ) == 16 );
   
   lsqline_dispose( &lsqline );

   return;
}


int
add_test_capacity( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_capacity", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_capacity_1
   add_test_to_suite( p_suite, test_capacity_1, "test_capacity_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

