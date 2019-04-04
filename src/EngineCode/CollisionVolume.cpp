#include "CollisionVolume.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"

CollisionVolume::CollisionVolume()
{
}

CollisionVolume::~CollisionVolume()
{
}

void CollisionVolume::ComputeData(Model * mod, Matrix & mat)
{
	(void)mod;
	(void)mat;
}

bool CollisionVolume::Intersect(CollisionVolume & other)
{
	(void)other;
	return false;
}

bool CollisionVolume::Intersect(CollisionVolumeBSphere & other)
{
	(void)other;
	return false;
}

bool CollisionVolume::Intersect(CollisionVolumeAABB & other)
{
	(void)other;
	return false;
}

bool CollisionVolume::Intersect(CollisionVolumeOBB & other)
{
	(void)other;
	return false;
}

void CollisionVolume::DebugView(const Vect & color)
{
	(void)color;
}

