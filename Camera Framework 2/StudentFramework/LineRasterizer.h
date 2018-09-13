#ifndef LINERASTERIZER_H
#define LINERASTERIZER_H
#include "Vector4.h"

typedef struct Color
{
  unsigned char Red;
  unsigned char Green;
  unsigned char Blue;

}Color;

//interface function
void DrawLineDDA(float X1, float Y1, float X2, float Y2, float distance1, float distance2, Color rgb);

//helper functions
void DrawVerticalLine(float X, float Y1, float Y2, Color rgb, float distance1, float distance2);
void DrawHorizontalLine(float X1, float X2, float Y, Color rgb, float distance1, float distance2);
void DrawLineDDALargeSlope(float X1, float Y1, float X2, float Y2, Color rgb, float distance1, float distance2);
void DrawLineDDASmallSlope(float X1, float Y1, float X2, float Y2, Color rgb, float distance1, float distance2);


void DrawFilledTriangle(float fX1, float fY1, float fX2, float fY2, float fX3, float fY3, float distance1, float distance2, float distance3, Color rgb);
void DrawUnfilledTriangle(float X1, float Y1, float X2, float Y2, float X3, float Y3, float distance1, float distance2, float distance3, Color rgb);
#endif