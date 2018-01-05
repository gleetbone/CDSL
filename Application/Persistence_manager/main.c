/**
 @file main.c
 @author Greg Lee
 @version 0.0

 description: "source file for persistence component"
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
#include "soa_local_store.h"
#include "soa_data_store.h"
#include "soa_component.h"
#include "soa_component_utility.h"
#include "snstp.h"
#include "snstp_DList.h"
#include "Configuration.h"
#include "soa_heartbeat_monitor.h"
#include "soa_timer.h"

// defines

#define MAX_ARGS 100
#define MAX_FILENAME_LENGTH 1024
#define MAX_STRING_LENGTH 256
#define LINE_MAX 32000

// configuration application state

static char_t tipc_type_id[MAX_STRING_LENGTH] = {0};
static char_t tipc_instance_id[MAX_STRING_LENGTH] = {0};
static char_t component_id[MAX_STRING_LENGTH] = {0};
static char_t component_priority[MAX_STRING_LENGTH] = {0};
static char_t restore_flag[MAX_STRING_LENGTH] = {0};

static char_t config_filename[MAX_FILENAME_LENGTH] = {0};
static char_t directory[MAX_FILENAME_LENGTH] = {0};

static soa_configuration_t *configuration = NULL;
static soa_local_store_t *local_store = NULL;
static soa_data_store_t *data_store = NULL;
static soa_heartbeat_monitor_t *heartbeat_monitor = NULL;
static soa_component_t *soa_component = NULL;

/**
   callback to update data store on receipt of message
*/

static void callback
(
   void *user_defined,
   string_t *command,
   soa_node_t *update,
   string_t *path
)
{
   // save all received messages
   soa_data_store_put_message
   (
      data_store,
      path,
      command,
      update
   );

   return;
}

/**
   main_loop function prototype
*/

void
main_loop( void );

/**
   main() function to implement the persistence component.

*/

