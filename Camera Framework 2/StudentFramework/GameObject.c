#include "GameObject.h"
#include "Matrix4.h"

void GameObject_Init(GameObject * GO, Cube * cube)
{
  GO->Mesh = cube;
  Vector4_Set(&GO->Position, 0,0,0,1);
  Vector4_Set(&GO->Rotation, 0,0,0,0);
  Vector4_Set(&GO->Scale, 1,1,1,0);

}
void GameObject_CalcTransform(GameObject * GO, struct Matrix4 * Output)
{
  Matrix4 Translate;
  Matrix4 RotateX;
  Matrix4 RotateY;
  Matrix4 RotateZ;
  Matrix4 Scale;

   //set the values for every mtx
  Matrix4_Translation(&Translate, GO->Position.x, GO->Position.y, GO->Position.z);
  Matrix4_XaxisRotation(&RotateX, GO->Rotation.x);
  Matrix4_YaxisRotation(&RotateY, GO->Rotation.y);
  Matrix4_ZaxisRotation(&RotateZ, GO->Rotation.z);
  Matrix4_Scale(&Scale, GO->Scale.x, GO->Scale.y, GO->Scale.z);
  Matrix4_Identity(Output);

  //concationate the matrices
  Matrix4_Multiply(Output, &Scale,     Output);
  Matrix4_Multiply(Output, &RotateX,   Output);
  Matrix4_Multiply(Output, &RotateY,   Output);
  Matrix4_Multiply(Output, &RotateZ,   Output);
  Matrix4_Multiply(Output, &Translate, Output);
}
void GameObject_Draw(GameObject * GO, struct Matrix4 * WorldToCamera, struct Matrix4 * Projection, BOOLEAN PerspectiveDivide, struct Matrix4 * ViewPort, Vector4* sunVector)
{
  Matrix4 Transform;
  GameObject_CalcTransform(GO, &Transform);
  Cube_MatrixDrawWithCamera(GO->Mesh, &Transform, WorldToCamera, Projection, PerspectiveDivide, ViewPort, sunVector);
}
