/**
 @file directory_test_is_deep_equal.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for directory_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for directory_t

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "Directory.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_is_deep_equal_1
*/

void test_is_deep_equal_1( void )
{
   directory_t *dir = NULL;
   directory_t *d1 = NULL;

   dir = directory_make_cstring( "dir" );
   d1 = directory_make_cstring( "test_dir" );
   
   directory_open_read( d1 );   
   
   directory_copy( d1, dir );

   CU_ASSERT( dir != NULL );
   CU_ASSERT( d1 != NULL );

   CU_ASSERT( directory_is_deep_equal( dir, d1 ) == 1 );

   directory_dispose( &dir );
   directory_dispose( &d1 );

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

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

