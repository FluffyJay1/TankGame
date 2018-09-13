#ifndef CAMERA_H
#define CAMERA_H
#include "Vector4.h"
struct Matrix4;
struct GameObject;

enum CAMERAMODES
{
  FREE_CAMERA,
  FIRST_PERSON_SPHERE,
  FIRST_PERSON_CYLINDRICAL,
  THIRD_PERSON_SPHERE,
  THIRD_PERSON_CYLINDRICAL,
  THIRD_PERSON_SPRING,
  THIRD_PERSON_RIGID
};

typedef struct Camera
{
  //basic camera orientation
  Vector4 Position;
  Vector4 LookAt;
  Vector4 Up;

  //camera algorithm data
  int mode;
  struct GameObject * TargetObject;

  //spherical coordinates
  float R;
  float theta;
  float phi;
  float RotationalOffset;
  //height used in Cylindrical coordinates
  float height;

  //for rigid and spring following camera
  float HorizontalFollowDistance;
  float VerticalFollowDistance;

  //spring values
  float SpringStrength;
  float SpringDampining;
  Vector4 Velocity;

}Camera;

void Camera_Init(Camera * theCam, struct GameObject * Target);
void Matrix4_WorldToCamera(struct Matrix4 * output, Camera * theCam);

//camera updates
void Camera_Update(Camera * theCam);
void Camera_1stPersonSphere(Camera * theCam);
void Camera_1stPersonCylinder(Camera * theCam);
void Camera_3rdPersonSphere(Camera * theCam);
void Camera_3rdPersonCylinder(Camera * theCam);
void Camera_3rdPersonRigid(Camera * theCam);
void Camera_3rdPersonSpring(Camera * TheCam);

//coordinate system transformations
void SphereToCartesian(Vector4 * output, float r, float theta, float phi);
void CylinderToCartesian(Vector4 * Output, float r, float theta, float height);





#endif