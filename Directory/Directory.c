/**
 @file Directory.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Directories (contains files, links, and other directories"

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

 Function definitions for the opaque directory_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include "Directory.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   defines
*/

/**
   directory structure
*/

struct directory_struct
{
   int32_t _type;

   string_t *name;
   DIR *dir;
   string_t *last_entry;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/*
   local functions
*/

/**
   read_directory

   get a directory entry

   @param directory the directory to read from
   @return the directory entry
*/
struct dirent *
read_directory( DIR *directory )
{
   struct dirent *result = NULL;
   int32_t flag = 0;

   // get directory entry
   result = readdir( directory );

   flag = 0;
   while( flag == 0 )
   {
      if ( result != NULL )
      {
         if (
            ( strcmp( (*result).d_name, "." ) == 0 )
            ||
            ( strcmp( (*result).d_name, ".." ) == 0 )
         )
         {
            // get next directory entry
            result = readdir( directory );

            flag = 0;
         }
         else
         {
            flag = 1;
         }
      }
      else
      {
         flag = 1;
      }
   }

   return result;
}

#if INVARIANT_CONDITIONAL != 0

static
int32_t
name_not_null( directory_t *p )
{
   int32_t result = 1;

   result = ( (*p).name != NULL );

   return result;
}

static
void invariant( directory_t *p )
{
   assert( ( ( void ) "name not null", name_not_null( p ) ) );
   return;
}

#endif

/**
   get_num_files

   return the number of files

   @param dir_name the name of the directory
   @return the number of files in the directory
*/
static
int32_t
get_num_files( string_t *dir_name )
{
   DIR *dir = NULL;
   struct dirent *ent = NULL;
   int32_t result = 0;
   int32_t flag = 0;

   // open the directory for reading
   dir = opendir( string_as_cstring( dir_name ) );

   // if the directory exists, continue
   if ( dir != NULL )
   {
      while( flag == 0 )
      {
         // get directory entry
         ent = read_directory( dir );

         if ( ent == NULL )
         {
            flag = 1;
         }
         else
         {
            // if the entry is a file, count it
            if ( (*ent).d_type == DT_REG )
            {
               result = result + 1;
            }
         }
      }

      // close the directory
      closedir( dir );
   }

   return result;
}

/**
   get_num_directories

   return the number of directories

   @param dir_name the name of the directory
   @return the number of directories in the directory
*/
static
int32_t
get_num_directories( string_t *dir_name )
{
   DIR *dir = NULL;
   struct dirent *ent = NULL;
   int32_t result = 0;
   int32_t flag = 0;

   // open the directory for reading
   dir = opendir( string_as_cstring( dir_name ) );

   // if the directory exists, continue
   if ( dir != NULL )
   {
      while( flag == 0 )
      {
         // get directory entry
         ent = read_directory( dir );

         if ( ent == NULL )
         {
            flag = 1;
         }
         else
         {
            // if the entry is a file, count it
            if ( (*ent).d_type == DT_DIR )
            {
               result = result + 1;
            }
         }
      }

      // close the directory
      closedir( dir );
   }

   return result;
}

/**
   get_num_links

   return the number of links

   @param dir_name the name of the directory
   @return the number of links in the directory
*/
static
int32_t
get_num_links( string_t *dir_name )
{
   DIR *dir = NULL;
   struct dirent *ent = NULL;
   int32_t result = 0;
   int32_t flag = 0;

   // open the directory for reading
   dir = opendir( string_as_cstring( dir_name ) );

   // if the directory exists, continye
   if ( dir != NULL )
   {
      while( flag == 0 )
      {
         // get directory entry
         ent = read_directory( dir );

         if ( ent == NULL )
         {
            flag = 1;
         }
         else
         {
            // if the entry is a file, count it
            if ( (*ent).d_type == DT_LNK )
            {
               result = result + 1;
            }
         }
      }

      // close the directory
      closedir( dir );
   }

   return result;
}

/**
   does_directory_exist

   retuns 1 if the directory exists

   @param name the name of the directory to check for
   @return 1 if directory exists, 0 otherwise
*/

static
int32_t
does_directory_exist( string_t *name )
{
   int32_t result = 0;
   struct stat sb;

   if (
      ( stat( string_as_cstring( name ), &sb ) == 0 )
      &&
      ( S_ISDIR( sb.st_mode ) )
   )
   {
      result = 1;
   }

   return result;
}

/**
   directory_make
*/

directory_t *
directory_make( string_t *name )
{
   PRECONDITION( "name not null", name != NULL );

   // allocate directory struct
   directory_t * directory = ( directory_t * ) calloc( 1, sizeof( directory_t ) );
   CHECK( "directory allocated correctly", directory != NULL );

   // set type
   (*directory)._type = DIRECTORY_TYPE;

   // set name
   (*directory).name = string_clone( name );

   // set dir
   (*directory).dir = NULL;

   // set last_entry
   (*directory).last_entry = NULL;

   MULTITHREAD_MUTEX_INIT( (*directory).mutex );

   INVARIANT( directory );

   return directory;
}

/**
   directory_make_cstring
*/

directory_t *
directory_make_cstring( char_t *name )
{
   PRECONDITION( "name not null", name != NULL );

   // allocate directory struct
   directory_t * directory = ( directory_t * ) calloc( 1, sizeof( directory_t ) );
   CHECK( "directory allocated correctly", directory != NULL );

   // set type
   (*directory)._type = DIRECTORY_TYPE;

   // set name
   (*directory).name = string_make_from_cstring( name );

   // set dir
   (*directory).dir = NULL;

   // set last_entry
   (*directory).last_entry = NULL;

   MULTITHREAD_MUTEX_INIT( (*directory).mutex );

   INVARIANT( directory );

   return directory;
}

/**
   directory_clone
*/

directory_t *
directory_clone( directory_t *other )
{
   PRECONDITION( "other not null", other != NULL );
   INVARIANT( other );
   LOCK( (*other).mutex );

   // allocate directory struct
   directory_t * directory = ( directory_t * ) calloc( 1, sizeof( directory_t ) );
   CHECK( "directory allocated correctly", directory != NULL );

   // set type
   (*directory)._type = DIRECTORY_TYPE;

   // set name
   (*directory).name = string_clone( (*other).name );

   // set dir
   (*directory).dir = NULL;

   // set last_entry
   (*directory).last_entry = NULL;

   MULTITHREAD_MUTEX_INIT( (*directory).mutex );

   INVARIANT( directory );
   INVARIANT( other );

   UNLOCK( (*other).mutex );

   return directory;
}

/**
   directory_deep_clone
*/

directory_t *
directory_deep_clone( directory_t *other )
{
   // deep_clone is same as clone for this type
   return directory_clone( other );
}

/**
   directory_is_equal
*/

int32_t
directory_is_equal( directory_t *current, directory_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "other not null", other != NULL );
   INVARIANT( current );
   INVARIANT( other );

