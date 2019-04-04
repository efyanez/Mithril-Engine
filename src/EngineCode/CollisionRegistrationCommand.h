#ifndef _CollisionRegistrationCommand
#define _CollisionRegistrationCommand

#include "CommandBase.h"
#include "CollidableGroup.h"

template<typename C>
class CollisionRegistrationCommand : public CommandBase
{
private:

	C* ptrCol;

public:
	CollisionRegistrationCommand(C* c)
		: ptrCol(c)
	{};

	//! Execute override. Calls Register() on Collidable<C> pointer.
	virtual void Execute() override
	{
		CollidableGroup<C>::Register(ptrCol);
	}

};

#endif // !_CollisionRegistrationCommand