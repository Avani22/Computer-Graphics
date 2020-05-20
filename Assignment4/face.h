// Chandorkar, Avani
// arc8554
// 2020-05-08
#if !defined( __FACE_H__ )
#define __FACE_H__

//----------------------------------------------------------
typedef struct _Face {
  int v1;
  int v2;
  int v3;
} Face;

//----------------------------------------------------------
void   dumpFace( Face *face );

//----------------------------------------------------------
#endif

