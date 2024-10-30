/**
   @file hello_agent.c
   @author Greg Lee
   @version 0.0

   description: "Generalized action to be executed"
   author: "Greg Lee"
   date: "$Date: 2014-06-26 10:34:55 -0800 (Thu, 26 Jun 2014) $"
   revision: "$Revision: 4433 $"

   @section DESCRIPTION

   Functions to support a generalized action to be executed.

 */

#include "hello_agent.h" 
#include "Agent.ph" 
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define CHECK_FILE DBC_YES
#define INVARIANT_FILE DBC_YES

#include "dbc.h"

/**
   Defines
*/
#define HELLO_AGENT_TYPE 0xA5010000

/**
   Function prototypes
*/

void do_hello( int32_t i );

/**
   hello_agent structure
   
*/

struct hello_agent_struct
{
   agent_t agent;
   
   int32_t _type;
   void (*do_hello)( int32_t );
   int32_t i;
};

#if INVARIANT_CONDITIONAL != 0

static
int32_t
type_ok( hello_agent_t *current )
{
   int32_t result = 0;

   result = (*current).agent._type == AGENT_TYPE; 

   return result;
}

static
int32_t
execute_ok( hello_agent_t *current )
{
   int32_t result = 0;

   result = (*current).agent.execute != NULL; 

   return result;
}

static
int32_t
dispose_ok( hello_agent_t *current )
{
   int32_t result = 0;

   result = ( (*current).agent.dispose != NULL );

   return result;
}

static
int32_t
function_ok( hello_agent_t *current )
{
   int32_t result = 0;

   result = (*current).do_hello != NULL; 

   return result;
}


static
void invariant( hello_agent_t *current )
{
   assert(((void) "type_ok", type_ok( current ) ));
   assert(((void) "execute_ok", execute_ok( current ) ));
   assert(((void) "dispose_ok", dispose_ok( current ) ));
   assert(((void) "function_ok", function_ok( current ) ));
   return;
}

#else

static
void invariant( hello_agent_t *current )
{
   return;
}

#endif

/**
   hello_agent_make
*/

agent_t *
hello_agent_make
(
   int32_t i
)
{
   // allocate hello agent struct
   hello_agent_t * result = ( hello_agent_t * ) calloc( 1, sizeof( hello_agent_t ) );

   // set type
   (*result)._type = HELLO_AGENT_TYPE;

   // set agent type 
   (*result).agent._type = AGENT_TYPE;

   // set execute 
   (*result).agent.execute = hello_agent_execute;

   // set dispose
   (*result).agent.dispose = hello_agent_dispose;

   // set function to execute 
   (*result).do_hello = do_hello;

   // set parameter
   (*result).i = i;
   
   INVARIANT( result );

   return &(*result).agent;
}

/**
   hello_agent_execute
*/
void
hello_agent_execute( agent_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == AGENT_TYPE );
   
   // get pointer to hello_agent
   hello_agent_t *p = ( hello_agent_t * ) current;
   
   // check preconditions
   PRECONDITION( "current type OK", (*p)._type == HELLO_AGENT_TYPE );
   INVARIANT( p );

   // execute hello_agent
   (*p).do_hello( (*p).i );
   
   INVARIANT( p );
   
   return;
}

/**
   hello_agent_dispose
*/
void
hello_agent_dispose( agent_t **current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "*current ok", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == AGENT_TYPE );

   // get pointer to hello_agent
   hello_agent_t *p = ( hello_agent_t * ) *current;
   
   // check preconditions
   PRECONDITION( "current type OK", (*p)._type == HELLO_AGENT_TYPE );
   INVARIANT( p );

   // dispose hello_agent
   free( p );
   *current = NULL;
   
   return;
}

/* End of file */
