#include "CollisionVolumeBoundingBoxBase.h"

Vect & CollisionVolumeBoundingBoxBase::GetCornerMin()
{
	return cornerMin;
}

Vect & CollisionVolumeBoundingBoxBase::GetCornerMax()
{
	return cornerMax;
}

Matrix & CollisionVolumeBoundingBoxBase::GetWorld()
{
	return world;
}

Vect & CollisionVolumeBoundingBoxBase::GetCenter()
{
	return center;
}
