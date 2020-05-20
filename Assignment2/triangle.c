// Chandorkar, Avani
// arc8554
// 2020-04-20
//----------------------------------------------------------
#include <stdio.h>

#include "triangle.h"
#include "vertex.h"

//----------------------------------------------------------
void dumpTriangle( Vertex *v1, Vertex *v2, Vertex *v3 )
{
  // TODO: Print three 'l' lines, one for each side of
  //       this triangle.  (Remember that triangles get
  //       drawn in counter-clockwise order, so the lines
  //       are v1->v2, v2->v3, v3->v1.)

  printf( "l %8.1f %8.1f %8.1f %8.1f\n",
    v1->x, v1->y, v2->x, v2->y );

  printf( "l %8.1f %8.1f %8.1f %8.1f\n",
    v2->x, v2->y, v3->x, v3->y );

  printf( "l %8.1f %8.1f %8.1f %8.1f\n",
    v3->x, v3->y, v1->x, v1->y );
}

//----------------------------------------------------------

