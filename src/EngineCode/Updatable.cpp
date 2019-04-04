#include "Updatable.h"
#include "Scene.h"
#include "SceneManager.h"
#include "UpdateRegistrationCommand.h"
#include "UpdateDeregistrationCommand.h"

Updatable::Updatable()
{
	regCmd = new UpdateRegistrationCommand(this);
	dregCmd = new UpdateDeregistrationCommand(this);
	currState = RegistrationState::CURRENTLY_DEREGISTERED;
}

Updatable::~Updatable()
{
	//delete regCmd;
	//delete dregCmd;
}

void Updatable::SceneRegistration()
{
	assert(currState == RegistrationState::PENDING_REGISTRATION);
	SceneManager::GetCurrentScene()->Register(this);
	currState = RegistrationState::CURRENTLY_REGISTERED;
}

void Updatable::SceneDeregistration()
{
	assert(currState == RegistrationState::PENDING_DEREGISTRATION);
	SceneManager::GetCurrentScene()->Deregister(this);
	currState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Updatable::SubmitUpdateRegistration()
{
	assert(currState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneManager::GetCurrentScene()->SubmitCommand(regCmd);
	currState = RegistrationState::PENDING_REGISTRATION;
}

void Updatable::SubmitUpdateDeregistration()
{
	assert(currState == RegistrationState::CURRENTLY_REGISTERED);
	SceneManager::GetCurrentScene()->SubmitCommand(dregCmd);
	currState = RegistrationState::PENDING_DEREGISTRATION;
}

void Updatable::SetIterator(UpdatableManager::StorageListRef ref)
{
	myRef = ref;
}

UpdatableManager::StorageListRef Updatable::GetIterator()
{
	return myRef;
}
