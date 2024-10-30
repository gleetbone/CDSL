/**
 @file Svd_test_reconstructed_input.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Svd_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Svd_make.

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

#include "f_Svd.h"
#include "d_Svd.h"
#include "cf_Svd.h"
#include "cd_Svd.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_reconstructed_input_1
*/

void test_reconstructed_input_1( void )
{
   f_svd_t *fsvd = NULL;
   f_matvec_t *m = NULL;
   f_matvec_t *lsv = NULL;
   f_matvec_t *rsv = NULL;
   f_matvec_t *sv = NULL;
   f_matvec_t *rm = NULL;

   fsvd = f_svd_make();
   m = f_matvec_make_from_args( 2, 2, 4, 1.0, 0.0, 0.0, 1.0 );
   lsv = f_matvec_make_from_args( 2, 2, 4, 1.0, 0.0, 0.0, 1.0 );
   rsv = f_matvec_make_from_args( 2, 2, 4, 1.0, 0.0, 0.0, 1.0 );
   sv = f_matvec_make_from_args( 2, 1, 2, 1.0, 1.0 );
   f_svd_set_input( fsvd, m );
   f_svd_svd( fsvd );
   rm = f_svd_reconstructed_input( fsvd );

   CU_ASSERT( fsvd != NULL );
   CU_ASSERT( m != NULL );

   CU_ASSERT( f_matvec_is_approximately_equal( f_svd_left_singular_vectors( fsvd ), lsv, 0.000001 ) == 1 );
   CU_ASSERT( f_matvec_is_approximately_equal( f_svd_right_singular_vectors( fsvd ), rsv, 0.000001 ) == 1 );
   CU_ASSERT( f_matvec_is_approximately_equal( f_svd_singular_values( fsvd ), sv, 0.000001 ) == 1 );
   CU_ASSERT( f_matvec_is_approximately_equal( rm, m, 0.000001 ) == 1 );

   f_svd_deep_dispose( &fsvd );
   f_matvec_dispose( &lsv );
   f_matvec_dispose( &rsv );
   f_matvec_dispose( &sv );
   f_matvec_dispose( &rm );


   fsvd = f_svd_make();
   m = f_matvec_make_from_args( 2, 3, 6, 1.0, 0.0, 0.0, 0.0, 2.0, 0.0 );
   lsv = f_matvec_make_from_args( 2, 2, 4, 0.0, 1.0, 1.0, 0.0 );
   rsv = f_matvec_make_from_args( 2, 3, 6, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0 );
   sv = f_matvec_make_from_args( 2, 1, 2, 2.0, 1.0 );
   f_svd_set_input( fsvd, m );
   f_svd_svd( fsvd );
   rm = f_svd_reconstructed_input( fsvd );

   CU_ASSERT( fsvd != NULL );
   CU_ASSERT( m != NULL );

   CU_ASSERT( f_matvec_is_approximately_equal( f_svd_left_singular_vectors( fsvd ), lsv, 0.000001 ) == 1 );
   CU_ASSERT( f_matvec_is_approximately_equal( f_svd_right_singular_vectors( fsvd ), rsv, 0.000001 ) == 1 );
   CU_ASSERT( f_matvec_is_approximately_equal( f_svd_singular_values( fsvd ), sv, 0.000001 ) == 1 );
   CU_ASSERT( f_matvec_is_approximately_equal( rm, m, 0.000001 ) == 1 );

   f_svd_deep_dispose( &fsvd );
   f_matvec_dispose( &lsv );
   f_matvec_dispose( &rsv );
   f_matvec_dispose( &sv );
   f_matvec_dispose( &rm );



   fsvd = f_svd_make();
   m = f_matvec_make_from_args( 2, 2, 4, 1.0, 0.0, 1.0, 2.0 );
   lsv = f_matvec_make_from_args( 2, 2, 4, 0.229752920547, 0.973248989468, 0.973248989468, -0.229752920547 );
   rsv = f_matvec_make_from_args( 2, 2, 4, 0.525731112119, 0.850650808352, 0.850650808352, -0.525731112119 );
   sv = f_matvec_make_from_args( 2, 1, 2, 2.288245611271, 0.874032048898 );
   f_svd_set_input( fsvd, m );
   f_svd_svd( fsvd );
   rm = f_svd_reconstructed_input( fsvd );

   CU_ASSERT( fsvd != NULL );
   CU_ASSERT( m != NULL );

   CU_ASSERT( f_matvec_is_approximately_equal( f_svd_left_singular_vectors( fsvd ), lsv, 0.000001 ) == 1 );
   CU_ASSERT( f_matvec_is_approximately_equal( f_svd_right_singular_vectors( fsvd ), rsv, 0.000001 ) == 1 );
   CU_ASSERT( f_matvec_is_approximately_equal( f_svd_singular_values( fsvd ), sv, 0.000001 ) == 1 );
   CU_ASSERT( f_matvec_is_approximately_equal( rm, m, 0.000001 ) == 1 );

   f_svd_deep_dispose( &fsvd );
   f_matvec_dispose( &lsv );
   f_matvec_dispose( &rsv );
   f_matvec_dispose( &sv );
   f_matvec_dispose( &rm );

   fsvd = f_svd_make();
   m = f_matvec_make_from_args( 3, 2, 6, 2.0, 0.0, 0.5, 1.0, 1.0, 0.0 );
   lsv = f_matvec_make_from_args( 3, 2, 6, 0.862298672496, -0.237573145392, 0.265614851363, 0.964079224304, 0.431149336248, -0.118786572696 );
   rsv = f_matvec_make_from_args( 2, 2, 4, 0.993332061381, -0.115288402857, 0.115288402857, 0.993332061381 );
   sv = f_matvec_make_from_args( 2, 1, 2, 2.303916480598, 0.970550797449 );
   f_svd_set_input( fsvd, m );
   f_svd_svd( fsvd );
   rm = f_svd_reconstructed_input( fsvd );

   CU_ASSERT( fsvd != NULL );
   CU_ASSERT( m != NULL );

   CU_ASSERT( f_matvec_is_approximately_equal( f_svd_left_singular_vectors( fsvd ), lsv, 0.000001 ) == 1 );
   CU_ASSERT( f_matvec_is_approximately_equal( f_svd_right_singular_vectors( fsvd ), rsv, 0.000001 ) == 1 );
   CU_ASSERT( f_matvec_is_approximately_equal( f_svd_singular_values( fsvd ), sv, 0.000001 ) == 1 );
   CU_ASSERT( f_matvec_is_approximately_equal( rm, m, 0.000001 ) == 1 );

   f_svd_deep_dispose( &fsvd );
   f_matvec_dispose( &lsv );
   f_matvec_dispose( &rsv );
   f_matvec_dispose( &sv );
   f_matvec_dispose( &rm );


   fsvd = f_svd_make();
   m = f_matvec_make_from_args( 2, 3, 6, 2.0, 0.5, 1.0, 0.0, 1.0, 0.0 );
   lsv = f_matvec_make_from_args( 2, 2, 4, 0.993332061381, 0.115288402857, -0.115288402857, 0.993332061381 );
   rsv = f_matvec_make_from_args( 2, 3, 6, 0.862298672496, 0.265614851363, 0.431149336248, -0.237573145392, 0.964079224304, -0.118786572696 );
   sv = f_matvec_make_from_args( 2, 1, 2, 2.303916480598, 0.970550797449 );
   f_svd_set_input( fsvd, m );
   f_svd_svd( fsvd );
   rm = f_svd_reconstructed_input( fsvd );

   CU_ASSERT( fsvd != NULL );
   CU_ASSERT( m != NULL );

   CU_ASSERT( f_matvec_is_approximately_equal( f_svd_left_singular_vectors( fsvd ), lsv, 0.000001 ) == 1 );
   CU_ASSERT( f_matvec_is_approximately_equal( f_svd_right_singular_vectors( fsvd ), rsv, 0.000001 ) == 1 );
   CU_ASSERT( f_matvec_is_approximately_equal( f_svd_singular_values( fsvd ), sv, 0.000001 ) == 1 );
   CU_ASSERT( f_matvec_is_approximately_equal( rm, m, 0.000001 ) == 1 );

   f_svd_deep_dispose( &fsvd );
   f_matvec_dispose( &lsv );
   f_matvec_dispose( &rsv );
   f_matvec_dispose( &sv );
   f_matvec_dispose( &rm );

   return;
}

