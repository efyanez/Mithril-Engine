#include "FinalScene.h"
#include "../EngineCode/GodCamera.h"
#include "Frigate.h"

FinalScene::FinalScene()
{
}

FinalScene::~FinalScene()
{
	delete testFrigate;
	delete testGodCamera;
}

void FinalScene::Initialize()
{
	SetTerrain("FinalTerrain");

	testFrigate = new Frigate();
	
	testGodCamera = new GodCamera();

	ColMgr->SetCollisionTerrain<Frigate>();
}

void FinalScene::Terminate()
{
}
