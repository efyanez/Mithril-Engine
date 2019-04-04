#include "FirstScene.h"
#include "Frigate.h"
#include "Plane.h"
#include "Axis.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "SkySphere.h"
#include "TimedEnemySpawner.h"
#include "../EngineCode/GodCamera.h"
#include "../EngineCode/ParticleEffectSphericalBurst.h"
#include "../EngineCode/ParticleEffectPulse.h"
#include "../EngineCode/ParticleEffectStream.h"
#include "../EngineCode/ParticleEmitter.h"

FirstScene::FirstScene()
{
}

FirstScene::~FirstScene()
{
}

void FirstScene::Initialize()
{

	SetTerrain("StartTerrain");

	testFrigate = new Frigate();
	//testFrigate2 = new Frigate();
	//testPlane = new Plane();
	testAxis = new Axis();
	spawner = new TimedEnemySpawner(testFrigate);
	//godCam = new GodCamera();
	testSky = new SkySphere();

	ColMgr->SetCollisionSelf<Enemy>();
	ColMgr->SetCollisionPair<Frigate, Enemy>();
	//ColMgr->SetCollisionPair<Frigate, EnemyBullet>();
	ColMgr->SetCollisionPair<Bullet, Enemy>();
}

void FirstScene::Terminate()
{
	delete testFrigate;
	//delete testPlane;
	delete testAxis;
	delete testSky;
	delete spawner;
	DebugMsg::out("USER SCENE TERMINATED\n");
}
