#include "Vector4.h"

Vector4 Vector4_CreateZero(void)
{
  Vector4 Out;
  Out.x = 0;
  Out.y = 0;
  Out.z = 0;
  Out.w = 0;

  return Out;
}
Vector4 Vector4_Create(f32 X_, f32 Y_, f32 Z_, f32 W_)
{
  Vector4 Out;
  Out.x = X_;
  Out.y = Y_;
  Out.z = Z_;
  Out.w = W_;
  return Out;
}

void Vector4_Copy(Vector4* output, Vector4* input)
{
  //copy in case of self assignment
  Vector4 In = *input;
  *output = In;
}

void Vector4_Negate(Vector4 * output, Vector4 * input)
{
  Vector4 In;
  Vector4_Copy(&In, input);

  output->x = -In.x;
  output->y = -In.y;
  output->z = -In.z;
  output->w = -In.w;

}

void Vector4_Add(Vector4 * output, Vector4* left, Vector4 * right)
{
  Vector4 Left, Right;
  Vector4_Copy(&Left, left);
  Vector4_Copy(&Right, right);

  output->x = Left.x + Right.x;
  output->y = Left.y + Right.y;
  output->z = Left.z + Right.z;
  output->w = Left.w + Right.w;


}
void Vector4_Subtract(Vector4* output, Vector4 * left, Vector4 * right)
{
  Vector4 Left, Right;
  Vector4_Copy(&Left, left);
  Vector4_Copy(&Right, right);

  output->x = Left.x - Right.x;
  output->y = Left.y - Right.y;
  output->z = Left.z - Right.z;
  output->w = Left.w - Right.w;

}
void Vector4_Multiply(Vector4 * output, Vector4 * left, f32 right)
{
  Vector4 Left;
  Vector4_Copy(&Left, left);

  output->x = Left.x * right;
  output->y = Left.y * right;
  output->z = Left.z * right;
  output->w = Left.w * right;
}

void Vector4_Divide(Vector4 * output, Vector4 * left, f32 right)
{
  Vector4 Left;
  Vector4_Copy(&Left, left);

  output->x = Left.x / right;
  output->y = Left.y / right;
  output->z = Left.z / right;
  output->w = Left.w / right;
}

BOOLEAN Vector4_IsEqual(Vector4 * left, Vector4 * right)
{
  return float_IsEqual(left->x, right->x) &&
         float_IsEqual(left->y, right->y) &&
         float_IsEqual(left->z, right->z) &&
         float_IsEqual(left->w, right->w) ? TRUE: FALSE;
}
BOOLEAN Vector4_IsNotEqual(Vector4 * left, Vector4 * right)
{
  return !Vector4_IsEqual(left, right);
}

void Vector4_Dot(f32 * output, Vector4 * left, Vector4* right)
{
  Vector4 Left, Right;
  Vector4_Copy(&Left, left);
  Vector4_Copy(&Right, right);

  *output = Left.x * Right.x +
            Left.y * Right.y +
            Left.z * Right.z +
            Left.w * Right.w;
}
void Vector4_Cross(Vector4 * output, Vector4 * left, Vector4 * right)
{
  Vector4 Left, Right, Cross;
  Vector4_Copy(&Left, left);
  Vector4_Copy(&Right, right);

  Cross.x = Left.y * Right.z - Left.z * Right.y;
  Cross.y = Left.z * Right.x - Left.x * Right.z;
  Cross.z = Left.x * Right.y - Left.y * Right.x;
  Cross.w = 0; //vector, so no w component
  Vector4_Copy(output, &Cross);
}

void Vector4_Length(f32 * output, Vector4 * input)
{
  float LengthSq;
  Vector4_LengthSquared(&LengthSq, input);
  *output = sqrt(LengthSq);
}
void Vector4_LengthSquared( f32 * output, Vector4 * input)
{
  *output = input->x * input->x +
            input->y * input->y +
            input->z * input->z +
            input->w * input->w;
}

void Vector4_Normalize(Vector4 * output, Vector4 * input)
{
  Vector4 In;
  f32 Length;
  Vector4_Copy(&In, input);
  Vector4_Length(&Length, &In);

  Vector4_Divide(output, &In, Length);
}
void Vector4_Zero(Vector4 * output)
{
  output->x = 0;
  output->y = 0;
  output->x = 0;
  output->z = 0;
}

void Vector4_Set(Vector4 * Vec, float X, float Y, float Z, float W)
{
  Vec->x = X;
  Vec->y = Y;
  Vec->z = Z;
  Vec->w = W;
}