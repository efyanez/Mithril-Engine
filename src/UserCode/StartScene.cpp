#include "StartScene.h"
#include "StartSceneFrigate.h"
#include "Plane.h"
#include "SkySphere.h"
#include "../EngineCode/ColorLibrary.h"
#include "../EngineCode/ParticleEffectManager.h"
#include "TankEnemy.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

void StartScene::Initialize()
{
	SetTerrain("StartTerrain");
	testFrigate = new StartSceneFrigate();
	testSky = new SkySphere();

	Vect pos(0.0f, 60.0f, 0.0f);
	Matrix rot(IDENTITY);
	ParticleEffect* pe = ParticleEffectManager::GetParticleEffect("Water1");
	pe->SpawnParticleEmitter(pos, rot, true);

	Vect pos2(0.0f, 60.0f, 0.0f);
	Matrix rot2(IDENTITY);
	ParticleEffect* pe2 = ParticleEffectManager::GetParticleEffect("Explosion");
	pe2->SpawnParticleEmitter(pos2, rot2, true);
}

void StartScene::Terminate()
{
	delete testFrigate;
	delete testSky;
}
