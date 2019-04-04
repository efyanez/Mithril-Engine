#ifndef _UpdateRegistrationCommand
#define _UpdateRegistrationCommand

#include "CommandBase.h"

class Updatable;

class UpdateRegistrationCommand : public CommandBase
{
public:
	UpdateRegistrationCommand(Updatable* up);
	~UpdateRegistrationCommand();
	UpdateRegistrationCommand(const UpdateRegistrationCommand&) = delete;
	UpdateRegistrationCommand& operator=(const UpdateRegistrationCommand&) = delete;

	//! Execute override. Calls SceneRegistration() on Updatable pointer.
	void Execute() override;
private:
	Updatable* ptrUp;
};

#endif // !_CommandBase
