/**
 @file Matvec_test_vector_from_row.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Matvec_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Matvec_t

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "f_Matvec.h"
#include "d_Matvec.h"
#include "cf_Matvec.h"
#include "cd_Matvec.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_vector_from_row_1
*/

void test_vector_from_row_1( void )
{
   f_matvec_t *fm = NULL;
   f_matvec_t *v = NULL;

   fm = f_matvec_make_from_args( 3, 3, 9, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 );
   v = f_matvec_vector_from_row( fm, 2 );

   CU_ASSERT( fm != NULL );
   CU_ASSERT( v != NULL );
   CU_ASSERT( f_matvec_is_row_vector( v ) == 1 );
   CU_ASSERT( f_matvec_vector_item( v, 0 ) == 7.0 );
   CU_ASSERT( f_matvec_vector_item( v, 1 ) == 8.0 );
   CU_ASSERT( f_matvec_vector_item( v, 2 ) == 9.0 );

   f_matvec_dispose( &fm );
   f_matvec_dispose( &v );

   return;
}

/**
   test_vector_from_row_2
*/
void test_vector_from_row_2( void )
{
   d_matvec_t *dm = NULL;
   d_matvec_t *v = NULL;

   dm = d_matvec_make_from_args( 3, 3, 9, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 );
   v = d_matvec_vector_from_row( dm, 2 );

   CU_ASSERT( dm != NULL );
   CU_ASSERT( v != NULL );
   CU_ASSERT( d_matvec_is_row_vector( v ) == 1 );
   CU_ASSERT( d_matvec_vector_item( v, 0 ) == 7.0 );
   CU_ASSERT( d_matvec_vector_item( v, 1 ) == 8.0 );
   CU_ASSERT( d_matvec_vector_item( v, 2 ) == 9.0 );

   d_matvec_dispose( &dm );
   d_matvec_dispose( &v );

   return;
}


/**
   test_vector_from_row_3
*/

void test_vector_from_row_3( void )
{
   cf_matvec_t *cfm = NULL;
   cf_matvec_t *v = NULL;

   cfm = cf_matvec_make_from_args( 3, 3, 9, 1.0 + 1.0*I, 2.0 + 2.0*I, 3.0 + 3.0*I, 4.0 + 4.0*I, 5.0 + 5.0*I, 6.0 + 6.0*I, 7.0 + 7.0*I, 8.0 + 8.0*I, 9.0 + 9.0*I );
   v = cf_matvec_vector_from_row( cfm, 2 );

   CU_ASSERT( cfm != NULL );
   CU_ASSERT( v != NULL );
   CU_ASSERT( cf_matvec_is_row_vector( v ) == 1 );
   CU_ASSERT( cf_matvec_vector_item( v, 0 ) == 7.0 + 7.0*I );
   CU_ASSERT( cf_matvec_vector_item( v, 1 ) == 8.0 + 8.0*I );
   CU_ASSERT( cf_matvec_vector_item( v, 2 ) == 9.0 + 9.0*I );

   cf_matvec_dispose( &cfm );
   cf_matvec_dispose( &v );

   return;
}

/**
   test_vector_from_row_4
*/

void test_vector_from_row_4( void )
{
   cd_matvec_t *cdm = NULL;
   cd_matvec_t *v = NULL;

   cdm = cd_matvec_make_from_args( 3, 3, 9, 1.0 + 1.0*I, 2.0 + 2.0*I, 3.0 + 3.0*I, 4.0 + 4.0*I, 5.0 + 5.0*I, 6.0 + 6.0*I, 7.0 + 7.0*I, 8.0 + 8.0*I, 9.0 + 9.0*I );
   v = cd_matvec_vector_from_row( cdm, 2 );

   CU_ASSERT( cdm != NULL );
   CU_ASSERT( v != NULL );
   CU_ASSERT( cd_matvec_is_row_vector( v ) == 1 );
   CU_ASSERT( cd_matvec_vector_item( v, 0 ) == 7.0 + 7.0*I );
   CU_ASSERT( cd_matvec_vector_item( v, 1 ) == 8.0 + 8.0*I );
   CU_ASSERT( cd_matvec_vector_item( v, 2 ) == 9.0 + 9.0*I );

   cd_matvec_dispose( &cdm );
   cd_matvec_dispose( &v );

   return;
}

int
add_test_vector_from_row( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_vector_from_row", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_vector_from_row_1
   add_test_to_suite( p_suite, test_vector_from_row_1, "test_vector_from_row_1" );

   // test_vector_from_row_2
   add_test_to_suite( p_suite, test_vector_from_row_2, "test_vector_from_row_2" );

   // test_vector_from_row_3
   add_test_to_suite( p_suite, test_vector_from_row_3, "test_vector_from_row_3" );

   // test_vector_from_row_4
   add_test_to_suite( p_suite, test_vector_from_row_4, "test_vector_from_row_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

