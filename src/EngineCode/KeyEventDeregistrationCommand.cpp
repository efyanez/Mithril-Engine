#include "KeyEventDeregistrationCommand.h"
//#include "Inputable.h"

KeyEventDeregistrationCommand::KeyEventDeregistrationCommand(Inputable * in, AZUL_KEY key, Inputable::EVENT_TYPE type)
{
	ptrIn = in;
	myKey = key;
	myType = type;
}

KeyEventDeregistrationCommand::~KeyEventDeregistrationCommand()
{
	delete ptrIn;
}

void KeyEventDeregistrationCommand::Execute()
{
	ptrIn->KeyEventDeregistration(myKey, myType);
}
