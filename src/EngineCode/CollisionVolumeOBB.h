#ifndef _CollisionVolumeOBB
#define _CollisionVolumeOBB

#include "CollisionVolumeBoundingBoxBase.h"
#include "Align16.h"

class CollisionVolumeOBB : public CollisionVolumeBoundingBoxBase, public Align16
{
public:
	//! CollisionVolumeAABB constructor
	/*!
	\ingroup Collisions
	*/
	CollisionVolumeOBB(Model* mod);
	~CollisionVolumeOBB();

	//! Computes the transformation data of an AABB. Re-calculates corners and center.
	/*!
	\param mod A model pointer.
	\param mat A const matrix reference.
	*/
	void ComputeData(Model* mod, Matrix& mat) override;

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

	//! Intersection with AABB.
	/*!
	\param other A collision volume reference.
	\return Boolean result of intersection.
	*/
	bool Intersect(CollisionVolumeAABB& other) override;

	//! Intersection with OBB.
	/*!
	\param other A collision volume reference.
	\return Boolean result of intersection.
	*/
	bool Intersect(CollisionVolumeOBB& other) override;

	//! Enables the debug view of the OBB
	void DebugView(const Vect& color) override;

	//! Returns the world space matrix
	/*!
	\return Matrix The original world matrix.
	*/
	Matrix GetOriginalWorld();

	//! Returns the half-diagonal in local space
	/*!
	\return Vect The half-diagonal in local space.
	*/
	Vect GetHalfDiagonal();

	//! Returns the center of the world matrix in world space
	/*!
	\return Vect The center of the world matrix in world space.
	*/
	Vect GetCenterWorld();

	//! Returns the scale square of the OBB
	/*!
	\return float The scale square of the OBB.
	*/
	float GetScaleSquared();

private:
	Matrix originalWorld;
	Vect halfDiagonal;
	Vect centerWorld;
	float scaleSquared;

};

#endif // !_CollisionVolumeOBB
