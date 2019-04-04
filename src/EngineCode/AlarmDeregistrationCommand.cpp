#include "AlarmDeregistrationCommand.h"
#include "Alarmable.h"

AlarmDeregistrationCommand::AlarmDeregistrationCommand(Alarmable * al, AlarmEnum::AlarmID alID)
{
	ptrAl = al;
	currentID = alID;
}

AlarmDeregistrationCommand::~AlarmDeregistrationCommand()
{
	delete ptrAl;
}

void AlarmDeregistrationCommand::Execute()
{
	ptrAl->SceneDeregistration((AlarmEnum::AlarmID)currentID);
}
