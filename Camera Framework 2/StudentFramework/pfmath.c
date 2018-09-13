#include "pfmath.h"

void AlgebraicProjToViewport(Vector4 * Out, Vector4 * In, int ViewportWidth, int ViewPortHeight)
{
  Vector4 input;
  Vector4_Copy(&input, In);
  Out->x = input.x * ViewportWidth + ViewportWidth/2;
  Out->y = -1 * input.y * ViewPortHeight + ViewPortHeight/2;
}
void AlgebraicPerspProjection(Vector4 * Out, Vector4 * In, float focal, float ProjectionWindowWidth, float ProjectionWindowHeight)
{
    
  Vector4 input;
  Vector4_Copy(&input, In);

  Out->x = -input.x * (focal/ProjectionWindowWidth)/ input.z;
  Out->y = -input.y * (focal/ProjectionWindowHeight) / input.z;
  Out->z = -focal;
}
void AlgebraicOrthoProjection(Vector4 * Out, Vector4 * In, float focal, float ProjectionWindowWidth, float ProjectionWindowHeight)
{
    Vector4 input;
  Vector4_Copy(&input, In);
  //normalize x and y
  Out->x = input.x/ProjectionWindowWidth;
  Out->y = input.y/ProjectionWindowHeight;
  Out->z = -focal;
}



void Matrix4_ModelToWorld(Matrix4 * Output, struct Vector4 * Translation, struct Vector4 * Rotation, struct Vector4 * Scale)
{
  Matrix4 Translate, RotationX, RotationY, RotationZ, ScaleMat;

    //built the matrices for world transform
   Matrix4_Translation(&Translate, Translation->x, Translation->y, Translation->z);
   Matrix4_Scale(&ScaleMat, Scale->x, Scale->y, Scale->z);
   Matrix4_XaxisRotation(&RotationX, Rotation->x);
   Matrix4_YaxisRotation(&RotationY, Rotation->y);
   Matrix4_ZaxisRotation(&RotationZ, Rotation->z);

   //concatonate them
   Matrix4_Multiply(Output, &RotationX, &ScaleMat);
   Matrix4_Multiply(Output, &RotationY, Output);
   Matrix4_Multiply(Output, &RotationZ, Output);
   Matrix4_Multiply(Output, &Translate, Output);
}


void Matrix4_Projection(Matrix4 * output, float focal, float Width, float Height)
{
  // [ f/w   0   0  0 ]
  // [  0   f/h  0  0 ]
  // [  0    0   f  0 ]
  // [  0    0  -1  0 ]

  Matrix4_Zero(output);
  output->m00 = focal/Width;
  output->m11 = focal/Height;
  output->m22 = focal;
  output->m32 = -1;
}
void Matrix4_ProjToViewport(Matrix4 * output, int ScreenWidth, int ScreenHeight)
{
  // [ sw   0  0  sw/2 ]
  // [  0 -sh  0  sh/2 ]
  // [  0   0  1  0    ]
  // [  0   0  0  1    ]
  Matrix4_Zero(output);
  output->m00 = ScreenWidth;
  output->m11 = -ScreenHeight;
  output->m22 = 1;
  output->m33 = 1;

  output->m03 = ScreenWidth/2;
  output->m13 = ScreenHeight/2;
}

void Matrix4_OrthoProjection(Matrix4 * output, float focal, float Width, float Height)
{
  // [ 1/w   0   0   0 ]
  // [  0   1/h  0   0 ]
  // [  0    0   0  -d ]
  // [  0    0   0   1 ]

  Matrix4_Zero(output);
  output->m00 = 1/Width;
  output->m11 = 1/Height;
  output->m23 = -focal;
  output->m33 = 1;

}