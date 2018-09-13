#include "MatrixStack.h"
#include "Matrix4.h"


BOOLEAN MatrixStack_Init(MatrixStack * stack, int Size)
{
  stack->size = Size;
  stack->Index = -1;
  stack->Stack = (Matrix4 *) malloc(sizeof(Matrix4) * Size);
  if(stack->Stack == NULL)
    return FALSE;
  else
    return TRUE;
}
void MatrixStack_Delete(MatrixStack * stack)
{
  free(stack->Stack);
}
BOOLEAN MatrixStack_Pop(MatrixStack * stack)
{
  //if at the end
  if(stack->Index == -1)
    return FALSE;
  stack->Index--;
  return TRUE;

}
BOOLEAN MatrixStack_Push(MatrixStack * stack, Matrix4 * Input)
{
  //if no room
  if(stack->Index == stack->size - 1)
    return FALSE;

  stack->Index++;
  stack->Stack[stack->Index] = *Input;
  return TRUE;
}
BOOLEAN MatrixStack_IsEmpty(MatrixStack * stack)
{
  if(stack->Index == -1)
    return TRUE;
  else
    return FALSE;
}
int MatrixStack_Size(MatrixStack * stack)
{
  return stack->Index + 1;
}
BOOLEAN MatrixStack_Top(MatrixStack * stack, Matrix4 * Output)
{
  if(MatrixStack_IsEmpty(stack) == TRUE)
    return FALSE;

  *Output = stack->Stack[stack->Index];
  return TRUE;
}

Matrix4 MatrixStack_Concat(MatrixStack * stack)
{
  Matrix4 Accum;
  int i;

  Matrix4_Identity(&Accum);
  //walk from bottom to top of stack
  for(i = 0; i < stack->Index + 1; ++i)
  {
    Matrix4_Multiply(&Accum, &Accum, &stack->Stack[i]);
  }

  return Accum;
}