   int32_t result = string_is_equal( (*current).name, (*other).name );

   INVARIANT( current );
   INVARIANT( other );

   return result;
}

/**
   directory_is_deep_equal
*/

int32_t
directory_is_deep_equal( directory_t *current, directory_t *other )
{
   // is_deep_equal is same as is_equal for this type
   return directory_is_equal( current, other );
}

/**
   directory_copy
*/

void
directory_copy( directory_t *current, directory_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "other not null", other != NULL );
   INVARIANT( current );
   INVARIANT( other );

   // copy name
   string_wipe_out( (*current).name );
   string_append( (*current).name, (*other).name );

   // if dir is not NULL, close it
   if ( (*current).dir != NULL )
   {
      closedir( (*current).dir );
      (*current).dir = NULL;
   }

   // wipe out last entry
   if ( (*current).last_entry != NULL )
   {
      string_wipe_out( (*current).last_entry );
   }

   INVARIANT( current );
   INVARIANT( other );

   return;
}

/**
   directory_deep_copy
*/

void
directory_deep_copy( directory_t *current, directory_t *other )
{
   // deep_copy is same as copy for this type
   directory_copy( current, other );
   return;
}

/**
   directory_dispose
*/

void
directory_dispose( directory_t **directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "*directory not null", *directory != NULL );
   PRECONDITION( "directory type OK", (**directory)._type == DIRECTORY_TYPE );
   LOCK( (**directory).mutex );
   INVARIANT(*directory);

   // delete directory name
   string_deep_dispose( &(**directory).name );

   // if dir is not NULL, close it
   if ( (**directory).dir != NULL )
   {
      closedir( (**directory).dir );
   }

   // if last_entry is not NULL, dispose it
   if ( (**directory).last_entry != NULL )
   {
      string_deep_dispose( &(**directory).last_entry );
   }

   MULTITHREAD_MUTEX_DESTROY( (**directory).mutex );

   // delete directory struct
   free(*directory);

   // set directory to NULL
   *directory = NULL;
   return;
}

/**
   directory_deep_dispose
*/

void
directory_deep_dispose( directory_t **directory )
{
   // deep_dispose is same as dispose for this type
   directory_dispose( directory );

   return;
}


/**
   directory_name
*/

string_t *
directory_name( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   string_t *result = (*directory).name;

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return result;
}

/**
   directory_name_cstring
*/

char_t *
directory_name_cstring( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   char_t *result = string_as_cstring( (*directory).name );

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return result;
}

/**
   directory_last_entry
*/

string_t *
directory_last_entry( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   string_t *result = (*directory).last_entry;

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return result;
}

/**
   directory_last_entry_cstring
*/

char_t *
directory_last_entry_cstring( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   char_t *result = string_as_cstring( (*directory).last_entry );

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return result;
}

/**
   directory_filenames
*/

string_t **
directory_filenames( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   int32_t num_files = 0;
   DIR *dir = NULL;
   int32_t flag = 0;
   struct dirent *ent = NULL;
   string_t *s = NULL;
   int32_t i = 0;

   num_files = get_num_files( (*directory).name );

   string_t **result = ( string_t ** ) calloc( num_files + 1, sizeof( string_t * ) );
   CHECK( "result allocated correctly", result != NULL );

   // open the directory for reading
   dir = opendir( string_as_cstring( (*directory).name ) );

   // if the directory exists, continue
   if ( dir != NULL )
   {
      while( flag == 0 )
      {
         // get directory entry
         ent = read_directory( dir );

         if ( ent == NULL )
         {
            flag = 1;
         }
         else
         {
            // if the entry is a file, copy its name, put into result
            if ( (*ent).d_type == DT_REG )
            {
               s = string_make_from_cstring( (*ent).d_name );
               result[i] = s;
               i = i + 1;
            }
         }
      }

      // close the directory
      closedir( dir );
   }

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return result;
}

/**
   directory_filenames_cstring
*/
char_t **
directory_filenames_cstring( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   int32_t num_files = 0;
   DIR *dir = NULL;
   int32_t flag = 0;
   struct dirent *ent = NULL;
   char_t *cp = NULL;
   int32_t i = 0;

   num_files = get_num_files( (*directory).name );

   char_t **result = ( char_t ** ) calloc( num_files + 1, sizeof( char_t * ) );
   CHECK( "result allocated correctly", result != NULL );

   // open the directory for reading
   dir = opendir( string_as_cstring( (*directory).name ) );

   // if the directory exists, continue
   if ( dir != NULL )
   {
      while( flag == 0 )
      {
         // get directory entry
         ent = read_directory( dir );

         if ( ent == NULL )
         {
            flag = 1;
         }
         else
         {
            // if the entry is a file, copy its name, put into result
            if ( (*ent).d_type == DT_REG )
            {
               cp = calloc( strlen( (*ent).d_name ) + 1, sizeof( char ) );
               CHECK( "cp allocated correctly", cp != NULL );

               strcat( cp, (*ent).d_name );
               result[i] = cp;
               i = i + 1;
            }
         }
      }

      // close the directory
      closedir( dir );
   }

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return result;
}

/**
   directory_filenames_count
*/
int32_t
directory_filenames_count( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   int32_t result = get_num_files( (*directory).name );

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return result;
}

/**
   directory_directories
*/

string_t **
directory_directories( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   int32_t num_directories = 0;
   DIR *dir = NULL;
   int32_t flag = 0;
   struct dirent *ent = NULL;
   string_t *s = NULL;
   int32_t i = 0;

   num_directories = get_num_directories( (*directory).name );

   string_t **result = ( string_t ** ) calloc( num_directories + 1, sizeof( string_t * ) );
   CHECK( "result allocated correctly", result != NULL );

   // open the directory for reading
   dir = opendir( string_as_cstring( (*directory).name ) );

   // if the directory exists, continue
   if ( dir != NULL )
   {
      while( flag == 0 )
      {
         // get directory entry
         ent = read_directory( dir );

         if ( ent == NULL )
         {
            flag = 1;
         }
         else
         {
            // if the entry is a file, copy its name, put into result
            if (  (*ent).d_type == DT_DIR )
            {
               s = string_make_from_cstring( (*ent).d_name );
               result[i] = s;
               i = i + 1;
            }
         }
      }

      // close the directory
      closedir( dir );
   }

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return result;
}

/**
   directory_directories_cstring
*/

char_t **
directory_directories_cstring( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   int32_t num_directories = 0;
   DIR *dir = NULL;
   int32_t flag = 0;
   struct dirent *ent = NULL;
   char_t *cp = NULL;
   int32_t i = 0;

   num_directories = get_num_directories( (*directory).name );

   char_t **result = ( char ** ) calloc( num_directories + 1, sizeof( char_t * ) );
   CHECK( "result allocated correctly", result != NULL );

   // open the directory for reading
   dir = opendir( string_as_cstring( (*directory).name ) );

   // if the directory exists, continue
   if ( dir != NULL )
   {
      while( flag == 0 )
      {
         // get directory entry
         ent = read_directory( dir );

         if ( ent == NULL )
         {
            flag = 1;
         }
         else
         {
            // if the entry is a file, copy its name, put into result
            if ( (*ent).d_type == DT_DIR )
            {
               cp = calloc( strlen( (*ent).d_name ) + 1, sizeof( char ) );
               CHECK( "cp allocated correctly", cp != NULL );

               strcat( cp, (*ent).d_name );
               result[i] = cp;
               i = i + 1;
            }
         }
      }

      // close the directory
      closedir( dir );
   }

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return result;
}

/**
   directory_directories_count
*/
int32_t
directory_directories_count( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   int32_t result = get_num_directories( (*directory).name );

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return result;
}

/**
   directory_links
*/

string_t **
directory_links( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   int32_t num_links = 0;
   DIR *dir = NULL;
   int32_t flag = 0;
   struct dirent *ent = NULL;
   string_t *s = NULL;
   int32_t i = 0;

   num_links = get_num_links( (*directory).name );

   string_t **result = ( string_t ** ) calloc( num_links + 1, sizeof( string_t * ) );
   CHECK( "result allocated correctly", result != NULL );

   // open the directory for reading
   dir = opendir( string_as_cstring( (*directory).name ) );

   // if the directory exists, continue
   if ( dir != NULL )
   {
      while( flag == 0 )
      {
         // get directory entry
         ent = read_directory( dir );

         if ( ent == NULL )
         {
            flag = 1;
         }
         else
         {
            // if the entry is a file, copy its name, put into result
            if ( (*ent).d_type == DT_LNK )
            {
               s = string_make_from_cstring( (*ent).d_name );
               result[i] = s;
               i = i + 1;
            }
         }
      }

      // close the directory
      closedir( dir );
   }

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return result;
}

/**
   directory_links_cstring
*/

char_t **
directory_links_cstring( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   int32_t num_links = 0;
   DIR *dir = NULL;
   int32_t flag = 0;
   struct dirent *ent = NULL;
   char_t *cp = NULL;
   int32_t i = 0;

   num_links = get_num_links( (*directory).name );

   char_t **result = ( char ** ) calloc( num_links + 1, sizeof( char_t * ) );
   CHECK( "result allocated correctly", result != NULL );

   // open the directory for reading
   dir = opendir( string_as_cstring( (*directory).name ) );

   // if the directory exists, continue
   if ( dir != NULL )
   {
      while( flag == 0 )
      {
         // get directory entry
         ent = read_directory( dir );

         if ( ent == NULL )
         {
            flag = 1;
         }
         else
         {
            // if the entry is a file, copy its name, put into result
            if ( (*ent).d_type == DT_LNK )
            {
               cp = calloc( strlen( (*ent).d_name ) + 1, sizeof( char ) );
               CHECK( "cp allocated correctly", cp != NULL );

               strcat( cp, (*ent).d_name );
               result[i] = cp;
               i = i + 1;
            }
         }
      }

      // close the directory
      closedir( dir );
   }

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return result;
}

/**
   directory_links_count
*/
int32_t
directory_links_count( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   int32_t result = get_num_files( (*directory).name );

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return result;
}

/**
   directory_is_closed
*/

int32_t
directory_is_closed( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   int32_t result = ( (*directory).dir == NULL );

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return result;
}

/**
   directory_is_open_read
*/

int32_t
directory_is_open_read( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   int32_t result = ( (*directory).dir != NULL );

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return result;
}

/**
   directory_end_of_input
*/

int32_t
directory_end_of_input( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   int32_t result = ( (*directory).last_entry == NULL );

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return result;
}

/**
   directory_exists
*/

int32_t
directory_exists( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   int32_t result = does_directory_exist( (*directory).name );

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return result;
}

/**
   directory_is_readable
*/

int32_t
directory_is_readable( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   int32_t result = 0;
   DIR *dir = NULL;

   // open the directory for reading
   dir = opendir( string_as_cstring( (*directory).name ) );

   if ( dir != NULL )
   {
      result = 1;

      // only close the directory if it is non-null
      closedir( dir );
   }

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return result;
}


/**
   directory_is_empty
*/

int32_t
directory_is_empty( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   int32_t count = 0;

   int32_t result = 0;

   count = get_num_files( (*directory).name )
           + get_num_directories( (*directory).name )
           + get_num_links( (*directory).name );

   result = ( count == 0 );

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return result;
}

/**
   directory_open_read
*/

void
directory_open_read( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   struct dirent *ent = NULL;

   // open directory for read
   (*directory).dir = opendir( string_as_cstring( (*directory).name ) );

   // get first entry into last_entry
   if ( (*directory).dir != NULL )
   {
      // get directory entry
      ent = read_directory( (*directory).dir );

      if ( ent != NULL )
      {
         // if the entry is a file, copy its name, put into result
         (*directory).last_entry = string_make_from_cstring( (*ent).d_name );
      }
   }


   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return;
}

/**
   directory_close
*/

void
directory_close( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   if ( (*directory).dir != NULL )
   {
      closedir( (*directory).dir );
      (*directory).dir = NULL;
   }

   if ( (*directory).last_entry != NULL )
   {
      string_deep_dispose( &(*directory).last_entry );
      (*directory).last_entry = NULL;
   }

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return;
}

/**
   directory_create
*/

void
directory_create( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   mkdir( string_as_cstring( (*directory).name ), 0777 );

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return;
}

/**
   directory_create_mode
*/

void
directory_create_mode( directory_t *directory, int32_t mode )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   mkdir( string_as_cstring( (*directory).name ), mode );

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return;
}

/**
   directory_recursive_create
*/

void
directory_recursive_create( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   string_t **array = NULL;
   int32_t count = 0;
   string_t *s = NULL;
   int32_t i = 0;

   // split directory name/path into separate directory names
   array = string_split_cstring( (*directory).name, "/", &count );

   s = string_make_n( 132 );

   if ( string_item( (*directory).name, 0 ) == '/' )
   {
      string_append_cstring( s, "/" );
   }

   for( i = 0; i < count; i++ )
   {
      string_append( s, array[i] );
      if ( does_directory_exist( s ) == 0 )
      {
         mkdir( string_as_cstring( s ), 0777 );
      }
      string_append_cstring( s, "/" );
   }

   // dispose of temp variables
   string_deep_dispose( &s );

   for ( i = 0; i < count; i++ )
   {
      string_deep_dispose( &array[i] );
   }

   free( array );

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return;
}

/**
   directory_delete
*/

void
directory_delete( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   rmdir( string_as_cstring( (*directory).name ) );

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return;
}

/**
   directory_delete_files
*/

void
directory_delete_files( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   DIR *dir = NULL;
   int32_t flag = 0;
   struct dirent *ent = NULL;
   string_t *s = NULL;

   // open the directory for reading
   dir = opendir( string_as_cstring( (*directory).name ) );

   // get string to use
   s = string_make_n( 128 );

   // if the directory exists, continue
   if ( dir != NULL )
   {
      while( flag == 0 )
      {
         // get directory entry
         ent = read_directory( dir );

         if ( ent == NULL )
         {
            flag = 1;
         }
         else
         {
            // if the entry is a file, delete it
            if ( (*ent).d_type == DT_REG )
            {
               string_wipe_out( s );
               string_append( s, (*directory).name );
               string_append_cstring( s, "/" );
               string_append_cstring( s, (*ent).d_name );
               remove( string_as_cstring( s ) );
            }
         }
      }

      // close the directory
      closedir( dir );
   }

   // clean up garbage
   string_deep_dispose( &s );

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return;
}

/**
   directory_recursive_delete
*/

void
directory_recursive_delete( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   string_t **array = NULL;
   int32_t count = 0;
   string_t *s = NULL;
   int32_t i = 0;
   int32_t i1 = 0;
   int32_t starts_with_slash = 0;

   // split directory name/path into separate directory names
   array = string_split_cstring( (*directory).name, "/", &count );

   s = string_make_n( 132 );

   if ( string_item( (*directory).name, 0 ) == '/' )
   {
      starts_with_slash = 1;
   }

   // delete each directory from the bottom up
   for( i = 0; i < count; i++ )
   {
      string_wipe_out( s );
      if ( starts_with_slash == 1 )
      {
         string_append_cstring( s, "/" );
      }

      // construct directory path
      for ( i1 = 0; i1 < ( count - i ); i1++ )
      {
         string_append( s, array[i1] );
         if ( i1 < ( count - i - 1 ) )
         {
            string_append_cstring( s, "/" );
         }
      }

      // delete the directory
      rmdir( string_as_cstring( s ) );

   }

   // dispose of temp variables
   string_deep_dispose( &s );

   for ( i = 0; i < count; i++ )
   {
      string_deep_dispose( &array[i] );
   }

   free( array );

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return;
}

/**
   directory_read_next_entry
*/

void
directory_read_next_entry( directory_t *directory )
{
   PRECONDITION( "directory not null", directory != NULL );
   PRECONDITION( "directory type OK", (*directory)._type == DIRECTORY_TYPE );
   PRECONDITION( "directory open", (*directory).dir != NULL );
   LOCK( (*directory).mutex );
   INVARIANT( directory );

   struct dirent *ent = NULL;
   string_t *s = NULL;

   // get next entry into last_entry
   if ( (*directory).dir != NULL )
   {
      s = (*directory).last_entry;

      // get directory entry
      ent = read_directory( (*directory).dir );

      if ( ent != NULL )
      {
         // copy entry's name, put into result
         (*directory).last_entry = string_make_from_cstring( (*ent).d_name );
      }
      else
      {
         (*directory).last_entry = NULL;
      }
   }

   // dispose of any previous last_entry
   if ( s != NULL )
   {
      string_deep_dispose( &s );
   }

   INVARIANT( directory );
   UNLOCK( (*directory).mutex );

   return;
}


#ifdef __cplusplus
}
#endif

/* End of file */

