#ifndef _DrawDeregistrationCommand
#define _DrawDeregistrationCommand

#include "CommandBase.h"

class Drawable;

class DrawDeregistrationCommand : public CommandBase
{
public:
	DrawDeregistrationCommand(Drawable* dr);
	~DrawDeregistrationCommand();
	DrawDeregistrationCommand(const DrawDeregistrationCommand&) = delete;
	DrawDeregistrationCommand& operator=(const DrawDeregistrationCommand&) = delete;

	//! Execute override. Calls SceneDeregistration() on Drawable pointer.
	void Execute() override;
private:
	Drawable* ptrDr;
};

#endif // !_DrawDeregistrationCommand
