// Chandorkar, Avani
// arc8554
// 2020-04-06
//----------------------------------------------------------
#include <stdio.h>

#include "vertex.h"

//----------------------------------------------------------
void dumpVertex( Vertex *vertex )
{
  // TODO: Put a printf here that dumps the given vertex's
  //       X, Y, and Z coordinates. Show 6 decimal places.
  //       Do NOT print a newline as part of this dump.  That
  //       gets done elsewhere.
  printf( "%13.6f, %13.6f, %13.6f", vertex->x, vertex->y, vertex->z );
}

//----------------------------------------------------------

