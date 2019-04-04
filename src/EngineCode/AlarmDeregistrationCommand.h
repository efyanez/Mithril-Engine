#ifndef _AlarmDeregistrationCommand
#define _AlarmDeregistrationCommand

#include "CommandBase.h"
#include "AlarmEnum.h"

class Alarmable;

class AlarmDeregistrationCommand : public CommandBase
{
public:
	AlarmDeregistrationCommand(Alarmable* al, AlarmEnum::AlarmID alID);
	~AlarmDeregistrationCommand();
	AlarmDeregistrationCommand(const AlarmDeregistrationCommand&) = delete;
	AlarmDeregistrationCommand& operator=(const AlarmDeregistrationCommand&) = delete;

	//! Execute override. Calls SceneDeregistration() on Alarmable pointer.
	void Execute() override;
private:
	Alarmable* ptrAl;
	int currentID;
};

#endif // !_DrawDeregistrationCommand
