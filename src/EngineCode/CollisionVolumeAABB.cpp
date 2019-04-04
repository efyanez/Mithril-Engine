#include "CollisionVolumeAABB.h"
#include "MathTools.h"
#include "Visualizer.h"
#include "ColorLibrary.h"

CollisionVolumeAABB::CollisionVolumeAABB(Model* mod)
{
	cornerMin = Vect(0, 0, 0);
	cornerMax = Vect(0, 0, 0);
	center = Vect(0, 0, 0);
	localCornerMin = mod->getMinAABB();
	localCornerMax = mod->getMaxAABB();
	halfDiagonal = (localCornerMax - localCornerMin) * .5f;
	localCenter = MathTools::FindCenter(localCornerMin, localCornerMax);
}

CollisionVolumeAABB::~CollisionVolumeAABB()
{
}

void CollisionVolumeAABB::ComputeData(Model * mod, Matrix & mat)
{
	cornerMin = MathTools::FindCornerMin(mod, mat);
	cornerMax = MathTools::FindCornerMax(mod, mat);
	center = MathTools::FindCenter(cornerMin, cornerMax);

	Matrix scale = Matrix(SCALE, (cornerMin - cornerMax));
	Matrix trans = Matrix(TRANS, center);
	world = scale * trans;
	centerWorld = (localCornerMin + halfDiagonal) * world;
	scaleSquared = mat.get(MatrixRowType::ROW_0).magSqr();
	originalWorld = mat;
}

void CollisionVolumeAABB::ComputeData(Vect & min, Vect & max)
{
	cornerMin = min;
	cornerMax = max;
	center = MathTools::FindCenter(cornerMin, cornerMax);

	Matrix scale = Matrix(SCALE, (cornerMin - cornerMax));
	Matrix trans = Matrix(TRANS, center);
	world = scale * trans;
	localCornerMin = cornerMin * world.getInv();
	localCornerMax = cornerMin * world.getInv();
	centerWorld = (localCornerMin + halfDiagonal) * world;
	scaleSquared = world.get(MatrixRowType::ROW_0).magSqr();
	originalWorld = world;
}

bool CollisionVolumeAABB::Intersect(CollisionVolume & other)
{
	return other.Intersect(*this);
}

bool CollisionVolumeAABB::Intersect(CollisionVolumeBSphere & other)
{
	return MathTools::Intersect(*this, other);
}

bool CollisionVolumeAABB::Intersect(CollisionVolumeAABB & other)
{
	return MathTools::Intersect(*this, other);
}

bool CollisionVolumeAABB::Intersect(CollisionVolumeOBB & other)
{
	return MathTools::Intersect(other, *this);
}

void CollisionVolumeAABB::DebugView(const Vect & color)
{
	Visualizer::ShowBox(*this, color);
}

Vect CollisionVolumeAABB::GetHalfDiagonal()
{
	return halfDiagonal;
}

float CollisionVolumeAABB::GetScaleSquared()
{
	return scaleSquared;
}

Vect CollisionVolumeAABB::GetLocalMin()
{
	return localCornerMin;
}

Vect CollisionVolumeAABB::GetLocalMax()
{
	return localCornerMax;
}

Vect CollisionVolumeAABB::GetLocalCenter()
{
	return localCenter;
}

Vect CollisionVolumeAABB::GetCenterWorld()
{
	return centerWorld;
}

Matrix CollisionVolumeAABB::GetOriginalWorld()
{
	return originalWorld;
}

void CollisionVolumeAABB::SetMin(Vect & m)
{ 
	cornerMin = m;
}

void CollisionVolumeAABB::SetMax(Vect & m)
{
	cornerMax = m;
}

void CollisionVolumeAABB::SetWorld(Matrix & m)
{
	world = m;
}
