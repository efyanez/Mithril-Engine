#include "UpdatableManager.h"
#include "Updatable.h"
#include "DebugOut.h"

UpdatableManager::~UpdatableManager()
{
	StorageList.clear();
	DebugMsg::out("UPDATABLE MANAGER TERMINATED\n");
}

void UpdatableManager::Register(Updatable * up)
{
	ref = StorageList.insert(StorageList.end(), up);
	up->SetIterator(ref);
}

void UpdatableManager::Deregister(Updatable* up)
{ 

	StorageList.erase(up->GetIterator());
}

void UpdatableManager::ProcessElements()
{
	std::list<Updatable*>::iterator it = StorageList.begin();

	for (it = StorageList.begin(); it != StorageList.end(); it++)
	{
		(*it)->Update();
	}
}
