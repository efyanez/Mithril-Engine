#include "DrawRegistrationCommand.h"
#include "Drawable.h"

DrawRegistrationCommand::DrawRegistrationCommand(Drawable * dr)
{
	ptrDr = dr;
}

DrawRegistrationCommand::~DrawRegistrationCommand()
{
	delete ptrDr;
}

void DrawRegistrationCommand::Execute()
{
	ptrDr->SceneRegistration();
}
