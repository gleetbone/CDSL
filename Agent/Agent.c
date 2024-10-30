/**
   @file Agent.c
   @author Greg Lee
   @version 2.0.0

   description: "Generalized action to be executed"
   author: "Greg Lee"
   date: "$Date: 2014-06-26 10:34:55 -0800 (Thu, 26 Jun 2014) $"
   revision: "$Revision: 4433 $"

   @section DESCRIPTION

   Functions to support a generalized action to be executed.

 */

#include "Agent.h"
#include "Agent.ph"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "dbc.h"

/**
   Defines
*/

/**
   agent structure

   defined in Agent.ph so it can be included in implementation classes
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
execute_ok( agent_t *current )
{
   int32_t result = 0;

   result = (*current).execute != NULL;

   return result;
}

static
int32_t
dispose_ok( agent_t *current )
{
   int32_t result = 0;

   result = ( (*current).dispose != NULL );

   return result;
}


static
void invariant( agent_t *current )
{
   assert( ( ( void ) "execute_ok", execute_ok( current ) ) );
   assert( ( ( void ) "dispose_ok", dispose_ok( current ) ) );
   return;
}

#else

static
void invariant( agent_t *current )
{
   return;
}

#endif

/**
   agent_execute
*/

void
agent_execute
(
   agent_t *current
)
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == AGENT_TYPE );
   INVARIANT( current );

   // execute agent
   (*current).execute( current );

   INVARIANT( current );

   return;
}

/**
   agent_dispose
*/
void
agent_dispose( agent_t **current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "*current ok", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == AGENT_TYPE );
   INVARIANT(*current);

   // dispose agent
   (**current).dispose( current );

   return;
}

/* End of file */
