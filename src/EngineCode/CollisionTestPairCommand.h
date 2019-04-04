#ifndef _CollisionTestPairCommand
#define _CollisionTestPairCommand

#include "CommandBase.h"
#include "CollidableGroup.h"
#include "Visualizer.h"
#include "ColorLibrary.h"
#include "MathTools.h"

#define VISUALIZE_ENABLE 1

template<typename C1, typename C2>
class CollisionTestPairCommand : public CommandBase, public Align16
{
private:

	typename CollidableGroup<C1>::CollidableCollection& Collection1;
	typename CollidableGroup<C2>::CollidableCollection& Collection2;

	typename CollidableGroup<C1> ColGroup1;
	typename CollidableGroup<C2> ColGroup2;

public:

	CollisionTestPairCommand()
		: Collection1(CollidableGroup<C1>::GetColliderCollection()),
		Collection2(CollidableGroup<C2>::GetColliderCollection())
	{

	}

	//! Execute override. Calls Collision() methods on pairs in Collidable Group container.
	/*!
	\sa CollisionVolumeBSphere::Intersect()
	*/
	virtual void Execute()
	{

		//ColGroup1.UpdateAABB();
		//ColGroup2.UpdateAABB();

		//Visualizer::ShowBox(ColGroup1.GetAABB(), Colors::Yellow);
		//Visualizer::ShowBox(ColGroup2.GetAABB(), Colors::Yellow);

		CollidableGroup<C1>::CollidableCollection::iterator it1;
		CollidableGroup<C2>::CollidableCollection::iterator it2;

		CollisionVolumeAABB& first = ColGroup1.GetAABB();
		CollisionVolumeAABB& second = ColGroup2.GetAABB();

		bool test_result = MathTools::Intersect(first, second);

		if (test_result)
		{
			for (it1 = Collection1.begin(); it1 != Collection1.end(); ++it1)
			{
				if (MathTools::Intersect(second, *((*it1)->GetDefaultBSphere())))
				{
						for (it2 = Collection2.begin(); it2 != Collection2.end(); it2++)
						{
							test_result = MathTools::Intersect(*((*it1)->GetDefaultBSphere()), *((*it2)->GetDefaultBSphere()));

							if (test_result)
							{
								test_result = MathTools::Intersect(*it1, *it2);

								if (test_result)
								{
									(*it1)->Collision(*it2);
									(*it2)->Collision(*it1);
								}
								else
								{
#if VISUALIZE_ENABLE
									Visualizer::VisualizeMe(*it1, Colors::White);
									Visualizer::VisualizeMe(*it2, Colors::White);
#endif
								}
							}
							else
							{
#if VISUALIZE_ENABLE
								Visualizer::VisualizeMe(((*it1)->GetDefaultBSphere()), Colors::Red);
								Visualizer::VisualizeMe(((*it2)->GetDefaultBSphere()), Colors::Red);
#endif
							}
						}
				}
				else
				{
#if VISUALIZE_ENABLE
					Visualizer::VisualizeMe((&first), Colors::Red);
					Visualizer::VisualizeMe((&second), Colors::Red);
#endif
				}
			}
		}
		else
		{
#if VISUALIZE_ENABLE
			Visualizer::VisualizeMe((&first), Colors::White);
			Visualizer::VisualizeMe((&second), Colors::White);
#endif
		}
	}
};

#endif // !_CollisionTestPairCommand
