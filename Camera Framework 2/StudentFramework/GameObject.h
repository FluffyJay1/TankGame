#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Vector4.h"
#include "Cube.h"
struct Matrix4;


typedef struct GameObject
{
  Vector4 Position;
  Vector4 Rotation;
  Vector4 Scale;
  Cube* Mesh;
}GameObject;

void GameObject_Init(GameObject * GO, Cube * cube);
void GameObject_CalcTransform(GameObject * GO, struct Matrix4 * Output);
void GameObject_Draw(GameObject * GO,struct Matrix4 * WorldToCamera, struct Matrix4 * Projection, BOOLEAN PerspectiveDivide, struct Matrix4 * ViewPort, Vector4* sunVector);


#endif