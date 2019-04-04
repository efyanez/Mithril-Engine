#include "CollisionVolumeOBB.h"
#include "MathTools.h"
#include "Visualizer.h"

CollisionVolumeOBB::CollisionVolumeOBB(Model* mod)
{
	center = Vect(0, 0, 0);
	cornerMin = mod->getMinAABB();
	cornerMax = mod->getMaxAABB();
	halfDiagonal = (cornerMax - cornerMin) * .5f;
	center = MathTools::FindCenter(cornerMin, cornerMax);
}

CollisionVolumeOBB::~CollisionVolumeOBB()
{
}

void CollisionVolumeOBB::ComputeData(Model * mod, Matrix & mat)
{
	(void)mod;
	centerWorld = (cornerMin + halfDiagonal) * mat;

	

	Matrix scale = Matrix(SCALE, (cornerMin - cornerMax));
	Matrix trans = Matrix(TRANS, center);
	world = scale * trans * mat;

	scaleSquared = mat.get(MatrixRowType::ROW_0).magSqr();

	originalWorld = mat;
}

bool CollisionVolumeOBB::Intersect(CollisionVolume & other)
{
	return other.Intersect(*this);
}

bool CollisionVolumeOBB::Intersect(CollisionVolumeBSphere & other)
{
	return MathTools::Intersect(*this, other);
}

bool CollisionVolumeOBB::Intersect(CollisionVolumeAABB & other)
{
	return MathTools::Intersect(*this, other);
}

bool CollisionVolumeOBB::Intersect(CollisionVolumeOBB & other)
{
	return MathTools::Intersect(*this, other);
}

void CollisionVolumeOBB::DebugView(const Vect & color)
{
	Visualizer::ShowBox(*this, color);
}

Matrix CollisionVolumeOBB::GetOriginalWorld()
{
	return originalWorld;
}

Vect CollisionVolumeOBB::GetHalfDiagonal()
{
	return halfDiagonal;
}

Vect CollisionVolumeOBB::GetCenterWorld()
{
	return centerWorld;
}

float CollisionVolumeOBB::GetScaleSquared()
{
	return scaleSquared;
}
