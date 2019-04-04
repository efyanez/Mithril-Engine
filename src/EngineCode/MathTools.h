#ifndef _MathTools
#define _MathTools

#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"
#include <cmath>
#include <cfloat>

class Collidable;
class Model;

class MathTools
{
public:

	MathTools() {};

	//! Calculates the intersection of two BSphere volumes.
	/*!
	\param sphere1 a CollisionVolumeBSphere reference.
	\param sphere2 a CollisionVolumeBSphere reference.
	\return The test results of the intersection, true or false.
	*/
	static bool Intersect(CollisionVolumeBSphere& sphere1, CollisionVolumeBSphere& sphere2)
	{
		float centerDistance = Vect(sphere2.GetCenter() - sphere1.GetCenter()).mag();
		float sum = sphere2.GetRadius() + sphere1.GetRadius();
		if (centerDistance <= sum)
		{
			return true;
		}
		return false;
	}

	static bool Intersect(CollisionVolumeAABB& box1, CollisionVolumeAABB& box2)
	{
		Vect box1Min = box1.GetCornerMin();
		Vect box1Max = box1.GetCornerMax();

		Vect box2Min = box2.GetCornerMin();
		Vect box2Max = box2.GetCornerMax();

		if (!(box1Max.X() < box2Min.X()) && !(box1Min.X() > box2Max.X()))
		{
			if (!(box1Max.Y() < box2Min.Y()) && !(box1Min.Y() > box2Max.Y()))
			{
				if (!(box1Max.Z() < box2Min.Z()) && !(box1Min.Z() > box2Max.Z()))
				{
					return true;
				}
			}
		}
		return false;
	}

	static float Clamp(float toClamp, float min, float max)
	{
		float temp;
		if (toClamp < min)
		{
			temp = min;
		}
		else if(toClamp > max)
		{
			temp = max;
		}
		else
		{
			temp = toClamp;
		}
		return temp;
	}

	static bool Intersect(CollisionVolumeAABB& box1, CollisionVolumeBSphere& sphere1)
	{
		Vect sphereCenter = sphere1.GetCenter();
		Vect min = box1.GetCornerMin();
		Vect max = box1.GetCornerMax();
		Vect temp = Vect(0, 0, 0);
		temp.X() = Clamp(sphereCenter.X(), min.X(), max.X());
		temp.Y() = Clamp(sphereCenter.Y(), min.Y(), max.Y());
		temp.Z() = Clamp(sphereCenter.Z(), min.Z(), max.Z());
		float distance = (sphereCenter - temp).mag();
		if (distance <= sphere1.GetRadius())
		{
			return true;
		}
		return false;
	}

	static bool Intersect(CollisionVolumeOBB& box1, CollisionVolumeBSphere& sphere1)
	{
		Matrix worldInverse = box1.GetOriginalWorld().getInv();
		Vect localCenter = sphere1.GetCenter() * worldInverse;
		Vect min = box1.GetCornerMin();
		Vect max = box1.GetCornerMax();

		Vect temp = Vect(0, 0, 0);
		temp.X() = Clamp(localCenter.X(), min.X(), max.X());
		temp.Y() = Clamp(localCenter.Y(), min.Y(), max.Y());
		temp.Z() = Clamp(localCenter.Z(), min.Z(), max.Z());
		temp = temp * box1.GetOriginalWorld();

		float distance = (sphere1.GetCenter() - temp).mag();

		if (distance <= sphere1.GetRadius())
		{
			return true;
		}
		return false;
	}

