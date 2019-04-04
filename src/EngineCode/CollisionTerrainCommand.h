#ifndef _CollisionTerrainCommand
#define _CollisionTerrainCommand

#include "CommandBase.h"
#include "CollidableGroup.h"
#include "MathTools.h"
#include "TerrainObject.h"
#include "TerrainManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "DebugOut.h"
#include "Visualizer.h"

#define VISUALIZE_ENABLE_TERRAIN 1

template<class C1>
class CollisionTerrainCommand : public CommandBase, public Align16
{
private:

	typename CollidableGroup<C1>::CollidableCollection& Collection1;
	typename CollidableGroup<C1> ColGroup1;

	std::list<TerrainObject::TerrainCell> myList;

public:

	CollisionTerrainCommand()
		: Collection1(CollidableGroup<C1>::GetColliderCollection())
	{

	}

	//! Execute override. Calls the terrain to get all candidate collidable cells, calls Collision() function if true on any.
	/*!
	\sa TerrainObject::GetCellCandidates() used for check
	*/
	virtual void Execute()
	{

		//ColGroup1.UpdateAABB();

		bool test_result;

		CollidableGroup<C1>::CollidableCollection::iterator it1;
		for (it1 = Collection1.begin(); it1 != Collection1.end(); ++it1)
		{
			SceneManager::GetCurrentScene()->GetTerrain()->GetCellCandidates(*it1, myList);

			for (auto it2 = myList.begin(); it2 != myList.end(); it2++)
			{
				CollisionVolumeAABB cellAABB;
				cellAABB.ComputeData((*it2).cellMin, (*it2).cellMax);

				test_result = MathTools::Intersect(cellAABB, *((*it1)->GetDefaultBSphere()));

				if (test_result)
				{
#if VISUALIZE_ENABLE_TERRAIN
					Visualizer::VisualizeMe((*it2).cellMin, (*it2).cellMax, Colors::Orange);
					Visualizer::VisualizeMe((*it1)->GetDefaultBSphere(), Colors::Orange);
#endif

					test_result = (*it1)->GetCollisionVolume().Intersect(cellAABB);

					if (test_result)
					{
#if VISUALIZE_ENABLE_TERRAIN
						Visualizer::VisualizeMe((*it2).cellMin, (*it2).cellMax, Colors::Red);
						Visualizer::VisualizeMe((*it1), Colors::Red);
#endif
						(*it1)->TerrainCollision(cellAABB);

					}

				}
				else
				{
#if VISUALIZE_ENABLE_TERRAIN
					Visualizer::VisualizeMe((*it2).cellMin, (*it2).cellMax, Colors::SkyBlue);
					Visualizer::VisualizeMe((*it1)->GetDefaultBSphere(), Colors::SkyBlue);
#endif
				}
			}
		}

		myList.clear();

	}
};

#endif // !_CollisionTerrainCommand
