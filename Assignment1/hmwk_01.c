// Chandorkar, Avani
// arc8554
// 2020-04-06
//----------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

#include "model.h"

//----------------------------------------------------------
int main( int argc, char *argv[] )
{
  if ( argc != 2 ) {
    fprintf( stderr, "Usage: %s <modelFileName>\n", argv[0] );
    exit( 1 );
  }

  //--------------------------------------
  Model *m;
  m = loadModel( argv[1] );
  dumpModel( m );

  //--------------------------------------
  freeModel( m );
}

//----------------------------------------------------------