int main( int argc, char *argv[] )
{
   int32_t i = 0;
   int32_t count = 0;
   s_dlist_t *args = NULL;
   char *cmd = NULL;
   char *arg = NULL;
   int32_t flag = 0;
   string_t *s = NULL;
   string_t *key = NULL;
   string_t *value = NULL;
   s_dlist_t *priority_paths = NULL;
   s_dlist_t *subscribe_paths = NULL;
   s_dlist_t *non_subscribe_paths = NULL;
   s_dlist_t *publish_paths = NULL;
   s_dlist_t *non_publish_paths = NULL;
   s_dlist_t *pre_priority_get_paths = NULL;
   snstp_dlist_t *services = NULL;
   snstp_t *snstp = NULL;
   soa_path_t *callback_path = NULL;

   // initalize garbage collection
   // GC_INIT();

   // uncomment to tell GC to emit debug info
   // GC_set_find_leak(1);

   // parse and handle the command line
   // handle pre-start configuration options, extract others
   args = s_dlist_make();

   // skip program name
   i = 1;

   while( i < argc )
   {
      cmd = argv[i];

      // set config file name
      if ( ( strcmp( cmd, "-config_file" ) == 0 ) || ( strcmp( cmd, "config_file" ) == 0 ) )
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

      // else save command for after startup
      else
      {
         s = string_make_from_cstring( argv[i] );
         s_dlist_put_last( args, s );
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
   s_dlist_start( args );
   while( s_dlist_off( args ) == 0 )
   {
	   key = s_dlist_item_at( args );
	   s_dlist_forth( args );
	   value = s_dlist_item_at( args );
	   s_dlist_forth( args );
	   if ( string_item( key, 0 ) == '-' )
	   {
	      string_remove( key, 0 );
	      soa_configuration_put( configuration, key, value );
	   }
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

   int32_t c_prio = 0;
   if ( soa_configuration_has_cstring( configuration, "component_priority" ) )
   {
      strcpy( component_priority,  string_as_cstring( soa_configuration_item_cstring( configuration, "component_priority" ) ) );
      sscanf( component_priority, "%d", &c_prio );
   }

   // make local store
   local_store 
      =  soa_local_store_make
         ( 
            soa_configuration_item_cstring( configuration, "component_name" ),
            tt_id, 
            ti_id, 
            c_id 
         );

   // init data directory
   if ( strlen( directory ) == 0 )
   {
      if ( soa_configuration_has_cstring( configuration, "data_directory" ) )
      {
         strcpy( directory, string_as_cstring( soa_configuration_item_cstring( configuration, "data_directory"  ) ) );
      }
      else
      {
         strcpy( directory, "data" );
      }
   }

   int32_t r_flag = 0;
   if ( soa_configuration_has_cstring( configuration, "restore_flag" ) )
   {
      strcpy( restore_flag,  string_as_cstring( soa_configuration_item_cstring( configuration, "restore_flag" ) ) );
      sscanf( restore_flag, "%d", &r_flag );
   }

   // make data store
   data_store = soa_data_store_make_cstring( directory );
   
   // init data store, possibly reading existing files
   if ( r_flag == 0 )
   {
      soa_data_store_init_new( data_store );
   }
   else
   {
      soa_data_store_init( data_store );
      soa_data_store_get_latest( data_store );
   }
   
   // make component
   soa_component = soa_component_make( soa_configuration_item_cstring( configuration, "component_name" ), c_id );
   
   // set paths for component registration
   
   // priority_paths
   priority_paths = s_dlist_make();
   s = string_make_from_cstring( "/*" );
   s_dlist_put_last( priority_paths, s );

   // subscribe_paths
   subscribe_paths = s_dlist_make();
   s = string_make_from_cstring( "/*" );
   s_dlist_put_last( subscribe_paths, s );

   // non_subscribe_paths
   non_subscribe_paths = s_dlist_make();

   // publish_paths
   publish_paths = s_dlist_make();
   s = string_make_from_cstring( "/*" );
   s_dlist_put_last( publish_paths, s );

   // non_publish_paths
   non_publish_paths = s_dlist_make();

   // pre_priority_get_paths
   pre_priority_get_paths = s_dlist_make();

   // service name, service type, priority
   snstp
      =  snstp_make
         ( 
            soa_configuration_item_cstring( configuration, "service_name" ),
            soa_configuration_item_cstring( configuration, "service_type" ),
            c_prio 
         );
      
   services = snstp_dlist_make();
   snstp_dlist_put_last( services, snstp );

   // register component
   soa_component_utility_register_component
   (
      local_store,
      configuration,
      priority_paths,
      subscribe_paths,
      non_subscribe_paths,
      publish_paths,
      non_publish_paths,
      pre_priority_get_paths,
      c_prio,
      services
   );
   
   // make and init heartbeat monitor
   heartbeat_monitor = soa_heartbeat_monitor_make( local_store, configuration );
   soa_heartbeat_monitor_start( heartbeat_monitor );

   // install message save callback
   callback_path = soa_path_make_cstring( "/*", 1 );
   
   soa_local_store_register_callback
   (
      local_store,
      callback,
      NULL,
      callback_path
   );
   
   // loop forever
   main_loop();
   
   return 0;
}

/**
   timer_callback - periodically pings condition variable 
*/

void
timer_callback( void *p )
{
   MULTITHREAD_COND_SIGNAL( (* ( MULTITHREAD_COND_TYPE * ) p ) );
   return;
}

/**
   main_loop - wait for timer ping on condition variable, switch to new data
   file and dump contents of local store 
*/

void
main_loop( void )
{
   MULTITHREAD_MUTEX_DEFINITION_INIT( mutex );
   MULTITHREAD_COND_DEFINITION_INIT( cv );
   float64_t period = 0.0;
   char_t str[132] = {0};
   soa_timer_t *timer = NULL;
   soa_node_t *node = NULL;
   string_t *path = NULL;
   
   strcpy( str,  string_as_cstring( soa_configuration_item_cstring( configuration, "dump_timer_period" ) ) );
   sscanf( str, "%lf", &period );
   
   timer = soa_timer_make( period, timer_callback, &cv );
   soa_timer_start( timer );
   
   while( 1 )
   {
      // wait for timer ping of condition variable
      LOCK( mutex );
      MULTITHREAD_COND_WAIT( cv, mutex );
      UNLOCK( mutex );

      // start new file with dump of contents of local store
      path = string_make_from_cstring( "/" );
      node = soa_local_store_get_copy( local_store, path );
      if ( node != NULL )
      {
         soa_data_store_put_new_file( data_store, node );
         soa_node_dispose( node );
      }
      string_dispose_with_contents( path );
   }
   
   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */

