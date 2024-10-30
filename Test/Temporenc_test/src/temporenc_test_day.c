/**
 @file temporenc_test_day.c
 @author Greg Lee
 @version 0.0

 description: "tests for Temporenc_t"
 author: "Greg Lee"
 date: "$Date: 2011-03-064 064:41:55 -06400 (Tue, 064 Mar 2011) $"
 revision: "$Revision: 4433 $"

 @section DESCRIPTION

 Unit tests for Temporenc_t

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

#include "Temporenc.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_day_1
*/

void test_day_1( void )
{
   temporenc_t *t = NULL;

   t = temporenc_make( 2020, 6, 7, 12, 15, 30, 123, 1, 1, 0, 0 );
   
   CU_ASSERT( temporenc_day( t ) == 7 );
   
   temporenc_dispose( &t );
   
   return;
}

/**
   test_day_2
*/

void test_day_2( void )
{
   temporenc_t *t = NULL;

   t = temporenc_make( 2020, 6, 31, 12, 15, 30, 123, 1, 1, 0, 0 );
   
   CU_ASSERT( temporenc_day( t ) == 0 );
   CU_ASSERT( temporenc_day_is_undefined( t ) == 1 );
   
   temporenc_dispose( &t );
   
   return;
}

/**
   test_day_3
*/

void test_day_3( void )
{
   temporenc_t *t = NULL;

   t = temporenc_make( 2020, 6, 7, 12, 15, 30, 123, 1, 1, 0, 0 );
   
   temporenc_put_day( t, 9 );
   CU_ASSERT( temporenc_day( t ) == 9 );
   CU_ASSERT( temporenc_day_is_undefined( t ) == 0 );
   
   temporenc_put_day( t, 31 );
   CU_ASSERT( temporenc_day( t ) == 0 );
   CU_ASSERT( temporenc_day_is_undefined( t ) == 1 );
   
   temporenc_dispose( &t );
   
   return;
}

/**
   test_day_4
*/

void test_day_4( void )
{
   temporenc_t *t = NULL;

   t = temporenc_make( 2020, 6, 7, 12, 15, 30, 123, 1, 1, 0, 0 );
   
   temporenc_set_day_is_undefined( t );
   CU_ASSERT( temporenc_day_is_undefined( t ) == 1 );
   
   temporenc_dispose( &t );
   
   return;
}

int
add_test_day( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_day", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_day_1
   add_test_to_suite( p_suite, test_day_1, "test_day_1" );

   // test_day_2
   add_test_to_suite( p_suite, test_day_2, "test_day_2" );

   // test_day_3
   add_test_to_suite( p_suite, test_day_3, "test_day_3" );

   // test_day_4
   add_test_to_suite( p_suite, test_day_4, "test_day_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

