#ifndef MATRIXSTACK_H
#define MATRIXSTACK_H
#include "FrameworkInterface.h"
#include "Utilities.h"
#include "Matrix4.h"

typedef struct MatrixStack
{
  int size;
  int Index;
  struct Matrix4 * Stack;
}MatrixStack;

BOOLEAN MatrixStack_Init(MatrixStack * stack, int Size);
void MatrixStack_Delete(MatrixStack * stack);
BOOLEAN MatrixStack_Pop (MatrixStack * stack);
BOOLEAN MatrixStack_Top(MatrixStack * stack, struct Matrix4 * Output);
BOOLEAN MatrixStack_Push(MatrixStack * stack, struct Matrix4 * Input);
BOOLEAN MatrixStack_IsEmpty(MatrixStack * stack);
int MatrixStack_Size(MatrixStack * stack);
Matrix4 MatrixStack_Concat(MatrixStack * stack);


#endif