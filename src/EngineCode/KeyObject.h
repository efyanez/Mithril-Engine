#ifndef _KeyObject
#define _KeyObject

#include "AzulCore.h"
#include <list>
#include "Inputable.h"

class KeyObject
{
public:

	KeyObject(Inputable* in, AZUL_KEY k, Inputable::EVENT_TYPE type);
	~KeyObject();
	KeyObject(const KeyObject&) = delete;
	KeyObject& operator=(const KeyObject&) = delete;

	AZUL_KEY GetKey() { return key; }

	void RegisterInputable(Inputable* in, Inputable::EVENT_TYPE type);
	void DeregisterInputable(Inputable* in, Inputable::EVENT_TYPE type);

	void CheckStatus();

private:

	AZUL_KEY key;

	std::list<Inputable*> keyPresses;
	std::list<Inputable*> keyReleases;

	bool prevState;
	bool currState;

	

};

#endif // !_KeyObject
