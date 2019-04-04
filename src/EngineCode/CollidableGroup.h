#ifndef _CollidableGroup
#define _CollidableGroup

#include "CollidableGroupBase.h"
#include "CollisionVolumeAABB.h"
#include <set>
#include "Visualizer.h"
#include <cfloat>

template <typename C>
class CollidableGroup : public CollidableGroupBase, public Align16
{

private:
	void privRegister(C* p);
	void privDeregister(C* p);
	void privUpdateAABB();
	void privTerminate();
	void privClearList();
public:
	static CollidableGroup* self;
	CollidableGroup(const CollidableGroup&) {};
	CollidableGroup& operator= (const CollidableGroup) {};
	~CollidableGroup();

	static CollidableGroup& Instance()
	{
		if (!self)
		{
			self = new CollidableGroup();
		}
		return *self;
	};

	typedef std::set<C*> CollidableCollection;
	CollidableCollection CollideCol;

	CollisionVolumeAABB groupAABB;
	Vect currentMin = Vect(FLT_MAX, FLT_MAX, FLT_MAX);
	Vect currentMax = Vect(FLT_MIN, FLT_MIN, FLT_MIN);

	CollidableGroup() 
	{
		//groupAABB = new CollisionVolumeAABB();
	}

	static void Register(C* p) { Instance().privRegister(p); }
	static void Deregister(C* p) { Instance().privDeregister(p); }
	void ClearList() { Instance().privClearList(); }
	static CollidableCollection& GetColliderCollection() { return Instance().CollideCol; }
	void UpdateAABB() { Instance().privUpdateAABB(); }
	static CollisionVolumeAABB & GetAABB() { return Instance().groupAABB; }
	void Terminate() { Instance().privTerminate(); }


};

template <typename C>
CollidableGroup<C>* CollidableGroup<C>::self = NULL;

template<typename C>
inline void CollidableGroup<C>::privRegister(C * p)
{
	Instance().CollideCol.insert(p);
}

template<typename C>
inline void CollidableGroup<C>::privDeregister(C * p)
{
	Instance().CollideCol.erase(p);
}

template<typename C>
CollidableGroup<C>::~CollidableGroup()
{
	CollideCol.clear();
}

template<typename C>
inline void CollidableGroup<C>::privUpdateAABB()
{

	if (!CollideCol.empty())
	{
		auto it1 = CollideCol.begin();
		CollisionVolumeBSphere* one = (*it1)->GetDefaultBSphere();
		currentMin = one->GetAABBMin();
		currentMax = one->GetAABBMax();

		for (auto it = CollideCol.begin(); it != CollideCol.end(); it++)
		{
			Vect sphereMin = (*it)->GetDefaultBSphere()->GetAABBMin();
			Vect sphereMax = (*it)->GetDefaultBSphere()->GetAABBMax();
			currentMin = MathTools::GetMinVect(currentMin, sphereMin);
			currentMax = MathTools::GetMaxVect(currentMax, sphereMax);
		}

		groupAABB.ComputeData(currentMin, currentMax);
	}
}

template<typename C>
inline void CollidableGroup<C>::privTerminate()
{
	CollideCol.clear();
	delete self;
	self = 0;
}

template<typename C>
inline void CollidableGroup<C>::privClearList()
{
	CollideCol.clear();
}

#endif // !_CollidableGroup

