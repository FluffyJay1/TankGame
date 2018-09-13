#include "Tank.h"
#include "Matrix4.h"
#include "GameObject.h"
#include "Cube.h"
#include "FrameworkInterface.h"

const int ArenaSize = 2500; /*UPDATE IN FRAMEWORKINTERFACE.C TOO*/
float deathTimer = 2.5;
BOOLEAN deathExploded = FALSE;
Matrix4 worldTankTransform, tankWheelTransform;
void Tank_Init(Tank * theTank, struct Cube * mesh)
{
  GameObject base;
  GameObject_Init(&base, mesh);
  Vector4_Set(&base.Position, 0, 26.5, 50, 0);
  Vector4_Set(&base.Rotation, 0, 0, 0, 0);
  Vector4_Set(&base.Scale, 1, 1, 1, 0);
  theTank->Base = base;
  theTank->GunRotation = 0;
  theTank->TurretRotation = 0;
  theTank->FrontWheelXRotation = 0;
  theTank->FrontWheelYRotation = 0;
  theTank->BackWheelXRotation = 0;
  theTank->BackWheelYRotation = 0;
  theTank->velocity = 0;
  theTank->rotationalVelocity = 0;
  theTank->fireCooldown = 0;
  theTank->maxFireCooldown = 2.4;
  theTank->maxhp = 150;
  theTank->hp = theTank->maxhp;
  theTank->maxRecoilLength = 10;
  theTank->recoilLength = theTank->maxRecoilLength;
	theTank->smokeMaxTimer = 1;
	theTank->smokeTimer = 0;
}

