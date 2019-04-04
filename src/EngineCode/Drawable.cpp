#include "Drawable.h"
#include "Scene.h"
#include "SceneManager.h"
#include "DrawRegistrationCommand.h"
#include "DrawDeregistrationCommand.h"

Drawable::Drawable()
{
	regCmd = new DrawRegistrationCommand(this);
	dregCmd = new DrawDeregistrationCommand(this);
	currState = RegistrationState::CURRENTLY_DEREGISTERED;
}

Drawable::~Drawable()
{
	//delete regCmd;
	//delete dregCmd;
}

void Drawable::SceneRegistration()
{
	assert(currState == RegistrationState::PENDING_REGISTRATION);
	SceneManager::GetCurrentScene()->Register(this);
	currState = RegistrationState::CURRENTLY_REGISTERED;
}

void Drawable::SceneDeregistration()
{
	assert(currState == RegistrationState::PENDING_DEREGISTRATION);
	SceneManager::GetCurrentScene()->Deregister(this);
	currState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Drawable::SubmitDrawRegistration()
{
	assert(currState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneManager::GetCurrentScene()->SubmitCommand(regCmd);
	currState = RegistrationState::PENDING_REGISTRATION;
}

void Drawable::SubmitDrawDeregistration()
{
	assert(currState == RegistrationState::CURRENTLY_REGISTERED);
	SceneManager::GetCurrentScene()->SubmitCommand(dregCmd);
	currState = RegistrationState::PENDING_DEREGISTRATION;
}

void Drawable::SetIterator(DrawableManager::StorageListRef ref)
{
	myRef = ref;
}

DrawableManager::StorageListRef Drawable::GetIterator()
{
	return myRef;
}
