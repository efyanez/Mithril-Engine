#include "SecondScene.h"

#include "Frigate.h"
#include "Field.h"
#include "Axis.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Pyramid.h"
#include "../EngineCode/GodCamera.h"
#include "TankEnemy.h"

SecondScene::SecondScene()
{
}

SecondScene::~SecondScene()
{
}

void SecondScene::Initialize()
{
	SetTerrain("MainTerrain");

	testFrigate = new Frigate();
	testField = new Field();
	testAxis = new Axis();
	testPyramid = new Pyramid();
	Vect test = Vect(-120, 5, 0);
	testPyramid2 = new Pyramid(test);
	godCam = new GodCamera();

	Matrix enemyScale = Matrix(SCALE, 1.0f, 1.0f, 1.0f);
	Matrix enemyRot = Matrix(IDENTITY);
	Vect enemyPos = Vect(200.0f, 10.0f, 200.0f);
	enemy1 = new TankEnemy(enemyScale, enemyRot, enemyPos, testFrigate);

	ColMgr->SetCollisionPair<Frigate, Pyramid>();
	ColMgr->SetCollisionPair<Bullet, TankEnemy>();
	ColMgr->SetCollisionTerrain<Frigate>();
}

void SecondScene::Terminate()
{
	delete enemy1;
	delete testFrigate;
	delete testField;
	delete testAxis;
	delete godCam;
	DebugMsg::out("USER SCENE TERMINATED\n");
}
