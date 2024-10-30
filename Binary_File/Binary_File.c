/**
 @file Binary_File.c
 @author Greg Lee
 @version 2.0.0
 @brief: "binary file type"

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

 Function definitions for the opaque binary_file_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include "Binary_File.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>
#include <dirent.h>
#include <endian.h>

#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   defines
*/

union Int_16_union
{
   uint16_t    u;
   int16_t     i;
};

typedef union Int_16_union Int_16_t;

union Int_Float_32_union
{
   uint32_t    u;
   int32_t     i;
   float32_t   f;
};

typedef union Int_Float_32_union Int_Float_32_t;

union Int_Float_64_union
{
   uint64_t    u;
   int64_t     i;
   float64_t   f;
};

typedef union Int_Float_64_union Int_Float_64_t;

/**
   binary_file structure
*/

struct binary_file_struct
{
   int32_t _type;

   string_t *name;
   FILE *file;
   int32_t is_open_read;
   int32_t is_open_write;
   int32_t is_open_append;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

#if INVARIANT_CONDITIONAL != 0

static
int32_t
name_not_null( binary_file_t *p )
{
   int32_t result = 1;

   result = ( (*p).name != NULL );

   return result;
}

static
void invariant( binary_file_t *p )
{
   assert( ( ( void ) "name not null", name_not_null( p ) ) );
   return;
}

#endif

/**
   is_end_of_file
*/

static
int32_t
is_file_end_of_file( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file open", (*current).file != NULL );

   int64_t pos = 0;
   int64_t count = 0;
   int32_t result = 0;

   // get current position
   pos = ftell( (*current).file );

   // move to end of file
   fseek( (*current).file, 0, SEEK_END );

   // get position = size of file
   count = ftell( (*current).file );

   // return to original position
   fseek( (*current).file, pos, SEEK_SET );

   // return true if file at eof or file is empty
   result = ( feof( (*current).file ) != 0 ) || ( count == pos );

   return result;
}

/**
   binary_file_make
*/

binary_file_t *
binary_file_make( string_t *name )
{
   PRECONDITION( "name not null", name != NULL );

   // allocate binary_file struct
   binary_file_t * result = ( binary_file_t * ) calloc( 1, sizeof( binary_file_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = BINARY_FILE_TYPE;

   // set name
   (*result).name = string_clone( name );

   // set file
   (*result).file = NULL;

   // set flags
   (*result).is_open_write = 0;
   (*result).is_open_append = 0;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   binary_file_make_cstring
*/

binary_file_t *
binary_file_make_cstring( char_t *name )
{
   PRECONDITION( "name not null", name != NULL );

   // allocate binary_file struct
   binary_file_t * result = ( binary_file_t * ) calloc( 1, sizeof( binary_file_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = BINARY_FILE_TYPE;

   // set name
   (*result).name = string_make_from_cstring( name );

   // set file
   (*result).file = NULL;

   // set flags
   (*result).is_open_read = 0;
   (*result).is_open_write = 0;
   (*result).is_open_append = 0;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   binary_file_make_open_read
*/
binary_file_t *
binary_file_make_open_read( string_t *name )
{
   PRECONDITION( "name not null", name != NULL );

   binary_file_t *result = binary_file_make( name );

   (*result).file = fopen( string_as_cstring( name ), "rb" );
   if ( (*result).file != NULL )
   {
      (*result).is_open_read = 1;
   }

   return result;
}

/**
   binary_file_make_open_read_cstring
*/
binary_file_t *
binary_file_make_open_read_cstring( char_t *name )
{
   PRECONDITION( "name not null", name != NULL );

   binary_file_t *result = binary_file_make_cstring( name );

   (*result).file = fopen( name, "rb" );
   if ( (*result).file != NULL )
   {
      (*result).is_open_read = 1;
   }

   return result;
}

/**
   binary_file_make_open_write
*/
binary_file_t *
binary_file_make_open_write( string_t *name )
{
   PRECONDITION( "name not null", name != NULL );

   binary_file_t *result = binary_file_make( name );

   (*result).file = fopen( string_as_cstring( name ), "wb" );
   if ( (*result).file != NULL )
   {
      (*result).is_open_write = 1;
   }

   return result;
}

/**
   binary_file_make_open_write_cstring
*/
binary_file_t *
binary_file_make_open_write_cstring( char_t *name )
{
   PRECONDITION( "name not null", name != NULL );

   binary_file_t *result = binary_file_make_cstring( name );

   (*result).file = fopen( name, "wb" );
   if ( (*result).file != NULL )
   {
      (*result).is_open_write = 1;
   }

   return result;
}

/**
   binary_file_make_open_read_write
*/
binary_file_t *
binary_file_make_open_read_write( string_t *name )
{
   PRECONDITION( "name not null", name != NULL );

   binary_file_t *result = binary_file_make( name );

   (*result).file = fopen( string_as_cstring( name ), "r+b" );
   if ( (*result).file != NULL )
   {
      (*result).is_open_read = 1;
      (*result).is_open_write = 1;
   }

   return result;
}

/**
   binary_file_make_open_read_write_cstring
*/
binary_file_t *
binary_file_make_open_read_write_cstring( char_t *name )
{
   PRECONDITION( "name not null", name != NULL );

   binary_file_t *result = binary_file_make_cstring( name );

   (*result).file = fopen( name, "r+b" );
   if ( (*result).file != NULL )
   {
      (*result).is_open_read = 1;
      (*result).is_open_write = 1;
   }

   return result;
}

/**
   binary_file_make_create_read_write
*/
binary_file_t *
binary_file_make_create_read_write( string_t *name )
{
   PRECONDITION( "name not null", name != NULL );

   binary_file_t *result = binary_file_make( name );

   (*result).file = fopen( string_as_cstring( name ), "w+b" );
   if ( (*result).file != NULL )
   {
      (*result).is_open_read = 1;
      (*result).is_open_write = 1;
   }

   return result;
}

/**
   binary_file_make_create_read_write_cstring
*/
binary_file_t *
binary_file_make_create_read_write_cstring( char_t *name )
{
   PRECONDITION( "name not null", name != NULL );

   binary_file_t *result = binary_file_make_cstring( name );

   (*result).file = fopen( name, "w+b" );
   if ( (*result).file != NULL )
   {
      (*result).is_open_read = 1;
      (*result).is_open_write = 1;
   }

   return result;
}

/**
   binary_file_make_open_append
*/
binary_file_t *
binary_file_make_open_append( string_t *name )
{
   PRECONDITION( "name not null", name != NULL );

   binary_file_t *result = binary_file_make( name );

   (*result).file = fopen( string_as_cstring( name ), "ab" );
   if ( (*result).file != NULL )
   {
      (*result).is_open_append = 1;
   }

   return result;
}

/**
   binary_file_make_open_append_cstring
*/
binary_file_t *
binary_file_make_open_append_cstring( char_t *name )
{
   PRECONDITION( "name not null", name != NULL );

   binary_file_t *result = binary_file_make_cstring( name );

   (*result).file = fopen( name, "ab" );
   if ( (*result).file != NULL )
   {
      (*result).is_open_append = 1;
   }

   return result;
}

/**
   binary_file_make_open_read_append
*/
binary_file_t *
binary_file_make_open_read_append( string_t *name )
{
   PRECONDITION( "name not null", name != NULL );

   binary_file_t *result = binary_file_make( name );

   (*result).file = fopen( string_as_cstring( name ), "a+b" );
   if ( (*result).file != NULL )
   {
      (*result).is_open_read = 1;
      (*result).is_open_append = 1;
   }

   return result;
}

/**
   binary_file_make_open_read_append_cstring
*/
binary_file_t *
binary_file_make_open_read_append_cstring( char_t *name )
{
   PRECONDITION( "name not null", name != NULL );

   binary_file_t *result = binary_file_make_cstring( name );

   (*result).file = fopen( name, "a+b" );
   if ( (*result).file != NULL )
   {
      (*result).is_open_read = 1;
      (*result).is_open_append = 1;
   }

   return result;
}



/**
   binary_file_dispose
*/

void
binary_file_dispose( binary_file_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == BINARY_FILE_TYPE );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   // delete binary_file name
   string_deep_dispose( &(**current).name );

   // if file is not NULL, close it
   if ( (**current).file != NULL )
   {
      fclose( (**current).file );
      (**current).file = NULL;
      (**current).is_open_read = 0;
      (**current).is_open_write = 0;
      (**current).is_open_append = 0;
   }

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete binary_file struct
   free(*current);

   // set pointer to null
   *current = NULL;

   return;
}


/**
   binary_file_name
*/

string_t *
binary_file_name( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = (*current).name;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_name_cstring
*/

char_t *
binary_file_name_cstring( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *result = string_as_cstring( (*current).name );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_position
*/

int64_t
binary_file_position( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int64_t result = ftell( (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_count
*/

int64_t
binary_file_count( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int64_t pos = 0;
   int64_t result = 0;

   // get current position
   pos = ftell( (*current).file );

   // move to end of file
   fseek( (*current).file, 0, SEEK_END );

   // get position = size of file
   result = ftell( (*current).file );

   // return to original position
   fseek( (*current).file, pos, SEEK_SET );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_after
*/

int32_t
binary_file_after( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int64_t pos = 0;
   int64_t count = 0;
   int32_t result = 0;

   // get current position
   pos = ftell( (*current).file );

   // move to end of file
   fseek( (*current).file, 0, SEEK_END );

   // get position = size of file
   count = ftell( (*current).file );

   // return to original position
   fseek( (*current).file, pos, SEEK_SET );

   // return true if file at eof or file is empty
   result = ( is_file_end_of_file( current ) != 0 ) || ( count == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_before
*/

int32_t
binary_file_before( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   int64_t pos = 0;

   // return file position
   pos = ftell( (*current).file );

   // return 1 if pos is zero
   if ( pos == 0 )
   {
      result = 1;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_off
*/

int32_t
binary_file_off( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   int64_t pos = 0;

   // return file position
   pos = ftell( (*current).file );

   // return true if pos at 0 or pos at eof
   result = ( pos == 0 ) || ( is_file_end_of_file( current ) != 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_end_of_file
*/

int32_t
binary_file_end_of_file( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   // return true if file at eof or file is empty
   result = is_file_end_of_file( current );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_exists
*/

int32_t
binary_file_exists( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file not open", (*current).file == NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( access( string_as_cstring( (*current).name ), F_OK ) != -1 )
   {
      result = 1;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_is_closed
*/

int32_t
binary_file_is_closed( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // true if file struct member is NULL
   int32_t result = ( (*current).file == NULL );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_is_open_read
*/

int32_t
binary_file_is_open_read( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // return struct member
   int32_t result = (*current).is_open_read;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_is_open_write
*/

int32_t
binary_file_is_open_write( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // return struct member
   int32_t result = (*current).is_open_write;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_is_open_append
*/

int32_t
binary_file_is_open_append( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // return struct member
   int32_t result = (*current).is_open_append;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_open_read
*/

void
binary_file_open_read( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file not open", (*current).file == NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // open file
   (*current).file = fopen( string_as_cstring( (*current).name ), "rb" );
   (*current).is_open_read = 1;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_open_write
*/

void
binary_file_open_write( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file not open", (*current).file == NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // open file
   (*current).file = fopen( string_as_cstring( (*current).name ), "wb" );
   (*current).is_open_write = 1;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_open_append
*/

void
binary_file_open_append( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file not open", (*current).file == NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // open file
   (*current).file = fopen( string_as_cstring( (*current).name ), "ab" );
   (*current).is_open_append = 1;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_open_read_write
*/

void
binary_file_open_read_write( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file not open", (*current).file == NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // open file
   (*current).file = fopen( string_as_cstring( (*current).name ), "r+b" );
   (*current).is_open_read = 1;
   (*current).is_open_write = 1;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_create_read_write
*/

void
binary_file_create_read_write( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file not open", (*current).file == NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // open file
   (*current).file = fopen( string_as_cstring( (*current).name ), "w+b" );
   (*current).is_open_read = 1;
   (*current).is_open_write = 1;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_open_read_append
*/

void
binary_file_open_read_append( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file not open", (*current).file == NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // open file
   (*current).file = fopen( string_as_cstring( (*current).name ), "a+b" );
   (*current).is_open_read = 1;
   (*current).is_open_append = 1;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_close
*/

void
binary_file_close( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // close file, if open
   if ( (*current).file != NULL )
   {
      fclose( (*current).file );
      (*current).file = NULL;
      (*current).is_open_read = 0;
      (*current).is_open_write = 0;
      (*current).is_open_append = 0;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_start
*/

void
binary_file_start( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fseek( (*current).file, 0, SEEK_SET );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_finish
*/

void
binary_file_finish( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fseek( (*current).file, 0, SEEK_END );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_forth
*/

void
binary_file_forth( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fseek( (*current).file, 1, SEEK_CUR );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_back
*/

void
binary_file_back( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fseek( (*current).file, -1, SEEK_CUR );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_move
*/

void
binary_file_move( binary_file_t *current, int64_t offset )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fseek( (*current).file, offset, SEEK_CUR );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_go
*/

void
binary_file_go( binary_file_t *current, int64_t pos )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fseek( (*current).file, pos, SEEK_SET );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_recede
*/

void
binary_file_recede( binary_file_t *current, int64_t pos )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fseek( (*current).file, -pos, SEEK_END );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_flush
*/

void
binary_file_flush( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fflush( (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_touch
*/

void
binary_file_touch( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file not open", (*current).file == NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   utime( string_as_cstring( (*current).name ), NULL );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_rename
*/

void
binary_file_rename( binary_file_t *current, string_t *name )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "name not null", name != NULL );
   PRECONDITION( "binary_file not open", (*current).file == NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   rename( string_as_cstring( (*current).name ), string_as_cstring( name ) );

   string_deep_dispose( &(*current).name );
   (*current).name = string_clone( name );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_rename_cstring
*/

void
binary_file_rename_cstring( binary_file_t *current, char_t *name )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "name not null", name != NULL );
   PRECONDITION( "binary_file not open", (*current).file == NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   rename( string_as_cstring( (*current).name ), name );

   string_deep_dispose( &(*current).name );
   (*current).name = string_make_from_cstring( name );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_int8
*/

void
binary_file_put_int8( binary_file_t *current, int8_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fwrite( &arg, sizeof( int8_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_int16
*/

void
binary_file_put_int16( binary_file_t *current, int16_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fwrite( &arg, sizeof( int16_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_int32
*/

void
binary_file_put_int32( binary_file_t *current, int32_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fwrite( &arg, sizeof( int32_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_int64
*/

void
binary_file_put_int64( binary_file_t *current, int64_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fwrite( &arg, sizeof( int64_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_uint8
*/

void
binary_file_put_uint8( binary_file_t *current, uint8_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fwrite( &arg, sizeof( uint8_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_uint16
*/

void
binary_file_put_uint16( binary_file_t *current, uint16_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fwrite( &arg, sizeof( uint16_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_uint32
*/

void
binary_file_put_uint32( binary_file_t *current, uint32_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fwrite( &arg, sizeof( uint32_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_uint64
*/

void
binary_file_put_uint64( binary_file_t *current, uint64_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fwrite( &arg, sizeof( uint64_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_float32
*/

void
binary_file_put_float32( binary_file_t *current, float32_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fwrite( &arg, sizeof( float32_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_float64
*/

void
binary_file_put_float64( binary_file_t *current, float64_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fwrite( &arg, sizeof( float64_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_int8_be
*/

void
binary_file_put_int8_be( binary_file_t *current, int8_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fwrite( &arg, sizeof( int8_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_int16_be
*/

void
binary_file_put_int16_be( binary_file_t *current, int16_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_16_t u = {0};
   u.i = arg;
   u.u = htobe16( u.u );

   fwrite( &u.u, sizeof( int16_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_int32_be
*/

void
binary_file_put_int32_be( binary_file_t *current, int32_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_Float_32_t u = {0};
   u.i = arg;
   u.u = htobe32( u.u );

   fwrite( &u.u, sizeof( int32_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_int64_be
*/

void
binary_file_put_int64_be( binary_file_t *current, int64_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_Float_64_t u = {0};
   u.i = arg;
   u.u = htobe64( u.u );

   fwrite( &u.u, sizeof( int64_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_uint8_be
*/

void
binary_file_put_uint8_be( binary_file_t *current, uint8_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fwrite( &arg, sizeof( uint8_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_uint16_be
*/

void
binary_file_put_uint16_be( binary_file_t *current, uint16_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint16_t i = 0;

   i = htobe16( arg );

   fwrite( &i, sizeof( uint16_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_uint32_be
*/

void
binary_file_put_uint32_be( binary_file_t *current, uint32_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint32_t i = 0;

   i = htobe32( arg );

   fwrite( &i, sizeof( uint32_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_uint64_be
*/

void
binary_file_put_uint64_be( binary_file_t *current, uint64_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint64_t i = 0;

   i = htobe64( arg );

   fwrite( &i, sizeof( uint64_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_float32_be
*/

void
binary_file_put_float32_be( binary_file_t *current, float32_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_Float_32_t u = {0};
   u.f = arg;
   u.u = htobe32( u.u );

   fwrite( &u.u, sizeof( float32_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_float64_be
*/

void
binary_file_put_float64_be( binary_file_t *current, float64_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_Float_64_t u = {0};
   u.f = arg;
   u.u = htobe64( u.u );

   fwrite( &u.u, sizeof( float64_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_int8_le
*/

void
binary_file_put_int8_le( binary_file_t *current, int8_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fwrite( &arg, sizeof( int8_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_int16_le
*/

void
binary_file_put_int16_le( binary_file_t *current, int16_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_16_t u = {0};
   u.i = arg;
   u.u = htole16( u.u );

   fwrite( &u.u, sizeof( int16_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_int32_le
*/

void
binary_file_put_int32_le( binary_file_t *current, int32_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_Float_32_t u = {0};
   u.i = arg;
   u.u = htole32( u.u );

   fwrite( &u.u, sizeof( int32_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_int64_le
*/

void
binary_file_put_int64_le( binary_file_t *current, int64_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_Float_64_t u = {0};
   u.i = arg;
   u.u = htole64( u.u );

   fwrite( &u.u, sizeof( int64_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_uint8_le
*/

void
binary_file_put_uint8_le( binary_file_t *current, uint8_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fwrite( &arg, sizeof( uint8_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_uint16_le
*/

void
binary_file_put_uint16_le( binary_file_t *current, uint16_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint16_t i = 0;

   i = htole16( arg );

   fwrite( &i, sizeof( uint16_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_uint32_le
*/

void
binary_file_put_uint32_le( binary_file_t *current, uint32_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint32_t i = 0;

   i = htole32( arg );

   fwrite( &i, sizeof( uint32_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_uint64_le
*/

void
binary_file_put_uint64_le( binary_file_t *current, uint64_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint64_t i = 0;

   i = htole64( arg );

   fwrite( &i, sizeof( uint64_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_float32_le
*/

void
binary_file_put_float32_le( binary_file_t *current, float32_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_Float_32_t u = {0};
   u.f = arg;
   u.u = htole32( u.u );

   fwrite( &u.u, sizeof( float32_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_float64_le
*/

void
binary_file_put_float64_le( binary_file_t *current, float64_t arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_Float_64_t u = {0};
   u.f = arg;
   u.u = htole64( u.u );

   fwrite( &u.u, sizeof( float64_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_raw_buffer
*/

void
binary_file_put_raw_buffer( binary_file_t *current, raw_buffer_t *arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   PRECONDITION( "arg not null", arg != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fwrite
   (
      raw_buffer_base( arg ),
      sizeof( uint8_t ),
      raw_buffer_count( arg ),
      (*current).file
   );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_string
*/

void
binary_file_put_string( binary_file_t *current, string_t *arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   PRECONDITION( "arg not null", arg != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fwrite
   (
      string_as_cstring( arg ),
      sizeof( char_t ),
      string_count( arg ) + 1,
      (*current).file
   );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_cstring
*/

void
binary_file_put_cstring( binary_file_t *current, char_t *arg )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   PRECONDITION( "arg not null", arg != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fwrite
   (
      arg,
      sizeof( char_t ),
      strlen( arg ) + 1,
      (*current).file
   );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_put_bytes
*/

void
binary_file_put_bytes( binary_file_t *current, uint8_t *arg, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   PRECONDITION( "arg not null", arg != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   fwrite
   (
      arg,
      sizeof( uint8_t ),
      count,
      (*current).file
   );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_read_int8
*/

int8_t
binary_file_read_int8( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int8_t result = 0;
   fread( &result, sizeof( int8_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_read_int16
*/

int16_t
binary_file_read_int16( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int16_t result = 0;
   fread( &result, sizeof( int16_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_read_int32
*/

int32_t
binary_file_read_int32( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   fread( &result, sizeof( int32_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_read_int64
*/

int64_t
binary_file_read_int64( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int64_t result = 0;
   fread( &result, sizeof( int64_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_read_uint8
*/

uint8_t
binary_file_read_uint8( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint8_t result = 0;

   fread( &result, sizeof( uint8_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_read_uint16
*/

uint16_t
binary_file_read_uint16( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint16_t result = 0;
   fread( &result, sizeof( uint16_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_read_uint32
*/

uint32_t
binary_file_read_uint32( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint32_t result = 0;
   fread( &result, sizeof( uint32_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_read_uint64
*/

uint64_t
binary_file_read_uint64( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint64_t result = 0;
   fread( &result, sizeof( uint64_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_read_float32
*/

float32_t
binary_file_read_float32( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   float32_t result = 0;
   fread( &result, sizeof( float32_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_read_float64
*/

float64_t
binary_file_read_float64( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   float64_t result = 0;
   fread( &result, sizeof( float64_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_read_int8_be
*/

int8_t
binary_file_read_int8_be( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int8_t result = 0;
   fread( &result, sizeof( int8_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_read_int16_be
*/

int16_t
binary_file_read_int16_be( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_16_t result = {0};

   fread( &result.u, sizeof( int16_t ), 1, (*current).file );

   result.u = be16toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.i;
}

/**
   binary_file_read_int32_be
*/

int32_t
binary_file_read_int32_be( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_Float_32_t result = {0};

   fread( &result.u, sizeof( int32_t ), 1, (*current).file );

   result.u = be32toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.i;
}

/**
   binary_file_read_int64_be
*/

int64_t
binary_file_read_int64_be( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_Float_64_t result = {0};

   fread( &result.u, sizeof( int64_t ), 1, (*current).file );

   result.u = be64toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.i;
}

/**
   binary_file_read_uint8_be
*/

uint8_t
binary_file_read_uint8_be( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint8_t result = 0;

   fread( &result, sizeof( uint8_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_read_uint16_be
*/

uint16_t
binary_file_read_uint16_be( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint16_t result = 0;

   fread( &result, sizeof( uint16_t ), 1, (*current).file );

   result = be16toh( result );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_read_uint32_be
*/

uint32_t
binary_file_read_uint32_be( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint32_t result = 0;

   fread( &result, sizeof( uint32_t ), 1, (*current).file );

   result = be32toh( result );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_read_uint64_be
*/

uint64_t
binary_file_read_uint64_be( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint64_t result = 0;

   fread( &result, sizeof( uint64_t ), 1, (*current).file );

   result = be64toh( result );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_read_float32_be
*/

float32_t
binary_file_read_float32_be( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_Float_32_t result = {0};

   fread( &result.u, sizeof( float32_t ), 1, (*current).file );

   result.u = be32toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.f;
}

/**
   binary_file_read_float64_be
*/

float64_t
binary_file_read_float64_be( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_Float_64_t result = {0};

   fread( &result.u, sizeof( float64_t ), 1, (*current).file );

   result.u = be64toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.f;
}

/**
   binary_file_read_int8_le
*/

int8_t
binary_file_read_int8_le( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int8_t result = 0;
   fread( &result, sizeof( int8_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_read_int16_le
*/

int16_t
binary_file_read_int16_le( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_16_t result = {0};

   fread( &result.u, sizeof( int16_t ), 1, (*current).file );

   result.u = le16toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.i;
}

/**
   binary_file_read_int32_le
*/

int32_t
binary_file_read_int32_le( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_Float_32_t result = {0};

   fread( &result.u, sizeof( int32_t ), 1, (*current).file );

   result.u = le32toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.i;
}

/**
   binary_file_read_int64_le
*/

int64_t
binary_file_read_int64_le( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_Float_64_t result = {0};

   fread( &result.u, sizeof( int64_t ), 1, (*current).file );

   result.u = le64toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.i;
}

/**
   binary_file_read_uint8_le
*/

uint8_t
binary_file_read_uint8_le( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint8_t result = 0;

   fread( &result, sizeof( uint8_t ), 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_read_uint16_le
*/

uint16_t
binary_file_read_uint16_le( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint16_t result = 0;

   fread( &result, sizeof( uint16_t ), 1, (*current).file );

   result = le16toh( result );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_read_uint32_le
*/

uint32_t
binary_file_read_uint32_le( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint32_t result = 0;

   fread( &result, sizeof( uint32_t ), 1, (*current).file );

   result = le32toh( result );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_read_uint64_le
*/

uint64_t
binary_file_read_uint64_le( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint64_t result = 0;

   fread( &result, sizeof( uint64_t ), 1, (*current).file );

   result = le64toh( result );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_read_float32_le
*/

float32_t
binary_file_read_float32_le( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_Float_32_t result = {0};

   fread( &result.u, sizeof( float32_t ), 1, (*current).file );

   result.u = le32toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.f;
}

/**
   binary_file_read_float64_le
*/

float64_t
binary_file_read_float64_le( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_Float_64_t result = {0};

   fread( &result.u, sizeof( float64_t ), 1, (*current).file );

   result.u = le64toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.f;
}

/**
   binary_file_read_raw_buffer
*/

raw_buffer_t *
binary_file_read_raw_buffer( binary_file_t *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   raw_buffer_t *result = raw_buffer_make( count );
   fread( raw_buffer_base( result ), sizeof( uint8_t ), count, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_read_string
*/

string_t *
binary_file_read_string( binary_file_t *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = string_make_n( count + 1 );
   char *s = ( char * ) calloc( count + 1, sizeof( char_t ) );
   CHECK( "s allocated correctly", s != NULL );

   fread( s, sizeof( char_t ), count + 1, (*current).file );
   string_append_cstring( result, s );
   free( s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_read_cstring
*/

char_t *
binary_file_read_cstring( binary_file_t *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *result = ( char_t * ) calloc( count + 1, sizeof( char_t ) );
   CHECK( "result allocated correctly", result != NULL );

   fread( result, sizeof( char_t ), count + 1, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_read_bytes
*/

uint8_t *
binary_file_read_bytes( binary_file_t *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*current).file != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint8_t *result = ( uint8_t * ) calloc( count, sizeof( uint8_t ) );
   CHECK( "result allocated correctly", result != NULL );

   fread( result, sizeof( uint8_t ), count, (*current).file );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   binary_file_wipe_out
*/

void
binary_file_wipe_out( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file not open", (*current).file == NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   FILE *fp = NULL;

   // open as write, then close to eliminate contents
   fp = fopen( string_as_cstring( (*current).name ), "w" );
   fclose( fp );
   (*current).file = NULL;
   (*current).is_open_read = 0;
   (*current).is_open_write = 0;
   (*current).is_open_append = 0;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   binary_file_delete
*/

void
binary_file_delete( binary_file_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "binary_file type OK", (*current)._type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file not open", (*current).file == NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // delete file
   remove( string_as_cstring( (*current).name ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */

