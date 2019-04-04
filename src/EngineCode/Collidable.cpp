#include "Collidable.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CollisionRegistrationCommand.h"
#include "CollisionDeregistrationCommand.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"

Collidable::Collidable()
{
	
}

Collidable::~Collidable()
{
	//delete colVolume;
}

void Collidable::Collision(Collidable *)
{
}

CollisionVolume & Collidable::GetCollisionVolume()
{
	return *colVolume;
}

void Collidable::SetColliderModel(Model * mod, CollisionType type)
{
	defaultBSphere = new CollisionVolumeBSphere();
	pColModel = mod;
	switch (type)
	{
	case(CollisionType::BSphere):
		colVolume = new CollisionVolumeBSphere();
		break;
	case(CollisionType::AABB):
		colVolume = new CollisionVolumeAABB(mod);
		break;
	case(CollisionType::OBB):
		colVolume = new CollisionVolumeOBB(mod);
		break;
	default:
		break;
	}
}

void Collidable::UpdateCollisionData(Matrix & mat)
{
	colVolume->ComputeData(pColModel, mat);
	defaultBSphere->ComputeData(pColModel, mat);
}
