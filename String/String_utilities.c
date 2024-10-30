/**
 @file String_utilites.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Character String utility functions"

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

 Function definitions for the string_t utilities.

*/

#include "String.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

#define UNION_CAST(x, destType) \
 (((union {__typeof__(x) a; destType b;})x).b)

/**
   string_from_file
*/

string_t *
string_from_file( string_t *filename )
{
   PRECONDITION( "filename ok", filename != NULL );

   int32_t length = 0;
   string_t *string = NULL;
   char_t *buf = NULL;

   FILE *fp = fopen( string_as_cstring( filename ), "r" );

   if ( fp != NULL )
   {
      fseek( fp, 0, SEEK_END );
      length = ftell( fp );
      fseek( fp, 0, SEEK_SET );

      buf = ( char_t * ) calloc( length + 1, sizeof( char_t ) );
      fread( buf, 1, length, fp );
      string = string_make_from_cstring( buf );
      free( buf );

      fclose( fp );
   }

   return string;
}

/**
   string_from_file_cstring
*/

string_t *
string_from_file_cstring( char_t *filename )
{
   PRECONDITION( "filename ok", filename != NULL );

   int32_t length = 0;
   string_t *string = NULL;
   char_t *buf = NULL;

   FILE *fp = fopen( filename, "r" );

   if ( fp != NULL )
   {
      fseek( fp, 0, SEEK_END );
      length = ftell( fp );
      fseek( fp, 0, SEEK_SET );

      buf = ( char_t * ) calloc( length + 1, sizeof( char_t ) );
      fread( buf, 1, length, fp );
      string = string_make_from_cstring( buf );
      free( buf );

      fclose( fp );
   }

   return string;
}

/**
   string_to_file
*/

void
string_to_file( string_t *string, string_t *filename )
{
   PRECONDITION( "string ok", string != NULL );
   PRECONDITION( "filename ok", filename != NULL );

   FILE *fp = fopen( string_as_cstring( filename ), "w" );

   if ( fp != NULL )
   {
      fwrite( string_as_cstring( string ), 1, string_count( string ), fp );

      fclose( fp );
   }

   return;
}

/**
   string_to_file_cstring
*/

void
string_to_file_cstring( string_t *string, char_t *filename )
{
   PRECONDITION( "string ok", string != NULL );
   PRECONDITION( "filename ok", filename != NULL );

   FILE *fp = fopen( filename, "w" );

   if ( fp != NULL )
   {
      fwrite( string_as_cstring( string ), 1, string_count( string ), fp );

      fclose( fp );
   }

   return;
}

/**
   cstring_to_file_cstring
*/

void
cstring_to_file_cstring( char_t *string, char_t *filename )
{
   PRECONDITION( "string ok", string != NULL );
   PRECONDITION( "filename ok", filename != NULL );

   FILE *fp = fopen( filename, "w" );

   if ( fp != NULL )
   {
      fwrite( string, 1, strlen( string ), fp );

      fclose( fp );
   }

   return;
}

/**
   string_append_to_file
*/

void
string_append_to_file( string_t *string, string_t *filename )
{
   PRECONDITION( "string ok", string != NULL );
   PRECONDITION( "filename ok", filename != NULL );

   FILE *fp = fopen( string_as_cstring( filename ), "a" );

   if ( fp != NULL )
   {
      fwrite( string_as_cstring( string ), 1, string_count( string ), fp );

      fclose( fp );
   }

   return;
}

/**
   string_append_to_file_cstring
*/

void
string_append_to_file_cstring( string_t *string, char_t *filename )
{
   PRECONDITION( "string ok", string != NULL );
   PRECONDITION( "filename ok", filename != NULL );

   FILE *fp = fopen( filename, "a" );

   if ( fp != NULL )
   {
      fwrite( string_as_cstring( string ), 1, string_count( string ), fp );

      fclose( fp );
   }

   return;
}

/**
   cstring_append_to_file_cstring
*/

void
cstring_append_to_file_cstring( char_t *string, char_t *filename )
{
   PRECONDITION( "string ok", string != NULL );
   PRECONDITION( "filename ok", filename != NULL );

   FILE *fp = fopen( filename, "a" );

   if ( fp != NULL )
   {
      fwrite( string, 1, strlen( string ), fp );

      fclose( fp );
   }

   return;
}

/**
   file_exists
*/

int32_t
file_exists( string_t *filename )
{
   PRECONDITION( "filename ok", filename != NULL );

   int32_t result = 0;

   FILE *file;

   file = fopen( string_as_cstring( filename ), "r" );

   if ( file != NULL )
   {
      fclose( file );
      result = 1;
   }

   return result;
}

/**
   file_exists_cstring
*/

