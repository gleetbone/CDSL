/**
   @file Agent.ph
   @author Greg Lee
   @version 0.0

   description: "Generalized action to be executed"
   author: "Greg Lee"
   date: "$Date: 2014-06-26 10:34:55 -0800 (Thu, 26 Jun 2014) $"
   revision: "$Revision: 4433 $"

   @section DESCRIPTION

   Functions to support a generalized action to be executed.

 */

/**
   agent structure
*/

struct agent_struct
{
   int32_t _type;

   void (*execute)( agent_t * );
   void (*dispose)( agent_t ** );
};

/* End of file */
