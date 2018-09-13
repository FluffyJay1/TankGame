#include "Camera.h"
#include "Matrix4.h"
#include "GameObject.h"
#include "Vector4.h"

void Camera_Init(Camera * theCam, struct GameObject * Target)
{
  /* Set camera default values

    look at position = 0 0 -1 0
    Set camera position at the origin
    Camera's up = 0 1 0 0

    Camera's target object = target
    Camera's Sphere coordinate radius is 10
    Camera's Sphere coordinate phi is PI
    Camera's Sphere coordinate theta is 0
    Camera's vertical follow distance is 10
    Camera's horizontal follow distance is 30

    Camera's springStrength = 0.5
    Camera's springDamping = 20 x sqrt( camera's SpringStrength)
  */
  theCam->LookAt = Vector4_Create(0, 0, -1, 0);
  theCam->Position = Vector4_Create(0, 1000, 0, 1);
  theCam->Up = Vector4_Create(0, 1, 0, 0);

  theCam->TargetObject = Target;
  theCam->R = 10;
  theCam->phi = 3.1415926535897932384626233832795;
  theCam->theta = 0;
  theCam->VerticalFollowDistance = 60;
  theCam->HorizontalFollowDistance = 140;
  theCam->RotationalOffset = 0;

  theCam->SpringStrength = 0.5;
  theCam->SpringDampining = 20 * sqrt(theCam->SpringStrength);
}
void Matrix4_WorldToCamera(Matrix4 * Output, Camera * theCam)
{

  Matrix4 Translation;
  Matrix4 Rotation;

  Vector4 Right;
  Vector4 InvTranslation;
  Vector4 PerpUp;
  Vector4 Origin;
  Vector4 NegativeLook;

  //Set Origin
  /*Origin = 0 0 0 1*/
  Origin = Vector4_Create(0, 0, 0, 1);
  //translation
  //Negate the camera position into inverse translation
  //Then create the translation matrix using the inverse translation
  Vector4_Negate(&InvTranslation, &theCam->Position);
  Matrix4_TranslationVector(&Translation, &InvTranslation);
  /*get the "Right" vector
    Get the cross product of cam's LookAt and cam's Up*/
  Vector4_Cross(&Right, &theCam->LookAt, &theCam->Up);
  /*Get the perpindicular "Up" vector
    Get the cross product of cam's Right and cam's LookAt*/
  Vector4_Cross(&PerpUp, &Right, &theCam->LookAt);
  //get the Negative look
  Vector4_Negate(&NegativeLook, &theCam->LookAt);
  //normalize vectors
  /*..NegativeLook
    ..Right
    ..PerpUp
  */
  Vector4_Normalize(&NegativeLook, &NegativeLook);
  Vector4_Normalize(&Right, &Right);
  Vector4_Normalize(&PerpUp, &PerpUp);
  //aligns with X, Y, -Z
  /*Build Rotation mtx using build basis with Right, PerpUp, NegativeLook, Origin*/
  Matrix4_BuildBasis(&Rotation, &Right, &PerpUp, &NegativeLook, &Origin);
  //inverse rotation
  //Use the transpose function...
  Matrix4_Transpose(&Rotation, &Rotation);
  /*translate to origin, then rotate
    Output = Rotation x Translation*/
  Matrix4_Multiply(Output, &Rotation, &Translation);
}

void Camera_Update(Camera * theCam)
{
  switch(theCam->mode)
  {
  case FIRST_PERSON_SPHERE:
    Camera_1stPersonSphere(theCam);
    break;
  case FIRST_PERSON_CYLINDRICAL:
    Camera_1stPersonCylinder(theCam);
    break;
  case THIRD_PERSON_SPHERE:
    Camera_3rdPersonSphere(theCam);
    break;
  case THIRD_PERSON_CYLINDRICAL:
    Camera_3rdPersonCylinder(theCam);
    break;
  case THIRD_PERSON_SPRING:
    Camera_3rdPersonSpring(theCam);
    break;
  case THIRD_PERSON_RIGID:
    Camera_3rdPersonRigid(theCam);
    break;
  default :
    break;
  }
}