/**
   test_reconstructed_input_2
*/
void test_reconstructed_input_2( void )
{
   d_svd_t *dsvd = NULL;
   d_matvec_t *m = NULL;
   d_matvec_t *lsv = NULL;
   d_matvec_t *rsv = NULL;
   d_matvec_t *sv = NULL;
   d_matvec_t *rm = NULL;

   dsvd = d_svd_make();
   m = d_matvec_make_from_args( 2, 2, 4, 1.0, 0.0, 0.0, 1.0 );
   lsv = d_matvec_make_from_args( 2, 2, 4, 1.0, 0.0, 0.0, 1.0 );
   rsv = d_matvec_make_from_args( 2, 2, 4, 1.0, 0.0, 0.0, 1.0 );
   sv = d_matvec_make_from_args( 2, 1, 2, 1.0, 1.0 );
   d_svd_set_input( dsvd, m );
   d_svd_svd( dsvd );
   rm = d_svd_reconstructed_input( dsvd );

   CU_ASSERT( dsvd != NULL );
   CU_ASSERT( m != NULL );

   CU_ASSERT( d_matvec_is_approximately_equal( d_svd_left_singular_vectors( dsvd ), lsv, 0.000001 ) == 1 );
   CU_ASSERT( d_matvec_is_approximately_equal( d_svd_right_singular_vectors( dsvd ), rsv, 0.000001 ) == 1 );
   CU_ASSERT( d_matvec_is_approximately_equal( d_svd_singular_values( dsvd ), sv, 0.000001 ) == 1 );
   CU_ASSERT( d_matvec_is_approximately_equal( rm, m, 0.000001 ) == 1 );

   d_svd_deep_dispose( &dsvd );
   d_matvec_dispose( &lsv );
   d_matvec_dispose( &rsv );
   d_matvec_dispose( &sv );
   d_matvec_dispose( &rm );

   
   dsvd = d_svd_make();
   m = d_matvec_make_from_args( 2, 3, 6, 1.0, 0.0, 0.0, 0.0, 2.0, 0.0 );
   lsv = d_matvec_make_from_args( 2, 2, 4, 0.0, 1.0, 1.0, 0.0 );
   rsv = d_matvec_make_from_args( 2, 3, 6, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0 );
   sv = d_matvec_make_from_args( 2, 1, 2, 2.0, 1.0 );
   d_svd_set_input( dsvd, m );
   d_svd_svd( dsvd );
   rm = d_svd_reconstructed_input( dsvd );

   CU_ASSERT( dsvd != NULL );
   CU_ASSERT( m != NULL );

   CU_ASSERT( d_matvec_is_approximately_equal( d_svd_left_singular_vectors( dsvd ), lsv, 0.000001 ) == 1 );
   CU_ASSERT( d_matvec_is_approximately_equal( d_svd_right_singular_vectors( dsvd ), rsv, 0.000001 ) == 1 );
   CU_ASSERT( d_matvec_is_approximately_equal( d_svd_singular_values( dsvd ), sv, 0.000001 ) == 1 );
   CU_ASSERT( d_matvec_is_approximately_equal( rm, m, 0.000001 ) == 1 );

   d_svd_deep_dispose( &dsvd );
   d_matvec_dispose( &lsv );
   d_matvec_dispose( &rsv );
   d_matvec_dispose( &sv );
   d_matvec_dispose( &rm );

   
   dsvd = d_svd_make();
   m = d_matvec_make_from_args( 2, 2, 4, 1.0, 0.0, 1.0, 2.0 );
   lsv = d_matvec_make_from_args( 2, 2, 4, 0.229752920547, 0.973248989468, 0.973248989468, -0.229752920547 );
   rsv = d_matvec_make_from_args( 2, 2, 4, 0.525731112119, 0.850650808352, 0.850650808352, -0.525731112119 );
   sv = d_matvec_make_from_args( 2, 1, 2, 2.288245611271, 0.874032048898 );
   d_svd_set_input( dsvd, m );
   d_svd_svd( dsvd );
   rm = d_svd_reconstructed_input( dsvd );

   CU_ASSERT( dsvd != NULL );
   CU_ASSERT( m != NULL );

   CU_ASSERT( d_matvec_is_approximately_equal( d_svd_left_singular_vectors( dsvd ), lsv, 0.000001 ) == 1 );
   CU_ASSERT( d_matvec_is_approximately_equal( d_svd_right_singular_vectors( dsvd ), rsv, 0.000001 ) == 1 );
   CU_ASSERT( d_matvec_is_approximately_equal( d_svd_singular_values( dsvd ), sv, 0.000001 ) == 1 );
   CU_ASSERT( d_matvec_is_approximately_equal( rm, m, 0.000001 ) == 1 );

   d_svd_deep_dispose( &dsvd );
   d_matvec_dispose( &lsv );
   d_matvec_dispose( &rsv );
   d_matvec_dispose( &sv );
   d_matvec_dispose( &rm );

   dsvd = d_svd_make();
   m = d_matvec_make_from_args( 3, 2, 6, 2.0, 0.0, 0.5, 1.0, 1.0, 0.0 );
   lsv = d_matvec_make_from_args( 3, 2, 6, 0.862298672496, -0.237573145392, 0.265614851363, 0.964079224304, 0.431149336248, -0.118786572696 );
   rsv = d_matvec_make_from_args( 2, 2, 4, 0.993332061381, -0.115288402857, 0.115288402857, 0.993332061381 );
   sv = d_matvec_make_from_args( 2, 1, 2, 2.303916480598, 0.970550797449 );
   d_svd_set_input( dsvd, m );
   d_svd_svd( dsvd );
   rm = d_svd_reconstructed_input( dsvd );

   CU_ASSERT( dsvd != NULL );
   CU_ASSERT( m != NULL );

   CU_ASSERT( d_matvec_is_approximately_equal( d_svd_left_singular_vectors( dsvd ), lsv, 0.000001 ) == 1 );
   CU_ASSERT( d_matvec_is_approximately_equal( d_svd_right_singular_vectors( dsvd ), rsv, 0.000001 ) == 1 );
   CU_ASSERT( d_matvec_is_approximately_equal( d_svd_singular_values( dsvd ), sv, 0.000001 ) == 1 );
   CU_ASSERT( d_matvec_is_approximately_equal( rm, m, 0.000001 ) == 1 );

   d_svd_deep_dispose( &dsvd );
   d_matvec_dispose( &lsv );
   d_matvec_dispose( &rsv );
   d_matvec_dispose( &sv );
   d_matvec_dispose( &rm );


   dsvd = d_svd_make();
   m = d_matvec_make_from_args( 2, 3, 6, 2.0, 0.5, 1.0, 0.0, 1.0, 0.0 );
   lsv = d_matvec_make_from_args( 2, 2, 4, 0.993332061381, 0.115288402857, -0.115288402857, 0.993332061381 );
   rsv = d_matvec_make_from_args( 2, 3, 6, 0.862298672496, 0.265614851363, 0.431149336248, -0.237573145392, 0.964079224304, -0.118786572696 );
   sv = d_matvec_make_from_args( 2, 1, 2, 2.303916480598, 0.970550797449 );
   d_svd_set_input( dsvd, m );
   d_svd_svd( dsvd );
   rm = d_svd_reconstructed_input( dsvd );

   CU_ASSERT( dsvd != NULL );
   CU_ASSERT( m != NULL );

   CU_ASSERT( d_matvec_is_approximately_equal( d_svd_left_singular_vectors( dsvd ), lsv, 0.000001 ) == 1 );
   CU_ASSERT( d_matvec_is_approximately_equal( d_svd_right_singular_vectors( dsvd ), rsv, 0.000001 ) == 1 );
   CU_ASSERT( d_matvec_is_approximately_equal( d_svd_singular_values( dsvd ), sv, 0.000001 ) == 1 );
   CU_ASSERT( d_matvec_is_approximately_equal( rm, m, 0.000001 ) == 1 );

   d_svd_deep_dispose( &dsvd );
   d_matvec_dispose( &lsv );
   d_matvec_dispose( &rsv );
   d_matvec_dispose( &sv );
   d_matvec_dispose( &rm );

   return;
}


