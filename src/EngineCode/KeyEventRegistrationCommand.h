#ifndef _KeyEventRegistrationCommand
#define _KeyEventRegistrationCommand

#include "AzulCore.h"
#include "CommandBase.h"
#include "Inputable.h"

class Inputable;

class KeyEventRegistrationCommand : public CommandBase
{
public:
	KeyEventRegistrationCommand(Inputable * in, AZUL_KEY key, Inputable::EVENT_TYPE type);
	~KeyEventRegistrationCommand();
	KeyEventRegistrationCommand(const KeyEventRegistrationCommand&) = delete;
	KeyEventRegistrationCommand& operator=(const KeyEventRegistrationCommand&) = delete;

	//! Execute override. Calls KeyEventRegistration() on Inputable pointer.
	void Execute() override;
private:
	Inputable* ptrIn;
	AZUL_KEY myKey;
	Inputable::EVENT_TYPE myType;
};

#endif // !_KeyEventRegistrationCommand
