#ifndef _CollidableGroupBase
#define _CollidableGroupBase

class CollidableGroupBase
{
public:

	CollidableGroupBase() { };

	virtual ~CollidableGroupBase() { };

	virtual void ClearList() {};
	virtual void UpdateAABB() {};
	virtual void Terminate() {};
};

#endif _CollidableGroupBase