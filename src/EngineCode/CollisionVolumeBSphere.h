#ifndef _CollisionVolumeBSphere
#define _CollisionVolumeBSphere

#include "CollisionVolume.h"
#include "Align16.h"

class CollisionVolumeBSphere : public CollisionVolume, public Align16
{
public:
	//! CollisionVolumeBSphere constructor
	/*!
	\ingroup Collisions
	*/
	CollisionVolumeBSphere();
	//CollisionVolumeBSphere(const CollisionVolume&) = delete;
	//CollisionVolumeBSphere& operator=(const CollisionVolumeBSphere&) = delete;
	~CollisionVolumeBSphere();

	//! Computes the transformation data of a BSphere. Re-calculates radius and center.
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

	//! Intersection with AABB.
	/*!
	\param other A collision volume reference.
	\return Boolean result of intersection.
	*/
	bool Intersect(CollisionVolumeOBB& other) override;

	void DebugView(const Vect& color) override;

	//! Returns the center of the BSphere.
	/*!
	\return Center as a Vector.
	*/
	Vect& GetCenter();

	//! Returns the radius of the BSphere.
	/*!
	\return Radius as a Float.
	*/
	float& GetRadius();

	//! Returns the world matrix of the BSphere.
	/*!
	\return World as a Matrix.
	*/
	Matrix& GetWorld();

	Vect GetAABBMin();

	Vect GetAABBMax();

protected:

	Vect center;
	float radius;
	Matrix world;

};

#endif // !_CollisionVolumeBSphere
