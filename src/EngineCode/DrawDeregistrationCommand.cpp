#include "DrawDeregistrationCommand.h"
#include "Drawable.h"

DrawDeregistrationCommand::DrawDeregistrationCommand(Drawable * dr)
{
	ptrDr = dr;
}

DrawDeregistrationCommand::~DrawDeregistrationCommand()
{
	delete ptrDr;
}

void DrawDeregistrationCommand::Execute()
{
	ptrDr->SceneDeregistration();
}
