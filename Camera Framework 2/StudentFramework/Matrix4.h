#ifndef MATRIX4_H
#define MATRIX4_H
#include "Utilities.h"

struct Vector4;

typedef struct Matrix4
{
  union
  {
    struct
    {
      f32 m00, m01, m02, m03,
          m10, m11, m12, m13,
          m20, m21, m22, m23,
          m30, m31, m32, m33;
    };
  
    f32 m[4][4];
    f32 v[16];
  };
}Matrix4;


//creation
Matrix4 Matrix4_CreateZero(void);
Matrix4 Matrix4_Create(f32 mm00, f32 mm01, f32 mm02, f32 mm03,
                       f32 mm10, f32 mm11, f32 mm12, f32 mm13,
                       f32 mm20, f32 mm21, f32 mm22, f32 mm23,
                       f32 mm30, f32 mm31, f32 mm32, f32 mm33);

//copy
void Matrix4_Copy(Matrix4* dest, Matrix4* src);

//vector arithmetic
void Matrix4_MultiplyVector(struct Vector4* result, Matrix4* left, struct Vector4* right);

//matrix arithmetic
void Matrix4_Multiply(Matrix4* result, Matrix4* left, Matrix4* right);
void Matrix4_Add(Matrix4 * result, Matrix4 * left, Matrix4 * right);
void Matrix4_Subtract(Matrix4 * result, Matrix4* left, Matrix4 * right);

//scalar arithmetic

void Matrix4_MultiplyFloat(Matrix4* result, Matrix4* left, f32 right);
void Matrix4_DivideFloat(Matrix4* result, Matrix4* left, f32 right);

BOOLEAN Matrix4_IsEqual(Matrix4 * left, Matrix4 * right);
BOOLEAN Matrix4_IsNotEqual(Matrix4 * left, Matrix4* right);

void Matrix4_Zero(Matrix4 * Mat);

void Matrix4_XaxisRotation(Matrix4 * output, f32 angle);
void Matrix4_YaxisRotation(Matrix4 * output, f32 angle);
void Matrix4_ZaxisRotation(Matrix4 * output, f32 angle);

void Matrix4_TranslationVector(Matrix4* output, struct Vector4 * translation);
void Matrix4_Translation(Matrix4* output, f32 X, f32 Y, f32 Z);

void Matrix4_Scale(Matrix4 * output, f32 ScaleX, f32 ScaleY, f32 ScaleZ);

void Matrix4_Transpose(Matrix4 * output,  Matrix4 * input);
void Matrix4_Identity(Matrix4 * output);



void Matrix4_BuildBasis(Matrix4 * Output, struct Vector4 * B1, struct Vector4 * B2, struct Vector4 * B3, struct Vector4 * B4);

#endif