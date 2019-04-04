#ifndef _DrawRegistrationCommand
#define _DrawRegistrationCommand

#include "CommandBase.h"

class Drawable;

class DrawRegistrationCommand : public CommandBase
{
public:
	DrawRegistrationCommand(Drawable* dr);
	~DrawRegistrationCommand();
	DrawRegistrationCommand(const DrawRegistrationCommand&) = delete;
	DrawRegistrationCommand& operator=(const DrawRegistrationCommand&) = delete;

	//! Execute override. Calls SceneRegistration() on Drawable pointer.
	void Execute() override;
private:
	Drawable* ptrDr;
};

#endif // !_DrawRegistrationCommand
