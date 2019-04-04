#include "SceneManager.h"
#include "Scene.h"
#include "DebugOut.h"
#include "CameraManager.h"
#include "Visualizer.h"

SceneManager* SceneManager::self = NULL;

void SceneManager::privInitializeCurrentScene()
{
	currentScene->Initialize();
}

void SceneManager::privSetCurrentScene(Scene* sc)
{
	currentScene = sc;
}

Scene * SceneManager::privGetCurrentScene()
{
	return currentScene;
}

void SceneManager::privTerminate()
{
	currentScene->Terminate();
	delete currentScene;
	DebugMsg::out("SCENE MANAGER TERMINATED\n");
}

void SceneManager::privUpdateUpdatables()
{
	//if (nextScene != nullptr)
	//{
	//	Instance().privChangeScene();
	//	nextScene = nullptr;
	//}
	currentScene->Update();
}

void SceneManager::privDrawDrawables()
{
	Visualizer::ShowAll();
	currentScene->Draw();
}

void SceneManager::privSetNextScene(Scene * pnextScene)
{
	nextScene = pnextScene;
}

void SceneManager::privSubmitSceneChange(Scene * newScene)
{
	currentScene->SubmitSceneCommand(new SceneChangeCommand(newScene));
}

Camera * SceneManager::privGetCurrent3DCamera()
{
	return currentScene->GetCamManager()->GetCurrentCamera();
}

Camera * SceneManager::privGetCurrent2DCamera()
{
	return currentScene->GetCamManager()->GetCurrent2DCamera();
}

void SceneManager::privChangeScene()
{
	currentScene->Terminate();
	delete currentScene;
	currentScene = nextScene;
	currentScene->Initialize();
}
