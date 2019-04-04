#include "UpdateDeregistrationCommand.h"
#include "Updatable.h"

UpdateDeregistrationCommand::UpdateDeregistrationCommand(Updatable * up)
{
	ptrUp = up;
}

UpdateDeregistrationCommand::~UpdateDeregistrationCommand()
{
	delete ptrUp;
}

void UpdateDeregistrationCommand::Execute()
{
	ptrUp->SceneDeregistration();
}