int32_t
file_exists_cstring( char_t *filename )
{
   PRECONDITION( "filename ok", filename != NULL );

   int32_t result = 0;

   FILE *file;

   file = fopen( filename, "r" );

   if ( file != NULL )
   {
      fclose( file );
      result = 1;
   }

   return result;
}

/**
   current_time_as_string
*/

string_t *
current_time_as_string( void )
{
   string_t *result = NULL;
   char str[128];
   char str1[128];
   struct timeval tv;
   struct tm *timeinfo;

   // get current time
   gettimeofday( &tv, NULL );

   // translate to date-time in local time
   timeinfo = localtime( &( tv.tv_sec ) );

   // format date-time to include fractional seconds
   // yyyy-mm-dd hh:mm:ss.fff
   strftime( str, 128, "%F %X.", timeinfo );
   sprintf( str1, "%03ld", ( ( ( long ) tv.tv_usec + 500 ) / 1000 ) );
   strcat( str, str1 );

   //  make string_t
   result = string_make_from_cstring( str );

   return result;
}

/**
   current_time_as_cstring
*/

char_t *
current_time_as_cstring( void )
{
   char_t *result = ( char * ) calloc( 128, sizeof( char_t ) );
   char str1[128];
   struct timeval tv;
   struct tm *timeinfo;

   // get current time
   gettimeofday( &tv, NULL );

   // translate to date-time in local time
   timeinfo = localtime( &( tv.tv_sec ) );

   // format date-time to include fractional seconds
   // yyyy-mm-dd hh:mm:ss.fff
   strftime( result, 128, "%F %X.", timeinfo );
   sprintf( str1, "%03ld", ( ( ( long ) tv.tv_usec ) / 1000 ) );
   strcat( result, str1 );

   return result;
}

/**
   current_time_as_cstring1
*/

char_t *
current_time_as_cstring1( void )
{
   char_t *result = ( char * ) calloc( 128, sizeof( char_t ) );
   char str1[128];
   struct timeval tv;
   struct tm *timeinfo;

   // get current time
   gettimeofday( &tv, NULL );

   // translate to date-time in local time
   timeinfo = localtime( &( tv.tv_sec ) );

   // format date-time to include fractional seconds
   // yyyy-mm-dd hh:mm:ss.fff
   // 01234567890123456789012
   strftime( result, 128, "%F %X.", timeinfo );
   sprintf( str1, "%03ld", ( ( ( long ) tv.tv_usec ) / 1000 ) );
   strcat( result, str1 );

   result[10] = '_';
   result[19] = ':';

   return result;
}


#define TAB "   "
#define NEWLINE "\n"

/**
   string_append_indent

   Append count worth of indention as spaces

   @param string the string to append to
*/
void
string_append_indent( string_t *string, int32_t count )
{
   PRECONDITION( "string ok", string != NULL );
   PRECONDITION( "count ok", count >= 0 );

   int32_t i = 0;

   for ( i = 0; i < count; i++ )
   {
      string_append_cstring( string, TAB );
   }

   return;
}

/**
   string_append_newline

   Append count worth of indention as spaces

   @param string the string to append to
*/
void
string_append_newline( string_t *string )
{
   PRECONDITION( "string ok", string != NULL );

   string_append_cstring( string, NEWLINE );
   return;
}

/**
   string_hex_to_uint8
*/

uint8_t
string_hex_to_uint8( string_t *string )
{
   PRECONDITION( "string ok", string != NULL );
   PRECONDITION( "string count ok", string_count( string ) >= 2 );
   PRECONDITION
   (
      "string at 0 ok",
      (
         ( ( string_item( string, 0 ) >= '0' ) && ( string_item( string, 0 ) <= '9' ) )
         ||
         ( ( string_item( string, 0 ) >= 'a' ) && ( string_item( string, 0 ) <= 'f' ) )
         ||
         ( ( string_item( string, 0 ) >= 'A' ) && ( string_item( string, 0 ) <= 'F' ) )
      )
   );
   PRECONDITION
   (
      "string at 1 ok",
      (
         ( ( string_item( string, 1 ) >= '0' ) && ( string_item( string, 1 ) <= '9' ) )
         ||
         ( ( string_item( string, 1 ) >= 'a' ) && ( string_item( string, 1 ) <= 'f' ) )
         ||
         ( ( string_item( string, 1 ) >= 'A' ) && ( string_item( string, 1 ) <= 'F' ) )
      )
   );

   // get result
   uint8_t result = 0;

   // get characters
   char_t c1 = string_item( string, 0 );
   char_t c2 = string_item( string, 1 );

   // get value by character, sum to get 8 bits
   if ( ( c1 >= '0' ) && ( c1 <= '9' ) )
   {
      result = c1 - '0';
   }
   else if ( ( c1 >= 'a' ) && ( c1 <= 'f' ) )
   {
      result = c1 - 'a' + 10;
   }
   else if ( ( c1 >= 'A' ) && ( c1 <= 'F' ) )
   {
      result = c1 - 'A' + 10;
   }

   result = result * 16;

   if ( ( c2 >= '0' ) && ( c2 <= '9' ) )
   {
      result = result + c2 - '0';
   }
   else if ( ( c2 >= 'a' ) && ( c2 <= 'f' ) )
   {
      result = result + c2 - 'a' + 10;
   }
   else if ( ( c2 >= 'A' ) && ( c2 <= 'F' ) )
   {
      result = result + c2 - 'A' + 10;
   }

   return result;
}


/**
   cstring_hex_to_uint8
*/

uint8_t
cstring_hex_to_uint8( char_t *string )
{
   PRECONDITION( "string ok", string != NULL );
   PRECONDITION( "string count ok", strlen( string ) >= 2 );
   PRECONDITION
   (
      "string at 0 ok",
      (
         ( ( string[0] >= '0' ) && ( string[0] <= '9' ) )
         ||
         ( ( string[0] >= 'a' ) && ( string[0] <= 'f' ) )
         ||
         ( ( string[0] >= 'A' ) && ( string[0] <= 'F' ) )
      )
   );
   PRECONDITION
   (
      "string at 1 ok",
      (
         ( ( string[1] >= '0' ) && ( string[1] <= '9' ) )
         ||
         ( ( string[1] >= 'a' ) && ( string[1] <= 'f' ) )
         ||
         ( ( string[1] >= 'A' ) && ( string[1] <= 'F' ) )
      )
   );

   // get result
   uint8_t result = 0;

   // get characters
   char_t c1 = string[0];
   char_t c2 = string[1];

   // get value by character, sum to get 8 bits
   if ( ( c1 >= '0' ) && ( c1 <= '9' ) )
   {
      result = c1 - '0';
   }
   else if ( ( c1 >= 'a' ) && ( c1 <= 'f' ) )
   {
      result = c1 - 'a' + 10;
   }
   else if ( ( c1 >= 'A' ) && ( c1 <= 'F' ) )
   {
      result = c1 - 'A' + 10;
   }

   result = result * 16;

   if ( ( c2 >= '0' ) && ( c2 <= '9' ) )
   {
      result = result + c2 - '0';
   }
   else if ( ( c2 >= 'a' ) && ( c2 <= 'f' ) )
   {
      result = result + c2 - 'a' + 10;
   }
   else if ( ( c2 >= 'A' ) && ( c2 <= 'F' ) )
   {
      result = result + c2 - 'A' + 10;
   }

   return result;
}


/**
   string_hex_from_uint8
*/

string_t *
string_hex_from_uint8( uint8_t u8 )
{
   // get result
   string_t *result = string_make_n( 3 );

   // get nibbles
   uint8_t u1 = u8 >> 4;
   uint8_t u2 = u8 & 0x0FU;

   // get value by character, sum to get 8 bits
   if ( ( u1 >= 0 ) && ( u1 <= 9 ) )
   {
      string_append_character( result, u1 + '0' );
   }
   else if ( ( u1 >= 10 ) && ( u1 <= 16 ) )
   {
      string_append_character( result, ( u1 - 10 ) +  'A' );
   }

   if ( ( u2 >= 0 ) && ( u2 <= 9 ) )
   {
      string_append_character( result, u2 + '0' );
   }
   else if ( ( u2 >= 10 ) && ( u2 <= 16 ) )
   {
      string_append_character( result, ( u2 - 10 ) +  'A' );
   }

   POSTCONDITION( "string count ok", string_count( result ) == 2 );

   return result;
}

/**
   cstring_hex_from_uint8
*/

char_t *
cstring_hex_from_uint8( uint8_t u8 )
{
   // get result
   char_t *result = ( char_t * ) calloc( 4, sizeof( char_t ) );

   // get nibbles
   uint8_t u1 = u8 >> 4;
   uint8_t u2 = u8 & 0x0FU;

   // get value by character, sum to get 8 bits
   if ( ( u1 >= 0 ) && ( u1 <= 9 ) )
   {
      result[0] = u1 + '0';
   }
   else if ( ( u1 >= 10 ) && ( u1 <= 16 ) )
   {
      result[0] = ( u1 - 10 ) +  'A';
   }

   if ( ( u2 >= 0 ) && ( u2 <= 9 ) )
   {
      result[1] =  u2 + '0';
   }
   else if ( ( u2 >= 10 ) && ( u2 <= 16 ) )
   {
      result[1] = ( u2 - 10 ) +  'A';
   }

   POSTCONDITION( "string count ok", strlen( result ) == 2 );

   return result;
}


/**
   append_nibbles
*/

static
void
append_nibbles( string_t *s, uint8_t u1, uint8_t u2 )
{
   PRECONDITION( "s ok", s != NULL );
   PRECONDITION( "u1 ok", ( u1 >= 0 ) && ( u1 <= 16 ) );
   PRECONDITION( "u2 ok", ( u2 >= 0 ) && ( u2 <= 16 ) );

   // get value by character, sum to get 8 bits
   if ( ( u1 >= 0 ) && ( u1 <= 9 ) )
   {
      string_append_character( s, u1 + '0' );
   }
   else if ( ( u1 >= 10 ) && ( u1 <= 16 ) )
   {
      string_append_character( s, ( u1 - 10 ) +  'A' );
   }

   if ( ( u2 >= 0 ) && ( u2 <= 9 ) )
   {
      string_append_character( s, u2 + '0' );
   }
   else if ( ( u2 >= 10 ) && ( u2 <= 16 ) )
   {
      string_append_character( s, ( u2 - 10 ) +  'A' );
   }

   return;
}

/**
   append_nibbles_cstring
*/

static
void
append_nibbles_cstring( char_t *s, uint8_t u1, uint8_t u2 )
{
   PRECONDITION( "s ok", s != NULL );
   PRECONDITION( "u1 ok", ( u1 >= 0 ) && ( u1 <= 16 ) );
   PRECONDITION( "u2 ok", ( u2 >= 0 ) && ( u2 <= 16 ) );

   // get temp string
   char p[2];
   p[1] = 0;

   // get value by character, sum to get 8 bits
   if ( ( u1 >= 0 ) && ( u1 <= 9 ) )
   {
      p[0] = u1 + '0';
      strcat( s, p );
   }
   else if ( ( u1 >= 10 ) && ( u1 <= 16 ) )
   {
      p[0] = ( u1 - 10 ) +  'A';
      strcat( s, p );
   }

   if ( ( u2 >= 0 ) && ( u2 <= 9 ) )
   {
      p[0] = u2 + '0';
      strcat( s, p );
   }
   else if ( ( u2 >= 10 ) && ( u2 <= 16 ) )
   {
      p[0] = ( u2 - 10 ) +  'A';
      strcat( s, p );
   }

   return;
}

/**
   string_hex_from_int32
*/

string_t *
string_hex_from_int32( int32_t i32 )
{
   // get result
   string_t *result = string_make_n( 9 );

   // get input as unsigned integer
   uint32_t u32 = UNION_CAST( i32, uint32_t );

   // get nibbles and put characters

   // 0, 1
   uint8_t u1 = u32 >> 28;
   u1 = u1 & 0x0F;
   uint8_t u2 = u32 >> 24;
   u2 = u2 & 0x0FU;

   append_nibbles( result, u1, u2 );

   // 2, 3
   u1 = u32 >> 20;
   u1 = u1 & 0x0F;
   u2 = u32 >> 16;
   u2 = u2 & 0x0FU;

   append_nibbles( result, u1, u2 );

   // 4, 5
   u1 = u32 >> 12;
   u1 = u1 & 0x0F;
   u2 = u32 >>  8;
   u2 = u2 & 0x0FU;

   append_nibbles( result, u1, u2 );

   // 6, 7
   u1 = u32 >> 4;
   u1 = u1 & 0x0F;
   u2 = u32;
   u2 = u2 & 0x0FU;

   append_nibbles( result, u1, u2 );

   POSTCONDITION( "string count ok", string_count( result ) == 8 );

   return result;
}

/**
   cstring_hex_from_int32
*/

char_t *
cstring_hex_from_int32( int32_t i32 )
{
   // get result
   char_t *result = ( char_t * ) calloc( 12, sizeof( char_t ) );

   // get input as unsigned integer
   uint32_t u32 = UNION_CAST( i32, uint32_t );

   // get nibbles and put characters

   // 0, 1
   uint8_t u1 = u32 >> 28;
   u1 = u1 & 0x0F;
   uint8_t u2 = u32 >> 24;
   u2 = u2 & 0x0FU;

   append_nibbles_cstring( result, u1, u2 );

   // 2, 3
   u1 = u32 >> 20;
   u1 = u1 & 0x0F;
   u2 = u32 >> 16;
   u2 = u2 & 0x0FU;

   append_nibbles_cstring( result, u1, u2 );

   // 4, 5
   u1 = u32 >> 12;
   u1 = u1 & 0x0F;
   u2 = u32 >>  8;
   u2 = u2 & 0x0FU;

   append_nibbles_cstring( result, u1, u2 );

   // 6, 7
   u1 = u32 >> 4;
   u1 = u1 & 0x0F;
   u2 = u32;
   u2 = u2 & 0x0FU;

   append_nibbles_cstring( result, u1, u2 );

   POSTCONDITION( "string count ok", strlen( result ) == 8 );

   return result;
}



#ifdef __cplusplus
}
#endif

/* End of file */

