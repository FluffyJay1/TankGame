#include "Matrix4.h"
#include "Vector4.h"

//creation
Matrix4 Matrix4_CreateZero(void)
{
  Matrix4 NewMatrix;
  memset(&NewMatrix, 0, sizeof(NewMatrix));
  return NewMatrix;
}
Matrix4 Matrix4_Create(f32 mm00, f32 mm01, f32 mm02, f32 mm03,
                       f32 mm10, f32 mm11, f32 mm12, f32 mm13,
                       f32 mm20, f32 mm21, f32 mm22, f32 mm23,
                       f32 mm30, f32 mm31, f32 mm32, f32 mm33)
{
  Matrix4 NewMatrix;
  NewMatrix.m00 = mm00;
  NewMatrix.m01 = mm01;
  NewMatrix.m02 = mm02;
  NewMatrix.m03 = mm03;

  NewMatrix.m10 = mm10;
  NewMatrix.m11 = mm11;
  NewMatrix.m12 = mm12;
  NewMatrix.m13 = mm13;

  NewMatrix.m20 = mm20;
  NewMatrix.m21 = mm21;
  NewMatrix.m22 = mm22;
  NewMatrix.m23 = mm23;

  NewMatrix.m30 = mm30;
  NewMatrix.m31 = mm31;
  NewMatrix.m32 = mm32;
  NewMatrix.m33 = mm33;

  return NewMatrix;

}

//copy
void Matrix4_Copy(Matrix4* dest, Matrix4* src)
{
  *dest = *src;
}

//vector arithmetic
void Matrix4_MultiplyVector(struct Vector4* result, Matrix4* left, struct Vector4* right)
{
  Vector4 Input;
  Vector4_Copy(&Input, right);

  result->x = left->m00 * Input.x + left->m01 * Input.y + left->m02 * Input.z + left->m03 * Input.w;

  result->y = left->m10 * Input.x + left->m11 * Input.y + left->m12 * Input.z + left->m13 * Input.w;

  result->z = left->m20 * Input.x + left->m21 * Input.y + left->m22 * Input.z + left->m23 * Input.w;

  result->w = left->m30 * Input.x + left->m31 * Input.y + left->m32 * Input.z + left->m33 * Input.w;

}

//matrix arithmetic
void Matrix4_Multiply(Matrix4* result, Matrix4* left, Matrix4* right)
{
  int i, j;
  Matrix4 lhs, rhs;
  Matrix4_Copy(&lhs, left);
  Matrix4_Copy(&rhs, right);
  
  for (i = 0; i < 4; ++i)
  {
    for(j = 0; j < 4; ++j)
    {
      result->m[i][j] = lhs.m[i][0] * rhs.m[0][j]
                      + lhs.m[i][1] * rhs.m[1][j]
                      + lhs.m[i][2] * rhs.m[2][j]
                      + lhs.m[i][3] * rhs.m[3][j];
    }
  }
}
void Matrix4_Add(Matrix4 * result, Matrix4 * left, Matrix4 * right)
{
  int i;
  for(i = 0; i < 16; ++i)
  {
    result->v[i] = left->v[i] + right->v[i];
  }
}
void Matrix4_Subtract(Matrix4 * result, Matrix4* left, Matrix4 * right)
{
  int i;
  for(i = 0; i < 16; ++i)
  {
    result->v[i] = left->v[i] - right->v[i];
  }
}

//scalar arithmetic
void Matrix4_MultiplyFloat(Matrix4* result, Matrix4* left, f32 right)
{
  int i;
  for(i = 0; i < 16; ++i)
  {
    result->v[i] = left->v[i] * right;
  }
}
void Matrix4_DivideFloat(Matrix4* result, Matrix4* left, f32 right)
{
  
  int i;
  for(i = 0; i < 16; ++i)
  {
    result->v[i] = left->v[i] * right;
  }

}

BOOLEAN Matrix4_IsEqual(Matrix4 * left, Matrix4 * right)
{
  int i;
  for(i = 0; i < 16; ++i)
  {
    if(!float_IsEqual(left->v[i], right->v[i]))
    {
      return FALSE;
    }
  }

  return TRUE;
}
BOOLEAN Matrix4_IsNotEqual(Matrix4 * left, Matrix4* right)
{
  return !Matrix4_IsEqual(left, right);
}

