#include "CollisionManager.h"

CollisionManager::~CollisionManager()
{
	//for (auto it = CollisionGroups.begin(); it != CollisionGroups.end(); it++)
	//{
	//	(*it)->Terminate();
	//}
	for (auto it = CollisionTestCommands.begin(); it != CollisionTestCommands.end(); it++)
	{
		delete (*it);
	}
	CollisionTestCommands.clear();
	CollisionGroups.clear();
	DebugMsg::out("COLLISION MANAGER TERMINATED\n");
}

void CollisionManager::UpdateAABBs()
{
	for (auto it = CollisionGroups.begin(); it != CollisionGroups.end(); it++)
	{
		(*it)->UpdateAABB();
	}
}

void CollisionManager::ProcessCollisionTest()
{
	UpdateAABBs();
	for (auto it = CollisionTestCommands.begin(); it != CollisionTestCommands.end(); it++)
	{
		(*it)->Execute();
	}
}

void CollisionManager::ClearList()
{
	for (auto it = CollisionGroups.begin(); it != CollisionGroups.end(); it++)
	{
		(*it)->ClearList();
	}
}
