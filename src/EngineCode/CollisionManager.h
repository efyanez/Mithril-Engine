#ifndef _CollisionManager
#define _CollisionManager

#include <list>
#include <set>

#include "CollisionTestSelfCommand.h"
#include "CollisionTestPairCommand.h"
#include "CollisionTerrainCommand.h"

class CollidableGroupBase;

class CollisionManager
{

	friend class Scene;

private:
	void UpdateAABBs();
	void ProcessCollisionTest();
	void ClearList();

public:
	CollisionManager() {};
	virtual ~CollisionManager();

	std::list<CommandBase*> CollisionTestCommands;
	std::set<CollidableGroupBase*> CollisionGroups;

	template <typename C1, typename C2>
	void SetCollisionPair()
	{
		CollisionGroups.insert(&CollidableGroup<C1>::Instance());
		CollisionGroups.insert(&CollidableGroup<C2>::Instance());
		CollisionTestCommands.push_back(new CollisionTestPairCommand<C1, C2>());
	}

	template <typename C1>
	void SetCollisionSelf()
	{
		CollisionGroups.insert(&CollidableGroup<C1>::Instance());
		CollisionTestCommands.push_back(new CollisionTestSelfCommand<C1>());
	}

	template <typename C1>
	void SetCollisionTerrain()
	{
		CollisionGroups.insert(&CollidableGroup<C1>::Instance());
		CollisionTestCommands.push_back(new CollisionTerrainCommand<C1>());
	}

private:

};

#endif // !_CollisionManager
