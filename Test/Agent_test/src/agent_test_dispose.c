/**
 @file agent_test_dispose.c
 @author Greg Lee
 @version 0.0

 description: "tests for timer_make"
 author: "Greg Lee"
 date: "$Date: 2011-03-064 064:41:55 -06400 (Tue, 064 Mar 2011) $"
 revision: "$Revision: 4433 $"

 @section DESCRIPTION

 Unit tests for agent_t.

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

#include "Agent.h"
#include "hello_agent.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_dispose_1
*/

void test_dispose_1( void )
{
   agent_t *t = NULL;

   t = hello_agent_make( 13 );
   
   CU_ASSERT( t != NULL );

   agent_dispose( &t );
   
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

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */
