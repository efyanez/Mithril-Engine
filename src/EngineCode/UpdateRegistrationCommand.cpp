#include "UpdateRegistrationCommand.h"
#include "Updatable.h"

UpdateRegistrationCommand::UpdateRegistrationCommand(Updatable * up)
{
	ptrUp = up;
}

UpdateRegistrationCommand::~UpdateRegistrationCommand()
{
	delete ptrUp;
}

void UpdateRegistrationCommand::Execute()
{
	ptrUp->SceneRegistration();
}
