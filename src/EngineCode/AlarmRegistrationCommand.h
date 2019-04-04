#ifndef _AlarmRegistrationCommand
#define _AlarmRegistrationCommand

#include "CommandBase.h"
#include "AlarmEnum.h"

class Alarmable;

class AlarmRegistrationCommand : public CommandBase
{
public:
	AlarmRegistrationCommand(Alarmable* dr, AlarmEnum::AlarmID alID);
	~AlarmRegistrationCommand();
	AlarmRegistrationCommand(const AlarmRegistrationCommand&) = delete;
	AlarmRegistrationCommand& operator=(const AlarmRegistrationCommand&) = delete;

	//! Execute override. Calls SceneRegistration() on Alarmable pointer.
	void Execute() override;
private:
	Alarmable* ptrAl;
	int currentID;
};

#endif // !_DrawRegistrationCommand