void Tank_Draw(Tank * theTank, MatrixStack * stack, Matrix4 WorldToCamera, Matrix4 Projection, BOOLEAN PerspectiveDivide, Matrix4 ViewPort, Vector4* sunVector)
{
  Matrix4 worldTankTransform, Scale, tankWheelRotationXf, tankWheel2RotationXf, tankWheelRotationYf, tankWheelRotationXb, tankWheel2RotationXb, tankWheelRotationYb, tankWheelTranslate, tankWheelTransformf, tankWheel2Transformf, tankWheelTransformb, tankWheel2Transformb, turretTranslate, turretRotationY, gunTranslate, gunRotationX, Accum;
  int i = 0;
  float previousR[12];
  float previousG[12];
  float previousB[12];
  worldTankTransform = Tank_CalcTransform(theTank);
  MatrixStack_Push(stack, &worldTankTransform);
  Matrix4_Scale(&Scale, 30, 25, 80);
  MatrixStack_Push(stack, &Scale);
  for(i = 0; i < 12; i++)
  {
    previousR[i] = theTank->Base.Mesh->TriangleList[i].rgb.Red;
    previousG[i] = theTank->Base.Mesh->TriangleList[i].rgb.Green;
    previousB[i] = theTank->Base.Mesh->TriangleList[i].rgb.Blue;
    theTank->Base.Mesh->TriangleList[i].rgb.Red *= theTank->hp / theTank->maxhp;
    theTank->Base.Mesh->TriangleList[i].rgb.Green *= theTank->hp / theTank->maxhp;
    theTank->Base.Mesh->TriangleList[i].rgb.Blue *= theTank->hp / theTank->maxhp;
  }

  Accum = MatrixStack_Concat(stack);
  Cube_MatrixDrawWithCamera(theTank->Base.Mesh, &Accum, &WorldToCamera, &Projection, PerspectiveDivide, &ViewPort, sunVector); /*BASE*/
  MatrixStack_Pop(stack);
  
  Matrix4_XaxisRotation(&tankWheelRotationXf, theTank->FrontWheelXRotation);
  Matrix4_XaxisRotation(&tankWheel2RotationXf, theTank->FrontWheelXRotation + PI / 4);
  Matrix4_YaxisRotation(&tankWheelRotationYf, theTank->FrontWheelYRotation);
  Matrix4_XaxisRotation(&tankWheelRotationXb, theTank->BackWheelXRotation);
  Matrix4_XaxisRotation(&tankWheel2RotationXb, theTank->BackWheelXRotation + PI / 4);
  Matrix4_YaxisRotation(&tankWheelRotationYb, theTank->BackWheelYRotation);

  Matrix4_Scale(&Scale, 5, 20, 20);
  Matrix4_Multiply(&tankWheelTransformf, &tankWheelRotationXf, &Scale);
  Matrix4_Multiply(&tankWheelTransformb, &tankWheelRotationXb, &Scale);
  Matrix4_Multiply(&tankWheel2Transformf, &tankWheel2RotationXf, &Scale);
  Matrix4_Multiply(&tankWheel2Transformb, &tankWheel2RotationXb, &Scale);

  Matrix4_Translation(&tankWheelTranslate, 17.5, -12.5, -25);
  MatrixStack_Push(stack, &tankWheelTranslate);
  MatrixStack_Push(stack, &tankWheelRotationYf);
  MatrixStack_Push(stack, &tankWheelTransformf);
  Accum = MatrixStack_Concat(stack);
  Cube_MatrixDrawWithCamera(theTank->Base.Mesh, &Accum, &WorldToCamera, &Projection, PerspectiveDivide, &ViewPort, sunVector); /*FRONT WHEEL*/
  MatrixStack_Pop(stack);
  MatrixStack_Push(stack, &tankWheel2Transformf);
  Accum = MatrixStack_Concat(stack);
  Cube_MatrixDrawWithCamera(theTank->Base.Mesh, &Accum, &WorldToCamera, &Projection, PerspectiveDivide, &ViewPort, sunVector);
  MatrixStack_Pop(stack);
  MatrixStack_Pop(stack);
  MatrixStack_Pop(stack);

  Matrix4_Translation(&tankWheelTranslate, -17.5, -12.5, -25);
  MatrixStack_Push(stack, &tankWheelTranslate);
  MatrixStack_Push(stack, &tankWheelRotationYf);
  MatrixStack_Push(stack, &tankWheelTransformf);
  Accum = MatrixStack_Concat(stack);
  Cube_MatrixDrawWithCamera(theTank->Base.Mesh, &Accum, &WorldToCamera, &Projection, PerspectiveDivide, &ViewPort, sunVector); /*FRONT WHEEL*/
  MatrixStack_Pop(stack);
  MatrixStack_Push(stack, &tankWheel2Transformf);
  Accum = MatrixStack_Concat(stack);
  Cube_MatrixDrawWithCamera(theTank->Base.Mesh, &Accum, &WorldToCamera, &Projection, PerspectiveDivide, &ViewPort, sunVector);
  MatrixStack_Pop(stack);
  MatrixStack_Pop(stack);
  MatrixStack_Pop(stack);

  Matrix4_Translation(&tankWheelTranslate, 17.5, -12.5, 25);
  MatrixStack_Push(stack, &tankWheelTranslate);
  MatrixStack_Push(stack, &tankWheelRotationYb);
  MatrixStack_Push(stack, &tankWheelTransformb);
  Accum = MatrixStack_Concat(stack);
  Cube_MatrixDrawWithCamera(theTank->Base.Mesh, &Accum, &WorldToCamera, &Projection, PerspectiveDivide, &ViewPort, sunVector); /*BACK WHEEL*/
  MatrixStack_Pop(stack);
  MatrixStack_Push(stack, &tankWheel2Transformb);
  Accum = MatrixStack_Concat(stack);
  Cube_MatrixDrawWithCamera(theTank->Base.Mesh, &Accum, &WorldToCamera, &Projection, PerspectiveDivide, &ViewPort, sunVector);
  MatrixStack_Pop(stack);
  MatrixStack_Pop(stack);
  MatrixStack_Pop(stack);

  Matrix4_Translation(&tankWheelTranslate, -17.5, -12.5, 25);
  MatrixStack_Push(stack, &tankWheelTranslate);
  MatrixStack_Push(stack, &tankWheelRotationYb);
  MatrixStack_Push(stack, &tankWheelTransformb);
  Accum = MatrixStack_Concat(stack);
  Cube_MatrixDrawWithCamera(theTank->Base.Mesh, &Accum, &WorldToCamera, &Projection, PerspectiveDivide, &ViewPort, sunVector); /*BACK WHEEL*/
  MatrixStack_Pop(stack);
  MatrixStack_Push(stack, &tankWheel2Transformb);
  Accum = MatrixStack_Concat(stack);
  Cube_MatrixDrawWithCamera(theTank->Base.Mesh, &Accum, &WorldToCamera, &Projection, PerspectiveDivide, &ViewPort, sunVector);
  MatrixStack_Pop(stack);
  MatrixStack_Pop(stack);
  MatrixStack_Pop(stack);

  Matrix4_Translation(&turretTranslate, 0, 20, 0);
  Matrix4_YaxisRotation(&turretRotationY, theTank->TurretRotation);
  Matrix4_Scale(&Scale, 25, 15, 25);
  MatrixStack_Push(stack, &turretTranslate);
  MatrixStack_Push(stack, &turretRotationY);
  MatrixStack_Push(stack, &Scale);
  Accum = MatrixStack_Concat(stack);
  Cube_MatrixDrawWithCamera(theTank->Base.Mesh, &Accum, &WorldToCamera, &Projection, PerspectiveDivide, &ViewPort, sunVector);
  MatrixStack_Pop(stack);

  Matrix4_XaxisRotation(&gunRotationX, theTank->GunRotation);
  Matrix4_Translation(&gunTranslate, 0, 0, -20 + theTank->recoilLength);
  Matrix4_Scale(&Scale, 5, 5, 40);
  MatrixStack_Push(stack, &gunRotationX);
  MatrixStack_Push(stack, &gunTranslate);
  MatrixStack_Push(stack, &Scale);
  Accum = MatrixStack_Concat(stack);
  Cube_MatrixDrawWithCamera(theTank->Base.Mesh, &Accum, &WorldToCamera, &Projection, PerspectiveDivide, &ViewPort, sunVector);

  MatrixStack_Pop(stack);
  MatrixStack_Pop(stack);
  MatrixStack_Pop(stack);
  MatrixStack_Pop(stack);
  MatrixStack_Pop(stack);
  MatrixStack_Pop(stack);

  for(i = 0; i < 12; i++)
  {
  theTank->Base.Mesh->TriangleList[i].rgb.Red = previousR[i];
  theTank->Base.Mesh->TriangleList[i].rgb.Green = previousG[i];
  theTank->Base.Mesh->TriangleList[i].rgb.Blue = previousB[i];
  }
}
Matrix4 Tank_CalcTransform(Tank* theTank)
{
  Matrix4 Translate;
  Matrix4 RotateX;
  Matrix4 RotateY;
  Matrix4 RotateZ;
  Matrix4 Scale;
  Matrix4 Output;

   //set the values for every mtx
  Matrix4_Translation(&Translate, theTank->Base.Position.x, theTank->Base.Position.y, theTank->Base.Position.z);
  Matrix4_XaxisRotation(&RotateX, theTank->Base.Rotation.x);
  Matrix4_YaxisRotation(&RotateY, theTank->Base.Rotation.y);
  Matrix4_ZaxisRotation(&RotateZ, theTank->Base.Rotation.z);
  Matrix4_Scale(&Scale, theTank->Base.Scale.x, theTank->Base.Scale.y, theTank->Base.Scale.z);
  Matrix4_Identity(&Output);

  //concationate the matrices
  Matrix4_Multiply(&Output, &Scale,     &Output);
  Matrix4_Multiply(&Output, &RotateX,   &Output);
  Matrix4_Multiply(&Output, &RotateY,   &Output);
  Matrix4_Multiply(&Output, &RotateZ,   &Output);
  Matrix4_Multiply(&Output, &Translate, &Output);
  return Output;
}
void Tank_Move(Tank* theTank)
{
  Tank_MoveForward(theTank, theTank->velocity);
  theTank->velocity *= 0.98;
  theTank->rotationalVelocity *= 0.96;
  if(theTank->fireCooldown > 0)
  {
    theTank->fireCooldown -= 0.0167; /*1 / 60*/
  }
  if(theTank->recoilLength > 0)
  {
	  theTank->recoilLength = theTank->maxRecoilLength * theTank->fireCooldown / theTank->maxFireCooldown;
  }
  if(theTank->rotationalVelocity > 0)
  {
    Tank_TurnRight(theTank, theTank->rotationalVelocity);
  }
  else
  {
    Tank_TurnLeft(theTank, -theTank->rotationalVelocity);
  }
}
void Tank_Move_AI(Tank* theTank, Tank* targetTank, Bullet* bulletList, int numBullets)
{
  Vector4 vectorToTarget, tankForwardVector, turretForwardVector, tankCross, turretCross;
  float length, desiredAngle;
  Vector4_Subtract(&vectorToTarget, &targetTank->Base.Position, &theTank->Base.Position);
  Vector4_Set(&tankForwardVector, -sin(theTank->Base.Rotation.y), 0, -cos(theTank->Base.Rotation.y), 0);
  Vector4_Set(&turretForwardVector, -sin(theTank->TurretRotation + theTank->Base.Rotation.y), 0, -cos(theTank->TurretRotation + theTank->Base.Rotation.y), 0);
  Vector4_Cross(&tankCross, &tankForwardVector, &vectorToTarget);
  Vector4_Cross(&turretCross, &turretForwardVector, &vectorToTarget);
  if(tankCross.y > 0)
  {
    theTank->rotationalVelocity -= 0.03;
  }
  else
  {
    theTank->rotationalVelocity += 0.03;
  }
  if(turretCross.y < 0)
  {
    theTank->TurretRotation -= 0.01;
  }
  else
  {
    theTank->TurretRotation += 0.01;
  }
  Vector4_Length(&length, &vectorToTarget);
  if(length >= 350)
  {
    theTank->velocity += 1.6;
  }
  desiredAngle = sqrt(length / 500) - 0.5;
  if(theTank->GunRotation < PI / 4 && theTank->GunRotation < desiredAngle)
  {
    theTank->GunRotation += 0.02;
  }
  else if(theTank->GunRotation > -PI / 6 && theTank->GunRotation > desiredAngle)
  {
    theTank->GunRotation -= 0.02;
  }
  if(turretCross.y < 0.2 && turretCross.y > -0.2)
  {
    Tank_Shoot(theTank, bulletList, numBullets, 320, 0.08);
  }
  Tank_Move(theTank);
}

