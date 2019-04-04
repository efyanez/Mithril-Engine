#ifndef _CollisionDeregistrationCommand
#define _CollisionDeregistrationCommand

#include "CommandBase.h"
#include "CollidableGroup.h"

template<typename C>
class CollisionDeregistrationCommand : public CommandBase
{
private:

	C* ptrCol;

public:
	CollisionDeregistrationCommand(C* c)
		: ptrCol(c)
	{};

	//! Execute override. Calls Deregister() on Collidable<C> pointer.
	virtual void Execute() override
	{
		CollidableGroup<C>::Deregister(ptrCol);
	}

};

#endif // !_CollisionDeregistrationCommand
