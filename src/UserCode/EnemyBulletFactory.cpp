#include "EnemyBulletFactory.h"
#include "EnemyBullet.h"
#include "DebugOut.h"
#include "Enemy.h"

EnemyBulletFactory* EnemyBulletFactory::ptrInstance = NULL;

void EnemyBulletFactory::privCreateBullet(Enemy* rotation, float offX, float offY, float offZ)
{
	EnemyBullet* b;

	if (recycledItems.empty())
	{
		//ConsoleMsg::WriteLine("New Bullet"); // For illustration purposes

		b = new EnemyBullet();

		// Declares that this object should be returned here (rather than deleted) when destroyed
		//b->SetExternalManagement(RecycleBullet);
		//DebugMsg::out("NEW BULLET CREATED\n");
		activeItems.push(b);

	}
	else
	{
		//ConsoleMsg::WriteLine("Recycled Bullet"); // For illustration purposes

		b = recycledItems.top();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

								// Tell the object to register itself to the scene
								//b->RegisterToCurrentScene();
								//DebugMsg::out("OLD BULLET USED\n");
		activeItems.push(b);
	}

	b->Initialize(rotation, offX, offY, offZ);
	b->GameObject::SubmitEntry();
}

void EnemyBulletFactory::privRecycleBullet(EnemyBullet* b)
{
	recycledItems.push(b);
	activeItems.pop();
	// For illustration purposes
	//ConsoleMsg::WriteLine("Recycled Stack Size: " + Tools::ToString(recycledItems.size()));
	//DebugMsg::out("Recycled stack size: %d\n", recycledItems.size());
}

void EnemyBulletFactory::privTerminate()
{
	delete Instance().ptrInstance;
	Instance().ptrInstance = nullptr;	// important habit for Singleton. Why?
}


// Why is this necessary?
EnemyBulletFactory::~EnemyBulletFactory()
{
	// forcefully delele all recycled gameobjects
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
		DebugMsg::out("Recycled stack size: %d\n", recycledItems.size());
	}

	while (!activeItems.empty())
	{
		delete activeItems.top();
		activeItems.pop();
		DebugMsg::out("Active stack size: %d\n", activeItems.size());
	}
}