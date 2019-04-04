#include "GameObjectExitCommand.h"
#include "GameObject.h"

GameObjectExitCommand::GameObjectExitCommand(GameObject * go)
{
	ptrGO = go;
}

GameObjectExitCommand::~GameObjectExitCommand()
{
	delete ptrGO;
}

void GameObjectExitCommand::Execute()
{
	ptrGO->DisconnectFromScene();
}
