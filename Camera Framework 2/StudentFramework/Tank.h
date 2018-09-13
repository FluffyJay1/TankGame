#ifndef TANK_H
#define TANK_H
#include "Vector4.h"
#include "MatrixStack.h"
#include "Matrix4.h"
#include "GameObject.h"
#include "Cube.h"
typedef struct Tank
{
  GameObject Base;
  
  float FrontWheelXRotation;
  float FrontWheelYRotation;

  float BackWheelXRotation;
  float BackWheelYRotation;

  float TurretRotation;
  float GunRotation;

  float velocity;
  float rotationalVelocity;

  float maxFireCooldown;
  float fireCooldown;
  float maxRecoilLength;
  float recoilLength;

	float smokeMaxTimer;
	float smokeTimer;

  float maxhp;
  float hp;
}Tank;

typedef struct Bullet
{
  GameObject Base;

  float xVel;
  float yVel;
  float zVel;
  BOOLEAN isAvailable;
}Bullet;

enum PARTICLETYPES
{
  SMOKE,
	EXPLOSION,
	IMPACT,
	FRAGMENT
};

typedef struct Particle
{
  GameObject Base;

  float xVel;
  float yVel;
  float zVel;

  float maxLifetime;
  float lifetime;
	int mode;

  BOOLEAN isAvailable;
}Particle;

void Tank_Init(Tank * theTank, Cube * mesh);
void Tank_Draw(Tank * theTank, MatrixStack * stack, Matrix4 WorldToCamera, Matrix4 Projection, BOOLEAN PerspectiveDivide, Matrix4 ViewPort, Vector4* sunVector);
Matrix4 Tank_CalcTransform(Tank* theTank);
void Tank_Move(Tank* theTank);
void Tank_Move_AI(Tank* theTank, Tank* targetTank, Bullet* bulletList, int numBullets);
void Tank_MoveForward(Tank * theTank, float speed);
void Tank_TurnLeft(Tank * theTank, float speed);
void Tank_TurnRight(Tank * theTank, float speed);
void Tank_Shoot(Tank* theTank, Bullet* bulletList, int numBullets, float power, float spread);
void Tank_CheckPlayerDeath(Tank* playerTank, int winID, Particle* particleList, int numParticles, Cube* explosionCube, Cube* fragmentCube, BOOLEAN* isAlive);
void Tank_CheckEnemyDeath(Tank* enemyTank, Tank* playerTank, Cube* mesh, Particle* particleList, int numParticles, Cube* explosionCube, Cube* fragmentCube);
void Tank_Smoke(Tank* theTank, Particle* particleList, int numParticles, Cube* smokeCube);
void Bullet_Init(Bullet* theBullet, Cube* mesh);
void Bullet_UpdateAndDraw(Bullet* theBullet, struct Matrix4 * WorldToCamera, struct Matrix4 * Projection, BOOLEAN PerspectiveDivide, struct Matrix4 * ViewPort, Vector4* sunVector);
void Bullet_CheckCollisionWithTank(Bullet* theBullet, Tank* theTank, Particle* particleList, int numParticles, Cube* impactCube);
void Bullet_HitTank(Bullet* theBullet, Tank* theTank, Particle* particleList, int numParticles, Cube* impactCube);
void Particle_Init(Particle* theParticle, Cube* mesh);
void Particle_Create(Particle* particleList, int numParticles, Cube* mesh, float x, float y, float z, float velX, float velY, float velZ, float scaleX, float scaleY, float scaleZ, int mode, float maxLifetime);
void Particle_UpdateAndDraw(Particle* theParticle, struct Matrix4 * WorldToCamera, struct Matrix4 * Projection, BOOLEAN PerspectiveDivide, struct Matrix4 * ViewPort, Vector4* sunVector);
#endif