#include "GameObject.h"
#include "GameObjectEntryCommand.h"
#include "GameObjectExitCommand.h"
#include "AzulCore.h"
#include "Scene.h"
#include "SceneManager.h"

GameObject::GameObject()
{
	pRegCmd = new GameObjectEntryCommand(this);
	pDeregCmd = new GameObjectExitCommand(this);
	currState = RegistrationState::CURRENTLY_DEREGISTERED;
}

GameObject::~GameObject()
{
	//DebugMsg::out("GAMEOBJECT COMMANDS DELETED\n");
}

void GameObject::SubmitEntry()
{
	assert(currState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneManager::GetCurrentScene()->SubmitCommand(pRegCmd);
	currState = RegistrationState::PENDING_REGISTRATION;
}

void GameObject::SubmitExit()
{
	assert(currState == RegistrationState::CURRENTLY_REGISTERED);
	SceneManager::GetCurrentScene()->SubmitCommand(pDeregCmd);
	currState = RegistrationState::PENDING_DEREGISTRATION;
}

void GameObject::ConnectToScene()
{
	assert(currState == RegistrationState::PENDING_REGISTRATION);
	SceneManager::GetCurrentScene()->Register(this);
	currState = RegistrationState::CURRENTLY_REGISTERED;
}

void GameObject::DisconnectFromScene()
{
	assert(currState == RegistrationState::PENDING_DEREGISTRATION);
	SceneManager::GetCurrentScene()->Deregister(this);
	currState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void GameObject::SceneEntry()
{
}

void GameObject::SceneExit()
{
}
