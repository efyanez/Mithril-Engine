#include "SceneRegistrationBroker.h"
#include "CommandBase.h"
#include "DebugOut.h"

SceneRegistrationBroker::SceneRegistrationBroker()
{
}

SceneRegistrationBroker::~SceneRegistrationBroker()
{
	commandList.clear();
	DebugMsg::out("BROKER TERMINATED\n");
}

void SceneRegistrationBroker::AddCommand(CommandBase * cmd)
{
	commandList.push_back(cmd);
}

void SceneRegistrationBroker::AddSceneCommand(CommandBase * cmd)
{
	sceneCommandList.push_back(cmd);
}

void SceneRegistrationBroker::ExecuteCommands()
{
	auto it = commandList.begin();
	for (it = commandList.begin(); it != commandList.end(); it++)
	{
		(*it)->Execute();
	}
	commandList.clear();
}

void SceneRegistrationBroker::ExecuteSceneCommands()
{
	auto it = sceneCommandList.begin();
	for (it = sceneCommandList.begin(); it != sceneCommandList.end(); it++)
	{
		(*it)->Execute();
	}
	sceneCommandList.clear();
}