/**
   test_reconstructed_input_3
*/

void test_reconstructed_input_3( void )
{
   cf_svd_t *cfsvd = NULL;
   cf_matvec_t *m = NULL;
   cf_matvec_t *lsv = NULL;
   cf_matvec_t *rsv = NULL;
   cf_matvec_t *sv = NULL;
   cf_matvec_t *rm = NULL;

   cfsvd = cf_svd_make();
   m = cf_matvec_make_from_args( 2, 2, 4, 1.0 + 0.0*I, 0.0 + 0.0*I, 0.0 + 0.0*I, 1.0 + 0.0*I );
   lsv = cf_matvec_make_from_args( 2, 2, 4, 1.0 + 0.0*I, 0.0 + 0.0*I, 0.0 + 0.0*I, 1.0 + 0.0*I );
   rsv = cf_matvec_make_from_args( 2, 2, 4, 1.0 + 0.0*I, 0.0 + 0.0*I, 0.0 + 0.0*I, 1.0 + 0.0*I );
   sv = cf_matvec_make_from_args( 2, 1, 2, 1.0 + 0.0*I, 1.0 + 0.0*I );
   cf_svd_set_input( cfsvd, m );
   cf_svd_svd( cfsvd );
   rm = cf_svd_reconstructed_input( cfsvd );

   CU_ASSERT( cfsvd != NULL );
   CU_ASSERT( m != NULL );

   CU_ASSERT( cf_matvec_is_approximately_equal( cf_svd_left_singular_vectors( cfsvd ), lsv, 0.000001 ) == 1 );
   CU_ASSERT( cf_matvec_is_approximately_equal( cf_svd_right_singular_vectors( cfsvd ), rsv, 0.000001 ) == 1 );
   CU_ASSERT( cf_matvec_is_approximately_equal( cf_svd_singular_values( cfsvd ), sv, 0.000001 ) == 1 );
   CU_ASSERT( cf_matvec_is_approximately_equal( rm, m, 0.000001 ) == 1 );

   cf_svd_deep_dispose( &cfsvd );
   cf_matvec_dispose( &lsv );
   cf_matvec_dispose( &rsv );
   cf_matvec_dispose( &sv );
   cf_matvec_dispose( &rm );

   
   cfsvd = cf_svd_make();
   m = cf_matvec_make_from_args( 2, 3, 6, 1.0 + 0.0*I, 0.0 + 0.0*I, 0.0 + 0.0*I, 0.0 + 0.0*I, 2.0 + 0.0*I, 0.0 + 0.0*I );
   lsv = cf_matvec_make_from_args( 2, 2, 4, 0.0 + 0.0*I, 1.0 + 0.0*I, 1.0 + 0.0*I, 0.0 + 0.0*I );
   rsv = cf_matvec_make_from_args( 2, 3, 6, 0.0 + 0.0*I, 1.0 + 0.0*I, 0.0 + 0.0*I, 1.0 + 0.0*I, 0.0 + 0.0*I, 0.0 + 0.0*I );
   sv = cf_matvec_make_from_args( 2, 1, 2, 2.0 + 0.0*I, 1.0 + 0.0*I );
   cf_svd_set_input( cfsvd, m );
   cf_svd_svd( cfsvd );
   rm = cf_svd_reconstructed_input( cfsvd );

   CU_ASSERT( cfsvd != NULL );
   CU_ASSERT( m != NULL );

   CU_ASSERT( cf_matvec_is_approximately_equal( cf_svd_left_singular_vectors( cfsvd ), lsv, 0.000001 ) == 1 );
   CU_ASSERT( cf_matvec_is_approximately_equal( cf_svd_right_singular_vectors( cfsvd ), rsv, 0.000001 ) == 1 );
   CU_ASSERT( cf_matvec_is_approximately_equal( cf_svd_singular_values( cfsvd ), sv, 0.000001 ) == 1 );
   CU_ASSERT( cf_matvec_is_approximately_equal( rm, m, 0.000001 ) == 1 );

   cf_svd_deep_dispose( &cfsvd );
   cf_matvec_dispose( &lsv );
   cf_matvec_dispose( &rsv );
   cf_matvec_dispose( &sv );
   cf_matvec_dispose( &rm );

   
   cfsvd = cf_svd_make();
   m = cf_matvec_make_from_args( 2, 2, 4, 0.0 + 2.0*I, 0.0 + 1.0*I, 0.0 + 0.0*I, 0.0 + 1.0*I );
   lsv = cf_matvec_make_from_args( 2, 2, 4, 0.000000000000 + 0.973248989468*I, 0.000000000000 - 0.229752920547*I, 0.000000000000 + 0.229752920547*I, 0.000000000000 + 0.973248989468*I );
   rsv = cf_matvec_make_from_args( 2, 2, 4, 0.850650808352 + 0.000000000000*I, -0.525731112119 + 0.000000000000*I, 0.525731112119 + 0.000000000000*I, 0.850650808352 + 0.000000000000*I );
   sv = cf_matvec_make_from_args( 2, 1, 2, 2.288245611271 + 0.0*I, 0.874032048898 + 0.0*I );
   cf_svd_set_input( cfsvd, m );
   cf_svd_svd( cfsvd );
   rm = cf_svd_reconstructed_input( cfsvd );

   CU_ASSERT( cfsvd != NULL );
   CU_ASSERT( m != NULL );

   CU_ASSERT( cf_matvec_is_approximately_equal( cf_svd_left_singular_vectors( cfsvd ), lsv, 0.000001 ) == 1 );
   CU_ASSERT( cf_matvec_is_approximately_equal( cf_svd_right_singular_vectors( cfsvd ), rsv, 0.000001 ) == 1 );
   CU_ASSERT( cf_matvec_is_approximately_equal( cf_svd_singular_values( cfsvd ), sv, 0.000001 ) == 1 );
   CU_ASSERT( cf_matvec_is_approximately_equal( rm, m, 0.000001 ) == 1 );

   cf_svd_deep_dispose( &cfsvd );
   cf_matvec_dispose( &lsv );
   cf_matvec_dispose( &rsv );
   cf_matvec_dispose( &sv );
   cf_matvec_dispose( &rm );

   cfsvd = cf_svd_make();
   m = cf_matvec_make_from_args( 3, 2, 6, 2.1 + 0.0*I, 1.3 + 0.0*I, -0.5 + 0.0*I, -2.9 + 0.0*I, 0.8 + 0.0*I, -1.3 + 0.0*I );
   lsv
      =  cf_matvec_make_from_args
         (
            3, 2, 6,
            0.5514080664088562  + 0.000000000000*I, 0.72686913267302133 + 0.000000000000*I,
           -0.79576027353432999 + 0.000000000000*I, 0.31096469860907316 + 0.000000000000*I,
           -0.25042909448347817 + 0.000000000000*I, 0.61234158782997772 + 0.000000000000*I
         );
   rsv = cf_matvec_make_from_args( 2, 2, 4, 0.375074729372 + 0.000000000000*I, 0.926994577862 + 0.000000000000*I, 0.926994577862 + 0.000000000000*I, -0.375074729372 + 0.000000000000*I );
   sv = cf_matvec_make_from_args( 2, 1, 2, 3.6139296117084276 + 0.0*I, 2.0073646309569595 + 0.0*I );
   cf_svd_set_input( cfsvd, m );
   cf_svd_svd( cfsvd );
   rm = cf_svd_reconstructed_input( cfsvd );

   CU_ASSERT( cfsvd != NULL );
   CU_ASSERT( m != NULL );

   CU_ASSERT( cf_matvec_is_approximately_equal( cf_svd_left_singular_vectors( cfsvd ), lsv, 0.000001 ) == 1 );
   CU_ASSERT( cf_matvec_is_approximately_equal( cf_svd_right_singular_vectors( cfsvd ), rsv, 0.000001 ) == 1 );
   CU_ASSERT( cf_matvec_is_approximately_equal( cf_svd_singular_values( cfsvd ), sv, 0.000001 ) == 1 );
   CU_ASSERT( cf_matvec_is_approximately_equal( rm, m, 0.000001 ) == 1 );

   cf_svd_deep_dispose( &cfsvd );
   cf_matvec_dispose( &lsv );
   cf_matvec_dispose( &rsv );
   cf_matvec_dispose( &sv );
   cf_matvec_dispose( &rm );


   cfsvd = cf_svd_make();
   m = cf_matvec_make_from_args( 2, 3, 6, 2.0 + 0.0*I, 0.5 + 0.0*I, 1.0 + 0.0*I, 0.0 + 0.0*I, 1.0 + 0.0*I, 0.0 + 0.0*I );
   lsv = cf_matvec_make_from_args( 2, 2, 4, 0.993332061381 + 0.0*I, 0.115288402857 + 0.0*I, -0.115288402857 + 0.0*I, 0.993332061381 + 0.0*I );
   rsv = cf_matvec_make_from_args( 2, 3, 6, 0.862298672496 + 0.0*I, 0.265614851363 + 0.0*I, 0.431149336248 + 0.0*I, -0.237573145392 + 0.0*I, 0.964079224304 + 0.0*I, -0.118786572696 + 0.0*I );
   sv = cf_matvec_make_from_args( 2, 1, 2, 2.303916480598 + 0.0*I, 0.970550797449 + 0.0*I );
   cf_svd_set_input( cfsvd, m );
   cf_svd_svd( cfsvd );
   rm = cf_svd_reconstructed_input( cfsvd );

   CU_ASSERT( cfsvd != NULL );
   CU_ASSERT( m != NULL );

   CU_ASSERT( cf_matvec_is_approximately_equal( cf_svd_left_singular_vectors( cfsvd ), lsv, 0.000001 ) == 1 );
   CU_ASSERT( cf_matvec_is_approximately_equal( cf_svd_right_singular_vectors( cfsvd ), rsv, 0.000001 ) == 1 );
   CU_ASSERT( cf_matvec_is_approximately_equal( cf_svd_singular_values( cfsvd ), sv, 0.000001 ) == 1 );
   CU_ASSERT( cf_matvec_is_approximately_equal( rm, m, 0.000001 ) == 1 );

   cf_svd_deep_dispose( &cfsvd );
   cf_matvec_dispose( &lsv );
   cf_matvec_dispose( &rsv );
   cf_matvec_dispose( &sv );
   cf_matvec_dispose( &rm );

   return;
}