	static bool Intersect(CollisionVolumeOBB& box1, CollisionVolumeAABB& box2)
	{
		bool result = true;

		Matrix box1World = box1.GetOriginalWorld();
		Matrix box2World = box2.GetOriginalWorld();

		Vect box1X = box1World.get(ROW_0);
		Vect box1Y = box1World.get(ROW_1);
		Vect box1Z = box1World.get(ROW_2);

		Vect box2X = box2World.get(ROW_0);
		Vect box2Y = box2World.get(ROW_1);
		Vect box2Z = box2World.get(ROW_2);

		Vect XCrossX = box1X.cross(box2X);
		Vect XCrossY = box1X.cross(box2Y);
		Vect XCrossZ = box1X.cross(box2Z);

		Vect YCrossX = box1Y.cross(box2X);
		Vect YCrossY = box1Y.cross(box2Y);
		Vect YCrossZ = box1Y.cross(box2Z);

		Vect ZCrossX = box1Z.cross(box2X);
		Vect ZCrossY = box1Z.cross(box2Y);
		Vect ZCrossZ = box1Z.cross(box2Z);

		Vect box1Center = box1.GetCenterWorld();
		Vect box2Center = box2.GetCenter();

		float D;

		if (box1X.magSqr() <= FLT_EPSILON)
		{

		}
		else {
			D = (abs((box2Center - box1Center).dot(box1X))) / box1X.mag();
			if (!(IntersectionTest(box1, box2, box1X, D)))
			{
				result = false;
			}
		}

		if (box1Y.magSqr() <= FLT_EPSILON)
		{

		}
		else {
			D = (abs((box2Center - box1Center).dot(box1Y))) / box1Y.mag();
			if (!(IntersectionTest(box1, box2, box1Y, D)))
			{
				result = false;
			}
		}

		if (box1Z.magSqr() <= FLT_EPSILON)
		{

		}
		else {
			D = (abs((box2Center - box1Center).dot(box1Z))) / box1Z.mag();
			if (!(IntersectionTest(box1, box2, box1Z, D)))
			{
				result = false;
			}
		}

		if (box2X.magSqr() <= FLT_EPSILON)
		{

		}
		else {
			D = (abs((box2Center - box1Center).dot(box2X))) / box2X.mag();
			if (!(IntersectionTest(box1, box2, box2X, D)))
			{
				result = false;
			}
		}

		if (box2Y.magSqr() <= FLT_EPSILON)
		{

		}
		else {
			D = (abs((box2Center - box1Center).dot(box2Y))) / box2Y.mag();
			if (!(IntersectionTest(box1, box2, box2Y, D)))
			{
				result = false;
			}
		}

		if (box2Z.magSqr() <= FLT_EPSILON)
		{

		}
		else {
			D = (abs((box2Center - box1Center).dot(box2Z))) / box2Z.mag();
			if (!(IntersectionTest(box1, box2, box2Z, D)))
			{
				result = false;
			}
		}

		if (XCrossX.magSqr() <= FLT_EPSILON)
		{

		}
		else {
			D = (abs((box2Center - box1Center).dot(XCrossX))) / XCrossX.mag();
			if (!(IntersectionTest(box1, box2, XCrossX, D)))
			{
				result = false;
			}
		}

		if (XCrossY.magSqr() <= FLT_EPSILON)
		{

		}
		else {
			D = (abs((box2Center - box1Center).dot(XCrossY))) / XCrossY.mag();
			if (!(IntersectionTest(box1, box2, XCrossY, D)))
			{
				result = false;
			}
		}

		if (XCrossZ.magSqr() <= FLT_EPSILON)
		{

		}
		else {
			D = (abs((box2Center - box1Center).dot(XCrossZ))) / XCrossZ.mag();
			if (!(IntersectionTest(box1, box2, XCrossZ, D)))
			{
				result = false;
			}
		}

		if (YCrossX.magSqr() <= FLT_EPSILON)
		{

		}
		else {
			D = (abs((box2Center - box1Center).dot(YCrossX))) / YCrossX.mag();
			if (!(IntersectionTest(box1, box2, YCrossX, D)))
			{
				result = false;
			}
		}

		if (YCrossY.magSqr() <= FLT_EPSILON)
		{

		}
		else
		{
			D = (abs((box2Center - box1Center).dot(YCrossY))) / YCrossY.mag();
			if (!(IntersectionTest(box1, box2, YCrossY, D)))
			{
				result = false;
			}
		}

		if (YCrossZ.magSqr() <= FLT_EPSILON)
		{

		}
		else {
			D = (abs((box2Center - box1Center).dot(YCrossZ))) / YCrossZ.mag();
			if (!(IntersectionTest(box1, box2, YCrossZ, D)))
			{
				result = false;
			}
		}

		if (ZCrossX.magSqr() <= FLT_EPSILON)
		{

		}
		else {
			D = (abs((box2Center - box1Center).dot(ZCrossX))) / ZCrossX.mag();
			if (!(IntersectionTest(box1, box2, ZCrossX, D)))
			{
				result = false;
			}
		}

		if (ZCrossY.magSqr() <= FLT_EPSILON)
		{

		}
		else {
			D = (abs((box2Center - box1Center).dot(ZCrossY))) / ZCrossY.mag();
			if (!(IntersectionTest(box1, box2, ZCrossY, D)))
			{
				result = false;
			}
		}

		if (ZCrossZ.magSqr() <= FLT_EPSILON)
		{

		}
		else {
			D = (abs((box2Center - box1Center).dot(ZCrossZ))) / ZCrossZ.mag();
			if (!(IntersectionTest(box1, box2, ZCrossZ, D)))
			{
				result = false;
			}
		}

		return result;
	}

	static bool Intersect(CollisionVolumeOBB& box1, CollisionVolumeOBB& box2)
	{

		bool result = true;

		Matrix box1World = box1.GetWorld();
		Matrix box2World = box2.GetWorld();

		Vect box1X = box1World.get(ROW_0);
		Vect box1Y = box1World.get(ROW_1);
		Vect box1Z = box1World.get(ROW_2);

		Vect box2X = box2World.get(ROW_0);
		Vect box2Y = box2World.get(ROW_1);
		Vect box2Z = box2World.get(ROW_2);

		Vect XCrossX = box1X.cross(box2X);
		Vect XCrossY = box1X.cross(box2Y);
		Vect XCrossZ = box1X.cross(box2Z);

		Vect YCrossX = box1Y.cross(box2X);
		Vect YCrossY = box1Y.cross(box2Y);
		Vect YCrossZ = box1Y.cross(box2Z);

		Vect ZCrossX = box1Z.cross(box2X);
		Vect ZCrossY = box1Z.cross(box2Y);
		Vect ZCrossZ = box1Z.cross(box2Z);

		Vect box1Center = box1.GetCenterWorld();
		Vect box2Center = box2.GetCenterWorld();

		float D;

		if (box1X.magSqr() <= FLT_EPSILON)
		{
			
		}
		else {
			D = (abs((box2Center - box1Center).dot(box1X))) / box1X.mag();
			if (!(IntersectionTest(box1, box2, box1X, D)))
			{
				result = false;
			}
		}

		if (box1Y.magSqr() <= FLT_EPSILON)
		{
			
		}
		else {
			D = (abs((box2Center - box1Center).dot(box1Y))) / box1Y.mag();
			if (!(IntersectionTest(box1, box2, box1Y, D)))
			{
				result = false;
			}
		}

		if (box1Z.magSqr() <= FLT_EPSILON)
		{
			
		}
		else {
			D = (abs((box2Center - box1Center).dot(box1Z))) / box1Z.mag();
			if (!(IntersectionTest(box1, box2, box1Z, D)))
			{
				result = false;
			}
		}

		if (box2X.magSqr() <= FLT_EPSILON)
		{
			
		}
		else {
			D = (abs((box2Center - box1Center).dot(box2X))) / box2X.mag();
			if (!(IntersectionTest(box1, box2, box2X, D)))
			{
				result = false;
			}
		}

		if (box2Y.magSqr() <= FLT_EPSILON)
		{
			
		}
		else {
			D = (abs((box2Center - box1Center).dot(box2Y))) / box2Y.mag();
			if (!(IntersectionTest(box1, box2, box2Y, D)))
			{
				result = false;
			}
		}

		if (box2Z.magSqr() <= FLT_EPSILON)
		{
			
		}
		else {
			D = (abs((box2Center - box1Center).dot(box2Z))) / box2Z.mag();
			if (!(IntersectionTest(box1, box2, box2Z, D)))
			{
				result = false;
			}
		}

		if (XCrossX.magSqr() <= FLT_EPSILON)
		{
			
		}
		else {
			D = (abs((box2Center - box1Center).dot(XCrossX))) / XCrossX.mag();
			if (!(IntersectionTest(box1, box2, XCrossX, D)))
			{
				result = false;
			}
		}

		if (XCrossY.magSqr() <= FLT_EPSILON)
		{
			
		}
		else {
			D = (abs((box2Center - box1Center).dot(XCrossY))) / XCrossY.mag();
			if (!(IntersectionTest(box1, box2, XCrossY, D)))
			{
				result = false;
			}
		}

		if (XCrossZ.magSqr() <= FLT_EPSILON)
		{
			
		}
		else {
			D = (abs((box2Center - box1Center).dot(XCrossZ))) / XCrossZ.mag();
			if (!(IntersectionTest(box1, box2, XCrossZ, D)))
			{
				result = false;
			}
		}

		if (YCrossX.magSqr() <= FLT_EPSILON)
		{
			
		}
		else {
			D = (abs((box2Center - box1Center).dot(YCrossX))) / YCrossX.mag();
			if (!(IntersectionTest(box1, box2, YCrossX, D)))
			{
				result = false;
			}
		}

		if (YCrossY.magSqr() <= FLT_EPSILON)
		{
			
		}
		else 
		{
			D = (abs((box2Center - box1Center).dot(YCrossY))) / YCrossY.mag();
			if (!(IntersectionTest(box1, box2, YCrossY, D)))
			{
				result = false;
			}
		}

		if (YCrossZ.magSqr() <= FLT_EPSILON)
		{
			
		}
		else {
			D = (abs((box2Center - box1Center).dot(YCrossZ))) / YCrossZ.mag();
			if (!(IntersectionTest(box1, box2, YCrossZ, D)))
			{
				result = false;
			}
		}

		if (ZCrossX.magSqr() <= FLT_EPSILON)
		{
			
		}
		else {
			D = (abs((box2Center - box1Center).dot(ZCrossX))) / ZCrossX.mag();
			if (!(IntersectionTest(box1, box2, ZCrossX, D)))
			{
				result = false;
			}
		}

		if (ZCrossY.magSqr() <= FLT_EPSILON)
		{
			
		}
		else {
			D = (abs((box2Center - box1Center).dot(ZCrossY))) / ZCrossY.mag();
			if (!(IntersectionTest(box1, box2, ZCrossY, D)))
			{
				result = false;
			}
		}

		if (ZCrossZ.magSqr() <= FLT_EPSILON)
		{
			
		}
		else {
			D = (abs((box2Center - box1Center).dot(ZCrossZ))) / ZCrossZ.mag();
			if (!(IntersectionTest(box1, box2, ZCrossZ, D)))
			{
				result = false;
			}
		}

		return result;
	}

	static bool Intersect(Collidable* col1, Collidable* col2);

	static Vect FindCornerMin(Model* mod, Matrix& world);
	static Vect FindCornerMax(Model* mod, Matrix& world);

	static int GetRandomInt(int minVal, int maxVal);
	static float GetRandomFloat(float minVal, float maxVal);
	static float GetProjectionMax(CollisionVolumeOBB& vol, Vect& V);
	static float GetProjectionMax(CollisionVolumeAABB& vol, Vect& V);
	static bool IntersectionTest(CollisionVolumeOBB & box1, CollisionVolumeOBB & box2, Vect & V, float d);
	static bool IntersectionTest(CollisionVolumeOBB & box1, CollisionVolumeAABB & box2, Vect & V, float d);

	static Vect GetMinVect(Vect & A, Vect & B);
	static Vect GetMaxVect(Vect & A, Vect & B);

	static Vect FindCenter(Vect& min, Vect& max);

	static Vect Lerp(Vect & A, Vect & B, float t)
	{
		float newX = (1 - t) * A.X() + t * B.X();
		float newY = (1 - t) * A.Y() + t * B.Y();
		float newZ = (1 - t) * A.Z() + t * B.Z();
		return Vect(newX, newY, newZ);
	}
};



#endif // !_MathTools
