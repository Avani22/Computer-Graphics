// Chandorkar, Avani
// arc8554
// 2020-04-06
//----------------------------------------------------------
#include <ctype.h>
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "model.h"

//----------------------------------------------------------
Model *allocModel( int numVertices, int numFaces )
{
  // TODO: Allocate a Model structure.
  //       Initialize its fields using the given number of
  //         vertices and faces.
  //       Return a pointer to the Model structure as the
  //         result of this function.
  // (You can use calloc() to allocate zeroed out memory.  This
  //  is useful when allocating the vertex and face arrays.)
  
 Model *m;

  m = (Model *) calloc( 1, sizeof( Model ) );
  if ( m == NULL ) 
  {
    fprintf( stderr, "allocModel: Unable to allocate Model.\n" );
    exit( 1 );
  }

  if ( numVertices > 0 ) 
  {
    m->m_numVertices = numVertices;
    m->m_vertex = (Vertex *) calloc( numVertices, sizeof( Vertex ) );
    if ( m->m_vertex == NULL ) 
	{
      fprintf( stderr, "allocModel: Unable to allocate %d Vertice.\n",numVertices);
    }
  }

  if ( numFaces > 0 ) 
  {
    m->m_numFaces = numFaces;
    m->m_face = (Face *) calloc( numFaces, sizeof( Face ) );
    if ( m->m_face == NULL ) 
	{
      fprintf( stderr, "allocModel: Unable to allocate %d Face.\n",numFaces );
    }
  }

  return m; 
}

//----------------------------------------------------------
void dumpModel( Model *model )
{
  printf( "#- Model parameters --------------------\n" );
  printf( "Vertex count : %5d\n", model->m_numVertices );
  printf( "Face count   : %5d\n", model->m_numFaces );

  printf( "\n#- Vertex list -------------------------\n" );
  for ( int i=0; i<model->m_numVertices; i++ ) {
    printf( "  [%5d]  ", i );
    dumpVertex( &model->m_vertex[i] );
    putc( '\n', stdout );
  }

  printf( "\n#- Face list ---------------------------\n" );
  for ( int i=0; i<model->m_numFaces; i++ ) {
    printf( "  [%5d]  ", i );
    dumpFace( &model->m_face[i] );
    putc( '\n', stdout );
  }

  printf( "#---------------------------------------\n" );
}

//----------------------------------------------------------
void freeModel( Model *model )
{
  // TODO: Free the vertex and face data of the given model.
  //       Free the model structure itself.
  if(model->m_vertex != NULL)
  {
	  free(model->m_vertex);
  }
  if(model->m_face!= NULL)
  {
	  free(model->m_face);
  }
  free(model);
}

//----------------------------------------------------------
Model *loadModel( char *fName )
{
  // TODO: Open the file indicated by fName.
  //       Determine how many vertex lines and how many face
  //         lines it includes.
  //       Allocate a Model structure using the vertex and face
  //         counts as arguments.
  //       Read each vertex line from the file and save its X, Y,
  //         Z coordinates.
  //       Read each face line from the file and save its three
  //         vertex numbers.  Don't forget to subtract one from
  //         each number so it can be used as an index into the
  //         vertex list.
  //       Return a pointer to the allocated model structure as
  //         the value of this function.
  FILE *fp = fopen( fName, "r" );
  if ( fp == NULL ) 
  {
    fprintf( stderr, "loadModel: Unable to open '%s' for read.\n", fName );
    exit( 1 );
  }
  
  int     numVertices = 0;
  int     numFaces    = 0;
  char   *line        = NULL;
  size_t  len         = 0;
  size_t  read;

  while ( ( read = getline( &line, &len, fp ) ) != -1 ) 
  {
    char *ptr = line;

    while ( *ptr && isspace( *ptr ) ) ptr++;
    if ( *ptr == 'v' ) ++numVertices;
    if ( *ptr == 'f' ) ++numFaces;
  }
  rewind( fp );
  
   Model *model = allocModel( numVertices, numFaces );

  Vertex *vertex  = model->m_vertex;
  Face   *face    = model->m_face;
  int     lineNum = 0;

  while ( ( read = getline( &line, &len, fp ) ) != -1 ) 
  {
		lineNum++;
		char *ptr = line;
		while ( *ptr && isspace( *ptr ) ) ptr++;
		if ( *ptr == 'v' ) 
		{
			int conv = sscanf( ptr+1, "%lf %lf %lf",&vertex->x, &vertex->y, &vertex->z );
			if ( conv != 3 ) 
			{
				fprintf( stderr, "loadModel: Unable to load vertex at line %d.", lineNum );
			}
			vertex++;
			continue;
		}

		if ( *ptr == 'f' ) 
		{
			int conv = sscanf( ptr+1, "%d %d %d",&face->v1, &face->v2, &face->v3 );
			face->v1--;
			face->v2--;
			face->v3--;
			if ( conv != 3 ) 
			{
				fprintf( stderr, "loadModel: Unable to load face at line %d.", lineNum );
			}
			face++;
			continue;
		}
	}	

	if ( line != NULL ) 
	{
		free( line );
	}
	fclose( fp );
	return model;
}

//----------------------------------------------------------

