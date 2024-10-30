/**
 @file tuple_test_string.c
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
   test_string_1
*/

void test_string_1( void )
{
   tuple_t *t = NULL;
   char_t *s = 0;
   int32_t count = 0;

   t = tuple_make( "tuple", 1, TUPLE_STRING_TYPE, "string", 32 );
   CU_ASSERT( t != NULL );
   
   tuple_put_string( t, 0, "13" );
   
   s = tuple_item_string( t, 0, &count );
   CU_ASSERT( strcmp( s, "13" ) == 0 );
   CU_ASSERT( count == 2 );
   free( s );
   
   tuple_dispose( &t );
   
   return;
}

/**
   test_string_2
*/

void test_string_2( void )
{
   tuple_t *t = NULL;
   char_t **astring = NULL;
   char_t **astringa = NULL;
   int32_t count = 0;
   int32_t length = 0;
   char_t *s = 0;

   t = tuple_make( "tuple", 1, TUPLE_ARRAY_STRING_TYPE, "astring", 32, 4 );
   CU_ASSERT( t != NULL );
   
   astring = ( char_t ** ) calloc( 4, sizeof( char_t *) );
   astring[0] = ( char_t * ) calloc( 32, sizeof( char_t ) );
   astring[1] = ( char_t * ) calloc( 32, sizeof( char_t ) );
   astring[2] = ( char_t * ) calloc( 32, sizeof( char_t ) );
   astring[3] = ( char_t * ) calloc( 32, sizeof( char_t ) );
   
   tuple_put_astring( t, 0, astring, 4, 32 );
   
   astringa = tuple_item_astring( t, 0, &count, &length );
   CU_ASSERT( astringa != NULL );
   CU_ASSERT( count == 4 );
   CU_ASSERT( length == 32 );
   CU_ASSERT( astringa[0] != NULL );
   CU_ASSERT( astringa[1] != NULL );
   CU_ASSERT( astringa[2] != NULL );
   CU_ASSERT( astringa[3] != NULL );

   tuple_put_element_astring( t, 0, 1, "13" );
   
   s = tuple_item_element_astring( t, 0, 1 );
   CU_ASSERT( strcmp( s, "13" ) == 0 );
   free( s );
   
   free( astring[0] );
   free( astring[1] );
   free( astring[2] );
   free( astring[3] );
   free( astring );
   
   free( astringa[0] );
   free( astringa[1] );
   free( astringa[2] );
   free( astringa[3] );
   free( astringa );
   
   tuple_dispose( &t );
   
   return;
}

int
add_test_string( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_string", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_string_1
   add_test_to_suite( p_suite, test_string_1, "test_string_1" );

   // test_string_2
   add_test_to_suite( p_suite, test_string_2, "test_string_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

