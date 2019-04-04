#ifndef _CollisionVolumeBoundingBoxBase
#define _CollisionVolumeBoundingBoxBase

#include "CollisionVolume.h"

class CollisionVolumeBoundingBoxBase: public CollisionVolume
{
public:
	CollisionVolumeBoundingBoxBase() = default;
	~CollisionVolumeBoundingBoxBase() = default;
	CollisionVolumeBoundingBoxBase(const CollisionVolumeBoundingBoxBase&) = default;
	CollisionVolumeBoundingBoxBase & operator=(const CollisionVolumeBoundingBoxBase&) = default;

	//! Returns the center of the BSphere.
	/*!
	\return Center as a Vector.
	*/
	Vect& GetCornerMin();

	//! Returns the radius of the BSphere.
	/*!
	\return Radius as a Float.
	*/
	Vect& GetCornerMax();

	//! Returns the world matrix of the BSphere.
	/*!
	\return World as a Matrix.
	*/
	Matrix& GetWorld();

	Vect& GetCenter();


protected:
	Vect cornerMin;
	Vect cornerMax;
	Vect center;
	Matrix world;
};

#endif // !_CollisionVolumeBoundingBoxBase
