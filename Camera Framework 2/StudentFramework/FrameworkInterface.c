#include "FrameworkInterface.h"
#include "Utilities.h"
#include "InputManager.h"
#include "pfmath.h"
#include "Cube.h"
#include "Camera.h"
#include "GameObject.h"
#include "Tank.h"
#include "MatrixStack.h"

extern int winID;
const int numBullets = 3000;
const int numTanks = 3;
const int numParticles = 9000;
int i = 0;
int j = 0;
BOOLEAN perspective = TRUE;
BOOLEAN Rotate = TRUE;
BOOLEAN UseColor = FALSE;
BOOLEAN isAlive = TRUE;

Cube TheCube, ImpactCube, SmokeCube, ExplosionCube, FragmentCube;
Camera TheCamera;
Tank theTank, enemyTank[3]; /*supposed to be numTanks*/
MatrixStack tankStack;
Vector4 sunVector;
Bullet bulletList[3000]; /*supposed to be numBullets*/
Particle particleList[9000]; /*supposed to be numParticles*/

float FOVScale = 1;
const int arenaSize = 2500; /*UPDATE IN TANK.C TOO*/
float arenaHeight = 10;
float rotationX = 90 * 3.14 / 180, rotationY = 90 * 3.14 / 180;
float lookX, lookY, lookZ;
Vector4 cross;
Vector4 lookVector;
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case VK_ESCAPE:
		FrameBuffer_Destroy(&GlobalFrameBuffer);
		glutDestroyWindow(winID);
		exit(0);
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
	/*switch (button)
	{
	}*/
}

void mouseMove(int x, int y)
{
}

void Init( void)
{
  Cube_Init(&TheCube, UseColor);
	Cube_Init(&ImpactCube, UseColor);
	Cube_Init(&SmokeCube, UseColor);
	Cube_Init(&ExplosionCube, UseColor);
	Cube_Init(&FragmentCube, UseColor);

	for(i = 0; i < 12; i++)
	{
		ImpactCube.TriangleList[i].rgb.Red = 127;
		ImpactCube.TriangleList[i].rgb.Green = 127;
		ImpactCube.TriangleList[i].rgb.Blue = 127;

		SmokeCube.TriangleList[i].rgb.Red = 255;
		SmokeCube.TriangleList[i].rgb.Green = 255;
		SmokeCube.TriangleList[i].rgb.Blue = 255;

		ExplosionCube.TriangleList[i].rgb.Red = 255;
		ExplosionCube.TriangleList[i].rgb.Green = 131;
		ExplosionCube.TriangleList[i].rgb.Blue = 0;

		FragmentCube.TriangleList[i].rgb.Red = 10;
		FragmentCube.TriangleList[i].rgb.Green = 10;
		FragmentCube.TriangleList[i].rgb.Blue = 10;
	}

  Tank_Init(&theTank, &TheCube);
  for(i = 0; i < numTanks; i++)
  {
    Tank_Init(&enemyTank[i], &TheCube);
    enemyTank[i].Base.Position.x = rand() % arenaSize - arenaSize / 2;
    enemyTank[i].Base.Position.z = rand() % arenaSize - arenaSize / 2; 

    enemyTank[i].maxhp = 30;
    enemyTank[i].hp = 30;
  }
  

  Camera_Init(&TheCamera, &theTank.Base);
  TheCamera.mode = THIRD_PERSON_SPRING;
  Vector4_Set(&sunVector, 5, -10, 3, 0);

  MatrixStack_Init(&tankStack, 20);

  for(i = 0; i < numBullets; i++)
  {
    Bullet_Init(&bulletList[i], &TheCube);
  }

	for(i = 0; i < numParticles; i++)
  {
		Particle_Init(&particleList[i], &TheCube);
	}
}

