// Chandorkar, Avani
// arc8554
// 2020-04-06
//----------------------------------------------------------
#include <stdio.h>

#include "face.h"

//----------------------------------------------------------
void dumpFace( Face *face )
{
  // TODO: Put a printf here that dumps the given face's
  //       three vertex numbers.  These are integers.
  //       Do NOT print a newline as part of this dump.  That
  //       gets done elsewhere.

  printf( "%5d, %5d, %5d", face->v1, face->v2, face->v3 );
}

//----------------------------------------------------------

