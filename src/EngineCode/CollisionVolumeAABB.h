#ifndef _CollisionVolumeAABB
#define _CollisionVolumeAABB

#include "CollisionVolumeBoundingBoxBase.h"
#include "Align16.h"

class CollisionVolumeAABB : public CollisionVolumeBoundingBoxBase, public Align16
{
public:

	CollisionVolumeAABB() = default;

	//! CollisionVolumeAABB constructor
	/*!
	\ingroup Collisions
	*/
	CollisionVolumeAABB(Model* mod);
	~CollisionVolumeAABB();

	//! Computes the transformation data of an AABB. Re-calculates corners and center.
	/*!
	\param mod A model pointer.
	\param mat A const matrix reference.
	*/
	void ComputeData(Model* mod, Matrix& mat) override;

	void ComputeData(Vect & min, Vect & max);

	//! Intersection with genertic Collision Volume.
	/*!
	\param other A collision volume reference.
	\return Boolean result of intersection.
	*/
	bool Intersect(CollisionVolume& other) override;

	//! Intersection with BSphere.
	/*!
	\param other A collision volume reference.
	\return Boolean result of intersection.
	*/
	bool Intersect(CollisionVolumeBSphere& other) override;

	bool Intersect(CollisionVolumeAABB& other) override;

	bool Intersect(CollisionVolumeOBB& other) override;

	void DebugView(const Vect& color) override;

	Vect GetHalfDiagonal();

	float GetScaleSquared();

	Vect GetLocalMin();

	Vect GetLocalMax();

	Vect GetLocalCenter();

	Vect GetCenterWorld();

	Matrix GetOriginalWorld();

	void SetMin(Vect & m);

	void SetMax(Vect & m);

	void SetWorld(Matrix & m);

private:
	Vect localCornerMin;
	Vect localCornerMax;
	Vect localCenter;
	Vect halfDiagonal;
	Vect centerWorld;
	Matrix originalWorld;
	float scaleSquared;

};

#endif // !_CollisionVolumeAABB
