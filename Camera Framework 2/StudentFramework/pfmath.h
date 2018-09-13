#ifndef PFMATH_H
#define PFMATH_H
#include "Vector4.h"
#include "Matrix4.h"



void AlgebraicProjToViewport(Vector4 * Out, Vector4 * In, int ViewportWidth, int ViewPortHeight);
void AlgebraicPerspProjection(Vector4 * Out, Vector4 * In, float focal, float ProjectionWindowWidth, float ProjectionWindowHeight);
void AlgebraicOrthoProjection(Vector4 * Out, Vector4 * In, float focal, float ProjectionWindowWidth, float ProjectionWindowHeight);


//graphics specific matrices
void Matrix4_ModelToWorld(Matrix4 * Output, struct Vector4 * Translation, struct Vector4 * Rotation, struct Vector4 * Scale);
void Matrix4_Projection(Matrix4 * output, float focal, float Width, float Height);
void Matrix4_ProjToViewport(Matrix4 * output, int ScreenWidth, int ScreenHeight);
void Matrix4_OrthoProjection(Matrix4 * output, float focal, float Width, float Height);


#endif