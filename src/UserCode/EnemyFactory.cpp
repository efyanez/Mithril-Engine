#include "EnemyFactory.h"
#include "Enemy.h"
#include "Frigate.h"

EnemyFactory* EnemyFactory::ptrInstance = NULL;


void EnemyFactory::privCreateEnemy(const Matrix& mscale, const Matrix& mrot, const Vect& mpos, Frigate* p)
{
	Enemy* e;

	if (recycledItems.empty())
	{
		//ConsoleMsg::WriteLine("New Bullet"); // For illustration purposes

		e = new Enemy();

		// Declares that this object should be returned here (rather than deleted) when destroyed
		//b->SetExternalManagement(RecycleBullet);
		//DebugMsg::out("NEW BULLET CREATED\n");
		activeItems.push(e);

	}
	else
	{
		//ConsoleMsg::WriteLine("Recycled Bullet"); // For illustration purposes

		e = recycledItems.top();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

								// Tell the object to register itself to the scene
								//b->RegisterToCurrentScene();
		//DebugMsg::out("OLD BULLET USED\n");
		activeItems.push(e);
	}

	e->Initialize(mrot, mscale, mpos, p);
	e->GameObject::SubmitEntry();
}

void EnemyFactory::privRecycleEnemy(Enemy* e)
{
	recycledItems.push(e);
	activeItems.pop();

	// For illustration purposes
	//ConsoleMsg::WriteLine("Recycled Stack Size: " + Tools::ToString(recycledItems.size()));
	//DebugMsg::out("Recycled stack size: %d\n", recycledItems.size());
}

void EnemyFactory::privTerminate()
{
	delete Instance().ptrInstance;
	Instance().ptrInstance = nullptr;	// important habit for Singleton. Why?
}


// Why is this necessary?
EnemyFactory::~EnemyFactory()
{
	// forcefully delele all recycled gameobjects
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
		//DebugMsg::out("Recycled stack size: %d\n", recycledItems.size());
	}

	//while (!activeItems.empty())
	//{
	//	delete activeItems.top();
	//	activeItems.pop();
	//	DebugMsg::out("Active stack size: %d\n", activeItems.size());
	//}
}