#include "KeyEventRegistrationCommand.h"
//#include "Inputable.h"

KeyEventRegistrationCommand::KeyEventRegistrationCommand(Inputable * in, AZUL_KEY key, Inputable::EVENT_TYPE type)
{
	ptrIn = in;
	myKey = key;
	myType = type;
}

KeyEventRegistrationCommand::~KeyEventRegistrationCommand()
{
	delete ptrIn;
}

void KeyEventRegistrationCommand::Execute()
{
	ptrIn->KeyEventRegistration(myKey, myType);
}
