/**
 @file Binary_File.c
 @author Greg Lee
 @version 1.0.0
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

#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   defines
*/

#define BINARY_FILE_TYPE 0xA5000701

/**
   binary_file structure
*/

struct binary_file_struct
{
   int32_t type;
   
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
   assert(((void) "name not null", name_not_null( p ) ));
   return;
}

#endif

/**
   is_end_of_file
*/

static
int32_t
is_file_end_of_file( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
  
   int64_t pos = 0;
   int64_t count = 0;
   int32_t result = 0;

   // get current position
   pos = ftell( (*binary_file).file );

   // move to end of file
   fseek( (*binary_file).file, 0, SEEK_END );

   // get position = size of file
   count = ftell( (*binary_file).file );

   // return to original position
   fseek( (*binary_file).file, pos, SEEK_SET );

   // return true if file at eof or file is empty
   result = ( feof( (*binary_file).file ) != 0 ) || ( count == pos );

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
   binary_file_t * binary_file = ( binary_file_t * ) calloc( 1, sizeof( binary_file_t ) );

   // set type
   (*binary_file).type = BINARY_FILE_TYPE;

   // set name
   (*binary_file).name = string_make_from( name );

   // set file
   (*binary_file).file = NULL;

   // set flags
   (*binary_file).is_open_read = 0;
   (*binary_file).is_open_write = 0;
   (*binary_file).is_open_append = 0;

   MULTITHREAD_MUTEX_INIT( (*binary_file).mutex );

   INVARIANT( binary_file );

   return binary_file;
}

/**
   binary_file_make_cstring
*/