void Tank_MoveForward(Tank * theTank, float speed)
{
  float frameSpeed = speed * 1 / 60;
  Vector4 moveVector = Vector4_Create(frameSpeed * -sin(theTank->Base.Rotation.y), 0, frameSpeed * -cos(theTank->Base.Rotation.y), 0);
  Vector4_Add(&theTank->Base.Position, &theTank->Base.Position, &moveVector);
  theTank->FrontWheelXRotation -= speed/(12 * 60);
  theTank->FrontWheelYRotation += (0 - theTank->FrontWheelYRotation) * abs(speed) / 600;
  theTank->BackWheelXRotation -= speed/(12 * 60);
  theTank->BackWheelYRotation += (0 - theTank->BackWheelYRotation) * abs(speed) / 600;
}
void Tank_TurnLeft(Tank * theTank, float speed)
{
  float frameSpeed = speed * 1 / 60;
  theTank->Base.Rotation.y += frameSpeed;
  if(theTank->velocity <= 30 && theTank->velocity >= -15)
  {
    theTank->FrontWheelXRotation -= ((30 - theTank->velocity) / 30) * speed/ 40;
    theTank->BackWheelXRotation -= ((30 - theTank->velocity) / 30) * speed/ 40;
  }
  if(theTank->velocity >= -30 && theTank->velocity < -15)
  {
    theTank->FrontWheelXRotation -= ((-30 - theTank->velocity) / 30) * speed/ 40;
    theTank->BackWheelXRotation -= ((-30 - theTank->velocity) / 30) * speed/ 40;
  }
  if(theTank->velocity >= -15)
  {
    if(theTank->FrontWheelYRotation < PI / 2)
    {
      theTank->FrontWheelYRotation += (PI / 2 - theTank->FrontWheelYRotation) * speed / 40;
    }
    if(theTank->BackWheelYRotation > -PI / 2)
    {
      theTank->BackWheelYRotation += (- PI / 2 - theTank->BackWheelYRotation) * speed / 40;
    }
  }
  else
  {
    if(theTank->FrontWheelYRotation > -PI / 2)
    {
      theTank->FrontWheelYRotation += (- PI / 2 - theTank->FrontWheelYRotation) * speed / 40;
    }
    if(theTank->BackWheelYRotation < PI / 2)
    {
      theTank->BackWheelYRotation += (PI / 2 - theTank->BackWheelYRotation) * speed / 40;
    }
  }
}
void Tank_TurnRight(Tank * theTank, float speed)
{
  float frameSpeed = speed * 1 / 60;
  theTank->Base.Rotation.y -= frameSpeed;
  if(theTank->velocity <= 30 && theTank->velocity >= -15)
  {
    theTank->FrontWheelXRotation -= ((30 - theTank->velocity) / 30) * speed/ 40;
    theTank->BackWheelXRotation -= ((30 - theTank->velocity) / 30) * speed/ 40;
  }
  if(theTank->velocity >= -30 && theTank->velocity < -15)
  {
    theTank->FrontWheelXRotation -= ((-30 - theTank->velocity) / 30) * speed/ 40;
    theTank->BackWheelXRotation -= ((-30 - theTank->velocity) / 30) * speed/ 40;
  }
  if(theTank->velocity >= -15)
  {
    if(theTank->FrontWheelYRotation > -PI / 2)
    {
      theTank->FrontWheelYRotation += (- PI / 2 - theTank->FrontWheelYRotation) * speed / 40;
    }
    if(theTank->BackWheelYRotation < PI / 2)
    {
      theTank->BackWheelYRotation += (PI / 2 - theTank->BackWheelYRotation) * speed / 40;
    }
  }
  else
  {
    if(theTank->FrontWheelYRotation < PI / 2)
    {
      theTank->FrontWheelYRotation += (PI / 2 - theTank->FrontWheelYRotation) * speed / 40;
    }
    if(theTank->BackWheelYRotation > -PI / 2)
    {
      theTank->BackWheelYRotation += (- PI / 2 - theTank->BackWheelYRotation) * speed / 40;
    }
  }
}

void Tank_Shoot(Tank* theTank, Bullet* bulletList, int numBullets, float power, float spread)
{
  float randomness = spread * ((rand() % 100) - 50) / 50;
  if(theTank->fireCooldown <= 0)
  {
    int bulletIdToUse = 0, i;
    for(i = 0; i < numBullets; i++)
    {
      if(bulletList[i].isAvailable == TRUE)
      {
        bulletIdToUse = i;
        break;
      }
    }
    bulletList[i].Base.Position = theTank->Base.Position;
    bulletList[i].Base.Position.y += 20;
    bulletList[i].xVel = -sin(theTank->TurretRotation + theTank->Base.Rotation.y) * cos(theTank->GunRotation);
    bulletList[i].zVel = -cos(theTank->TurretRotation + theTank->Base.Rotation.y) * cos(theTank->GunRotation);
    bulletList[i].yVel = sin(theTank->GunRotation);
    bulletList[i].Base.Position.x += bulletList[i].xVel * 40;
    bulletList[i].Base.Position.y += bulletList[i].yVel * 40;
    bulletList[i].Base.Position.z += bulletList[i].zVel * 40;
    bulletList[i].xVel = power * -sin(theTank->TurretRotation + theTank->Base.Rotation.y + randomness) * cos(theTank->GunRotation + randomness);
	randomness = spread * ((rand() % 100) - 50) / 50;
    bulletList[i].zVel = power * -cos(theTank->TurretRotation + theTank->Base.Rotation.y + randomness) * cos(theTank->GunRotation + randomness);
	randomness = spread * ((rand() % 100) - 50) / 50;
    bulletList[i].yVel = power * sin(theTank->GunRotation + randomness);
    bulletList[i].isAvailable = FALSE;
    theTank->fireCooldown = theTank->maxFireCooldown;
	theTank->recoilLength = theTank->maxRecoilLength;
  }
}

