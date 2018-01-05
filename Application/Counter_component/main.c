/**
 @file main.c
 @author Greg Lee
 @version 0.0

 description: "source file for counter component"
 author: "Greg Lee"
 date: "$Date: 2011-03-064 064:41:55 -06400 (Tue, 064 Mar 2011) $"
 revision: "$Revision: 4433 $"

 @section DESCRIPTION

 A simple counter component to write text out to the console.

*/

#ifdef __cplusplus
extern "C" {
#endif

// Include files

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "basic_types.h"
#include "soa_base.h"
#include "soa_base_struct.h"
#include "soa_worker.h"
#include "soa_worker_struct.h"
#include "soa_local_store.h"
#include "soa_job_monitor.h"
#include "String.h"
#include "Configuration.h"

/* user defined functions */

int32_t check_job( soa_worker_t *worker, soa_node_t *job, void *user_defined )
{
   int32_t result = 0;

   string_t *output_path = NULL;
   soa_node_t *sn_str = NULL;

   if ( soa_node_dict_has_cstring( job, "output_path" ) == 1 )
   {
      result = 1;

      // check output path
      if ( result == 1 )
      {
         sn_str = soa_node_dict_item_cstring( job, "output_path" );
         output_path = soa_node_ref( sn_str );

         if ( soa_local_store_has( (*worker).soa_local_store, output_path ) == 0 )
         {
            result = 0;
         }

      }

   }

   return result;
}

void work( soa_worker_t *worker, void *user_defined )
{
   soa_node_t *job = (*worker).job;

   string_t *s = NULL;
   string_t *last_string = NULL;
   string_t *output_path = NULL;
   soa_node_t *sn_str = NULL;
   soa_node_t *sn_str1 = NULL;
   soa_node_t *sn_str2 = NULL;
   char_t c = 0;

   while( 1 )
   {
      while ( soa_worker_has_working_priority( worker ) == 1 )
      {
         
         // get last string sent path
         sn_str = soa_node_dict_item_cstring( job, "output_path" );
         output_path = soa_node_ref( sn_str );
         s = string_make_from( output_path );
         string_append_cstring( s, "/last_string" );
      
         sn_str1 = soa_local_store_get_copy( (*worker).soa_local_store, s );
         last_string = soa_node_str( sn_str1 );
      
         // get next string
         c = string_item( last_string, 0 );
         switch ( c )
         {
            case '1':
            string_put( last_string, '2', 0 );
            break;
            
            case '2':
            string_put( last_string, '3', 0 );
            break;
            
            case '3':
            string_put( last_string, '4', 0 );
            break;
            
            case '4':
            string_put( last_string, '5', 0 );
            break;
            
            case '5':
            string_put( last_string, '6', 0 );
            break;
            
            case '6':
            string_put( last_string, '7', 0 );
            break;
            
            case '7':
            string_put( last_string, '8', 0 );
            break;
            
            case '8':
            string_put( last_string, '1', 0 );
            break;
            
         }
            
         // print output to screen
         if ( string_item( last_string, 0 ) == '8' )
         {
            printf( "%s\n", string_as_cstring( last_string ) );
            fflush( stdout );
         }
         else
         {
            printf( "%s ", string_as_cstring( last_string ) );
            fflush( stdout );
         }
        
        // put last string into local store
         sn_str2 = soa_node_make_from_str_cstring( "last_string", string_as_cstring( last_string ) );
      
         // get output path
         sn_str = soa_node_dict_item_cstring( job, "output_path" );
         output_path = soa_node_ref( sn_str );
      
         // put output
         soa_local_store_put( (*worker).soa_local_store, sn_str2, output_path );
      
         // dispose
         string_dispose_with_contents( s );
         soa_node_dispose( sn_str1 );
         soa_node_dispose( sn_str2 );
         
         sleep( 1 );
      }
      
      if ( soa_worker_has_working_priority( worker ) == 0 )
      {
         sleep( 1 );
      }
      
   }   
   
   return;
}

void add_to_configuration( soa_base_t *base, void *user_defined )
{
/*
   soa_configuration_put_cstring( (*base).configuration, "heartbeat_period", "1.0" );
   soa_configuration_put_cstring( (*base).configuration, "watchdog_period", "1.0" );
   soa_configuration_put_cstring( (*base).configuration, "service_monitor_period", "1.0" );
   soa_configuration_put_cstring( (*base).configuration, "job_monitor_period", "1.0" );
   soa_configuration_put_cstring( (*base).configuration, "initial_wait_period", "1.0" );
   soa_configuration_put_cstring( (*base).configuration, "debug_verbose_flag", "1" );
   soa_configuration_put_cstring( (*base).configuration, "wait_for_persistence_flag", "0" );
   soa_configuration_put_cstring( (*base).configuration, "network_get_delay", "0.1" );
*/
   return;
}


void
init( soa_base_t *base, void *user_defined )
{
   string_t *s = NULL;
   soa_worker_t *worker = NULL;

   // publish paths
   s = string_make_from_cstring( "/jobs/*" );
   s_dlist_put_last( (*base).publish_paths, s );

   s = string_make_from_cstring( "/components/*" );
   s_dlist_put_last( (*base).publish_paths, s );

   s = string_make_from_cstring( "/products/*" );
   s_dlist_put_last( (*base).publish_paths, s );


   // subscribe paths
   s = string_make_from_cstring( "/jobs/*" );
   s_dlist_put_last( (*base).subscribe_paths, s );

   s = string_make_from_cstring( "/components/*" );
   s_dlist_put_last( (*base).subscribe_paths, s );

   s = string_make_from_cstring( "/products/*" );
   s_dlist_put_last( (*base).subscribe_paths, s );

   s = string_make_from_cstring( "/null/*" );
   s_dlist_put_last( (*base).subscribe_paths, s );


   // pre-get paths
   s = string_make_from_cstring( "/jobs/*" );
   s_dlist_put_last( (*base).pre_priority_get_paths, s );

   s = string_make_from_cstring( "/components/*" );
   s_dlist_put_last( (*base).pre_priority_get_paths, s );

   s = string_make_from_cstring( "/products/*" );
   s_dlist_put_last( (*base).pre_priority_get_paths, s );


   // worker
   string_t *name = string_make_from_cstring( "worker" );
   string_t *type = string_make_from_cstring( "counter" );

   worker
      =  soa_worker_make
         (
            (*base).configuration,
            (*base).soa_local_store,
            (*base).name,
            name,
            type,
            1,
            0,
            check_job,
            NULL,
            work,
            NULL
         );

   sw_dlist_put_last( (*base).workers, worker );

   string_dispose_with_contents( name );
   string_dispose_with_contents( type );

   return;
}

void
pre_start( soa_base_t *base, void *user_defined )
{
   string_t *path = NULL;
   soa_node_t *sn_job = NULL;
   soa_node_t *sn_requesting_service_name = NULL;
   soa_node_t *sn_requested_service_type = NULL;
   soa_node_t *sn_request = NULL;
   soa_node_t *sn_status = NULL;
   soa_node_t *sn_priority = NULL;
   soa_node_t *sn_is_parallel = NULL;
   soa_node_t *sn_responsible_services = NULL;
   soa_node_t *sn_output_path = NULL;
   soa_node_t *sn_dict = NULL;
   soa_node_t *sn_str = NULL;

   path = string_make_from_cstring( "/jobs/counter/job" );

   // set the job for the counter service
   if ( soa_local_store_has( (*base).soa_local_store, path ) == 0 )
   {
      // job does not exist, create and put it
      sn_job = soa_node_make_dict_cstring( "job" );

      // requesting_service_name
      sn_requesting_service_name
         =  soa_node_make_from_str_cstring
            (
               "requesting_service_name",
               "client"
            );
      soa_node_dict_put( sn_job, sn_requesting_service_name );

      // requested_service_type
      sn_requested_service_type
         =  soa_node_make_from_str_cstring
            (
               "requested_service_type",
               "counter"
            );
      soa_node_dict_put( sn_job, sn_requested_service_type );

      // request
      sn_request
         =  soa_node_make_from_str_cstring
            (
               "request",
               "START"
            );
      soa_node_dict_put( sn_job, sn_request );

      // status
      sn_status
         =  soa_node_make_from_str_cstring
            (
               "status",
               "ISSUED"
            );
      soa_node_dict_put( sn_job, sn_status );

      // priority
      sn_priority
         =  soa_node_make_i32_cstring
            (
               "priority",
               1
            );
      soa_node_dict_put( sn_job, sn_priority );

      // is_parallel
      sn_is_parallel
         =  soa_node_make_i32_cstring
            (
               "is_parallel",
               0
            );
      soa_node_dict_put( sn_job, sn_is_parallel );

      // responsible_services
      sn_responsible_services
         =  soa_node_make_dict_cstring
            (
               "responsible_services"
            );
      soa_node_dict_put( sn_job, sn_responsible_services );

      // output_path
      sn_output_path
         =  soa_node_make_from_ref_cstring
            (
               "output_path",
               "/products/counter"
            );
      soa_node_dict_put( sn_job, sn_output_path );

      // put the job
      string_wipe_out( path );
      string_append_cstring( path, "/jobs/counter" );
      soa_local_store_put( (*base).soa_local_store, sn_job, path );

      // put the output
      string_wipe_out( path );
      string_append_cstring( path, "/products" );
      sn_dict = soa_node_make_dict_cstring( "counter" );
      soa_local_store_put( (*base).soa_local_store, sn_dict, path );
         
      string_wipe_out( path );
      string_append_cstring( path, "/products/counter" );
      sn_str
         =  soa_node_make_from_str_cstring
            (
               "last_string",
               "8"
            );
      soa_local_store_put( (*base).soa_local_store, sn_str, path );

      // dispose
      string_dispose_with_contents( path );
      soa_node_dispose( sn_job );
      soa_node_dispose( sn_str );

   }

   return;
}

#define MAX_FILENAME_LENGTH 1024

/**
   main() function to implement the counter component.
*/

int main( int argc, char *argv[] )
{
   soa_local_store_t *local_store = NULL;
   char_t config_filename[MAX_FILENAME_LENGTH] = {0};
   string_t *component_name = NULL;
   int32_t tipc_type_id = 0;
   int32_t tipc_instance_id = 0;
   int32_t component_id = 0;
   int32_t component_priority = 0;
   char_t cstr[128] = {0};
   soa_base_t *base = NULL;
   s_dlist_t *args = NULL;
   string_t *s = NULL;
   string_t *key = NULL;
   string_t *value = NULL;
   char *cmd = NULL;
   char *arg = NULL;
   int32_t i = 0;
   int32_t flag = 0;
   soa_configuration_t *configuration = NULL;

   // initalize garbage collection
   GC_INIT();

   // uncomment to tell GC to emit debug info
   // GC_set_find_leak(1);

   // parse and handle the command line
   // set pre-start configuration options, extract others
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

   // set flags defined on command line
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


   // init local store
   component_name = soa_configuration_item_cstring( configuration, "component_name" );
   
   s = soa_configuration_item_cstring( configuration, "tipc_type_id" );
   strcpy( cstr, string_as_cstring( s ) );
   sscanf( cstr, "%d", &tipc_type_id );
   
   s = soa_configuration_item_cstring( configuration, "tipc_instance_id" );
   strcpy( cstr, string_as_cstring( s ) );
   sscanf( cstr, "%d", &tipc_instance_id );
   
   s = soa_configuration_item_cstring( configuration, "component_id" );
   strcpy( cstr, string_as_cstring( s ) );
   sscanf( cstr, "%d", &component_id );
      
   s = soa_configuration_item_cstring( configuration, "component_priority" );
   strcpy( cstr, string_as_cstring( s ) );
   sscanf( cstr, "%d", &component_priority );
      
   local_store 
      =  soa_local_store_make
         ( 
            component_name, 
            tipc_type_id, 
            tipc_instance_id, 
            component_id
         );
   
   
   // make base
   base
      =  soa_base_make
         (
            configuration,
            local_store,
            component_name,
            component_id,
            component_priority,
            add_to_configuration,
            NULL,
            init,
            NULL,
            pre_start,
            NULL
         );
   
         
   // loop forever
   while( 1 )
   {
      sleep( 4 );
   }
         
   // dispose
   soa_base_dispose( base );
   soa_local_store_dispose( local_store );
   soa_configuration_dispose( configuration );
   
   return 0;
}

#ifdef __cplusplus
}
#endif

/* End of file */

