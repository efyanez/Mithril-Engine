#ifndef _KeyEventDeregistrationCommand
#define _KeyEventDeregistrationCommand

#include "CommandBase.h"
#include "AzulCore.h"
#include "Inputable.h"

//class Inputable;

class KeyEventDeregistrationCommand : public CommandBase
{
public:
	KeyEventDeregistrationCommand(Inputable * in, AZUL_KEY key, Inputable::EVENT_TYPE type);
	~KeyEventDeregistrationCommand();
	KeyEventDeregistrationCommand(const KeyEventDeregistrationCommand&) = delete;
	KeyEventDeregistrationCommand& operator=(const KeyEventDeregistrationCommand&) = delete;

	//! Execute override. Calls KeyEventDeregistration() on Inputable pointer.
	void Execute() override;
private:
	Inputable* ptrIn;
	AZUL_KEY myKey;
	Inputable::EVENT_TYPE myType;
};

#endif // !_KeyEventDeregistrationCommand