binary_file_t *
binary_file_make_cstring( char_t *name )
{
   PRECONDITION( "name not null", name != NULL );

   // allocate binary_file struct
   binary_file_t * binary_file = ( binary_file_t * ) calloc( 1, sizeof( binary_file_t ) );

   // set type
   (*binary_file).type = BINARY_FILE_TYPE;

   // set name
   (*binary_file).name = string_make_from_cstring( name );

   // set file
   (*binary_file).file = NULL;

   // set flags
   (*binary_file).is_open_read = 0;
   (*binary_file).is_open_write = 0;
   (*binary_file).is_open_append = 0;

   MULTITHREAD_MUTEX_INIT( (*binary_file).mutex );

   INVARIANT( binary_file );

   return binary_file;
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
   binary_file_make_cstring_open_read
*/
binary_file_t *
binary_file_make_cstring_open_read( char_t *name )
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
   binary_file_make_cstring_open_write
*/
binary_file_t *
binary_file_make_cstring_open_write( char_t *name )
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
   binary_file_make_cstring_open_read_write
*/
binary_file_t *
binary_file_make_cstring_open_read_write( char_t *name )
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
   binary_file_make_cstring_create_read_write
*/
binary_file_t *
binary_file_make_cstring_create_read_write( char_t *name )
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
   binary_file_make_cstring_open_append
*/
binary_file_t *
binary_file_make_cstring_open_append( char_t *name )
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
   binary_file_make_cstring_open_read_append
*/
binary_file_t *
binary_file_make_cstring_open_read_append( char_t *name )
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
binary_file_dispose( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   // delete binary_file name
   string_dispose_with_contents( (*binary_file).name );

   // if file is not NULL, close it
   if ( (*binary_file).file != NULL )
   {
      fclose( (*binary_file).file );
      (*binary_file).file = NULL;
      (*binary_file).is_open_read = 0;
      (*binary_file).is_open_write = 0;
      (*binary_file).is_open_append = 0;
   }

   MULTITHREAD_MUTEX_DESTROY( (*binary_file).mutex );

   // delete binary_file struct
   free( binary_file );

   return;
}


/**
   binary_file_name
*/

string_t *
binary_file_name( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   string_t *result = (*binary_file).name;

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_name_cstring
*/

char_t *
binary_file_name_cstring( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   char_t *result = string_as_cstring( (*binary_file).name );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_position
*/

int64_t
binary_file_position( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   int64_t result = ftell( (*binary_file).file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_count
*/

int64_t
binary_file_count( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   int64_t pos = 0;
   int64_t result = 0;

   // get current position
   pos = ftell( (*binary_file).file );

   // move to end of file
   fseek( (*binary_file).file, 0, SEEK_END );

   // get position = size of file
   result = ftell( (*binary_file).file );

   // return to original position
   fseek( (*binary_file).file, pos, SEEK_SET );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_after
*/

int32_t
binary_file_after( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   int64_t pos = 0;
   int64_t count = 0;
   int32_t result = 0;

   // get current position
   pos = ftell( (*binary_file).file );

   // move to end of file
   fseek( (*binary_file).file, 0, SEEK_END );

   // get position = size of file
   count = ftell( (*binary_file).file );

   // return to original position
   fseek( (*binary_file).file, pos, SEEK_SET );

   // return true if file at eof or file is empty
   result = ( is_file_end_of_file( binary_file ) != 0 ) || ( count == 0 );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_before
*/

int32_t
binary_file_before( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   int32_t result = 0;
   int64_t pos = 0;

   // return file position
   pos = ftell( (*binary_file).file );

   // return 1 if pos is zero
   if ( pos == 0 )
   {
      result = 1;
   }

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_off
*/

int32_t
binary_file_off( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   int32_t result = 0;
   int64_t pos = 0;

   // return file position
   pos = ftell( (*binary_file).file );

   // return true if pos at 0 or pos at eof
   result = ( pos == 0 ) || ( is_file_end_of_file( binary_file ) != 0 );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_end_of_file
*/

int32_t
binary_file_end_of_file( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   int32_t result = 0;

   // return true if file at eof or file is empty
   result = is_file_end_of_file( binary_file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_exists
*/

int32_t
binary_file_exists( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file not open", (*binary_file).file == NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   int32_t result = 0;

   if ( access( string_as_cstring( (*binary_file).name ), F_OK ) != -1 )
   {
      result = 1;
   }

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_is_closed
*/

int32_t
binary_file_is_closed( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   // true if file struct member is NULL
   int32_t result = ( (*binary_file).file == NULL );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_is_open_read
*/

int32_t
binary_file_is_open_read( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   // return struct member
   int32_t result = (*binary_file).is_open_read;

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_is_open_write
*/

int32_t
binary_file_is_open_write( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   // return struct member
   int32_t result = (*binary_file).is_open_write;

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_is_open_append
*/

int32_t
binary_file_is_open_append( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   // return struct member
   int32_t result = (*binary_file).is_open_append;

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_open_read
*/

void
binary_file_open_read( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file not open", (*binary_file).file == NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   // open file
   (*binary_file).file = fopen( string_as_cstring( (*binary_file).name ), "rb" );
   (*binary_file).is_open_read = 1;

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_open_write
*/

void
binary_file_open_write( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file not open", (*binary_file).file == NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   // open file
   (*binary_file).file = fopen( string_as_cstring( (*binary_file).name ), "wb" );
   (*binary_file).is_open_write = 1;

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_open_append
*/

void
binary_file_open_append( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file not open", (*binary_file).file == NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   // open file
   (*binary_file).file = fopen( string_as_cstring( (*binary_file).name ), "ab" );
   (*binary_file).is_open_append = 1;

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_open_read_write
*/

void
binary_file_open_read_write( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file not open", (*binary_file).file == NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   // open file
   (*binary_file).file = fopen( string_as_cstring( (*binary_file).name ), "r+b" );
   (*binary_file).is_open_read = 1;
   (*binary_file).is_open_write = 1;

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_create_read_write
*/

void
binary_file_create_read_write( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file not open", (*binary_file).file == NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   // open file
   (*binary_file).file = fopen( string_as_cstring( (*binary_file).name ), "w+b" );
   (*binary_file).is_open_read = 1;
   (*binary_file).is_open_write = 1;

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_open_read_append
*/

void
binary_file_open_read_append( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file not open", (*binary_file).file == NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   // open file
   (*binary_file).file = fopen( string_as_cstring( (*binary_file).name ), "a+b" );
   (*binary_file).is_open_read = 1;
   (*binary_file).is_open_append = 1;

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_close
*/

void
binary_file_close( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   // close file, if open
   if ( (*binary_file).file != NULL )
   {
      fclose( (*binary_file).file );
      (*binary_file).file = NULL;
      (*binary_file).is_open_read = 0;
      (*binary_file).is_open_write = 0;
      (*binary_file).is_open_append = 0;
   }

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_start
*/

void
binary_file_start( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   fseek( (*binary_file).file, 0, SEEK_SET );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_finish
*/

void
binary_file_finish( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   fseek( (*binary_file).file, 0, SEEK_END );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_forth
*/

void
binary_file_forth( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   fseek( (*binary_file).file, 1, SEEK_CUR );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_back
*/

void
binary_file_back( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   fseek( (*binary_file).file, -1, SEEK_CUR );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_move
*/

void
binary_file_move( binary_file_t *binary_file, int64_t offset )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   fseek( (*binary_file).file, offset, SEEK_CUR );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_go
*/

void
binary_file_go( binary_file_t *binary_file, int64_t pos )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   fseek( (*binary_file).file, pos, SEEK_SET );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_recede
*/

void
binary_file_recede( binary_file_t *binary_file, int64_t pos )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   fseek( (*binary_file).file, -pos, SEEK_END );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_flush
*/

void
binary_file_flush( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   fflush( (*binary_file).file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_touch
*/

void
binary_file_touch( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file not open", (*binary_file).file == NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   utime( string_as_cstring( (*binary_file).name ), NULL );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_rename
*/

void
binary_file_rename( binary_file_t *binary_file, string_t *name )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "name not null", name != NULL );
   PRECONDITION( "binary_file not open", (*binary_file).file == NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   rename( string_as_cstring( (*binary_file).name ), string_as_cstring( name ) );

   string_dispose_with_contents( (*binary_file).name );
   (*binary_file).name = string_make_from( name );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_rename_cstring
*/

void
binary_file_rename_cstring( binary_file_t *binary_file, char_t *name )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "name not null", name != NULL );
   PRECONDITION( "binary_file not open", (*binary_file).file == NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   rename( string_as_cstring( (*binary_file).name ), name );

   string_dispose_with_contents( (*binary_file).name );
   (*binary_file).name = string_make_from_cstring( name );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_put_int8
*/

void
binary_file_put_int8( binary_file_t *binary_file, int8_t arg )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   fwrite( &arg, sizeof( int8_t ), 1, (*binary_file).file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_put_int16
*/

void
binary_file_put_int16( binary_file_t *binary_file, int16_t arg )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   fwrite( &arg, sizeof( int16_t ), 1, (*binary_file).file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_put_int32
*/

void
binary_file_put_int32( binary_file_t *binary_file, int32_t arg )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   fwrite( &arg, sizeof( int32_t ), 1, (*binary_file).file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_put_int64
*/

void
binary_file_put_int64( binary_file_t *binary_file, int64_t arg )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   fwrite( &arg, sizeof( int64_t ), 1, (*binary_file).file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_put_uint8
*/

void
binary_file_put_uint8( binary_file_t *binary_file, uint8_t arg )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   fwrite( &arg, sizeof( uint8_t ), 1, (*binary_file).file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_put_uint16
*/

void
binary_file_put_uint16( binary_file_t *binary_file, uint16_t arg )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   fwrite( &arg, sizeof( uint16_t ), 1, (*binary_file).file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_put_uint32
*/

void
binary_file_put_uint32( binary_file_t *binary_file, uint32_t arg )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   fwrite( &arg, sizeof( uint32_t ), 1, (*binary_file).file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_put_uint64
*/

void
binary_file_put_uint64( binary_file_t *binary_file, uint64_t arg )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   fwrite( &arg, sizeof( uint64_t ), 1, (*binary_file).file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_put_float32
*/

void
binary_file_put_float32( binary_file_t *binary_file, float32_t arg )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   fwrite( &arg, sizeof( float32_t ), 1, (*binary_file).file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_put_float64
*/

void
binary_file_put_float64( binary_file_t *binary_file, float64_t arg )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   fwrite( &arg, sizeof( float64_t ), 1, (*binary_file).file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_put_raw_buffer
*/

void
binary_file_put_raw_buffer( binary_file_t *binary_file, raw_buffer_t *arg )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   PRECONDITION( "arg not null", arg != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   fwrite
   (
      raw_buffer_base( arg ),
      sizeof( uint8_t ),
      raw_buffer_count( arg ),
      (*binary_file).file
   );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_put_string
*/

void
binary_file_put_string( binary_file_t *binary_file, string_t *arg )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   PRECONDITION( "arg not null", arg != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   fwrite
   (
      string_as_cstring( arg ),
      sizeof( char_t ),
      string_count( arg ) + 1,
      (*binary_file).file
   );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_put_cstring
*/

void
binary_file_put_cstring( binary_file_t *binary_file, char_t *arg )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   PRECONDITION( "arg not null", arg != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   fwrite
   (
      arg,
      sizeof( char_t ),
      strlen( arg ) + 1,
      (*binary_file).file
   );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_put_bytes
*/

void
binary_file_put_bytes( binary_file_t *binary_file, uint8_t *arg, int32_t count )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   PRECONDITION( "arg not null", arg != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   fwrite
   (
      arg,
      sizeof( uint8_t ),
      count,
      (*binary_file).file
   );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_read_int8
*/

int8_t
binary_file_read_int8( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   int8_t result = 0;
   fread( &result, sizeof( int8_t ), 1, (*binary_file).file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_read_int16
*/

int16_t
binary_file_read_int16( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   int16_t result = 0;
   fread( &result, sizeof( int16_t ), 1, (*binary_file).file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_read_int32
*/

int32_t
binary_file_read_int32( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   int32_t result = 0;
   fread( &result, sizeof( int32_t ), 1, (*binary_file).file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_read_int64
*/

int64_t
binary_file_read_int64( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   int64_t result = 0;
   fread( &result, sizeof( int64_t ), 1, (*binary_file).file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_read_uint8
*/

uint8_t
binary_file_read_uint8( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   uint8_t result = 0;
   fread( &result, sizeof( uint8_t ), 1, (*binary_file).file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_read_uint16
*/

uint16_t
binary_file_read_uint16( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   uint16_t result = 0;
   fread( &result, sizeof( uint16_t ), 1, (*binary_file).file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_read_uint32
*/

uint32_t
binary_file_read_uint32( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   uint32_t result = 0;
   fread( &result, sizeof( uint32_t ), 1, (*binary_file).file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_read_uint64
*/

uint64_t
binary_file_read_uint64( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   uint64_t result = 0;
   fread( &result, sizeof( uint64_t ), 1, (*binary_file).file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_read_float32
*/

float32_t
binary_file_read_float32( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   float32_t result = 0;
   fread( &result, sizeof( float32_t ), 1, (*binary_file).file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_read_float64
*/

float64_t
binary_file_read_float64( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   float64_t result = 0;
   fread( &result, sizeof( float64_t ), 1, (*binary_file).file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_read_raw_buffer
*/

raw_buffer_t *
binary_file_read_raw_buffer( binary_file_t *binary_file, int32_t count )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   raw_buffer_t *result = raw_buffer_make( count );
   fread( raw_buffer_base( result ), sizeof( uint8_t ), count, (*binary_file).file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_read_string
*/

string_t *
binary_file_read_string( binary_file_t *binary_file, int32_t count )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   string_t *result = string_make_n( count + 1 );
   char *s = ( char * ) calloc( count + 1, sizeof( char_t ) );
   fread( s, sizeof( char_t ), count + 1, (*binary_file).file );
   string_append_cstring( result, s );
   free( s );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_read_cstring
*/

char_t *
binary_file_read_cstring( binary_file_t *binary_file, int32_t count )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   char_t *result = ( char_t * ) calloc( count + 1, sizeof( char_t ) );
   fread( result, sizeof( char_t ), count + 1, (*binary_file).file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_read_bytes
*/

uint8_t *
binary_file_read_bytes( binary_file_t *binary_file, int32_t count )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file open", (*binary_file).file != NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   uint8_t *result = ( uint8_t * ) calloc( count, sizeof( uint8_t ) );
   fread( result, sizeof( uint8_t ), count, (*binary_file).file );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return result;
}

/**
   binary_file_wipe_out
*/

void
binary_file_wipe_out( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file not open", (*binary_file).file == NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   FILE *fp = NULL;

   // open as write, then close to eliminate contents
   fp = fopen( string_as_cstring( (*binary_file).name ), "w" );
   fclose( fp );
   (*binary_file).file = NULL;
   (*binary_file).is_open_read = 0;
   (*binary_file).is_open_write = 0;
   (*binary_file).is_open_append = 0;

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

/**
   binary_file_delete
*/

void
binary_file_delete( binary_file_t *binary_file )
{
   PRECONDITION( "binary_file not null", binary_file != NULL );
   PRECONDITION( "binary_file type OK", (*binary_file).type == BINARY_FILE_TYPE );
   PRECONDITION( "binary_file not open", (*binary_file).file == NULL );
   LOCK( (*binary_file).mutex );
   INVARIANT( binary_file );

   // delete file
   remove( string_as_cstring( (*binary_file).name ) );

   INVARIANT( binary_file );
   UNLOCK( (*binary_file).mutex );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */

