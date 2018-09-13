#pragma once

#include "windows.h"
#include "glut.h"
#include "math.h"
#include "stdio.h"

#define WIDTH 1600
#define HEIGHT 900

#define PI 3.14159265358979323846
#define DEG_TO_RAD (PI / 180.0)

#define EPSILON 0.0001f

#define TRUE 1
#define FALSE 0
#define BOOLEAN int

// Typedefs for consistency
typedef unsigned char      u8;
typedef char               s8;
typedef unsigned int       u32;
typedef int                s32;
typedef unsigned long long u64;
typedef long long          s64;
typedef float              f32;
typedef double             f64;

BOOLEAN float_IsEqual(f32 left, f32 right);
BOOLEAN double_IsEqual(f64 left, f64 right);
int Round(f64 input);



typedef struct FrameBuffer
{
  unsigned char * buffer;
  int width;
  int height;
} FrameBuffer;	

typedef struct DistanceBuffer
{
  float distanceAt[WIDTH][HEIGHT];
}DistanceBuffer;

FrameBuffer GlobalFrameBuffer;

void FrameBuffer_Clear(FrameBuffer * fb, unsigned char r, unsigned char g, unsigned char b);
void FrameBuffer_ClearToBackground(FrameBuffer* fb);
void FrameBuffer_Init(FrameBuffer * fb, unsigned int w, unsigned int h);
void FrameBuffer_SetPixel(FrameBuffer * fb,  int x, int y,  unsigned char r,  unsigned char g,  unsigned char b, float distance);
void FrameBuffer_GetPixel(FrameBuffer * fb, int x, int y, unsigned char r, unsigned char g, unsigned char b);
void FrameBuffer_Destroy(FrameBuffer * fb);


