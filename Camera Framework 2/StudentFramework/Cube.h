#ifndef CUBE_H
#define CUBE_H
#include "LineRasterizer.h"
#include "Camera.h"
struct Matrix4;
typedef struct LineSegment
{
  unsigned int PointOneIndex;
  float PointOneDistance;
  unsigned int PointTwoIndex;
  float PointTwoDistance;
  Color rgb;
}LineSegment;

typedef struct Triangle
{
  unsigned int PointOneIndex;
  float PointOneDistance;
  unsigned int PointTwoIndex;
  float PointTwoDistance;
  unsigned int PointThreeIndex;
  float PointThreeDistance;
  Color rgb;
}Triangle;

typedef struct Cube
{
  Vector4 VertexList[8];
  float distanceList[8];
  LineSegment LineList[12];
  Triangle TriangleList[12];
}Cube;

void Cube_Init( Cube * theCube, BOOLEAN color);
void Cube_TempTransform(Cube * theCube, BOOLEAN Rotate);
void Cube_AlgebraicDraw( Cube * theCube, BOOLEAN Perspective,
                                         int viewportWidth, int viewportHeight, 
                                         float focal, 
                                         float ProjectionWindowWidth, float ProjectionWindowHeight );

void Cube_MatrixDraw( Cube * theCube, struct Matrix4 * Transform, struct Matrix4 * Projection, BOOLEAN PerspectiveDivide, struct Matrix4 * ViewPort );

void Cube_MatrixDrawWithCamera(Cube * theCube, 
                               struct Matrix4 * Transform,
                               struct Matrix4 * WorldToCamera,
                               struct Matrix4 * Projection, 
                               BOOLEAN PerspectiveDivide,
                               struct Matrix4 * ViewPort,
                               Vector4* sunVector);
//line renderer that we need
void DDADrawLineList(LineSegment* ls, int size, Vector4 * VertexList, float* distanceList);
void DDADrawLineSegment(LineSegment ls, Vector4 * VertexList, Color rgb, float* distanceList);
void DDADrawTriangleList(Triangle* t, int size, Vector4 * VertexList, float* distanceList);
void DDADrawTriangle(Triangle t, Vector4 * VertexList, Color rgb, float* distanceList);
BOOLEAN isClockwise(Triangle t, Vector4* VertexList);
#endif