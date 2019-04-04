#ifndef _CollisionVolume
#define _CollisionVolume

#include "AzulCore.h"
#include "Matrix.h"

class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;

class CollisionVolume
{
public:
	//! CollisionVolume constructor
	/*!
	\ingroup Collisions
	*/
	CollisionVolume();
	CollisionVolume(const CollisionVolume&) = default;
	CollisionVolume& operator=(const CollisionVolume&) = default;
	~CollisionVolume();

	//! A pure virtual member.
	/*!
	\param mod A model pointer.
	\param mat A const matrix reference.
	*/
	virtual void ComputeData(Model* mod, Matrix& mat);

	//! A pure virtual member.
	/*!
	\param other A collision volume reference.
	\return Boolean result of intersection.
	*/
	virtual bool Intersect(CollisionVolume& other);

	//! A pure virtual member.
	/*!
	\param other A collision volume reference.
	\return Boolean result of intersection.
	*/
	virtual bool Intersect(CollisionVolumeBSphere& other);

	virtual bool Intersect(CollisionVolumeAABB& other);

	virtual bool Intersect(CollisionVolumeOBB& other);

	virtual void DebugView(const Vect& color);

protected:


};

#endif // !_CollisionVolume
