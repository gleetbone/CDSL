/**
 @file Configuration.c
 @author Greg Lee
 @version 1.0.0
 @brief: "Configuration composed of key-value pairs"
 
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee

 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0):
 
 1. Permission is hereby granted to use, copy, modify and/or
    distribute this package, provided that:
       * copyright notices are retained unchanged,
       * any distribution of this package, whether modified or not,
         includes this license text.
 2. Permission is hereby also granted to distribute binary programs
    which depend on this package. If the binary program depends on a
    modified version of this package, you are encouraged to publicly
    release the modified version of this package. 

 THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT WARRANTY. ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE AUTHORS BE LIABLE TO ANY PARTY FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES ARISING IN ANY WAY OUT OF THE USE OF THIS PACKAGE.
 
 @section Description

 Thread safe configuration object. Holds string-string configuration values.
 Function definitions for the opaque soa_configuration_t type.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "Configuration.h"
#include "Input_File_Reader.h"
   
#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"
#include "ss_HTable.h"

/**
   defines
*/

#define CONFIGURATION_TYPE 0xA5000700

/**
   Structure
*/

struct soa_configuration_struct
{
   int32_t type;
   
   ss_htable_t *table;
   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

typedef struct soa_configuration_struct soa_configuration_t;

/**
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
table_ok( soa_configuration_t *p )
{
   int32_t result = 1;

   result = (*p).table != NULL;

   return result;
}

static
void invariant( soa_configuration_t *p )
{
   assert(((void) "table ok", table_ok( p ) ));
   return;
}

#endif

/**
   soa_configuration_make
*/
soa_configuration_t *
soa_configuration_make( void )
{
   soa_configuration_t *result
      = ( soa_configuration_t * ) calloc( 1, sizeof( soa_configuration_t ) );

   // set type
   (*result).type = CONFIGURATION_TYPE;

   // set table
   (*result).table = ss_htable_make();
   
   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   soa_configuration_dispose
*/
void
soa_configuration_dispose( soa_configuration_t *configuration )
{
   PRECONDITION( "configuration not null", configuration != NULL );
   PRECONDITION( "configuration type OK", (*configuration).type == CONFIGURATION_TYPE );
   INVARIANT( configuration );

   ss_htable_dispose_with_contents( (*configuration).table );
   MULTITHREAD_MUTEX_DESTROY( (*configuration).mutex );

   free( configuration );

   return;
}

/**
   soa_configuration_put
*/
void
soa_configuration_put
(
   soa_configuration_t *configuration,
   string_t *key,
   string_t *value
)
{
   PRECONDITION( "configuration not null", configuration != NULL );
   PRECONDITION( "configuration type OK", (*configuration).type == CONFIGURATION_TYPE );
   PRECONDITION( "key not null", key != NULL );
   PRECONDITION( "value not null", value != NULL );

   LOCK( (*configuration).mutex );
   INVARIANT( configuration );
   
   ss_htable_replace_and_dispose( (*configuration).table, value, key );
   
   INVARIANT( configuration );
   UNLOCK( (*configuration).mutex );

   return;
}

/**
   soa_configuration_put_cstring
*/
void
soa_configuration_put_cstring
(
   soa_configuration_t *configuration,
   char_t *key,
   char_t *value
)
{
   PRECONDITION( "configuration not null", configuration != NULL );
   PRECONDITION( "configuration type OK", (*configuration).type == CONFIGURATION_TYPE );
   PRECONDITION( "key not null", key != NULL );
   PRECONDITION( "value not null", value != NULL );

   string_t *skey = string_make_from_cstring( key );
   string_t *svalue = string_make_from_cstring( value );

   LOCK( (*configuration).mutex );
   INVARIANT( configuration );
   ss_htable_replace_and_dispose( (*configuration).table, svalue, skey );
   INVARIANT( configuration );
   UNLOCK( (*configuration).mutex );

   return;
}

/**
   soa_configuration_has
*/
int32_t
soa_configuration_has
(
   soa_configuration_t *configuration,
   string_t *key
)
{
   PRECONDITION( "configuration not null", configuration != NULL );
   PRECONDITION( "configuration type OK", (*configuration).type == CONFIGURATION_TYPE );
   PRECONDITION( "key not null", key != NULL );

   int32_t result = 0;

   LOCK( (*configuration).mutex );
   INVARIANT( configuration );
   result = ss_htable_has( (*configuration).table, key );
   INVARIANT( configuration );
   UNLOCK( (*configuration).mutex );

   return result;
}

/**
   soa_configuration_has_cstring
*/
int32_t
soa_configuration_has_cstring
(
   soa_configuration_t *configuration,
   char_t *key
)
{
   PRECONDITION( "configuration not null", configuration != NULL );
   PRECONDITION( "configuration type OK", (*configuration).type == CONFIGURATION_TYPE );
   PRECONDITION( "key not null", key != NULL );

   int32_t result = 0;
   string_t *skey = string_make_from_cstring( key );

   LOCK( (*configuration).mutex );
   INVARIANT( configuration );
   result = ss_htable_has( (*configuration).table, skey );
   INVARIANT( configuration );
   UNLOCK( (*configuration).mutex );

   string_dispose_with_contents( skey );

   return result;
}

/**
   soa_configuration_item
*/
string_t *
soa_configuration_item
(
   soa_configuration_t *configuration,
   string_t *key
)
{
   PRECONDITION( "configuration not null", configuration != NULL );
   PRECONDITION( "configuration type OK", (*configuration).type == CONFIGURATION_TYPE );
   PRECONDITION( "key not null", key != NULL );

   string_t *result = NULL;
   int32_t flag = 0;

   LOCK( (*configuration).mutex );
   INVARIANT( configuration );
   flag = ss_htable_has( (*configuration).table, key );
   if ( flag == 1 )
   {
      result = ss_htable_item( (*configuration).table, key );
   }
   INVARIANT( configuration );
   UNLOCK( (*configuration).mutex );

   return result;
}

/**
   soa_configuration_item_cstring
*/
string_t *
soa_configuration_item_cstring
(
   soa_configuration_t *configuration,
   char_t *key
)
{
   PRECONDITION( "configuration not null", configuration != NULL );
   PRECONDITION( "configuration type OK", (*configuration).type == CONFIGURATION_TYPE );
   PRECONDITION( "key not null", key != NULL );

   string_t *result = NULL;
   int32_t flag = 0;
   string_t *skey = string_make_from_cstring( key );

   LOCK( (*configuration).mutex );
   INVARIANT( configuration );
   flag = ss_htable_has( (*configuration).table, skey );
   if ( flag == 1 )
   {
      result = ss_htable_item( (*configuration).table, skey );
   }
   INVARIANT( configuration );
   UNLOCK( (*configuration).mutex );

   string_dispose_with_contents( skey );

   return result;
}

/**
   soa_configuration_superkey_has
*/
int32_t
soa_configuration_superkey_has
(
   soa_configuration_t *configuration,
   string_t *superkey,
   string_t *key
)
{
   PRECONDITION( "configuration not null", configuration != NULL );
   PRECONDITION( "configuration type OK", (*configuration).type == CONFIGURATION_TYPE );
   PRECONDITION( "superkey not null", superkey != NULL );
   PRECONDITION( "key not null", key != NULL );

   int32_t result = 0;
   string_t *s = string_make_from( superkey );
   string_append_cstring( s, ":" );
   string_append( s, key );

   LOCK( (*configuration).mutex );
   INVARIANT( configuration );
   result = ss_htable_has( (*configuration).table, s );
   if ( result == 0 )
   {
      result = ss_htable_has( (*configuration).table, key );
   }
   INVARIANT( configuration );
   UNLOCK( (*configuration).mutex );

   string_dispose_with_contents( s );

   return result;
}

/**
   soa_configuration_has_cstring
*/
int32_t
soa_configuration_superkey_has_cstring
(
   soa_configuration_t *configuration,
   char_t *superkey,
   char_t *key
)
{
   PRECONDITION( "configuration not null", configuration != NULL );
   PRECONDITION( "configuration type OK", (*configuration).type == CONFIGURATION_TYPE );
   PRECONDITION( "superkey not null", superkey != NULL );
   PRECONDITION( "key not null", key != NULL );

   int32_t result = 0;
   string_t *skey = string_make_from_cstring( key );
   string_t *s = string_make_from_cstring( superkey );
   string_append_cstring( s, ":" );
   string_append_cstring( s, key );

   LOCK( (*configuration).mutex );
   INVARIANT( configuration );
   result = ss_htable_has( (*configuration).table, s );
   if ( result == 0 )
   {
      result = ss_htable_has( (*configuration).table, skey );
   }
   INVARIANT( configuration );
   UNLOCK( (*configuration).mutex );

   string_dispose_with_contents( skey );
   string_dispose_with_contents( s );

   return result;
}

/**
   soa_configuration_superkey_item
*/
string_t *
soa_configuration_superkey_item
(
   soa_configuration_t *configuration,
   string_t *superkey,
   string_t *key
)
{
   PRECONDITION( "configuration not null", configuration != NULL );
   PRECONDITION( "configuration type OK", (*configuration).type == CONFIGURATION_TYPE );
   PRECONDITION( "superkey not null", superkey != NULL );
   PRECONDITION( "key not null", key != NULL );

   string_t *result = NULL;
   int32_t flag = 0;
   string_t *s = string_make_from( superkey );
   string_append_cstring( s, ":" );
   string_append( s, key );

   LOCK( (*configuration).mutex );
   INVARIANT( configuration );
   flag = ss_htable_has( (*configuration).table, s );
   if ( flag == 1 )
   {
      result = ss_htable_item( (*configuration).table, s );
   }
   else
   {
      flag = ss_htable_has( (*configuration).table, key );
      if ( flag == 1 )
      {
         result = ss_htable_item( (*configuration).table, key );
      }
   }
   INVARIANT( configuration );
   UNLOCK( (*configuration).mutex );

   string_dispose_with_contents( s );

   return result;
}

/**
   soa_configuration_superkey_item_cstring
*/
string_t *
soa_configuration_superkey_item_cstring
(
   soa_configuration_t *configuration,
   char_t *superkey,
   char_t *key
)
{
   PRECONDITION( "configuration not null", configuration != NULL );
   PRECONDITION( "configuration type OK", (*configuration).type == CONFIGURATION_TYPE );
   PRECONDITION( "superkey not null", superkey != NULL );
   PRECONDITION( "key not null", key != NULL );

   string_t *result = NULL;
   int32_t flag = 0;
   string_t *skey = string_make_from_cstring( key );
   string_t *s = string_make_from_cstring( superkey );
   string_append_cstring( s, ":" );
   string_append_cstring( s, key );

   LOCK( (*configuration).mutex );
   INVARIANT( configuration );
   flag = ss_htable_has( (*configuration).table, s );
   if ( flag == 1 )
   {
      result = ss_htable_item( (*configuration).table, s );
   }
   else
   {
      flag = ss_htable_has( (*configuration).table, skey );
      if ( flag == 1 )
      {
         result = ss_htable_item( (*configuration).table, skey );
      }
   }
   INVARIANT( configuration );
   UNLOCK( (*configuration).mutex );

   string_dispose_with_contents( skey );
   string_dispose_with_contents( s );

   return result;
}

/**
   soa_configuration_list_items
*/
s_dlist_t *
soa_configuration_list_items
(
   soa_configuration_t *configuration,
   string_t *key
)
{
   PRECONDITION( "configuration not null", configuration != NULL );
   PRECONDITION( "configuration type OK", (*configuration).type == CONFIGURATION_TYPE );
   PRECONDITION( "key not null", key != NULL );

   s_dlist_t *result = s_dlist_make();
   int32_t flag = 0;
   string_t *s = NULL;
   string_t *s1 = NULL;

   int32_t i = 1;
   LOCK( (*configuration).mutex );
   INVARIANT( configuration );

   flag = 1;
   while( flag == 1 )
   {
      s = string_make_from( key );
      string_append_cstring( s, "_" );
      string_insert_int32( s, i, string_count( s ) );

      flag = ss_htable_has( (*configuration).table, s );
      if ( flag == 1 )
      {
         s1 = ss_htable_item( (*configuration).table, s );
         s_dlist_put_last( result, s1 );
      }
      string_dispose_with_contents( s );
      i = i + 1;
   }

   INVARIANT( configuration );
   UNLOCK( (*configuration).mutex );

   return result;
}

/**
   soa_configuration_list_items_cstring
*/
s_dlist_t *
soa_configuration_list_items_cstring
(
   soa_configuration_t *configuration,
   char_t *key
)
{
   PRECONDITION( "configuration not null", configuration != NULL );
   PRECONDITION( "configuration type OK", (*configuration).type == CONFIGURATION_TYPE );
   PRECONDITION( "key not null", key != NULL );

   s_dlist_t *result = s_dlist_make();
   int32_t flag = 0;
   string_t *s = NULL;
   string_t *s1 = NULL;

   int32_t i = 1;
   LOCK( (*configuration).mutex );
   INVARIANT( configuration );

   flag = 1;
   while( flag == 1 )
   {
      s = string_make_from_cstring( key );
      string_append_cstring( s, "_" );
      string_insert_int32( s, i, string_count( s ) );

      flag = ss_htable_has( (*configuration).table, s );
      if ( flag == 1 )
      {
         s1 = ss_htable_item( (*configuration).table, s );
         s_dlist_put_last( result, s1 );
      }
      string_dispose_with_contents( s );
      i = i + 1;
   }

   INVARIANT( configuration );
   UNLOCK( (*configuration).mutex );

   return result;
}


/**
   soa_configuration_superkey_list_items
*/
s_dlist_t *
soa_configuration_superkey_list_items
(
   soa_configuration_t *configuration,
   string_t *superkey,
   string_t *key
)
{
   PRECONDITION( "configuration not null", configuration != NULL );
   PRECONDITION( "configuration type OK", (*configuration).type == CONFIGURATION_TYPE );
   PRECONDITION( "superkey not null", superkey != NULL );
   PRECONDITION( "key not null", key != NULL );

   s_dlist_t *result = s_dlist_make();
   int32_t flag = 0;
   string_t *s = NULL;
   string_t *s1 = NULL;
   string_t *super = NULL;
   int32_t i = 1;
   
   super = string_make_from( superkey );
   string_append_cstring( super, ":" );
   string_append( super, key );

   LOCK( (*configuration).mutex );
   INVARIANT( configuration );

   s = string_make_from( super );
   string_append_cstring( s, "_" );
   string_insert_int32( s, i, string_count( s ) );

   flag = ss_htable_has( (*configuration).table, s );
   string_dispose_with_contents( s );

   // if superkey:key is present, only return superkey:key_X items
   if ( flag == 1 )
   {
      flag = 1;
      while( flag == 1 )
      {
         s = string_make_from( super );
         string_append_cstring( s, "_" );
         string_insert_int32( s, i, string_count( s ) );

         flag = ss_htable_has( (*configuration).table, s );
         if ( flag == 1 )
         {
            s1 = ss_htable_item( (*configuration).table, s );
            s_dlist_put_last( result, s1 );
         }
         string_dispose_with_contents( s );
         i = i + 1;
      }
   }
   // if superkey:key is not present, only return key_X items
   else
   {
      flag = 1;
      while( flag == 1 )
      {
         s = string_make_from( key );
         string_append_cstring( s, "_" );
         string_insert_int32( s, i, string_count( s ) );

         flag = ss_htable_has( (*configuration).table, s );
         if ( flag == 1 )
         {
            s1 = ss_htable_item( (*configuration).table, s );
            s_dlist_put_last( result, s1 );
         }
         string_dispose_with_contents( s );
         i = i + 1;
      }
   }

   string_dispose_with_contents( super );
   
   INVARIANT( configuration );
   UNLOCK( (*configuration).mutex );

   return result;
}

/**
   soa_configuration_superkey_list_items_cstring
*/
s_dlist_t *
soa_configuration_superkey_list_items_cstring
(
   soa_configuration_t *configuration,
   char_t *superkey,
   char_t *key
)
{
   PRECONDITION( "configuration not null", configuration != NULL );
   PRECONDITION( "configuration type OK", (*configuration).type == CONFIGURATION_TYPE );
   PRECONDITION( "superkey not null", superkey != NULL );
   PRECONDITION( "key not null", key != NULL );

   s_dlist_t *result = s_dlist_make();
   int32_t flag = 0;
   string_t *s = NULL;
   string_t *s1 = NULL;
   string_t *super = NULL;
   int32_t i = 1;
   
   super = string_make_from_cstring( superkey );
   string_append_cstring( super, ":" );
   string_append_cstring( super, key );

   LOCK( (*configuration).mutex );
   INVARIANT( configuration );

   s = string_make_from( super );
   string_append_cstring( s, "_" );
   string_insert_int32( s, i, string_count( s ) );

   flag = ss_htable_has( (*configuration).table, s );
   string_dispose_with_contents( s );

   // if superkey:key is present, only return superkey:key_X items
   if ( flag == 1 )
   {
      flag = 1;
      while( flag == 1 )
      {
         s = string_make_from( super );
         string_append_cstring( s, "_" );
         string_insert_int32( s, i, string_count( s ) );

         flag = ss_htable_has( (*configuration).table, s );
         if ( flag == 1 )
         {
            s1 = ss_htable_item( (*configuration).table, s );
            s_dlist_put_last( result, s1 );
         }
         string_dispose_with_contents( s );
         i = i + 1;
      }
   }
   // if superkey:key is not present, only return key_X items
   else
   {
      flag = 1;
      while( flag == 1 )
      {
         s = string_make_from_cstring( key );
         string_append_cstring( s, "_" );
         string_insert_int32( s, i, string_count( s ) );

         flag = ss_htable_has( (*configuration).table, s );
         if ( flag == 1 )
         {
            s1 = ss_htable_item( (*configuration).table, s );
            s_dlist_put_last( result, s1 );
         }
         string_dispose_with_contents( s );
         i = i + 1;
      }
   }

   string_dispose_with_contents( super );
   
   INVARIANT( configuration );
   UNLOCK( (*configuration).mutex );

   return result;
}


/**
   soa_configuration_set_from_file
*/
void
soa_configuration_set_from_file
(
   soa_configuration_t *configuration,
   string_t *filename
)
{
   PRECONDITION( "configuration not null", configuration != NULL );
   PRECONDITION( "configuration type OK", (*configuration).type == CONFIGURATION_TYPE );
   PRECONDITION( "filename not null", filename != NULL );

   ifr_t *ifr = NULL;
   s_dlist_t *tokens = NULL;
   string_t *key = NULL;
   string_t *value = NULL;

   LOCK( (*configuration).mutex );
   INVARIANT( configuration );

   ifr = ifr_make( filename );
   ifr_forth( ifr );

   while( ifr_eof( ifr ) == 0 )
   {
      tokens = ifr_tokens( ifr );

      if ( s_dlist_count( tokens ) >= 2 )
      {
         key = string_make_from( s_dlist_item( tokens, 0 ) );
         value = string_make_from( s_dlist_item( tokens, 1 ) );
         ss_htable_put( (*configuration).table, value, key );
         ifr_forth( ifr );
      }
   }

   ifr_dispose( ifr );

   INVARIANT( configuration );
   UNLOCK( (*configuration).mutex );

   return;
}

/**
   soa_configuration_set_from_file_cstring
*/
void
soa_configuration_set_from_file_cstring
(
   soa_configuration_t *configuration,
   char_t *filename
)
{
   PRECONDITION( "configuration not null", configuration != NULL );
   PRECONDITION( "configuration type OK", (*configuration).type == CONFIGURATION_TYPE );
   PRECONDITION( "filename not null", filename != NULL );

   ifr_t *ifr = NULL;
   s_dlist_t *tokens = NULL;
   string_t *key = NULL;
   string_t *value = NULL;

   LOCK( (*configuration).mutex );
   INVARIANT( configuration );

   ifr = ifr_make_cstring( filename );

   ifr_forth( ifr );

   while( ifr_eof( ifr ) == 0 )
   {
      tokens = ifr_tokens( ifr );

      if ( s_dlist_count( tokens ) >= 2 )
      {
         key = string_make_from( s_dlist_item( tokens, 0 ) );
         value = string_make_from( s_dlist_item( tokens, 1 ) );
         ss_htable_put( (*configuration).table, value, key );
         ifr_forth( ifr );
      }
   }

   ifr_dispose( ifr );

   INVARIANT( configuration );
   UNLOCK( (*configuration).mutex );

   return;
}

/* End of file */
