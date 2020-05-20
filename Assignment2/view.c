// Chandorkar, Avani
// arc8554
// 2020-04-20
//----------------------------------------------------------
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "view.h"

//----------------------------------------------------------
View *allocView()
{
  // TODO: Allocate a View structure.
  //       Return a pointer to the View structure as the
  //         result of this function.
  // (You can use calloc() to allocate zeroed out memory.)
  View *view;

  view = (View *) calloc( 1, sizeof( View ) );
  if ( view == NULL ) {
    fprintf( stderr, "allocView: Could not allocate view!\n" );
    exit( 1 );
  }

  return view;
}

//----------------------------------------------------------
void dumpView( View *view )
{
  printf( "#- View parameters ---------------------\n" );
  printf( "# Bézier resolution : %5d\n",
    view->m_resolution );

  printf( "# Euler angles      : %13.6f, %13.6f, %13.6f\n",
    view->m_phi, view->m_theta, view->m_psi );

  printf( "# World limits      : %13.6f, %13.6f, %13.6f, %13.6f\n",
    view->m_worldXMin, view->m_worldYMin,
    view->m_worldXMax, view->m_worldYMax );

  printf( "# Camera distance   : %13.6f\n", view->m_cameraDistance );

  printf( "# Canvas width      : %5d\n", view->m_width );
  printf( "# Canvas height     : %5d\n", view->m_height );

  printf( "# Screen limits     : %13.6f, %13.6f, %13.6f, %13.6f\n",
    view->m_viewportXMin, view->m_viewportYMin,
    view->m_viewportXMax, view->m_viewportYMax );

  printf( "# Portal pixels     : %4d, %4d, %4d, %4d\n",
    view->m_portalXMin, view->m_portalXMax,
    view->m_portalYMin, view->m_portalYMax );

  printf( "#---------------------------------------\n" );
}

//----------------------------------------------------------
void freeView( View *view )
{
  // TODO: Free the view structure.
  free( view );
}

//----------------------------------------------------------
View *loadView( char *fName )
{
  // TODO: Open the file indicated by fName.
  //       Allocate a View structure.
  //       Process each 'c', 'd', 's', and 'w' line.
  //       Compute the xMin, xMax, yMin, and yMax of the viewport
  //         and save the values in the m_portal... slots.
  //       Return a pointer to the allocated View structure as
  //         the value of this function.
  //
  // This code is very similar to what was done in loadModel().
  // The primary difference is that a view file has different
  // kinds of lines in it and therefore the line processing is
  // different.

    //--------------------------------------
  
  FILE *fp = fopen( fName, "r" );
  if ( fp == NULL ) 
  {
    fprintf( stderr, "loadView: Could not open '%s' for read.\n", fName );
    exit( 1 );
  }

  View   *view  = allocView();
  char   *line  = NULL;
  size_t  len   = 0;
  size_t  read;

  int     lineNum = 0;

  while ( ( read = getline( &line, &len, fp ) ) != -1 ) {
    lineNum++;

    char *ptr = line;

    while ( *ptr && isspace( *ptr ) ) ptr++;

    if ( *ptr == 'c' ) {
      int conv = sscanf( ptr+1, "%d %d",
        &view->m_width, &view->m_height );

      if ( conv != 2 ) {
        fprintf( stderr, "loadView: Could not load canvas size at line %d.", lineNum );
      }

      continue;
    }

    if ( *ptr == 'd' ) {
      int conv = sscanf( ptr+1, "%lf", &view->m_cameraDistance );

      if ( conv != 1 ) {
        fprintf( stderr, "loadView: Could not load camera distance at line %d.", lineNum );
      }

      continue;
    }

    if ( *ptr == 's' ) {
      int conv = sscanf( ptr+1, "%lf %lf %lf %lf",
        &view->m_viewportXMin, &view->m_viewportYMin,
        &view->m_viewportXMax, &view->m_viewportYMax );

      if ( conv != 4 ) {
        fprintf( stderr, "loadView: Could not load viewport limits at line %d.", lineNum );
      }

      continue;
    }

    if ( *ptr == 'w' ) {
      int conv = sscanf( ptr+1, "%lf %lf %lf %lf",
        &view->m_worldXMin, &view->m_worldYMin,
        &view->m_worldXMax, &view->m_worldYMax );

      if ( conv != 4 ) {
        fprintf( stderr, "loadView: Could not load world limits at line %d.", lineNum );
      }

      continue;
    }
  }

  //--------------------------------------
  if ( line != NULL ) {
    free( line );
  }

  fclose( fp );

  //--------------------------------------
  view->m_portalXMin = view->m_width * view->m_viewportXMin;
  view->m_portalYMin = view->m_height * view->m_viewportYMin;
  view->m_portalXMax = view->m_width * view->m_viewportXMax;
  view->m_portalYMax = view->m_height * view->m_viewportYMax;

  //--------------------------------------
  return view;
}

//----------------------------------------------------------

