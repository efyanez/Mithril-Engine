#ifndef _UpdateDeregistrationCommand
#define _UpdateDeregistrationCommand

#include "CommandBase.h"

class Updatable;

class UpdateDeregistrationCommand : public CommandBase
{
public:
	UpdateDeregistrationCommand(Updatable* up);
	~UpdateDeregistrationCommand();
	UpdateDeregistrationCommand(const UpdateDeregistrationCommand&) = delete;
	UpdateDeregistrationCommand& operator=(const UpdateDeregistrationCommand&) = delete;

	//! Execute override. Calls SceneDeregistration() on Updatable pointer.
	void Execute() override;
private:
	Updatable* ptrUp;
};

#endif // !_UpdateDeregistrationCommand
