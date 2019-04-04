#ifndef _CollisionTestSelfCommand
#define _CollisionTestSelfCommand

#include "CommandBase.h"
#include "CollidableGroup.h"
#include "MathTools.h"

template<class C1>
class CollisionTestSelfCommand : public CommandBase, public Align16
{
private:

	typename CollidableGroup<C1>::CollidableCollection& Collection1;
	typename CollidableGroup<C1> ColGroup1;

public:

	CollisionTestSelfCommand()
		: Collection1(CollidableGroup<C1>::GetColliderCollection())
	{

	}

	//! Execute override. Calls Collision() methods on pairs in Collidable Group container with same object types.
	/*!
	\sa CollisionVolumeBSphere::Intersect()
	*/
	virtual void Execute()
	{

		//ColGroup1.UpdateAABB();

		bool test_result;

		CollidableGroup<C1>::CollidableCollection::iterator it1;
		CollidableGroup<C1>::CollidableCollection::iterator it2;
		for (it1 = Collection1.begin(); it1 != Collection1.end(); ++it1)
		{
			for (it2 = next(it1); it2 != Collection1.end(); ++it2)
			{

				test_result = MathTools::Intersect(*((*it1)->GetDefaultBSphere()), *((*it2)->GetDefaultBSphere()));

				if (test_result)
				{
					test_result = MathTools::Intersect(*it1, *it2);

					if (test_result && it1 != Collection1.end() && it2 != Collection1.end())
					{
						(*it1)->Collision(*it2);
						(*it2)->Collision(*it1);
					}
				}
				else
				{
					//Visualizer::VisualizeMe(((*it1)->GetDefaultBSphere()), Colors::SkyBlue);
					//Visualizer::VisualizeMe(((*it2)->GetDefaultBSphere()), Colors::SkyBlue);
				}
			}
		}
	}
};

#endif // !_CollisionTestSelfCommand
