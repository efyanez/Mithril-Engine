#include "DrawableManager.h"
#include "Drawable.h"
#include "DebugOut.h"

DrawableManager::~DrawableManager()
{
	StorageList.clear();
	DebugMsg::out("DRAWABLE MANAGER TERMINATED\n");
}

void DrawableManager::Register(Drawable * dr)
{
	ref = StorageList.insert(StorageList.end(), dr);
	dr->SetIterator(ref);
}

void DrawableManager::Deregister(Drawable * dr)
{

	StorageList.erase(dr->GetIterator());

}

void DrawableManager::ProcessElements()
{
	std::list<Drawable*>::iterator it = StorageList.begin();

	for (it = StorageList.begin(); it != StorageList.end(); it++)
	{
		(*it)->Draw();
	}

	for (it = StorageList.begin(); it != StorageList.end(); it++)
	{
		(*it)->Draw2D();
	}
}
