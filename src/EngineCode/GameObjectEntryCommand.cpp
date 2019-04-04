#include "GameObjectEntryCommand.h"
#include "GameObject.h"

GameObjectEntryCommand::GameObjectEntryCommand(GameObject * go)
{
	ptrGO = go;
}

GameObjectEntryCommand::~GameObjectEntryCommand()
{
	delete ptrGO;
}

void GameObjectEntryCommand::Execute()
{
	ptrGO->ConnectToScene();
}
