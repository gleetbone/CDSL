/**
 @file Lsqline_test_put.c
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
   test_put_1
*/

void test_put_1( void )
{
   lsqline_t *lsqline = NULL;
   
   lsqline = lsqline_make( 4 );
   
   lsqline_put( lsqline, 1.0, 1.0 );

   CU_ASSERT( lsqline_capacity( lsqline ) == 4 );

   lsqline_dispose( &lsqline );

   return;
}

/**
   test_put_2
*/

void test_put_2( void )
{
   lsqline_t *lsqline = NULL;
   
   lsqline = lsqline_make( 4 );
   
   lsqline_put( lsqline, 1.0, 1.0 );
   lsqline_put( lsqline, 1.1, 1.1 );
   lsqline_put( lsqline, 1.2, 1.2 );
   lsqline_put( lsqline, 1.3, 1.3 );
   lsqline_put( lsqline, 1.4, 1.4 );
   lsqline_put( lsqline, 1.5, 1.5 );
   lsqline_put( lsqline, 1.6, 1.6 );
   lsqline_put( lsqline, 1.7, 1.7 );
   lsqline_put( lsqline, 1.8, 1.8 );
   lsqline_put( lsqline, 1.9, 1.9 );

   CU_ASSERT( lsqline_capacity( lsqline ) == 16 );

   lsqline_dispose( &lsqline );

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

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

