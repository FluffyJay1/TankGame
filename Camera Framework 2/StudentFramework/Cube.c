#include "Cube.h"
#include "pfmath.h"
#include <math.h>

void Cube_Init( Cube * theCube, BOOLEAN color)
{
  //every vertex and line by hand, now lines use indices!
  int i;
  theCube->VertexList[0] = Vector4_Create(0.5, -0.5, 0.5, 1);
  theCube->VertexList[1] = Vector4_Create(0.5, -0.5, -0.5, 1);
  theCube->VertexList[2] = Vector4_Create(0.5, 0.5, -0.5, 1);
  theCube->VertexList[3] = Vector4_Create(0.5, 0.5, 0.5, 1);
  theCube->VertexList[4] = Vector4_Create(-0.5, 0.5, 0.5, 1);
  theCube->VertexList[5] = Vector4_Create(-0.5, -0.5, 0.5, 1);
  theCube->VertexList[6] = Vector4_Create(-0.5, -0.5, -0.5, 1);
  theCube->VertexList[7] = Vector4_Create(-0.5, 0.5, -0.5, 1);

  //theCube->LineList[0].Point1 = theCube->VertexList + 0;
  //theCube->LineList[0].Point2 = theCube->VertexList + 1;
  theCube->LineList[0].PointOneIndex = 0;
  theCube->LineList[0].PointTwoIndex = 1;
  
  theCube->LineList[0].rgb.Red = 255;
  theCube->LineList[0].rgb.Green = 0;
  theCube->LineList[0].rgb.Blue = 0;


  //theCube->LineList[1].Point1 = theCube->VertexList + 1;
  //theCube->LineList[1].Point2 = theCube->VertexList + 2;
  theCube->LineList[1].PointOneIndex = 1;
  theCube->LineList[1].PointTwoIndex = 2;
  theCube->LineList[1].rgb.Red = 255;
  theCube->LineList[1].rgb.Green = 0;
  theCube->LineList[1].rgb.Blue = 0;

  //theCube->LineList[2].Point1 = theCube->VertexList + 2;
  //theCube->LineList[2].Point2 = theCube->VertexList + 3;
  theCube->LineList[2].PointOneIndex = 2;
  theCube->LineList[2].PointTwoIndex = 3;
  theCube->LineList[2].rgb.Red = 255;
  theCube->LineList[2].rgb.Green = 0;
  theCube->LineList[2].rgb.Blue = 0;


  //theCube->LineList[3].Point1 = theCube->VertexList + 3;
  //theCube->LineList[3].Point2 = theCube->VertexList + 0;
  theCube->LineList[3].PointOneIndex = 3;
  theCube->LineList[3].PointTwoIndex = 0;
  theCube->LineList[3].rgb.Red = 255;
  theCube->LineList[3].rgb.Green = 0;
  theCube->LineList[3].rgb.Blue = 0;

  //theCube->LineList[4].Point1 = theCube->VertexList + 4;
  //theCube->LineList[4].Point2 = theCube->VertexList + 3;
  theCube->LineList[4].PointOneIndex = 4;
  theCube->LineList[4].PointTwoIndex = 3;
  theCube->LineList[4].rgb.Red = 0;
  theCube->LineList[4].rgb.Green = 255;
  theCube->LineList[4].rgb.Blue = 0;

  //theCube->LineList[5].Point1 = theCube->VertexList + 0;
  //theCube->LineList[5].Point2 = theCube->VertexList + 5;
  theCube->LineList[5].PointOneIndex = 0;
  theCube->LineList[5].PointTwoIndex = 5;
  theCube->LineList[5].rgb.Red = 0;
  theCube->LineList[5].rgb.Green = 255;
  theCube->LineList[5].rgb.Blue = 0;

  //theCube->LineList[6].Point1 = theCube->VertexList + 4;
  //theCube->LineList[6].Point2 = theCube->VertexList + 5;
  theCube->LineList[6].PointOneIndex = 4;
  theCube->LineList[6].PointTwoIndex = 5;
  theCube->LineList[6].rgb.Red = 0;
  theCube->LineList[6].rgb.Green = 255;
  theCube->LineList[6].rgb.Blue = 0;

  //theCube->LineList[7].Point1 = theCube->VertexList + 4;
  //theCube->LineList[7].Point2 = theCube->VertexList + 7;
  theCube->LineList[7].PointOneIndex = 4;
  theCube->LineList[7].PointTwoIndex = 7;
  theCube->LineList[7].rgb.Red = 0;
  theCube->LineList[7].rgb.Green = 0;
  theCube->LineList[7].rgb.Blue = 255;

  //theCube->LineList[8].Point1 = theCube->VertexList + 5;
  //theCube->LineList[8].Point2 = theCube->VertexList + 6;
  theCube->LineList[8].PointOneIndex = 5;
  theCube->LineList[8].PointTwoIndex = 6;
  theCube->LineList[8].rgb.Red = 0;
  theCube->LineList[8].rgb.Green = 0;
  theCube->LineList[8].rgb.Blue = 255;

  //theCube->LineList[9].Point1 = theCube->VertexList + 6;
  //theCube->LineList[9].Point2 = theCube->VertexList + 7;
  theCube->LineList[9].PointOneIndex = 6;
  theCube->LineList[9].PointTwoIndex = 7;
  theCube->LineList[9].rgb.Red = 0;
  theCube->LineList[9].rgb.Green = 0;
  theCube->LineList[9].rgb.Blue = 255;

  //theCube->LineList[10].Point1 = theCube->VertexList + 7;
  //theCube->LineList[10].Point2 = theCube->VertexList + 2;
  theCube->LineList[10].PointOneIndex = 7;
  theCube->LineList[10].PointTwoIndex = 2;
  theCube->LineList[10].rgb.Red = 0;
  theCube->LineList[10].rgb.Green = 0;
  theCube->LineList[10].rgb.Blue = 255;

  //theCube->LineList[11].Point1 = theCube->VertexList + 6;
  //theCube->LineList[11].Point2 = theCube->VertexList + 1;
  theCube->LineList[11].PointOneIndex = 6;
  theCube->LineList[11].PointTwoIndex = 1;
  theCube->LineList[11].rgb.Red = 0;
  theCube->LineList[11].rgb.Green = 0;
  theCube->LineList[11].rgb.Blue = 255;

  theCube->TriangleList[0].PointOneIndex = 0;
  theCube->TriangleList[0].PointTwoIndex = 1;
  theCube->TriangleList[0].PointThreeIndex = 2;
  theCube->TriangleList[0].rgb.Red = 0;
  theCube->TriangleList[0].rgb.Green = 0;
  theCube->TriangleList[0].rgb.Blue = 255;

  theCube->TriangleList[1].PointOneIndex = 2;
  theCube->TriangleList[1].PointTwoIndex = 3;
  theCube->TriangleList[1].PointThreeIndex = 0;
  theCube->TriangleList[1].rgb.Red = 0;
  theCube->TriangleList[1].rgb.Green = 255;
  theCube->TriangleList[1].rgb.Blue = 0;


  theCube->TriangleList[2].PointOneIndex = 1;
  theCube->TriangleList[2].PointTwoIndex = 6;
  theCube->TriangleList[2].PointThreeIndex = 7;
  theCube->TriangleList[2].rgb.Red = 255;
  theCube->TriangleList[2].rgb.Green = 0;
  theCube->TriangleList[2].rgb.Blue = 0;

  theCube->TriangleList[3].PointOneIndex = 7;
  theCube->TriangleList[3].PointTwoIndex = 2;
  theCube->TriangleList[3].PointThreeIndex = 1;
  theCube->TriangleList[3].rgb.Red = 255;
  theCube->TriangleList[3].rgb.Green = 127;
  theCube->TriangleList[3].rgb.Blue = 127;


  theCube->TriangleList[4].PointOneIndex = 3;
  theCube->TriangleList[4].PointTwoIndex = 2;
  theCube->TriangleList[4].PointThreeIndex = 7;
  theCube->TriangleList[4].rgb.Red = 127;
  theCube->TriangleList[4].rgb.Green = 255;
  theCube->TriangleList[4].rgb.Blue = 127;

  theCube->TriangleList[5].PointOneIndex = 7;
  theCube->TriangleList[5].PointTwoIndex = 4;
  theCube->TriangleList[5].PointThreeIndex = 3;
  theCube->TriangleList[5].rgb.Red = 255;
  theCube->TriangleList[5].rgb.Green = 0;
  theCube->TriangleList[5].rgb.Blue = 255;


  theCube->TriangleList[6].PointOneIndex = 0;
  theCube->TriangleList[6].PointTwoIndex = 5;
  theCube->TriangleList[6].PointThreeIndex = 6;
  theCube->TriangleList[6].rgb.Red = 255;
  theCube->TriangleList[6].rgb.Green = 255;
  theCube->TriangleList[6].rgb.Blue = 0;

  theCube->TriangleList[7].PointOneIndex = 6;
  theCube->TriangleList[7].PointTwoIndex = 1;
  theCube->TriangleList[7].PointThreeIndex = 0;
  theCube->TriangleList[7].rgb.Red = 0;
  theCube->TriangleList[7].rgb.Green = 255;
  theCube->TriangleList[7].rgb.Blue = 255;


  theCube->TriangleList[8].PointOneIndex = 0;
  theCube->TriangleList[8].PointTwoIndex = 3;
  theCube->TriangleList[8].PointThreeIndex = 4;
  theCube->TriangleList[8].rgb.Red = 127;
  theCube->TriangleList[8].rgb.Green = 127;
  theCube->TriangleList[8].rgb.Blue = 255;

  theCube->TriangleList[9].PointOneIndex = 4;
  theCube->TriangleList[9].PointTwoIndex = 5;
  theCube->TriangleList[9].PointThreeIndex = 0;
  theCube->TriangleList[9].rgb.Red = 255;
  theCube->TriangleList[9].rgb.Green = 255;
  theCube->TriangleList[9].rgb.Blue = 255;


  theCube->TriangleList[10].PointOneIndex = 5;
  theCube->TriangleList[10].PointTwoIndex = 4;
  theCube->TriangleList[10].PointThreeIndex = 7;
  theCube->TriangleList[10].rgb.Red = 255;
  theCube->TriangleList[10].rgb.Green = 127;
  theCube->TriangleList[10].rgb.Blue = 255;

  theCube->TriangleList[11].PointOneIndex = 7;
  theCube->TriangleList[11].PointTwoIndex = 6;
  theCube->TriangleList[11].PointThreeIndex = 5;
  theCube->TriangleList[11].rgb.Red = 255;
  theCube->TriangleList[11].rgb.Green = 255;
  theCube->TriangleList[11].rgb.Blue = 127;
  
  if(color == FALSE)
  {
    for(i = 0; i < 12; ++i)
    {
      theCube->LineList[i].rgb.Red = 0;
      theCube->LineList[i].rgb.Green = 0;
      theCube->LineList[i].rgb.Blue = 0;
      theCube->TriangleList[i].rgb.Red = 235;
      theCube->TriangleList[i].rgb.Green = 245;
      theCube->TriangleList[i].rgb.Blue = 255;
    }
  }



}

void Cube_AlgebraicDraw( Cube * theCube, BOOLEAN Perspective,
                                         int viewportWidth, int viewportHeight, 
                                         float focal, 
                                         float ProjectionWindowWidth, float ProjectionWindowHeight )
{
  Cube ToDraw = *theCube;
  int i;

  for(i = 0; i < 8; ++i)
  {
    
    if(Perspective)
    {
      AlgebraicPerspProjection(&ToDraw.VertexList[i], &ToDraw.VertexList[i], focal, ProjectionWindowWidth, ProjectionWindowHeight);
    }
    else
    {
      AlgebraicOrthoProjection(&ToDraw.VertexList[i], &ToDraw.VertexList[i], focal, ProjectionWindowWidth, ProjectionWindowHeight);
    }
    
    AlgebraicProjToViewport(&ToDraw.VertexList[i], &ToDraw.VertexList[i], viewportWidth, viewportHeight);
  }

  DDADrawLineList(ToDraw.LineList, 12, ToDraw.VertexList, ToDraw.distanceList);
  
}

//line renderer that we need
void DDADrawLineList(LineSegment* ls, int size, Vector4 * VertexList, float* distanceList)
{
  int i;
  //draw each line segment
  for(i = 0; i < size; ++i)
  {
    DDADrawLineSegment(ls[i], VertexList, ls[i].rgb, distanceList);
  }
}

void DDADrawLineSegment(LineSegment ls, Vector4 * VertexList, Color rgb, float* distanceList)
{
  //draw thie line between the points indexed
  DrawLineDDA(VertexList[ls.PointOneIndex].x, VertexList[ls.PointOneIndex].y,
              VertexList[ls.PointTwoIndex].x, VertexList[ls.PointTwoIndex].y,
              distanceList[ls.PointOneIndex], distanceList[ls.PointTwoIndex],
              rgb);
}

void DDADrawTriangleList(Triangle* t, int size, Vector4 * VertexList, float* distanceList)
{
  int i;
  for(i = 0; i < size; ++i)
  {
    DDADrawTriangle(t[i], VertexList, t[i].rgb, distanceList);
  }
}

void DDADrawTriangle(Triangle t, Vector4 * VertexList, Color rgb, float* distanceList)
{
  if(isClockwise(t, VertexList))
  {
    DrawFilledTriangle(VertexList[t.PointOneIndex].x, VertexList[t.PointOneIndex].y,
                       VertexList[t.PointTwoIndex].x, VertexList[t.PointTwoIndex].y,
                       VertexList[t.PointThreeIndex].x, VertexList[t.PointThreeIndex].y,
                       distanceList[t.PointOneIndex], distanceList[t.PointTwoIndex], distanceList[t.PointThreeIndex],
                       rgb);
  }
}

