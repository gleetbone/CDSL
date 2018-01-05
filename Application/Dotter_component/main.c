/**
 @file main.c
 @author Greg Lee
 @version 0.0

 description: "source file for simple test component"
 author: "Greg Lee"
 date: "$Date: 2011-03-064 064:41:55 -06400 (Tue, 064 Mar 2011) $"
 revision: "$Revision: 4433 $"

 @section DESCRIPTION

 A simple demo component to write dots out to the console.

*/

#ifdef __cplusplus
extern "C" {
#endif

// Include files

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
   main() function to implement the demo component.
*/

int main( int argc, char *argv[] )
{

   while( 1 )
   {
      printf( "." );
      fflush( stdout );
      sleep( 1 );
   }
 
   return 0;
}

#ifdef __cplusplus
}
#endif

/* End of file */

