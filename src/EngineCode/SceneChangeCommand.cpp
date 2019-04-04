#include "SceneChangeCommand.h"
#include "SceneManager.h"

SceneChangeCommand::SceneChangeCommand(Scene * s)
{
	ptrScene = s;
}

SceneChangeCommand::~SceneChangeCommand()
{
}

void SceneChangeCommand::Execute()
{
	SceneManager::SetNextScene(ptrScene);
	SceneManager::ChangeScene();
}
