#include "Inputable.h"
#include "InputableManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "KeyEventRegistrationCommand.h"
#include "KeyEventDeregistrationCommand.h"

Inputable::Inputable()
{

}

void Inputable::SubmitKeyEventRegistration(AZUL_KEY k, EVENT_TYPE type)
{
	regCmd = new KeyEventRegistrationCommand(this, k, type);
	SceneManager::GetCurrentScene()->SubmitCommand(regCmd);
}

void Inputable::SubmitKeyEventDeregistration(AZUL_KEY k, EVENT_TYPE type)
{
	deregCmd = new KeyEventDeregistrationCommand(this, k, type);
	SceneManager::GetCurrentScene()->SubmitCommand(deregCmd);
}

void Inputable::KeyEventRegistration(AZUL_KEY k, EVENT_TYPE type)
{
	SceneManager::GetCurrentScene()->Register(this, k, type);
}

void Inputable::KeyEventDeregistration(AZUL_KEY k, EVENT_TYPE type)
{
	SceneManager::GetCurrentScene()->Deregister(this, k, type);
}

void Inputable::OnKeyPress(AZUL_KEY k)
{
	(void)k;
}

void Inputable::OnKeyRelease(AZUL_KEY k)
{
	(void)k;
}
