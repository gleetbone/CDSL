/**
 @file tuple_test_clone.c
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
   test_clone_1
*/

void test_clone_1( void )
{
   tuple_t *t = NULL;
   tuple_t *t1 = NULL;

   t = tuple_make( "tuple", 1, TUPLE_INT32_TYPE, "int32" );
   
   CU_ASSERT( t != NULL );

   t1 = tuple_clone( t );
   
   CU_ASSERT( t1 != NULL );

   tuple_dispose( &t );
   tuple_dispose( &t1 );
   
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