void Tank_CheckPlayerDeath(Tank* playerTank, int winID, Particle* particleList, int numParticles, Cube* explosionCube, Cube* fragmentCube, BOOLEAN* isAlive)
{
	int i = 0;
	float randomR, randomTheta, randomPhi, xVel, yVel, zVel;
  if(playerTank->hp <= 0)
  {
		playerTank->hp = 0;
		if(deathExploded == FALSE)
		{
			for(i = 0; i < 50; i++)
			{
				randomR = rand() % 500;
				randomTheta = (rand() % 180) / PI;
				randomPhi = (rand() % 180) / PI;
				xVel = randomR * cos(randomTheta) * cos(randomPhi);
				zVel = randomR * sin(randomTheta) * cos(randomPhi);
				yVel = randomR * sin(randomPhi);
				Particle_Create(particleList, numParticles, explosionCube, playerTank->Base.Position.x, playerTank->Base.Position.y, playerTank->Base.Position.z, xVel, yVel, zVel, 45, 45, 45, EXPLOSION, 1.6);
			}
			for(i = 0; i < 15; i++)
			{
				float randomXScale = rand() % 10 + 5;
				float randomYScale = rand() % 5 + 5;
				float randomZScale = rand() % 10 + 5;
				randomR = rand() % 300;
				randomTheta = (rand() % 180) / PI;
				randomPhi = (rand() % 180) / PI;
				xVel = randomR * cos(randomTheta) * cos(randomPhi);
				zVel = randomR * sin(randomTheta) * cos(randomPhi);
				yVel = randomR * sin(randomPhi);
				Particle_Create(particleList, numParticles, fragmentCube, playerTank->Base.Position.x, playerTank->Base.Position.y, playerTank->Base.Position.z, xVel, yVel, zVel, randomXScale, randomYScale, randomZScale, FRAGMENT, 8);
			}
			deathExploded = TRUE;
			*isAlive = FALSE;
		}
		deathTimer -= 0.0167;
		playerTank->GunRotation = -PI / 6;
		if(deathTimer <= 0)
		{
			FrameBuffer_Destroy(&GlobalFrameBuffer);
			glutDestroyWindow(winID);
			exit(0);
		}
  }
}

