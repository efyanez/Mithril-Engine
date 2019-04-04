#include "CollisionVolumeBSphere.h"
#include "MathTools.h"
#include "Visualizer.h"

CollisionVolumeBSphere::CollisionVolumeBSphere()
{
}

CollisionVolumeBSphere::~CollisionVolumeBSphere()
{
}

void CollisionVolumeBSphere::ComputeData(Model * mod, Matrix & mat)
{
	center = Vect(0, 0, 0) * world;
	radius = Vect(center - Vect(Vect(1, 0, 0) * world)).mag();
	Vect test = Vect(1, 0, 0) * world;
	Vect vBSSize = mod->getRadius() * Vect(1, 1, 1);
	Vect vBSPos = mod->getCenter();
	world = Matrix(SCALE, vBSSize) * Matrix(TRANS, vBSPos) * mat;

}

bool CollisionVolumeBSphere::Intersect(CollisionVolume & other)
{
	return other.Intersect(*this);
}

bool CollisionVolumeBSphere::Intersect(CollisionVolumeBSphere & other)
{
	return MathTools::Intersect(*this, other);
}

bool CollisionVolumeBSphere::Intersect(CollisionVolumeAABB & other)
{
	return MathTools::Intersect(other, *this);
}

bool CollisionVolumeBSphere::Intersect(CollisionVolumeOBB & other)
{
	return MathTools::Intersect(other, *this);
}

void CollisionVolumeBSphere::DebugView(const Vect & color)
{
	Visualizer::ShowSphere(*this, color);
}

Vect & CollisionVolumeBSphere::GetCenter()
{
	return center;
}

float & CollisionVolumeBSphere::GetRadius()
{
	return radius;
}

Matrix & CollisionVolumeBSphere::GetWorld()
{
	return world;
}

Vect CollisionVolumeBSphere::GetAABBMin()
{
	return Vect(center.X() - radius, center.Y() - radius, center.Z() - radius);
}

Vect CollisionVolumeBSphere::GetAABBMax()
{
	return Vect(center.X() + radius, center.Y() + radius, center.Z() + radius);
}