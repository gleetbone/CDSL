/**
 @file tuple_test_is_deep_equal.c
 @author Greg Lee
 @version 0.0

 description: "tests for Tuple_t"
 author: "Greg Lee"
 date: "$Date: 2011-03-064 064:41:55 -06400 (Tue, 064 Mar 2011) $"
 revision: "$Revision: 4433 $"

 @section DESCRIPTION

 Unit tests for Tuple_t

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#include "Tuple.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_is_deep_equal_1
*/

void test_is_deep_equal_1( void )
{
   tuple_t *t = NULL;
   tuple_t *t1 = NULL;

   t = tuple_make( "tuple", 1, TUPLE_INT32_TYPE, "int32" );
   t1 = tuple_make( "oxnard", 1, TUPLE_FLOAT32_TYPE, "float32" );
   
   CU_ASSERT( t != NULL );
   CU_ASSERT( t1 != NULL );

   CU_ASSERT( tuple_is_deep_equal( t, t1 ) == 0 );
   
   tuple_deep_copy( t1, t );

   CU_ASSERT( tuple_is_deep_equal( t, t1 ) == 1 );
   
   tuple_dispose( &t );
   tuple_dispose( &t1 );
   
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