void Matrix4_Zero(Matrix4 * Mat)
{
  memset(Mat, 0, sizeof(Matrix4));
}

void Matrix4_XaxisRotation(Matrix4 * output, f32 angle)
{

  // [   1    0     0    0 ]
  // [   0   cos  -sin   0 ]
  // [   0   sin   cos   0 ]
  // [   0    0     0    1 ]

  Matrix4_Identity(output);
  output->m11 = cos(angle);
  output->m12 = -sin(angle);
  output->m21= sin(angle);
  output->m22 = cos(angle);

}
void Matrix4_YaxisRotation(Matrix4 * output, f32 angle)
{
  // [  cos   0   sin   0 ]
  // [   0    1    0    0 ]
  // [ -sin   0   cos   0 ]
  // [   0    0    0    1 ]

  Matrix4_Identity(output);
  output->m00 = cos(angle);
  output->m02 = sin(angle);
  output->m20= -sin(angle);
  output->m22 = cos(angle);
}
void Matrix4_ZaxisRotation(Matrix4 * output, f32 angle)
{
  // [  cos   -sin   0   0 ]
  // [  sin    cos   0   0 ]
  // [   0      0    1   0 ]
  // [   0      0    0   1 ]

  Matrix4_Identity(output);
  output->m00 = cos(angle);
  output->m01 = -sin(angle);
  output->m10 = sin(angle);
  output->m11 = cos(angle);
}

void Matrix4_TranslationVector(Matrix4* output, struct Vector4 * translation)
{
  // [  1    0   0   Tx ]
  // [  0    1   0   Ty ]
  // [  0    0   1   Tz ]
  // [  0    0   0   1  ]

  Matrix4_Identity(output);
  output->m03 = translation->x;
  output->m13 = translation->y;
  output->m23 = translation->z;
}
void Matrix4_Translation(Matrix4* output, f32 X, f32 Y, f32 Z)
{
  // [  1    0   0   Tx ]
  // [  0    1   0   Ty ]
  // [  0    0   1   Tz ]
  // [  0    0   0   1  ]

  Matrix4_Identity(output);
  output->m03 = X;
  output->m13 = Y;
  output->m23 = Z;
}

void Matrix4_Scale(Matrix4 * output, f32 ScaleX, f32 ScaleY, f32 ScaleZ)
{
  // [  Sx   0   0   0 ]
  // [  0    Sy  0   0 ]
  // [  0    0   Sz  0 ]
  // [  0    0   0   1 ]


  Matrix4_Zero(output);
  output->m00 = ScaleX;
  output->m11 = ScaleY;
  output->m22 = ScaleZ;
  output->m33 = 1;
}

void Matrix4_Transpose(Matrix4 * output,  Matrix4 * input)
{
  Matrix4 In;
  int i, j;
  Matrix4_Copy(&In, input);

  for(i = 0; i < 3; ++i)
  {
    for(j= i + 1; j < 3; ++j)
    {
      output->m[i][j] = In.m[j][i];
      output->m[j][i] = In.m[i][j];
    }
  }

}
void Matrix4_Identity(Matrix4 * output)
{
  int i, j;
  for(i = 0; i < 4; ++i)
  {
    for(j = 0; j < 4; ++j)
    {
      output->m[i][j] = (i == j) ? 1 : 0;
    }
  }
}


void Matrix4_BuildBasis(Matrix4 * Output, Vector4 * B1, Vector4 * B2, Vector4 * B3, Vector4 * B4)
{

  //set the four column vectors so the matrix is the following
  // [B1 | B2 | B3 | B4 ]
  Output->m00 = B1->x;
  Output->m10 = B1->y;
  Output->m20 = B1->z;
  Output->m30 = B1->w;

  Output->m01 = B2->x;
  Output->m11 = B2->y;
  Output->m21 = B2->z;
  Output->m31 = B2->w;

  Output->m02 = B3->x;
  Output->m12 = B3->y;
  Output->m22 = B3->z;
  Output->m32 = B3->w;

  Output->m03 = B4->x;
  Output->m13 = B4->y;
  Output->m23 = B4->z;
  Output->m33 = B4->w;
}

