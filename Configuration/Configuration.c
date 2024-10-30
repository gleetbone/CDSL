/**
 @file Configuration.c
 @author Greg Lee
 @version 2.0.0
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
 Function definitions for the opaque configuration_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

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

/**
   Structure
*/

struct configuration_struct
{
   int32_t _type;

   ss_htable_t *table;
   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

typedef struct configuration_struct configuration_t;

/**
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
table_ok( configuration_t *p )
{
   int32_t result = 1;

   result = (*p).table != NULL;

   return result;
}

static
void invariant( configuration_t *p )
{
   assert( ( ( void ) "table ok", table_ok( p ) ) );
   return;
}

#endif

/**
   configuration_make
*/
configuration_t *
configuration_make( void )
{
   configuration_t *result
      = ( configuration_t * ) calloc( 1, sizeof( configuration_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = CONFIGURATION_TYPE;

   // set table
   (*result).table = ss_htable_make();

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   configuration_clone
*/

configuration_t *
configuration_clone( configuration_t *current )
{
   PRECONDITION( "configuration not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CONFIGURATION_TYPE );

   // allocate configuration struct
   configuration_t * result = ( configuration_t * ) calloc( 1, sizeof( configuration_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // lock mutex
   LOCK( (*current).mutex );

   // set type
   (*result)._type = CONFIGURATION_TYPE;

   (*result).table = ss_htable_clone( (*current).table );

   // unlock mutex
   UNLOCK( (*current).mutex );

   INVARIANT( current );

   return result;
}

/**
   configuration_deep_clone
*/

configuration_t *
configuration_deep_clone( configuration_t *current )
{
   PRECONDITION( "configuration not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CONFIGURATION_TYPE );

   // allocate configuration struct
   configuration_t * result = ( configuration_t * ) calloc( 1, sizeof( configuration_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // lock mutex
   LOCK( (*current).mutex );

   // set type
   (*result)._type = CONFIGURATION_TYPE;

   (*result).table = ss_htable_clone( (*current).table );

   // unlock mutex
   UNLOCK( (*current).mutex );

   INVARIANT( current );

   return result;
}

/**
  is_equal
*/

static
int32_t
is_equal(  configuration_t *current, configuration_t *other )
{
   int32_t result = 0;

   result =
      ( ss_htable_is_equal( (*current).table, (*other).table ) == 1 );

   return result;
};

/**
   configuration_is_equal
*/

int32_t
configuration_is_equal( configuration_t *current, configuration_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CONFIGURATION_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CONFIGURATION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( current == other )
   {
      result = 1;
   }
   else
   {
      // lock other
      LOCK( (*other).mutex );

      result = is_equal( current, other );

      // unlock other
      UNLOCK( (*other).mutex );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
  is_deep_equal
*/

static
int32_t
is_deep_equal(  configuration_t *current, configuration_t *other )
{
   int32_t result = 0;

   result =
      ( ss_htable_is_deep_equal( (*current).table, (*other).table ) == 1 );

   return result;
};

/**
   configuration_is_deep_equal
*/

int32_t
configuration_is_deep_equal( configuration_t *current, configuration_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CONFIGURATION_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CONFIGURATION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( current == other )
   {
      result = 1;
   }
   else
   {
      // lock other
      LOCK( (*other).mutex );

      result = is_deep_equal( current, other );

      // unlock other
      UNLOCK( (*other).mutex );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   configuration_copy
*/

void
configuration_copy( configuration_t *current, configuration_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CONFIGURATION_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CONFIGURATION_TYPE );

   INVARIANT( current );
   INVARIANT( other );

   // lock mutex
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );

   ss_htable_copy( (*current).table, (*other).table );

   INVARIANT( current );
   INVARIANT( other );

   // unlock mutex
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return;
}

/**
   configuration_deep_copy
*/

void
configuration_deep_copy( configuration_t *current, configuration_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CONFIGURATION_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CONFIGURATION_TYPE );

   INVARIANT( current );
   INVARIANT( other );

   // lock mutex
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );

   ss_htable_deep_copy( (*current).table, (*other).table );

   INVARIANT( current );
   INVARIANT( other );

   // unlock mutex
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return;
}

/**
   configuration_dispose
*/

void
configuration_dispose( configuration_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == CONFIGURATION_TYPE );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   // delete structure items
   ss_htable_dispose( &(**current).table );

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // deallocate the structure
   free(*current);

   // set the pointer to null
   *current = NULL;

   return;
}

/**
   configuration_deep_dispose
*/

void
configuration_deep_dispose( configuration_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == CONFIGURATION_TYPE );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   // delete structure items
   ss_htable_deep_dispose( &(**current).table );

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // deallocate the structure
   free(*current);

   // set the pointer to null
   *current = NULL;

   return;
}

/**
   configuration_put
*/
void
configuration_put
(
   configuration_t *current,
   string_t *key,
   string_t *value
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CONFIGURATION_TYPE );
   PRECONDITION( "key not null", key != NULL );
   PRECONDITION( "value not null", value != NULL );

   LOCK( (*current).mutex );
   INVARIANT( current );

   ss_htable_replace_and_dispose( (*current).table, value, key );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   configuration_put_cstring
*/
void
configuration_put_cstring
(
   configuration_t *current,
   char_t *key,
   char_t *value
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CONFIGURATION_TYPE );
   PRECONDITION( "key not null", key != NULL );
   PRECONDITION( "value not null", value != NULL );

   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *skey = NULL;
   string_t *svalue = NULL;

   skey = string_make_from_cstring( key );
   svalue = string_make_from_cstring( value );

   ss_htable_replace_and_dispose( (*current).table, svalue, skey );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   configuration_has
*/
int32_t
configuration_has
(
   configuration_t *current,
   string_t *key
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CONFIGURATION_TYPE );
   PRECONDITION( "key not null", key != NULL );

   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   result = ss_htable_has( (*current).table, key );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   configuration_has_cstring
*/
int32_t
configuration_has_cstring
(
   configuration_t *current,
   char_t *key
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CONFIGURATION_TYPE );
   PRECONDITION( "key not null", key != NULL );

   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   string_t *skey = string_make_from_cstring( key );

   result = ss_htable_has( (*current).table, skey );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   string_deep_dispose( &skey );

   return result;
}

/**
   configuration_item
*/
string_t *
configuration_item
(
   configuration_t *current,
   string_t *key
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CONFIGURATION_TYPE );
   PRECONDITION( "key not null", key != NULL );

   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = NULL;
   int32_t flag = 0;

   flag = ss_htable_has( (*current).table, key );
   if ( flag == 1 )
   {
      result = ss_htable_item( (*current).table, key );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   configuration_item_cstring
*/
string_t *
configuration_item_cstring
(
   configuration_t *current,
   char_t *key
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CONFIGURATION_TYPE );
   PRECONDITION( "key not null", key != NULL );

   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = NULL;
   int32_t flag = 0;
   string_t *skey = NULL;

   skey = string_make_from_cstring( key );

   flag = ss_htable_has( (*current).table, skey );
   if ( flag == 1 )
   {
      result = ss_htable_item( (*current).table, skey );
   }

   string_deep_dispose( &skey );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   configuration_superkey_has
*/
int32_t
configuration_superkey_has
(
   configuration_t *current,
   string_t *superkey,
   string_t *key
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CONFIGURATION_TYPE );
   PRECONDITION( "superkey not null", superkey != NULL );
   PRECONDITION( "key not null", key != NULL );

   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   string_t *s = NULL;

   s = string_clone( superkey );
   string_append_cstring( s, ":" );
   string_append( s, key );

   result = ss_htable_has( (*current).table, s );
   if ( result == 0 )
   {
      result = ss_htable_has( (*current).table, key );
   }

   string_deep_dispose( &s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   configuration_has_cstring
*/
int32_t
configuration_superkey_has_cstring
(
   configuration_t *current,
   char_t *superkey,
   char_t *key
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CONFIGURATION_TYPE );
   PRECONDITION( "superkey not null", superkey != NULL );
   PRECONDITION( "key not null", key != NULL );

   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   string_t *skey = NULL;
   string_t *s = NULL;

   skey = string_make_from_cstring( key );
   s = string_make_from_cstring( superkey );
   string_append_cstring( s, ":" );
   string_append_cstring( s, key );

   result = ss_htable_has( (*current).table, s );
   if ( result == 0 )
   {
      result = ss_htable_has( (*current).table, skey );
   }

   string_deep_dispose( &skey );
   string_deep_dispose( &s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   configuration_superkey_item
*/
string_t *
configuration_superkey_item
(
   configuration_t *current,
   string_t *superkey,
   string_t *key
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CONFIGURATION_TYPE );
   PRECONDITION( "superkey not null", superkey != NULL );
   PRECONDITION( "key not null", key != NULL );

   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = NULL;
   int32_t flag = 0;
   string_t *s = NULL;

   s = string_clone( superkey );
   string_append_cstring( s, ":" );
   string_append( s, key );

   flag = ss_htable_has( (*current).table, s );
   if ( flag == 1 )
   {
      result = ss_htable_item( (*current).table, s );
   }
   else
   {
      flag = ss_htable_has( (*current).table, key );
      if ( flag == 1 )
      {
         result = ss_htable_item( (*current).table, key );
      }
   }

   string_deep_dispose( &s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   configuration_superkey_item_cstring
*/
string_t *
configuration_superkey_item_cstring
(
   configuration_t *current,
   char_t *superkey,
   char_t *key
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CONFIGURATION_TYPE );
   PRECONDITION( "superkey not null", superkey != NULL );
   PRECONDITION( "key not null", key != NULL );

   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = NULL;
   int32_t flag = 0;
   string_t *skey = NULL;
   string_t *s = NULL;

   skey = string_make_from_cstring( key );
   s = string_make_from_cstring( superkey );
   string_append_cstring( s, ":" );
   string_append_cstring( s, key );

   flag = ss_htable_has( (*current).table, s );
   if ( flag == 1 )
   {
      result = ss_htable_item( (*current).table, s );
   }
   else
   {
      flag = ss_htable_has( (*current).table, skey );
      if ( flag == 1 )
      {
         result = ss_htable_item( (*current).table, skey );
      }
   }

   string_deep_dispose( &skey );
   string_deep_dispose( &s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   configuration_list_items
*/
s_dlist_t *
configuration_list_items
(
   configuration_t *current,
   string_t *key
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CONFIGURATION_TYPE );
   PRECONDITION( "key not null", key != NULL );

   LOCK( (*current).mutex );
   INVARIANT( current );

   s_dlist_t *result = NULL;
   int32_t flag = 0;
   string_t *s = NULL;
   string_t *s1 = NULL;

   result = s_dlist_make();
   int32_t i = 1;
   flag = 1;

   while( flag == 1 )
   {
      s = string_clone( key );
      string_append_cstring( s, "_" );
      string_insert_int32( s, i, string_count( s ) );

      flag = ss_htable_has( (*current).table, s );
      if ( flag == 1 )
      {
         s1 = ss_htable_item( (*current).table, s );
         s_dlist_put_last( result, s1 );
      }
      string_deep_dispose( &s );
      i = i + 1;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   configuration_list_items_cstring
*/
s_dlist_t *
configuration_list_items_cstring
(
   configuration_t *current,
   char_t *key
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CONFIGURATION_TYPE );
   PRECONDITION( "key not null", key != NULL );

   LOCK( (*current).mutex );
   INVARIANT( current );

   s_dlist_t *result = NULL;
   int32_t flag = 0;
   string_t *s = NULL;
   string_t *s1 = NULL;

   result = s_dlist_make();
   int32_t i = 1;

   flag = 1;
   while( flag == 1 )
   {
      s = string_make_from_cstring( key );
      string_append_cstring( s, "_" );
      string_insert_int32( s, i, string_count( s ) );

      flag = ss_htable_has( (*current).table, s );
      if ( flag == 1 )
      {
         s1 = ss_htable_item( (*current).table, s );
         s_dlist_put_last( result, s1 );
      }
      string_deep_dispose( &s );
      i = i + 1;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}


/**
   configuration_superkey_list_items
*/
s_dlist_t *
configuration_superkey_list_items
(
   configuration_t *current,
   string_t *superkey,
   string_t *key
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CONFIGURATION_TYPE );
   PRECONDITION( "superkey not null", superkey != NULL );
   PRECONDITION( "key not null", key != NULL );

   LOCK( (*current).mutex );
   INVARIANT( current );

   s_dlist_t *result = NULL;
   int32_t flag = 0;
   string_t *s = NULL;
   string_t *s1 = NULL;
   string_t *super = NULL;
   int32_t i = 1;

   result = s_dlist_make();

   super = string_clone( superkey );
   string_append_cstring( super, ":" );
   string_append( super, key );

   s = string_clone( super );
   string_append_cstring( s, "_" );
   string_insert_int32( s, i, string_count( s ) );

   flag = ss_htable_has( (*current).table, s );
   string_deep_dispose( &s );

   // if superkey:key is present, only return superkey:key_X items
   if ( flag == 1 )
   {
      flag = 1;
      while( flag == 1 )
      {
         s = string_clone( super );
         string_append_cstring( s, "_" );
         string_insert_int32( s, i, string_count( s ) );

         flag = ss_htable_has( (*current).table, s );
         if ( flag == 1 )
         {
            s1 = ss_htable_item( (*current).table, s );
            s_dlist_put_last( result, s1 );
         }
         string_deep_dispose( &s );
         i = i + 1;
      }
   }
   // if superkey:key is not present, only return key_X items
   else
   {
      flag = 1;
      while( flag == 1 )
      {
         s = string_clone( key );
         string_append_cstring( s, "_" );
         string_insert_int32( s, i, string_count( s ) );

         flag = ss_htable_has( (*current).table, s );
         if ( flag == 1 )
         {
            s1 = ss_htable_item( (*current).table, s );
            s_dlist_put_last( result, s1 );
         }
         string_deep_dispose( &s );
         i = i + 1;
      }
   }

   string_deep_dispose( &super );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   configuration_superkey_list_items_cstring
*/
s_dlist_t *
configuration_superkey_list_items_cstring
(
   configuration_t *current,
   char_t *superkey,
   char_t *key
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CONFIGURATION_TYPE );
   PRECONDITION( "superkey not null", superkey != NULL );
   PRECONDITION( "key not null", key != NULL );

   LOCK( (*current).mutex );
   INVARIANT( current );

   s_dlist_t *result = NULL;
   int32_t flag = 0;
   string_t *s = NULL;
   string_t *s1 = NULL;
   string_t *super = NULL;
   int32_t i = 1;

   result = s_dlist_make();

   super = string_make_from_cstring( superkey );
   string_append_cstring( super, ":" );
   string_append_cstring( super, key );

   s = string_clone( super );
   string_append_cstring( s, "_" );
   string_insert_int32( s, i, string_count( s ) );

   flag = ss_htable_has( (*current).table, s );
   string_deep_dispose( &s );

   // if superkey:key is present, only return superkey:key_X items
   if ( flag == 1 )
   {
      flag = 1;
      while( flag == 1 )
      {
         s = string_clone( super );
         string_append_cstring( s, "_" );
         string_insert_int32( s, i, string_count( s ) );

         flag = ss_htable_has( (*current).table, s );
         if ( flag == 1 )
         {
            s1 = ss_htable_item( (*current).table, s );
            s_dlist_put_last( result, s1 );
         }
         string_deep_dispose( &s );
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

         flag = ss_htable_has( (*current).table, s );
         if ( flag == 1 )
         {
            s1 = ss_htable_item( (*current).table, s );
            s_dlist_put_last( result, s1 );
         }
         string_deep_dispose( &s );
         i = i + 1;
      }
   }

   string_deep_dispose( &super );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}


/**
   configuration_set_from_file
*/
void
configuration_set_from_file
(
   configuration_t *current,
   string_t *filename
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CONFIGURATION_TYPE );
   PRECONDITION( "filename not null", filename != NULL );

   LOCK( (*current).mutex );
   INVARIANT( current );

   ifr_t *ifr = NULL;
   s_dlist_t *tokens = NULL;
   string_t *key = NULL;
   string_t *value = NULL;

   ifr = ifr_make( filename );
   ifr_forth( ifr );

   while( ifr_eof( ifr ) == 0 )
   {
      tokens = ifr_tokens( ifr );

      if ( s_dlist_count( tokens ) >= 2 )
      {
         key = string_clone( s_dlist_item( tokens, 0 ) );
         value = string_clone( s_dlist_item( tokens, 1 ) );
         ss_htable_put( (*current).table, value, key );
         ifr_forth( ifr );
      }
   }

   ifr_dispose( &ifr );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   configuration_set_from_file_cstring
*/
void
configuration_set_from_file_cstring
(
   configuration_t *current,
   char_t *filename
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CONFIGURATION_TYPE );
   PRECONDITION( "filename not null", filename != NULL );

   LOCK( (*current).mutex );
   INVARIANT( current );

   ifr_t *ifr = NULL;
   s_dlist_t *tokens = NULL;
   string_t *key = NULL;
   string_t *value = NULL;

   ifr = ifr_make_cstring( filename );

   ifr_forth( ifr );

   while( ifr_eof( ifr ) == 0 )
   {
      tokens = ifr_tokens( ifr );

      if ( s_dlist_count( tokens ) >= 2 )
      {
         key = string_clone( s_dlist_item( tokens, 0 ) );
         value = string_clone( s_dlist_item( tokens, 1 ) );
         ss_htable_put( (*current).table, value, key );
         ifr_forth( ifr );
      }
   }

   ifr_dispose( &ifr );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */
