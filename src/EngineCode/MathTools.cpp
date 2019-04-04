#include "MathTools.h"
#include "Collidable.h"
#include <ctime>

bool MathTools::Intersect(Collidable * col1, Collidable * col2)
{
	CollisionVolume& c1 = col1->GetCollisionVolume();
	CollisionVolume& c2 = col2->GetCollisionVolume();

	return c1.Intersect(c2);
}

Vect MathTools::FindCornerMin(Model * mod, Matrix& world)
{
	Vect* vectList = mod->getVectList();
	Vect temp;
	float minX = (vectList[0] * world).X();
	float minY = (vectList[0] * world).Y();
	float minZ = (vectList[0] * world).Z();
	for (int i = 0; i < mod->getVectNum(); i++)
	{
		temp = vectList[i] * world;
		if (temp.X() < minX)
		{
			minX = temp.X();
		}
		if (temp.Y() < minY)
		{
			minY = temp.Y();
		}
		if (temp.Z() < minZ)
		{
			minZ = temp.Z();
		}
	}
	Vect newMin = Vect(minX, minY, minZ);
	return newMin;
}

Vect MathTools::FindCornerMax(Model * mod, Matrix& world)
{
	Vect* vectList = mod->getVectList();
	Vect temp;
	float maxX = (vectList[0] * world).X();
	float maxY = (vectList[0] * world).Y();
	float maxZ = (vectList[0] * world).Z();
	for (int i = 0; i < mod->getVectNum(); i++)
	{
		temp = vectList[i] * world;
		if (temp.X() > maxX)
		{
			maxX = temp.X();
		}
		if (temp.Y() > maxY)
		{
			maxY = temp.Y();
		}
		if (temp.Z() > maxZ)
		{
			maxZ = temp.Z();
		}
	}
	Vect newMax = Vect(maxX, maxY, maxZ);
	return newMax;
}

int MathTools::GetRandomInt(int minVal, int maxVal)
{
	std::srand((unsigned int)time(0));
	int x = rand() % minVal + maxVal;
	return x;
}

float MathTools::GetRandomFloat(float minVal, float maxVal)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = maxVal - minVal;
	float r = random * diff;
	return minVal + r;
}

float MathTools::GetProjectionMax(CollisionVolumeOBB & vol, Vect & V)
{
	Vect localV = V * vol.GetOriginalWorld().getInv();
	Vect diagMax = vol.GetCornerMax() - vol.GetCenter();
	float proj = abs((localV.X() * diagMax.X())) + abs((localV.Y() * diagMax.Y())) + abs((localV.Z() * diagMax.Z()));
	return vol.GetScaleSquared() * (proj / V.mag());
}

float MathTools::GetProjectionMax(CollisionVolumeAABB & vol, Vect & V)
{
	Vect localV = V * vol.GetOriginalWorld().getInv();
	Vect diagMax = vol.GetLocalMax() - vol.GetLocalCenter();
	float proj = abs((localV.X() * diagMax.X())) + abs((localV.Y() * diagMax.Y())) + abs((localV.Z() * diagMax.Z()));
	return vol.GetScaleSquared() * (proj / V.mag());
}

bool MathTools::IntersectionTest(CollisionVolumeOBB & box1, CollisionVolumeOBB & box2, Vect & V, float d)
{
	float proj1 = GetProjectionMax(box1, V);
	float proj2 = GetProjectionMax(box2, V);
	return (d <= proj1 + proj2);
}

bool MathTools::IntersectionTest(CollisionVolumeOBB & box1, CollisionVolumeAABB & box2, Vect & V, float d)
{
	float proj1 = GetProjectionMax(box1, V);
	float proj2 = GetProjectionMax(box2, V);
	return (d <= proj1 + proj2);
}

Vect MathTools::GetMinVect(Vect & A, Vect & B)
{
	Vect temp = A;
	if (A.X() <= B.X())
	{
		temp.X() = A.X();
	}
	else
	{
		temp.X() = B.X();
	}

	if (A.Y() <= B.Y())
	{
		temp.Y() = A.Y();
	}
	else
	{
		temp.Y() = B.Y();
	}

	if (A.Z() <= B.Z())
	{
		temp.Z() = A.Z();
	}
	else
	{
		temp.Z() = B.Z();
	}
	return temp;
}

Vect MathTools::GetMaxVect(Vect & A, Vect & B)
{
	Vect temp = A;
	if (A.X() >= B.X())
	{
		temp.X() = A.X();
	}
	else
	{
		temp.X() = B.X();
	}

	if (A.Y() >= B.Y())
	{
		temp.Y() = A.Y();
	}
	else
	{
		temp.Y() = B.Y();
	}

	if (A.Z() >= B.Z())
	{
		temp.Z() = A.Z();
	}
	else
	{
		temp.Z() = B.Z();
	}
	return temp;
}

Vect MathTools::FindCenter(Vect & min, Vect & max)
{
	Vect temp = min + max;
	temp.X() = temp.X() / 2.0f;
	temp.Y() = temp.Y() / 2.0f;
	temp.Z() = temp.Z() / 2.0f;
	return temp;
}