BOOLEAN isClockwise(Triangle t, Vector4* VertexList)
{
  float deltaX12, deltaY12, deltaX32, deltaY32;
  Vector4 v1, v2, cross;
  deltaX12 = VertexList[t.PointTwoIndex].x - VertexList[t.PointOneIndex].x;
  deltaY12 = VertexList[t.PointTwoIndex].y - VertexList[t.PointOneIndex].y;
  deltaX32 = VertexList[t.PointTwoIndex].x - VertexList[t.PointThreeIndex].x;
  deltaY32 = VertexList[t.PointTwoIndex].y - VertexList[t.PointThreeIndex].y;
  Vector4_Set(&v1, deltaX12, deltaY12, 0, 0);
  Vector4_Set(&v2, deltaX32, deltaY32, 0, 0);
  Vector4_Cross(&cross, &v1, &v2);
  if(cross.z >= 0)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

void Cube_TempTransform(Cube * theCube, BOOLEAN Rotate)
{
  int i;
   for(i = 0; i < 8; ++i)
  {

    //scale
    theCube->VertexList[i].x *= 10;
    theCube->VertexList[i].y *= 10;
    theCube->VertexList[i].z *= 10;

    //rotate
    if(Rotate)
    {
      theCube->VertexList[i].y = cos(10.0 * 3.14/180) * theCube->VertexList[i].y - sin(10.0 * 3.14/180) * theCube->VertexList[i].z;
      theCube->VertexList[i].z = sin(10.0 * 3.14/180) * theCube->VertexList[i].y + cos(10.0 * 3.14/180) * theCube->VertexList[i].z; 
      
      theCube->VertexList[i].x = cos(15.0 * 3.14/180) *  theCube->VertexList[i].x + sin(15.0 * 3.14/180) * theCube->VertexList[i].z;
      theCube->VertexList[i].z = -sin(15.0 * 3.14/180) * theCube->VertexList[i].x + cos(15.0 * 3.14/180) * theCube->VertexList[i].z; 
    }
    
    //translate
    theCube->VertexList[i].z -= 30;
  }
}


void Cube_MatrixDraw( Cube * theCube,Matrix4 * Transform,  Matrix4 * Projection, BOOLEAN PerspectiveDivide, Matrix4 * ViewPort )
{
  Cube ToDraw = *theCube;
  int i;

  for(i = 0; i < 8; ++i)
  {
    //bring point into world space
    Matrix4_MultiplyVector(&ToDraw.VertexList[i], Transform, &ToDraw.VertexList[i]); 


    //bring point into projection space
    Matrix4_MultiplyVector(&ToDraw.VertexList[i], Projection, &ToDraw.VertexList[i]); 

    if(PerspectiveDivide)
      Vector4_Divide(&ToDraw.VertexList[i], &ToDraw.VertexList[i], ToDraw.VertexList[i].w);
    
    //bring point into viewport space
    Matrix4_MultiplyVector(&ToDraw.VertexList[i], ViewPort, &ToDraw.VertexList[i]); 
    
  }

  //draw the list of points
  /*
  DDADrawLineList(ToDraw.LineList, 12, ToDraw.VertexList);
  DDADrawTriangleList(ToDraw.TriangleList, 12, ToDraw.VertexList);
  */
}

void Cube_MatrixDrawWithCamera(Cube * theCube, struct Matrix4 * Transform,
                               struct Matrix4 * WorldToCamera, struct Matrix4 * Projection,
                               BOOLEAN PerspectiveDivide, struct Matrix4 * ViewPort, Vector4* sunVector)
{
  
  Cube ToDraw = *theCube;
  int i;

  for(i = 0; i < 8; ++i)
  {
    //bring point into world space
    Matrix4_MultiplyVector(&ToDraw.VertexList[i], Transform, &ToDraw.VertexList[i]); 
  }
  for(i = 0; i < 12; i++)
  {
   float deltaX12, deltaY12, deltaZ12, deltaX32, deltaY32, deltaZ32, angle, dot, l1, l2;
    Vector4 v1, v2, cross;
    deltaX12 = ToDraw.VertexList[ToDraw.TriangleList[i].PointTwoIndex].x - ToDraw.VertexList[ToDraw.TriangleList[i].PointOneIndex].x;
    deltaY12 = ToDraw.VertexList[ToDraw.TriangleList[i].PointTwoIndex].y - ToDraw.VertexList[ToDraw.TriangleList[i].PointOneIndex].y;
    deltaZ12 = ToDraw.VertexList[ToDraw.TriangleList[i].PointTwoIndex].z - ToDraw.VertexList[ToDraw.TriangleList[i].PointOneIndex].z;
    deltaX32 = ToDraw.VertexList[ToDraw.TriangleList[i].PointTwoIndex].x - ToDraw.VertexList[ToDraw.TriangleList[i].PointThreeIndex].x;
    deltaY32 = ToDraw.VertexList[ToDraw.TriangleList[i].PointTwoIndex].y - ToDraw.VertexList[ToDraw.TriangleList[i].PointThreeIndex].y;
    deltaZ32 = ToDraw.VertexList[ToDraw.TriangleList[i].PointTwoIndex].z - ToDraw.VertexList[ToDraw.TriangleList[i].PointThreeIndex].z;
    Vector4_Set(&v1, deltaX12, deltaY12, deltaZ12, 0);
    Vector4_Set(&v2, deltaX32, deltaY32, deltaZ32, 0);
    Vector4_Cross(&cross, &v1, &v2);
    Vector4_Negate(&cross, &cross);
    Vector4_Dot(&dot, &cross, sunVector); /*start calculating angle between normal and sun*/
    Vector4_Length(&l1, &cross);
    Vector4_Length(&l2, sunVector);
    angle = acos(dot / (l1 * l2)) / PI; /*now between 0 and 1*/
    ToDraw.TriangleList[i].rgb.Red *= angle;
    ToDraw.TriangleList[i].rgb.Blue *= angle;
    ToDraw.TriangleList[i].rgb.Green *= angle;
  }
  for(i = 0; i < 8; ++i)
  {
    Vector4 lengthV;
    float length;
    //bring into Camera Space
    Matrix4_MultiplyVector(&ToDraw.VertexList[i], WorldToCamera, &ToDraw.VertexList[i]);
    
    if(ToDraw.VertexList[i].z > 0)
      return;
    Vector4_Set(&lengthV, ToDraw.VertexList[i].x, ToDraw.VertexList[i].y, ToDraw.VertexList[i].z, 0);
    Vector4_Length(&length, &lengthV);
    ToDraw.distanceList[i] = length;
    //bring point into projection space
    Matrix4_MultiplyVector(&ToDraw.VertexList[i], Projection, &ToDraw.VertexList[i]); 

    if(PerspectiveDivide)
      Vector4_Divide(&ToDraw.VertexList[i], &ToDraw.VertexList[i], ToDraw.VertexList[i].w);

    //bring point into viewport space
    Matrix4_MultiplyVector(&ToDraw.VertexList[i], ViewPort, &ToDraw.VertexList[i]); 
  }
  //draw the list of points
  DDADrawLineList(ToDraw.LineList, 12, ToDraw.VertexList, ToDraw.distanceList);
  DDADrawTriangleList(ToDraw.TriangleList, 12, ToDraw.VertexList, ToDraw.distanceList);
}