/**
   test_reconstructed_input_4
*/

void test_reconstructed_input_4( void )
{
   cd_svd_t *cdsvd = NULL;
   cd_matvec_t *m = NULL;
   cd_matvec_t *lsv = NULL;
   cd_matvec_t *rsv = NULL;
   cd_matvec_t *sv = NULL;
   cd_matvec_t *rm = NULL;

   cdsvd = cd_svd_make();
   m = cd_matvec_make_from_args( 2, 2, 4, 1.0 + 0.0*I, 0.0 + 0.0*I, 0.0 + 0.0*I, 1.0 + 0.0*I );
   lsv = cd_matvec_make_from_args( 2, 2, 4, 1.0 + 0.0*I, 0.0 + 0.0*I, 0.0 + 0.0*I, 1.0 + 0.0*I );
   rsv = cd_matvec_make_from_args( 2, 2, 4, 1.0 + 0.0*I, 0.0 + 0.0*I, 0.0 + 0.0*I, 1.0 + 0.0*I );
   sv = cd_matvec_make_from_args( 2, 1, 2, 1.0 + 0.0*I, 1.0 + 0.0*I );
   cd_svd_set_input( cdsvd, m );
   cd_svd_svd( cdsvd );
   rm = cd_svd_reconstructed_input( cdsvd );

   CU_ASSERT( cdsvd != NULL );
   CU_ASSERT( m != NULL );

   CU_ASSERT( cd_matvec_is_approximately_equal( cd_svd_left_singular_vectors( cdsvd ), lsv, 0.000001 ) == 1 );
   CU_ASSERT( cd_matvec_is_approximately_equal( cd_svd_right_singular_vectors( cdsvd ), rsv, 0.000001 ) == 1 );
   CU_ASSERT( cd_matvec_is_approximately_equal( cd_svd_singular_values( cdsvd ), sv, 0.000001 ) == 1 );
   CU_ASSERT( cd_matvec_is_approximately_equal( rm, m, 0.000001 ) == 1 );

   cd_svd_deep_dispose( &cdsvd );
   cd_matvec_dispose( &lsv );
   cd_matvec_dispose( &rsv );
   cd_matvec_dispose( &sv );
   cd_matvec_dispose( &rm );

   
   cdsvd = cd_svd_make();
   m = cd_matvec_make_from_args( 2, 3, 6, 1.0 + 0.0*I, 0.0 + 0.0*I, 0.0 + 0.0*I, 0.0 + 0.0*I, 2.0 + 0.0*I, 0.0 + 0.0*I );
   lsv = cd_matvec_make_from_args( 2, 2, 4, 0.0 + 0.0*I, 1.0 + 0.0*I, 1.0 + 0.0*I, 0.0 + 0.0*I );
   rsv = cd_matvec_make_from_args( 2, 3, 6, 0.0 + 0.0*I, 1.0 + 0.0*I, 0.0 + 0.0*I, 1.0 + 0.0*I, 0.0 + 0.0*I, 0.0 + 0.0*I );
   sv = cd_matvec_make_from_args( 2, 1, 2, 2.0 + 0.0*I, 1.0 + 0.0*I );
   cd_svd_set_input( cdsvd, m );
   cd_svd_svd( cdsvd );
   rm = cd_svd_reconstructed_input( cdsvd );

   CU_ASSERT( cdsvd != NULL );
   CU_ASSERT( m != NULL );

   CU_ASSERT( cd_matvec_is_approximately_equal( cd_svd_left_singular_vectors( cdsvd ), lsv, 0.000001 ) == 1 );
   CU_ASSERT( cd_matvec_is_approximately_equal( cd_svd_right_singular_vectors( cdsvd ), rsv, 0.000001 ) == 1 );
   CU_ASSERT( cd_matvec_is_approximately_equal( cd_svd_singular_values( cdsvd ), sv, 0.000001 ) == 1 );
   CU_ASSERT( cd_matvec_is_approximately_equal( rm, m, 0.000001 ) == 1 );

   cd_svd_deep_dispose( &cdsvd );
   cd_matvec_dispose( &lsv );
   cd_matvec_dispose( &rsv );
   cd_matvec_dispose( &sv );
   cd_matvec_dispose( &rm );

   
   cdsvd = cd_svd_make();
   m = cd_matvec_make_from_args( 2, 2, 4, 0.0 + 2.0*I, 0.0 + 1.0*I, 0.0 + 0.0*I, 0.0 + 1.0*I );
   lsv = cd_matvec_make_from_args( 2, 2, 4, 0.000000000000 + 0.973248989468*I, 0.000000000000 - 0.229752920547*I, 0.000000000000 + 0.229752920547*I, 0.000000000000 + 0.973248989468*I );
   rsv = cd_matvec_make_from_args( 2, 2, 4, 0.850650808352 + 0.000000000000*I, -0.525731112119 + 0.000000000000*I, 0.525731112119 + 0.000000000000*I, 0.850650808352 + 0.000000000000*I );
   sv = cd_matvec_make_from_args( 2, 1, 2, 2.288245611271 + 0.0*I, 0.874032048898 + 0.0*I );
   cd_svd_set_input( cdsvd, m );
   cd_svd_svd( cdsvd );
   rm = cd_svd_reconstructed_input( cdsvd );

   CU_ASSERT( cdsvd != NULL );
   CU_ASSERT( m != NULL );

   CU_ASSERT( cd_matvec_is_approximately_equal( cd_svd_left_singular_vectors( cdsvd ), lsv, 0.000001 ) == 1 );
   CU_ASSERT( cd_matvec_is_approximately_equal( cd_svd_right_singular_vectors( cdsvd ), rsv, 0.000001 ) == 1 );
   CU_ASSERT( cd_matvec_is_approximately_equal( cd_svd_singular_values( cdsvd ), sv, 0.000001 ) == 1 );
   CU_ASSERT( cd_matvec_is_approximately_equal( rm, m, 0.000001 ) == 1 );

   cd_svd_deep_dispose( &cdsvd );
   cd_matvec_dispose( &lsv );
   cd_matvec_dispose( &rsv );
   cd_matvec_dispose( &sv );
   cd_matvec_dispose( &rm );

   cdsvd = cd_svd_make();
   m = cd_matvec_make_from_args( 3, 2, 6, 2.1 + 0.0*I, 1.3 + 0.0*I, -0.5 + 0.0*I, -2.9 + 0.0*I, 0.8 + 0.0*I, -1.3 + 0.0*I );
   lsv
      =  cd_matvec_make_from_args
         (
            3, 2, 6,
            0.5514080664088562  + 0.000000000000*I, 0.72686913267302133 + 0.000000000000*I,
           -0.79576027353432999 + 0.000000000000*I, 0.31096469860907316 + 0.000000000000*I,
           -0.25042909448347817 + 0.000000000000*I, 0.61234158782997772 + 0.000000000000*I
         );
   rsv = cd_matvec_make_from_args( 2, 2, 4, 0.375074729372 + 0.000000000000*I, 0.926994577862 + 0.000000000000*I, 0.926994577862 + 0.000000000000*I, -0.375074729372 + 0.000000000000*I );
   sv = cd_matvec_make_from_args( 2, 1, 2, 3.6139296117084276 + 0.0*I, 2.0073646309569595 + 0.0*I );
   cd_svd_set_input( cdsvd, m );
   cd_svd_svd( cdsvd );
   rm = cd_svd_reconstructed_input( cdsvd );

   CU_ASSERT( cdsvd != NULL );
   CU_ASSERT( m != NULL );

   CU_ASSERT( cd_matvec_is_approximately_equal( cd_svd_left_singular_vectors( cdsvd ), lsv, 0.000001 ) == 1 );
   CU_ASSERT( cd_matvec_is_approximately_equal( cd_svd_right_singular_vectors( cdsvd ), rsv, 0.000001 ) == 1 );
   CU_ASSERT( cd_matvec_is_approximately_equal( cd_svd_singular_values( cdsvd ), sv, 0.000001 ) == 1 );
   CU_ASSERT( cd_matvec_is_approximately_equal( rm, m, 0.000001 ) == 1 );

   cd_svd_deep_dispose( &cdsvd );
   cd_matvec_dispose( &lsv );
   cd_matvec_dispose( &rsv );
   cd_matvec_dispose( &sv );
   cd_matvec_dispose( &rm );


   cdsvd = cd_svd_make();
   m = cd_matvec_make_from_args( 2, 3, 6, 2.0 + 0.0*I, 0.5 + 0.0*I, 1.0 + 0.0*I, 0.0 + 0.0*I, 1.0 + 0.0*I, 0.0 + 0.0*I );
   lsv = cd_matvec_make_from_args( 2, 2, 4, 0.993332061381 + 0.0*I, 0.115288402857 + 0.0*I, -0.115288402857 + 0.0*I, 0.993332061381 + 0.0*I );
   rsv = cd_matvec_make_from_args( 2, 3, 6, 0.862298672496 + 0.0*I, 0.265614851363 + 0.0*I, 0.431149336248 + 0.0*I, -0.237573145392 + 0.0*I, 0.964079224304 + 0.0*I, -0.118786572696 + 0.0*I );
   sv = cd_matvec_make_from_args( 2, 1, 2, 2.303916480598 + 0.0*I, 0.970550797449 + 0.0*I );
   cd_svd_set_input( cdsvd, m );
   cd_svd_svd( cdsvd );
   rm = cd_svd_reconstructed_input( cdsvd );

   CU_ASSERT( cdsvd != NULL );
   CU_ASSERT( m != NULL );

   CU_ASSERT( cd_matvec_is_approximately_equal( cd_svd_left_singular_vectors( cdsvd ), lsv, 0.000001 ) == 1 );
   CU_ASSERT( cd_matvec_is_approximately_equal( cd_svd_right_singular_vectors( cdsvd ), rsv, 0.000001 ) == 1 );
   CU_ASSERT( cd_matvec_is_approximately_equal( cd_svd_singular_values( cdsvd ), sv, 0.000001 ) == 1 );
   CU_ASSERT( cd_matvec_is_approximately_equal( rm, m, 0.000001 ) == 1 );

   cd_svd_deep_dispose( &cdsvd );
   cd_matvec_dispose( &lsv );
   cd_matvec_dispose( &rsv );
   cd_matvec_dispose( &sv );
   cd_matvec_dispose( &rm );

   return;
}

int
add_test_reconstructed_input( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_reconstructed_input", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_reconstructed_input_1
   add_test_to_suite( p_suite, test_reconstructed_input_1, "test_reconstructed_input_1" );

   // test_reconstructed_input_2
   add_test_to_suite( p_suite, test_reconstructed_input_2, "test_reconstructed_input_2" );

   // test_reconstructed_input_3
   add_test_to_suite( p_suite, test_reconstructed_input_3, "test_reconstructed_input_3" );

   // test_reconstructed_input_4
   add_test_to_suite( p_suite, test_reconstructed_input_4, "test_reconstructed_input_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

