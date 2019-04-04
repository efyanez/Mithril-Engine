#include "KeyObject.h"
#include "DebugOut.h"

KeyObject::KeyObject(Inputable * in, AZUL_KEY k, Inputable::EVENT_TYPE type) : key(k)
{
	RegisterInputable(in, type);
}

KeyObject::~KeyObject()
{
	keyPresses.clear();
	keyReleases.clear();
}

void KeyObject::RegisterInputable(Inputable * in, Inputable::EVENT_TYPE type)
{
	switch (type)
	{
	case(Inputable::EVENT_TYPE::KEY_PRESS):
		keyPresses.push_back(in);
		break;
	case(Inputable::EVENT_TYPE::KEY_RELEASE):
		keyReleases.push_back(in);
		break;
	default:
		break;
	}
}

void KeyObject::DeregisterInputable(Inputable * in, Inputable::EVENT_TYPE type)
{
	switch (type)
	{
	case(Inputable::EVENT_TYPE::KEY_PRESS):
		keyPresses.remove(in);
		break;
	case(Inputable::EVENT_TYPE::KEY_RELEASE):
		keyReleases.remove(in);
		break;
	default:
		break;
	}
}

void KeyObject::CheckStatus()
{
	currState = Keyboard::GetKeyState(key);

	if (currState == true && prevState == false)
	{
		std::list<Inputable*>::iterator it;
		it = keyPresses.begin();
		while (it != keyPresses.end())
		{
			(*it)->OnKeyPress(key);
			it++;
		}
	}
	else if (currState == false && prevState == true)
	{
		std::list<Inputable*>::iterator it;
		it = keyReleases.begin();
		while (it != keyReleases.end())
		{
			(*it)->OnKeyRelease(key);
			it++;
		}
	}

	prevState = currState;
}