void Tank_CheckEnemyDeath(Tank* enemyTank, Tank* playerTank, Cube* mesh, Particle* particleList, int numParticles, Cube* explosionCube, Cube* fragmentCube)
{
  float maxhp;
	int i = 0;
	float randomR, randomTheta, randomPhi, xVel, yVel, zVel;
  if(enemyTank->hp <= 0)
  {
		for(i = 0; i < 30; i++)
		{
			randomR = rand() % 400;
			randomTheta = (rand() % 180) / PI;
			randomPhi = (rand() % 180) / PI;
			xVel = randomR * cos(randomTheta) * cos(randomPhi);
			zVel = randomR * sin(randomTheta) * cos(randomPhi);
			yVel = randomR * sin(randomPhi);
			Particle_Create(particleList, numParticles, explosionCube, enemyTank->Base.Position.x, enemyTank->Base.Position.y, enemyTank->Base.Position.z, xVel, yVel, zVel, 45, 45, 45, EXPLOSION, 1);
		}
		for(i = 0; i < 20; i++)
		{
			float randomXScale = rand() % 25 + 10;
			float randomYScale = rand() % 15 + 10;
			float randomZScale = rand() % 25 + 10;
			randomR = rand() % 300;
			randomTheta = (rand() % 180) / PI;
			randomPhi = (rand() % 180) / PI;
			xVel = randomR * cos(randomTheta) * cos(randomPhi);
			zVel = randomR * sin(randomTheta) * cos(randomPhi);
			yVel = randomR * sin(randomPhi);
			Particle_Create(particleList, numParticles, fragmentCube, enemyTank->Base.Position.x, enemyTank->Base.Position.y, enemyTank->Base.Position.z, xVel, yVel, zVel, randomXScale, randomYScale, randomZScale, FRAGMENT, 8);
		}
    maxhp = enemyTank->maxhp;
    Tank_Init(enemyTank, mesh);
    enemyTank->maxhp = maxhp;
    enemyTank->hp = maxhp;
    enemyTank->Base.Position.x = playerTank->Base.Position.x + rand() % ArenaSize - ArenaSize / 2;
    enemyTank->Base.Position.z = playerTank->Base.Position.z + rand() % ArenaSize - ArenaSize / 2; 
  }
}

void Tank_Smoke(Tank* theTank, Particle* particleList, int numParticles, Cube* smokeCube)
{
	float smokeTimerIncrement = 0.4 * (theTank->maxhp - theTank->hp) / theTank->maxhp;
	theTank->smokeTimer += smokeTimerIncrement;
	if(theTank->smokeTimer >= theTank->smokeMaxTimer)
	{
		float randomR = rand() % 30, randomTheta = (rand() % 180) / PI;
		float x = randomR * cos(randomTheta) + theTank->Base.Position.x, y = theTank->Base.Position.y, z = randomR * sin(randomTheta) + theTank->Base.Position.z;
		Particle_Create(particleList, numParticles, smokeCube, x, y, z, 0, 100, 0, 2, 2, 2, SMOKE, 1.2);
		theTank->smokeTimer = 0;
	}
}

void Bullet_Init(Bullet* theBullet, Cube* mesh)
{
  GameObject base;
  GameObject_Init(&base, mesh);
  Vector4_Set(&base.Position, 0, 0, 0, 1);
  Vector4_Set(&base.Rotation, 0, 0, 0, 0);
  Vector4_Set(&base.Scale, 5, 5, 5, 0);
  theBullet->Base = base;
  theBullet->xVel = 0;
  theBullet->yVel = 0;
  theBullet->zVel = 0;
  theBullet->isAvailable = TRUE;
}

void Bullet_UpdateAndDraw(Bullet* theBullet, struct Matrix4 * WorldToCamera, struct Matrix4 * Projection, BOOLEAN PerspectiveDivide, struct Matrix4 * ViewPort, Vector4* sunVector)
{
  if(theBullet->isAvailable == FALSE)
  {
    theBullet->Base.Position.x += theBullet->xVel / 60;
    theBullet->Base.Position.y += theBullet->yVel / 60;
    theBullet->Base.Position.z += theBullet->zVel / 60;
	theBullet->Base.Rotation.x += 0.3;
	theBullet->Base.Rotation.y += 0.3;
	theBullet->Base.Rotation.z += 0.3;
    GameObject_Draw(&theBullet->Base, WorldToCamera, Projection, PerspectiveDivide, ViewPort, sunVector);
    theBullet->yVel -= 4;
    if(theBullet->Base.Position.y <= 2)
    {
      theBullet->isAvailable = TRUE;
    }
  }
}

void Bullet_CheckCollisionWithTank(Bullet* theBullet, Tank* theTank, Particle* particleList, int numParticles, Cube* impactCube)
{
  Vector4 vectorToTarget;
  float length = 36;
  if(theBullet->isAvailable == FALSE);
  {
    Vector4_Subtract(&vectorToTarget, &theTank->Base.Position, &theBullet->Base.Position);
    Vector4_Length(&length, &vectorToTarget);
    if(length <= 35)
    {
      Bullet_HitTank(theBullet, theTank, particleList, numParticles, impactCube);
    }
  }
}

void Bullet_HitTank(Bullet* theBullet, Tank* theTank, Particle* particleList, int numParticles, Cube* impactCube)
{
  if(theBullet->isAvailable == FALSE)
  {
		int i;
    theBullet->isAvailable = TRUE;
		for(i = 0; i < 10; i++)
		{
			Particle_Create(particleList, numParticles, impactCube, theBullet->Base.Position.x, theBullet->Base.Position.y, theBullet->Base.Position.z, rand() % 160 - 80, rand() % 160 - 80, rand() % 160 - 80, 5, 5, 5, IMPACT, 0.3);
		}
    theBullet->Base.Position.y = -100;
    theTank->hp -= 15;
  }
}

void Particle_Init(Particle* theParticle, Cube* mesh)
{
	GameObject base;
  GameObject_Init(&base, mesh);
  Vector4_Set(&base.Position, 0, 0, 0, 1);
  Vector4_Set(&base.Rotation, 0, 0, 0, 0);
  Vector4_Set(&base.Scale, 5, 5, 5, 0);
	theParticle->Base = base;
	theParticle->lifetime = 0;
	theParticle->maxLifetime = 0;
  theParticle->xVel = 0;
  theParticle->yVel = 0;
  theParticle->zVel = 0;
	theParticle->mode = 0;
  theParticle->isAvailable = TRUE;
}

void Particle_Create(Particle* particleList, int numParticles, Cube* mesh, float x, float y, float z, float velX, float velY, float velZ, float scaleX, float scaleY, float scaleZ, int mode, float maxLifetime)
{
	int particleIDToUse, i;
	GameObject base;
  GameObject_Init(&base, mesh);
	for(i = 0; i < numParticles; i++)
	{
		if(particleList[i].isAvailable == TRUE)
		{
			particleIDToUse = i;
			break;
		}
	}
	particleList[i].maxLifetime = maxLifetime;
	particleList[i].lifetime = 0;
	particleList[i].Base = base;
	particleList[i].Base.Position.x = x;
	particleList[i].Base.Position.y = y;
	particleList[i].Base.Position.z = z;
	particleList[i].xVel = velX;
	particleList[i].yVel = velY;
	particleList[i].zVel = velZ;
	particleList[i].Base.Scale.x = scaleX;
	particleList[i].Base.Scale.y = scaleY;
	particleList[i].Base.Scale.z = scaleZ;
	particleList[i].mode = mode;
	particleList[i].isAvailable = FALSE;
}

void Particle_UpdateAndDraw(Particle* theParticle, struct Matrix4 * WorldToCamera, struct Matrix4 * Projection, BOOLEAN PerspectiveDivide, struct Matrix4 * ViewPort, Vector4* sunVector)
{
	if(theParticle->isAvailable == FALSE)
	{
		switch(theParticle->mode) /*create different particle behaviors here*/
		{
		case SMOKE:
			theParticle->yVel += 1;
			theParticle->Base.Scale.x += 0.3;
			theParticle->Base.Scale.y += 0.15;
			theParticle->Base.Scale.z += 0.3;
			theParticle->Base.Rotation.y += 0.04;
			break;
		case EXPLOSION:
			theParticle->xVel *= 0.97;
			theParticle->yVel *= 0.97;
			theParticle->zVel *= 0.97;
			theParticle->Base.Scale.x = 45 * (theParticle->maxLifetime - theParticle->lifetime) / theParticle->maxLifetime;
			theParticle->Base.Scale.y = 45 * (theParticle->maxLifetime - theParticle->lifetime) / theParticle->maxLifetime;
			theParticle->Base.Scale.z = 45 * (theParticle->maxLifetime - theParticle->lifetime) / theParticle->maxLifetime;
			if(theParticle->Base.Position.y < 0 + theParticle->Base.Scale.y / 2)
			{
				theParticle->yVel = 0;
			}
			break;
		case IMPACT:
			theParticle->xVel *= 0.96;
			theParticle->yVel *= 0.96;
			theParticle->zVel *= 0.96;
			theParticle->Base.Rotation.x -= 0.1;
			theParticle->Base.Rotation.y += 0.1;
			theParticle->Base.Rotation.z -= 0.1;
			theParticle->Base.Scale.x = 5 * (theParticle->maxLifetime - theParticle->lifetime) / theParticle->maxLifetime;
			theParticle->Base.Scale.y = 5 * (theParticle->maxLifetime - theParticle->lifetime) / theParticle->maxLifetime;
			theParticle->Base.Scale.z = 5 * (theParticle->maxLifetime - theParticle->lifetime) / theParticle->maxLifetime;
			break;
		case FRAGMENT:
			theParticle->yVel -= 4;
			if(theParticle->Base.Position.y < 0 + theParticle->Base.Scale.y / 2)
			{
				theParticle->yVel *= -0.5;
				theParticle->xVel *= 0.8;
				theParticle->zVel *= 0.8;
			}
			if(theParticle->maxLifetime - theParticle->lifetime <= 3)
			{
				theParticle->Base.Scale.x -= theParticle->Base.Scale.x / ((theParticle->maxLifetime - theParticle->lifetime) / 0.0167);
				theParticle->Base.Scale.y -= theParticle->Base.Scale.y / ((theParticle->maxLifetime - theParticle->lifetime) / 0.0167);
				theParticle->Base.Scale.z -= theParticle->Base.Scale.z / ((theParticle->maxLifetime - theParticle->lifetime) / 0.0167);
			}
			break;
		default:
			break;
		}
		theParticle->Base.Position.x += theParticle->xVel / 60;
		theParticle->Base.Position.y += theParticle->yVel / 60;
		theParticle->Base.Position.z += theParticle->zVel / 60;
		theParticle->lifetime += 0.0167;
		GameObject_Draw(&theParticle->Base, WorldToCamera, Projection, PerspectiveDivide, ViewPort, sunVector);
		if(theParticle->lifetime >= theParticle->maxLifetime)
		{
			theParticle->isAvailable = TRUE;
		}
	}
}