void render()
{
  //Your code goes here

  //variables used
  Matrix4 Projection;
  Matrix4 ViewPort;
  Matrix4 WorldToCamera;
  //Vector4 CameraToObject;
  //check input
      if(IsKeyPressed( '1'))
      TheCamera.mode = FREE_CAMERA;
      
    if(IsKeyPressed( '2'))
      TheCamera.mode = FIRST_PERSON_SPHERE;
      
    if(IsKeyPressed( '3'))
      TheCamera.mode = FIRST_PERSON_CYLINDRICAL;
      
    if(IsKeyPressed( '4'))
      TheCamera.mode = THIRD_PERSON_SPHERE;
      
    if(IsKeyPressed( '5'))
      TheCamera.mode = THIRD_PERSON_CYLINDRICAL;
      
    if(IsKeyPressed( '6'))
      TheCamera.mode = THIRD_PERSON_RIGID;
      
    if(IsKeyPressed( '7'))
      TheCamera.mode = THIRD_PERSON_SPRING;
      

    if(IsKeyPressed( 'o'))
			theTank.hp = 0; 
      
    /*
    if(IsKeyPressed( 'k'))
      UseColor = TRUE;
      
    if(IsKeyPressed( 'l'))
      UseColor = FALSE;
      */
    if(IsKeyPressed( 'w') && isAlive)
      theTank.velocity += 1.5;
      
    if(IsKeyPressed( 's') && isAlive)
      theTank.velocity -= 1.5;
      
    if(IsKeyPressed( 'a') && isAlive)
      theTank.rotationalVelocity -= 0.1;
      
    if(IsKeyPressed( 'd') && isAlive)
      theTank.rotationalVelocity += 0.1;
      
    if(TheCamera.mode == FREE_CAMERA)
    {
      if(IsKeyPressed( 'q') && isAlive)
        theTank.TurretRotation += 0.015;
      
      if(IsKeyPressed( 'e') && isAlive)
         theTank.TurretRotation -= 0.015;

      if(IsKeyPressed( 'r') && theTank.GunRotation <= PI / 4 && isAlive)
         theTank.GunRotation += 0.01;

      if(IsKeyPressed( 'f') && theTank.GunRotation >= -PI / 6 && isAlive)
         theTank.GunRotation -= 0.01;
    
      if(IsKeyPressed( 'y'))
        Vector4_Add(&TheCamera.Position, &TheCamera.Position, &TheCamera.LookAt);

      if(IsKeyPressed( 'h'))
        Vector4_Subtract(&TheCamera.Position, &TheCamera.Position, &TheCamera.LookAt);
      
      if(IsKeyPressed( 'g'))
      {
        Vector4_Cross(&cross, &TheCamera.LookAt, &TheCamera.Up);
        Vector4_Normalize(&cross, &cross);
        Vector4_Subtract(&TheCamera.Position, &TheCamera.Position, &cross);
      }
      if(IsKeyPressed( 'j'))
      {
        Vector4_Cross(&cross, &TheCamera.LookAt, &TheCamera.Up);
        Vector4_Normalize(&cross, &cross);
        Vector4_Add(&TheCamera.Position, &TheCamera.Position, &cross);
      }
      
      if(IsKeyPressed( 'i') && rotationX >= 0 + 0.1)
        rotationX -= 0.02f;
      

      if(IsKeyPressed( 'k') && rotationX <= 3.14 - 0.1)
        rotationX += 0.02f;

      if(IsKeyPressed( 't'))
        rotationY += 0.02f;
      

      if(IsKeyPressed( 'u'))
        rotationY -= 0.02f;
    }
    if(TheCamera.mode == THIRD_PERSON_SPRING)
    {
      if(IsKeyPressed( 'g') && isAlive)
        theTank.TurretRotation += 0.015;
      
      if(IsKeyPressed( 'j') && isAlive)
         theTank.TurretRotation -= 0.015;

      if(IsKeyPressed( 'y') && theTank.GunRotation <= PI / 4 && isAlive)
         theTank.GunRotation += 0.01;

      if(IsKeyPressed( 'h') && theTank.GunRotation >= -PI / 6 && isAlive)
         theTank.GunRotation -= 0.01;
    }
    if(IsKeyPressed( 'z') && isAlive)
      Tank_Shoot(&theTank, bulletList, numBullets, 350, 0);
      
    if(IsKeyPressed( 'x'))
    {
      TheCamera.RotationalOffset = theTank.TurretRotation;
      TheCamera.SpringStrength = 4;
      TheCamera.SpringDampining = 100;
    }
    else
    {
      TheCamera.RotationalOffset = 0;
      TheCamera.SpringStrength = 0.5;
      TheCamera.SpringDampining = 20;
    }
    if(IsKeyPressed(VK_ESCAPE))
    {
		  FrameBuffer_Destroy(&GlobalFrameBuffer);
		  glutDestroyWindow(winID);
		  exit(0);
    }

    if(IsKeyPressed( 'c'))
    {
      TheCamera.theta += PI/180.0f;
      TheCamera.height += 1;
    }
      

    if(IsKeyPressed( 'v'))
    {
      TheCamera.theta -= PI/180.0f;
      TheCamera.height -= 1;
    }
      
    if(IsKeyPressed( 'b'))
      TheCamera.phi += PI/180.0f;
      
    if(IsKeyPressed( 'n'))
      TheCamera.phi -= PI/180.0f;

    lookX = cos(rotationY);
    lookZ = -sin(rotationY);
    lookX *= sin(rotationX);
    lookZ *= sin(rotationX);
    lookY = cos(rotationX);
    lookVector = Vector4_Create(lookX, lookY, lookZ, 0);
    Vector4_Normalize(&lookVector, &lookVector);
    if(TheCamera.mode == FREE_CAMERA)
    {
      Vector4_Set(&TheCamera.LookAt,lookVector.x, 
                                  lookVector.y,
                                  lookVector.z,
                                 0);
    }
    Vector4_Length(&FOVScale, &TheCamera.Velocity);
    FOVScale = FOVScale * 0.3f + 1;
  Camera_Update(&TheCamera);
  if(perspective)
    Matrix4_Projection(&Projection, 24, 32 * FOVScale, 24 * FOVScale);
  else
    Matrix4_OrthoProjection(&Projection, 24, 32, 24);
  


  Matrix4_WorldToCamera(&WorldToCamera, &TheCamera);
  Matrix4_ProjToViewport(&ViewPort, WIDTH, HEIGHT);

  Tank_Move(&theTank);
	Tank_Smoke(&theTank, particleList, numParticles, &SmokeCube);
  Tank_Draw(&theTank, &tankStack, WorldToCamera, Projection, perspective, ViewPort, &sunVector);
  for(i = 0; i < numTanks; i++)
  {
		Tank_Smoke(&enemyTank[i], particleList, numParticles, &SmokeCube);
    Tank_Move_AI(&enemyTank[i], &theTank, bulletList, numBullets);
    Tank_Draw(&enemyTank[i], &tankStack, WorldToCamera, Projection, perspective, ViewPort, &sunVector);
    Tank_CheckEnemyDeath(&enemyTank[i], &theTank, &TheCube, particleList, numParticles, &ExplosionCube, &FragmentCube);
  }
  Tank_CheckPlayerDeath(&theTank, winID, particleList, numParticles, &ExplosionCube, &FragmentCube, &isAlive);
  for(i = 0; i < numBullets; i++)
  {
    Bullet_UpdateAndDraw(&bulletList[i], &WorldToCamera, &Projection, perspective, &ViewPort, &sunVector);
    Bullet_CheckCollisionWithTank(&bulletList[i], &theTank, particleList, numParticles, &ImpactCube);
    for(j = 0; j < numTanks; j++)
    {
      Bullet_CheckCollisionWithTank(&bulletList[i], &enemyTank[j], particleList, numParticles, &ImpactCube);
    }
  }
	for(i = 0; i < numParticles; i++)
	{
		Particle_UpdateAndDraw(&particleList[i], &WorldToCamera, &Projection, perspective, &ViewPort, &sunVector);
	}
}