void Camera_1stPersonSphere(Camera * theCam)
{
  Vector4 Target;
  /*Insert Sphere to cartesian coordinates into Target*/
 SphereToCartesian(&Target, theCam->R, theCam->theta, theCam->phi);
  /*
    Camera's position = camera's TargetObject position
    Add camera's TargetObject Y scale to Camera's y position
    camera's LookAt = Target
  */  
  theCam->Position = theCam->TargetObject->Position;
  theCam->Position.y += theCam->TargetObject->Scale.y;
  theCam->LookAt = Target;
}
void Camera_1stPersonCylinder(Camera * theCam)
{
  Vector4 Target;
  /*Insert Cylinder to cartesian coordinates into Target*/
  CylinderToCartesian(&Target, theCam->R, theCam->theta, theCam->height);
  /*
  Camera's position = camera's TargetObject position
  Add camera's TargetObject Y scale to Camera's y position
  camera's LookAt = Target
  */
  theCam->Position = theCam->TargetObject->Position;
  theCam->Position.y += theCam->TargetObject->Scale.y;
  theCam->LookAt = Target;
}
void Camera_3rdPersonSphere(Camera * theCam)
{
  
  Vector4 Target;
  Vector4 Lookat;
  
  /*Insert into Target sphere to cartesian coordinates*/
  SphereToCartesian(&Target, theCam->R, theCam->theta, theCam->phi);
  /*Add to Target the camera's TargetObject position*/
  Vector4_Add(&Target, &Target, &theCam->TargetObject->Position);
  /*Lookat = camera's target object position - Target*/
  Vector4_Subtract(&Lookat, &theCam->TargetObject->Position, &Target);
  /*camera's position = Target*/
  theCam->Position = Target;
  /*camera's LookAt = LookAt*/
  theCam->LookAt = Lookat;
}
void Camera_3rdPersonCylinder(Camera * theCam)
{
    
  Vector4 Target;
  Vector4 Lookat;
  
  /*Insert into Target cylinder to cartesian coordinates*/
  CylinderToCartesian(&Target, theCam->R, theCam->theta, theCam->height);
  /*Add to Target the camera's TargetObject position*/
   Vector4_Add(&Target, &Target, &theCam->TargetObject->Position);
  /*Lookat = camera's target object position - Target*/
   Vector4_Subtract(&Lookat, &theCam->TargetObject->Position, &Target);
  /*camera's position = Target*/
   theCam->Position = Target;
  /*camera's LookAt = LookAt*/
   theCam->LookAt = Lookat;
}
void Camera_3rdPersonRigid(Camera * theCam)
{
  Vector4 TargetForward, TargetUp, Offset;
  Matrix4 TargetTransform;
  /*1st step
  TargetForward = 0 0 -1 0
  TargetUp = 0 1 0 0*/
  TargetForward = Vector4_Create(0, 0, -1, 0);
  TargetUp = Vector4_Create(0, 1, 0, 0);
  /*2nd step
  GameObject_CalcTransform(theCam->TargetObject, &TargetTransfom);*/
  GameObject_CalcTransform(theCam->TargetObject, &TargetTransform);
  /*3rd step
  TargetForward = TargetTransform x TargetForward
  TargetUp = TargetTransform x TargetUp*/
  Matrix4_MultiplyVector(&TargetForward, &TargetTransform, &TargetForward);
  Matrix4_MultiplyVector(&TargetUp, &TargetTransform, &TargetUp);
  /*4th step
  theCam's up = TargetUp
  theCam's look at = theCam's TargetObject position - theCam's position*/
  theCam->Up = TargetUp;
  Vector4_Subtract(&theCam->LookAt, &theCam->TargetObject->Position, &theCam->Position);
  /*5th step
  Normalize TargetForward
  Normalize TargetUp*/
  Vector4_Normalize(&TargetForward, &TargetForward);
  Vector4_Normalize(&TargetUp, &TargetUp);
  /*6th step
  TargetForward = TargetForward x theCam's Horizontal follow distance
  TargetUp = TargetUp x theCam's vertical follow distance*/
  Vector4_Multiply(&TargetForward, &TargetForward, theCam->HorizontalFollowDistance);
  Vector4_Multiply(&TargetUp, &TargetUp, theCam->VerticalFollowDistance);
  /*7th step
  Negate Target Forward
  Offset = TargetForward + TargetUp
  theCam's position = Offset + theCam's target object position*/
  Vector4_Negate(&TargetForward, &TargetForward);
  Vector4_Add(&Offset, &TargetForward, &TargetUp);
  Vector4_Add(&theCam->Position, &Offset, &theCam->TargetObject->Position);
}

