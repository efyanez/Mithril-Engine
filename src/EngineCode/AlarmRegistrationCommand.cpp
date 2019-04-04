#include "AlarmRegistrationCommand.h"
#include "Alarmable.h"

AlarmRegistrationCommand::AlarmRegistrationCommand(Alarmable * al, AlarmEnum::AlarmID alID)
{
	ptrAl = al;
	currentID = alID;
}

AlarmRegistrationCommand::~AlarmRegistrationCommand()
{
	delete ptrAl;
}

void AlarmRegistrationCommand::Execute()
{
	ptrAl->SceneRegistration(ptrAl->GetTime((AlarmEnum::AlarmID)currentID), (AlarmEnum::AlarmID)currentID);
}
