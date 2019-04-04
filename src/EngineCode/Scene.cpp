#include "Scene.h"
#include "SceneManager.h"
#include "Updatable.h"
#include "UpdatableManager.h"
#include "Drawable.h"
#include "DrawableManager.h"
#include "Alarmable.h"
#include "AlarmableManager.h"
#include "InputableManager.h"
#include "TerrainObjectManager.h"
#include "TerrainManager.h"
#include "Collidable.h"
#include "CollisionManager.h"
#include "SceneRegistrationBroker.h"
#include "CommandBase.h"
#include "DebugOut.h"
#include "GameObject.h"
#include "CameraManager.h"
#include "SoundManager.h"

Scene::Scene()
{
	UpdateMgr = new UpdatableManager();
	DrawMgr = new DrawableManager();
	AlarmMgr = new AlarmableManager();
	InputMgr = new InputableManager();
	ColMgr = new CollisionManager();
	TerrainMgr = new TerrainManager();
	sceneBroker = new SceneRegistrationBroker();
	camMgr = new CameraManager();
	camMgr->SetDefaultCamera();
}

Scene::~Scene()
{
	ColMgr->ClearList();
	DebugMsg::out("SCENE DESTROYED\n");
}

void Scene::Update()
{
	sceneBroker->ExecuteCommands();
	AlarmMgr->ProcessElements();
	UpdateMgr->ProcessElements();
	InputMgr->ProcessElements();
	ColMgr->ProcessCollisionTest();
	sceneBroker->ExecuteSceneCommands();
}

void Scene::SubmitCommand(CommandBase * cmd)
{
	sceneBroker->AddCommand(cmd);
}

void Scene::SubmitSceneCommand(CommandBase * cmd)
{
	sceneBroker->AddSceneCommand(cmd);
}

void Scene::Draw()
{
	TerrainMgr->RenderTerrain();
	DrawMgr->ProcessElements();
}

void Scene::Register(Updatable * up)
{
	UpdateMgr->Register(up);
}

void Scene::Deregister(Updatable * up)
{
	UpdateMgr->Deregister(up);
}

void Scene::Register(Drawable * dr)
{
	DrawMgr->Register(dr);
}

void Scene::Deregister(Drawable * dr)
{
	DrawMgr->Deregister(dr);
}

void Scene::Register(float t, Alarmable * al, AlarmEnum::AlarmID ID)
{
	AlarmMgr->Register(t, al, ID);
}

void Scene::Deregister(Alarmable * al, AlarmEnum::AlarmID ID)
{
	AlarmMgr->Deregister(al, ID);
}

void Scene::AddTime(float t, Alarmable * al, AlarmEnum::AlarmID ID)
{
	AlarmMgr->AddTime(t, al, ID);
}

float Scene::GetRemainingTime(Alarmable * al, AlarmEnum::AlarmID ID)
{
	return AlarmMgr->GetRemainingTime(al, ID);
}

void Scene::Register(Inputable * in, AZUL_KEY k, Inputable::EVENT_TYPE type)
{
	InputMgr->Register(in, k, type);
}

void Scene::Deregister(Inputable * in, AZUL_KEY k, Inputable::EVENT_TYPE type)
{
	InputMgr->Deregister(in, k, type);
}

void Scene::Register(GameObject * go)
{
	go->SceneEntry();
}

void Scene::Deregister(GameObject * go)
{
	go->SceneExit();
}

void Scene::Register(Collidable * co)
{
	(void)co;
}

void Scene::Deregister(Collidable * co)
{
	(void)co;
}

void Scene::SetTerrain(std::string key)
{
	TerrainMgr->SetTerrain(key);
}

TerrainObject * Scene::GetTerrain()
{
	return TerrainMgr->GetTerrain();
}

void Scene::Initialize()
{

}

void Scene::Terminate()
{
	SoundManager::StopAllSounds();
	delete sceneBroker;
	delete UpdateMgr;
	delete AlarmMgr;
	delete InputMgr;
	delete ColMgr;
	delete TerrainMgr;
	camMgr->Terminate();
	delete camMgr;
}