void Camera_3rdPersonSpring(Camera * theCam)
{
  Vector4 TargetForward, TargetUp, Offset, idealPosition, displacement, springaccel, SpringVel, DampVel;
  Matrix4 TargetTransform;

  /*1st step
  TargetForward = 0 0 -1 0
  TargetUp = 0 1 0 0 */
  TargetForward = Vector4_Create(-sin(theCam->RotationalOffset), 0, -cos(theCam->RotationalOffset), 0);
  TargetUp = Vector4_Create(0, 1, 0, 0);
  /*2nd step
  GameObject_CalcTransform(theCam->TargetObject, &TargetTransfom);*/
  GameObject_CalcTransform(theCam->TargetObject, &TargetTransform);
  /*3rd step
  TargetForward = TargetTransform x TargetForward
  TargetUp = TargetTransform x TargetUp*/
  Matrix4_MultiplyVector(&TargetForward, &TargetTransform, &TargetForward);
  Matrix4_MultiplyVector(&TargetUp, &TargetTransform, &TargetUp);
  /*4th step - calculate look at and up
  theCam's up = TargetUp
  theCam's look at = theCam's TargetObject position - theCam's position*/
  theCam->Up = TargetUp;
  Vector4_Subtract(&theCam->LookAt, &theCam->TargetObject->Position, &theCam->Position);
  /*5th step - calculate "ideal position:
  Normalize TargetForward
  Normalize TargetUp*/
  Vector4_Normalize(&TargetForward, &TargetForward);
  Vector4_Normalize(&TargetUp, &TargetUp);
  /*6th step
  TargetForward = TargetForward x theCam's Horizontal follow distance
  TargetUp = TargetUp x theCam's vertical follow distance*/
  Vector4_Multiply(&TargetForward, &TargetForward, theCam->HorizontalFollowDistance);
  Vector4_Multiply(&TargetUp, &TargetUp, theCam->VerticalFollowDistance);
  /*7th step
  Negate Target Forward
  Offset = TargetForward + TargetUp
  idealPosition = Offset + theCam's target object position*/
  Vector4_Negate(&TargetForward, &TargetForward);
  Vector4_Add(&Offset, &TargetForward, &TargetUp);
  Vector4_Add(&idealPosition, &Offset, &theCam->TargetObject->Position);
  /*8th step - calculate the difference
  displacement = theCam's position - idealPosition*/
  Vector4_Subtract(&displacement, &theCam->Position, &idealPosition);
  /*9th step - calculate the spring forces
  SpringVel = displacement x (-theCam's spring strength)
  DampVel = theCam's Velocity x theCam's spring damping*/
  Vector4_Multiply(&SpringVel, &displacement, -theCam->SpringStrength);
  Vector4_Multiply(&DampVel, &theCam->Velocity, theCam->SpringDampining);
  /*SpringVel = SpringVel x 1 / 60 <--- this is a scalar multiplication, remember to use FLOATS
  DampVel = DampVel x 1 / 60 <--- this is a scalar multiplication, remember to use FLOATS*/
  Vector4_Multiply(&SpringVel, &SpringVel, 1.0f / 60.0f);
  Vector4_Multiply(&DampVel, &DampVel, 1.0f / 60.0f);
  /*10th step - euler integration
  springaccel = SpringVel - DampVel
  theCam's velocity = theCam's velocity + springaccel
  theCam's position = theCam's position + theCam's velocity*/
  Vector4_Subtract(&springaccel, &SpringVel, &DampVel);
  Vector4_Add(&theCam->Velocity, &theCam->Velocity, &springaccel);
  Vector4_Add(&theCam->Position, &theCam->Position, &theCam->Velocity);
}


void SphereToCartesian(Vector4 * output, float r, float theta, float phi)
{
  /*
  Convert sphere coordinates to cartesian coordinates
  */
  output->x = r * cos(theta) * cos(phi);
  output->y = r * sin(theta) * cos(phi);
  output->z = r * sin(phi);
  output->w = 1;
}

void CylinderToCartesian(Vector4 * Output, float r, float theta, float height)
{
  /*
  Insert into Ouput the cylindrical coordinates using r, phi and height
  */
  Output->x = r * cos(theta);
  Output->y = r * sin(theta);
  Output->z = height;
  Output->w = 1;
}
