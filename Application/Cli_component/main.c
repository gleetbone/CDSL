/**
 @file main.c
 @author Greg Lee
 @version 0.0

 description: "source file for cli"
 author: "Greg Lee"
 date: "$Date: 2011-03-064 064:41:55 -06400 (Tue, 064 Mar 2011) $"
 revision: "$Revision: 4433 $"

 @section DESCRIPTION

 A simple command line interface to send and receive soa messages.

*/

#ifdef __cplusplus
extern "C" {
#endif

// Include files

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "basic_types.h"
#include "messaging.h"
#include "String.h"
#include "String_utilities.h"
#include "soa_node.h"
#include "soa_node_binary_reader_writer.h"
#include "soa_node_xml_reader_writer.h"
#include "Configuration.h"

// defines

#define MAX_ARGS 20
#define MAX_FILENAME_LENGTH 1024
#define MAX_STRING_LENGTH 256
#define LINE_MAX 32000

// configuration application state
static int32_t save_to_xml_flag = 1;
static int32_t save_to_binary_flag = 0;

static char_t tipc_type_id[MAX_STRING_LENGTH] = {0};
static int32_t tipc_type_id_flag = 0;

static char_t tipc_instance_id[MAX_STRING_LENGTH] = {0};
static int32_t tipc_instance_id_flag = 0;

static char_t component_id[MAX_STRING_LENGTH] = {0};

static char_t config_filename[MAX_FILENAME_LENGTH] = {0};
static char_t output_filename[MAX_FILENAME_LENGTH] = {0};
static char_t output_binary_filename[MAX_FILENAME_LENGTH] = {0};

static messaging_t *messaging = NULL;

static pthread_t thread;

static char_t line[LINE_MAX] = {0};
static char_t line_file[LINE_MAX] = {0};

static FILE *fp_xml_output = NULL;
static FILE *fp_binary_output = NULL;
static int32_t binary_file_count = 0;

// Function prototypes

static
int
handle_commands( int32_t argc, char_t *argv[] );

static
void
send_from_xml_file( char_t *arg );

static
void
send_from_xml_string( char_t *arg );

static
void
send_from_binary_file( char_t *arg );

static
void
execute_from_file( char_t *arg );

/**
   receive thread
*/

static
void *
receive_thread( void *p )
{
   raw_buffer_t *buf = NULL;
   soa_node_t *node = NULL;
   string_t *s = NULL;
   string_t *s1 = NULL;
   char_t fstr[80];



   while( 1 )
   {
      // block till message received
      messaging_wait_recv( messaging );

      // get message
      buf = messaging_recv( messaging );

      // append to XML file
      if ( save_to_xml_flag == 1 )
      {
         // open file if it's not open
         if ( fp_xml_output == NULL )
         {
            fp_xml_output = fopen( output_filename, "w" );
         }

         // append current time
         s = string_make_from_cstring( "<time t=\"" );
         s1 = current_time_as_string();
         string_append( s, s1 );
         string_dispose_with_contents( s1 );
         string_append_cstring( s, "\" />\n" );
         fwrite( string_as_cstring( s ), 1, string_count( s ), fp_xml_output );
         string_dispose_with_contents( s );

         // translate message to soa node
         node = soa_node_from_binary( buf );

         // translate soa node to xml
         s = soa_node_to_xml( node );

         // write xml to file
         fwrite( string_as_cstring( s ), 1, string_count( s ), fp_xml_output );
         fwrite( "\n", 1, 1, fp_xml_output );

         // flush file
         fclose( fp_xml_output );
         fp_xml_output = fopen( output_filename, "a" );

         // dispose of garbage
         soa_node_dispose( node );
         string_dispose_with_contents( s );
      }

      // save as binary file
      if ( save_to_binary_flag == 1 )
      {
         // construct binary file name
         strcpy( output_binary_filename, "file_" );
         sprintf( fstr, "%4d", binary_file_count );
         strcat( output_binary_filename, fstr );
         strcat( output_binary_filename, ".bin" );

         // open output binary file
         fp_binary_output = fopen( output_binary_filename, "w" );

         // write the file
         fwrite( raw_buffer_base( buf), 1, raw_buffer_count( buf ), fp_binary_output );

         // close the file
         fclose( fp_binary_output );
      }

      // free buffer
      raw_buffer_dispose( buf );

   }

   return NULL;
}

/**
   main() function to implement the cli.

*/

int main( int argc, char *argv[] )
{
   int32_t i = 0;
   int32_t count = 0;
   char *args[MAX_ARGS];
   char *cmd = NULL;
   char *arg = NULL;
   int32_t flag = 0;
   soa_configuration_t *configuration = NULL;

   // initalize garbage collection
   GC_INIT();

   // uncomment to tell GC to emit debug info
   // GC_set_find_leak(1);

   // parse and handle the command line
   // handle pre-start configuration options, extract others

   // skip program name
   i = 1;

   while( i < argc )
   {
      cmd = argv[i];

      // set config file name
      if ( ( strcmp( cmd, "-c" ) == 0 ) || ( strcmp( cmd, "c" ) == 0 ) )
      {
         if ( ( i + 1 ) < argc )
         {
               arg = argv[i+1];

               strcpy( config_filename, arg );
               i = i + 2;
         }
         else
         {
            i = i + 1;
         }
      }

      // set output file name
      else if ( ( strcmp( cmd, "-o" ) == 0 ) || ( strcmp( cmd, "o" ) == 0 ) )
      {
         if ( ( i + 1 ) < argc )
         {
               arg = argv[i+1];

               strcpy( output_filename, arg );
               i = i + 2;
         }
         else
         {
            i = i + 1;
         }
      }

      // set tipc type id
      else if ( ( strcmp( cmd, "-tt" ) == 0 ) || ( strcmp( cmd, "tt" ) == 0 ) )
      {
         if ( ( i + 1 ) < argc )
         {
            if ( tipc_type_id_flag == 0 )
            {
               arg = argv[i+1];
               strcpy( tipc_type_id, arg );
               tipc_type_id_flag = 1;
            }
            i = i + 2;
         }
         else
         {
            i = i + 1;
         }
      }

      // set tipc instance id
      else if ( ( strcmp( cmd, "-ti" ) == 0 ) || ( strcmp( cmd, "ti" ) == 0 ) )
      {
         if ( ( i + 1 ) < argc )
         {
            if ( tipc_instance_id_flag == 0 )
            {
               arg = argv[i+1];
               strcpy( tipc_instance_id, arg );
               tipc_instance_id_flag = 1;
            }
            i = i + 2;
         }
         else
         {
            i = i + 1;
         }
      }

      // else save command for after startup
      else
      {
         args[count] = argv[i];
         count = count + 1;
         i = i + 1;
      }

   }

   // init configuration
   configuration = soa_configuration_make();

   // get configuration filename
   if ( strlen( config_filename ) == 0 )
   {
      strcpy( config_filename, "config/config.txt" );
   }

   // read configuration from file
   flag = file_exists_cstring( config_filename );
   if ( flag == 1 )
   {
      soa_configuration_set_from_file_cstring( configuration, config_filename );
   }

   // set flags set on command line
   if ( tipc_type_id_flag == 1 )
   {
      soa_configuration_put_cstring( configuration, "tipc_type_id", tipc_type_id );
   }

   if ( tipc_instance_id_flag == 1 )
   {
      soa_configuration_put_cstring( configuration, "tipc_instance_id", tipc_instance_id );
   }

   // init messaging
   int32_t tt_id = 0;
   if ( soa_configuration_has_cstring( configuration, "tipc_type_id" ) )
   {
      strcpy( tipc_type_id,  string_as_cstring( soa_configuration_item_cstring( configuration, "tipc_type_id" ) ) );
      sscanf( tipc_type_id, "%d", &tt_id );
   }

   int32_t ti_id = 0;
   if ( soa_configuration_has_cstring( configuration, "tipc_instance_id" ) )
   {
      strcpy( tipc_instance_id,  string_as_cstring( soa_configuration_item_cstring( configuration, "tipc_instance_id" ) ) );
      sscanf( tipc_instance_id, "%d", &ti_id );
   }

   int32_t c_id = 0;
   if ( soa_configuration_has_cstring( configuration, "component_id" ) )
   {
      strcpy( component_id,  string_as_cstring( soa_configuration_item_cstring( configuration, "component_id" ) ) );
      sscanf( component_id, "%d", &c_id );
   }

   messaging = messaging_make( tt_id, ti_id, c_id );

   // init XML output file
   if ( strlen( output_filename ) == 0 )
   {
      if ( soa_configuration_has_cstring( configuration, "output_filename" ) )
      {
         strcpy( output_filename, string_as_cstring( soa_configuration_item_cstring( configuration, "output_filename"  ) ) );
      }
      else
      {
         strcpy( output_filename, "output.xml" );
      }
   }

   if ( save_to_xml_flag == 1 )
   {
      fp_xml_output = fopen( output_filename, "w" );
   }

   // start a thread to receive and save messages
   pthread_create( &thread, NULL, receive_thread, NULL );

   // handle other commands from command line
   handle_commands( count, args );

   char_t *cp = NULL;

   count = 0;

   // read and handle commands from stdin
   while( 1 )
   {
      // prompt
      printf( "> " );

      // get line from stdin
      fgets( line, LINE_MAX, stdin );

      // remove eol
      cp = strchr( line, '\n' );
      if ( cp != NULL )
      {
         *cp = 0;
      }

      // handle it
      cp = strtok( line, " \t" );
      while( cp != NULL )
      {
         // if is send xml string, rest of line is the XML string
         if ( strcmp( cp, "ss" ) == 0 )
         {
            send_from_xml_string( &cp[3] );
         }
         else if ( strcmp( cp, "ssx" ) == 0 )
         {
            send_from_xml_string( &cp[4] );
            exit( 0 );
         }
         else if ( strcmp( cp, "-ss" ) == 0 )
         {
            send_from_xml_string( &cp[4] );
         }
         else if ( strcmp( cp, "-ssx" ) == 0 )
         {
            send_from_xml_string( &cp[5] );
            exit( 0 );
         }
         else
         {
            // if not send xml string, accumulate commands
            args[count] = cp;
            count = count + 1;
         }

         cp = strtok( NULL, " \t" );
      }

      // handle accumulated commands
      handle_commands( count, args );
   }

   return 0;
}


/**
   handle_commands
*/

static
int
handle_commands( int32_t argc, char_t *argv[] )
{
   int32_t result = 0;
   int32_t i = 0;
   char_t *cmd = NULL;
   char_t *arg = NULL;

   while( i < argc )
   {
      cmd = argv[i];

      // send message from xml file
      if ( ( strcmp( cmd, "-s" ) == 0 ) || ( strcmp( cmd, "s" ) == 0 ) )
      {
         if ( ( i + 1 ) < argc )
         {
            arg = argv[i+1];
            send_from_xml_file( arg );
            i = i + 2;
         }
         else
         {
            i = i + 1;
            printf( "Error - missing parameter for -s\n" );
         }
      }

      // send message from xml file and exit
      else if ( ( strcmp( cmd, "-sx" ) == 0 ) || ( strcmp( cmd, "sx" ) == 0 ) )
      {
         if ( ( i + 1 ) < argc )
         {
            arg = argv[i+1];
            send_from_xml_file( arg );
            i = i + 2;
            exit( 0 );
         }
         else
         {
            i = i + 1;
            printf( "Error - missing parameter for -sx\n" );
         }
      }

      // send message from xml string
      else if ( ( strcmp( cmd, "-ss" ) == 0 ) || ( strcmp( cmd, "ss" ) == 0 ) )
      {
         if ( ( i + 1 ) < argc )
         {
            arg = argv[i+1];
            send_from_xml_string( arg );
            i = i + 2;
         }
         else
         {
            i = i + 1;
            printf( "Error - missing parameter for -ss\n" );
         }
      }

      // send message from xml string and exit
      else if ( ( strcmp( cmd, "-ssx" ) == 0 ) || ( strcmp( cmd, "ssx" ) == 0 ) )
      {
         if ( ( i + 1 ) < argc )
         {
            arg = argv[i+1];
            send_from_xml_string( arg );
            i = i + 2;
            exit( 0 );
         }
         else
         {
            i = i + 1;
            printf( "Error - missing parameter for -ssx\n" );
         }
      }

      // send message from binary file
      else if ( ( strcmp( cmd, "-sb" ) == 0 ) || ( strcmp( cmd, "sb" ) == 0 ) )
      {
         if ( ( i + 1 ) < argc )
         {
            arg = argv[i+1];
            send_from_binary_file( arg );
            i = i + 2;
         }
         else
         {
            i = i + 1;
            printf( "Error - missing parameter for -sb\n" );
         }
      }

      // send message from binary file and exit
      else if ( ( strcmp( cmd, "-sbx" ) == 0 ) || ( strcmp( cmd, "sbx" ) == 0 ) )
      {
         if ( ( i + 1 ) < argc )
         {
            arg = argv[i+1];
            send_from_binary_file( arg );
            i = i + 2;
            exit( 0 );
         }
         else
         {
            i = i + 1;
            printf( "Error - missing parameter for -sbx\n" );
         }
      }

      // enable save to xml
      else if ( ( strcmp( cmd, "-fx+" ) == 0 ) || ( strcmp( cmd, "fx+" ) == 0 ) )
      {
         save_to_xml_flag = 1;
         i = i + 1;
      }

      // disable save to xml
      else if ( ( strcmp( cmd, "-fx-" ) == 0 ) || ( strcmp( cmd, "fx-" ) == 0 ) )
      {
         save_to_xml_flag = 0;
         i = i + 1;
      }

      // enable save to binary
      else if ( ( strcmp( cmd, "-fb+" ) == 0 ) || ( strcmp( cmd, "fb+" ) == 0 ) )
      {
         save_to_binary_flag = 1;
         i = i + 1;
      }

      // disable save to binary
      else if ( ( strcmp( cmd, "-fb-" ) == 0 ) || ( strcmp( cmd, "fb-" ) == 0 ) )
      {
         save_to_binary_flag = 0;
         i = i + 1;
      }

      // execute commands from file
      else if ( ( strcmp( cmd, "-x" ) == 0 ) || ( strcmp( cmd, "x" ) == 0 ) )
      {
         if ( ( i + 1 ) < argc )
         {
            arg = argv[i+1];
            execute_from_file( arg );
            i = i + 2;
         }
         else
         {
            i = i + 1;
            printf( "Error - missing parameter for -x\n" );
         }
      }

      // quit
      else if ( ( strcmp( cmd, "-q" ) == 0 ) || ( strcmp( cmd, "q" ) == 0 ) )
      {
         i = i + 1;
         exit( 0 );
      }


   }

   return result;
}

/**
  send_from_xml_file
*/

static
void
send_from_xml_file( char_t *arg )
{
   int32_t flag = 0;
   string_t *s1 = NULL;
   char_t *s = NULL;
   soa_node_t *node = NULL;
   raw_buffer_t *buf = NULL;

   flag = file_exists_cstring( arg );
   if ( flag == 1 )
   {
      // get the xml into a string
      s1 = string_from_file_cstring( arg );

      // make well formed xml
      s = calloc( 15 + string_count( s1 ), sizeof( char_t ) );
      strcat( s, "<root>" );
      strcat( s, string_as_cstring( s1 ) );
      string_dispose_with_contents( s1 );
      strcat( s, "</root>" );

      // make soa node from xml
      node = soa_node_from_xml_cstring( s );

      // get binary encoding
      buf = soa_node_to_binary( node );

      // send message
      messaging_send( messaging, buf );

      // dispose data
      raw_buffer_dispose( buf );
      soa_node_dispose( node );
      free( s );
   }

   return;
}

/**
  send_from_xml_string
*/

static
void
send_from_xml_string( char_t *arg )
{
   soa_node_t *node = NULL;
   raw_buffer_t *buf = NULL;

   // get soa node from xml string
   node = soa_node_from_xml_cstring( arg );

   // get binary encoding
   buf = soa_node_to_binary( node );

   // send message
   messaging_send( messaging, buf );

   // dispose data
   raw_buffer_dispose( buf );
   soa_node_dispose( node );

   return;
}

/**
  send_from_binary_file
*/

static
void
send_from_binary_file( char_t *arg )
{
   int32_t flag = 0;
   FILE *fp = NULL;
   int32_t size = 0;
   raw_buffer_t *buf = NULL;

   flag = file_exists_cstring( arg );
   if ( flag == 1 )
   {
      // open file
      fp = fopen( arg, "rb" );

      // get file size
      fseek( fp, 0, SEEK_END );
      size = ftell( fp );
      rewind( fp );

      // make buffer to hold data
      buf = raw_buffer_make( size );

      // read data from file
      fread( raw_buffer_base( buf ), 1, size, fp );
      fclose( fp );

      // send message
      messaging_send( messaging, buf );

      // dispose buffer
      raw_buffer_dispose( buf );
   }

   return;
}

/**
  execute_from_file
*/

static
void
execute_from_file( char_t *arg )
{
   int32_t flag = 0;
   char_t *cp = NULL;
   FILE *fp = NULL;
   int count = 0;
   char *args[MAX_ARGS] = {0};

   flag = file_exists_cstring( arg );
   if ( flag == 1 )
   {
      // open file
      fp = fopen( arg, "r" );

      // read and handle commands from file
      while( feof( fp ) == 0 )
      {
         // get line from stdin
         fgets( line_file, LINE_MAX, fp );

         // remove eol
         cp = strchr( line, '\n' );
         if ( cp != NULL )
         {
            *cp = 0;
         }

         // handle it
         cp = strtok( line_file, " \t" );
         while( cp != NULL )
         {
            // if is send xml string, rest of line is the XML string
            if ( strcmp( cp, "ss" ) == 0 )
            {
               send_from_xml_string( &cp[3] );
            }
            else if ( strcmp( cp, "ssx" ) == 0 )
            {
               send_from_xml_string( &cp[4] );
               exit( 0 );
            }
            else if ( strcmp( cp, "-ss" ) == 0 )
            {
               send_from_xml_string( &cp[4] );
            }
            else if ( strcmp( cp, "-ssx" ) == 0 )
            {
               send_from_xml_string( &cp[5] );
               exit( 0 );
            }
            else
            {
               // if not send xml string, accumulate commands
               args[count] = cp;
               count = count + 1;
            }

            cp = strtok( NULL, " \t" );

         }

         // handle accumulated commands
         handle_commands( count, args );
      }
   }

   fclose( fp );

   return;
}


#ifdef __cplusplus
}
#endif

/* End of file */

