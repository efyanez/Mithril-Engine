#include "InputableManager.h"
#include "KeyObject.h"

InputableManager::~InputableManager()
{
	for (auto it = storageList.begin(); it != storageList.end(); ++it)
	{
		delete *it;
	}
	DebugMsg::out("INPUT MANAGER TERMINATED\n");
}

void InputableManager::Register(Inputable * in, AZUL_KEY k, Inputable::EVENT_TYPE type)
{
	KeyObject* obj = FindKeyObject(k);
	if (obj == nullptr)
	{
		obj = new KeyObject(in, k, type);
		storageList.push_back(obj);
	}
	else
	{
		obj->RegisterInputable(in, type);
	}
}

void InputableManager::Deregister(Inputable * in, AZUL_KEY k, Inputable::EVENT_TYPE type)
{
	if (FindKeyObject(k) != nullptr) 
	{
		FindKeyObject(k)->DeregisterInputable(in, type);
	}
}

KeyObject * InputableManager::FindKeyObject(AZUL_KEY k)
{
	for (auto it = storageList.begin(); it != storageList.end(); ++it)
	{
		if ((*it)->GetKey() == k)
		{
			return *it;
		}
	}
	return nullptr;
}

void InputableManager::ProcessElements()
{
	for (auto it = storageList.begin(); it != storageList.end(); ++it)
	{
		(*it)->CheckStatus();
	}
}
