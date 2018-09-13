#ifndef VECTOR4_H
#define VECTOR4_H
#include "Utilities.h"

typedef struct Vector4
{
  union
  {
    struct 
    {
      f32 x, y, z, w;
    };
  
    struct  
    {
      f32 r, g, b, a;
    };
  
    f32 v[4];
  };
}Vector4;

Vector4 Vector4_CreateZero(void);
Vector4 Vector4_Create(f32 X_, f32 Y_, f32 Z_, f32 W_);

void Vector4_Copy(Vector4* output, Vector4* input);

void Vector4_Negate(Vector4 * output, Vector4 * input);

void Vector4_Add(Vector4 * output, Vector4* left, Vector4 * right);
void Vector4_Subtract(Vector4* output, Vector4 * left, Vector4 * right);
void Vector4_Multiply(Vector4 * output, Vector4 * left, f32 right);
void Vector4_Divide(Vector4 * output, Vector4 * left, f32 right);

BOOLEAN Vector4_IsEqual(Vector4 * left, Vector4 * right);
BOOLEAN Vector4_IsNotEqual(Vector4 * left, Vector4 * right);

void Vector4_Dot(f32 * output, Vector4 * left, Vector4* right);
void Vector4_Cross(Vector4 * output, Vector4 * left, Vector4 * right);

void Vector4_Length(f32 * output, Vector4 * input);
void Vector4_LengthSquared( f32 * output, Vector4 * input);

void Vector4_Normalize(Vector4 * output, Vector4 * input);
void Vector4_Zero(Vector4 * output);
void Vector4_Set(Vector4 * Vec, float X, float Y, float Z, float W);

#endif