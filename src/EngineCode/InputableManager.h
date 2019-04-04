#ifndef _InputableManager
#define _InputableManager

#include <list>
#include "AzulCore.h"
#include "Inputable.h"

class KeyObject;

class InputableManager
{
public:
	InputableManager() = default;
	virtual ~InputableManager();
	InputableManager(const InputableManager&) = delete;
	InputableManager& operator=(const InputableManager&) = delete;

	void Register(Inputable* in, AZUL_KEY k, Inputable::EVENT_TYPE type);
	void Deregister(Inputable* in, AZUL_KEY k, Inputable::EVENT_TYPE type);

private:

	typedef std::list<KeyObject*> KeyObjectList;
	KeyObjectList storageList;

	using StorageListRef = std::list<KeyObject*>::iterator;
	StorageListRef ref;
	
	KeyObject* FindKeyObject(AZUL_KEY k);

	friend class Scene;

	void ProcessElements();
};

#endif // !_InputableManager
