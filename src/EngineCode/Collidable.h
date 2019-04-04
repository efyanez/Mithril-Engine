#ifndef _Collidable
#define _Collidable

#include "GameObject.h"
#include "CollisionManager.h"
#include "CollidableGroup.h"
#include "CollisionRegistrationCommand.h"
#include "CollisionDeregistrationCommand.h"
#include "CollisionVolume.h"
#include "CollisionVolumeAABB.h"


class Model;
class Matrix;

class Collidable : public GameObject
{
public:

	Collidable();
	virtual ~Collidable();
	Collidable(const Collidable&) = delete;
	Collidable& operator=(const Collidable&) = delete;

	enum class CollisionType
	{
		BSphere,
		AABB,
		OBB
	};

	//! Called when a collision with <C> is detected
	/*!
	\ingroup Collisions
	\par Example:
	\code
	void Ship::Collision(Enemy*)
	{
	DebugMsg::out("Colliding with Enemy!\n");
	ShipHealth -= 10;
	}
	\endcode
	*/
	virtual void Collision(Collidable*);

	virtual void TerrainCollision() {};

	virtual void TerrainCollision(CollisionVolumeAABB& cellAABB) { (void)cellAABB; };

	//! Submit the object for Collision registration
	/*!
	\ingroup Collisions
	\par Example:
	\code
	void Ship::~Ship()
	{
	//In order to be collidable, it needs to be submitted
	SubmitCollisionRegistration<Ship>(this);
	}
	\endcode
	*/
	template <typename T>
	void Collidable::SubmitCollisionRegistration(T* col)
	{
		SceneManager::GetCurrentScene()->SubmitCommand(new CollisionRegistrationCommand<T>(col));
	}

	//! Submit the object for Collision deregistration
	/*!
	\ingroup Collisions
	\par Example:
	\code
	void Ship::~Ship()
	{
	//Needs to be submitted for deregistration upon destruction
	SubmitCollisionDeregistration<Ship>(this);
	}
	\endcode
	*/
	template <typename T>
	void Collidable::SubmitCollisionDeregistration(T* col)
	{
		SceneManager::GetCurrentScene()->SubmitCommand(new CollisionDeregistrationCommand<T>(col));
	}

	CollisionVolume& GetCollisionVolume();
	//! Sets the collider model for the object
	/*!
	\ingroup Collisions
	\par Example:
	\code
	void Ship::Ship()
	{
	//Needs a model for collision, pBoundingSphere is a model pointer
	SetColliderModel(pBoundingSphere);
	}
	\endcode
	*/
	void SetColliderModel(Model* mod, CollisionType type);

	//! Update the world data of the collider model
	/*!
	\ingroup Collisions
	\par Example:
	\code
	void Ship::Update()
	{
	//Needs to be updated to follow the graphic object of the object
	world = ShipScale * ShipRot * ShipTrans;
	UpdateCollisionData(world);
	}
	\endcode
	*/
	void UpdateCollisionData(Matrix& mat);

	//DrawableManager::StorageListRef myRef;

	friend class CollidableManager;

	CollisionVolumeBSphere* GetDefaultBSphere() { return defaultBSphere; }

private:
	//template<typename C>
	//CollisionRegistrationCommand<C>* regCmd;
	//template<typename C>
	//CollisionDeregistrationCommand<C>* dregCmd;

	//void SetIterator(DrawableManager::StorageListRef ref);
	//DrawableManager::StorageListRef GetIterator();

	template <typename C>
	void CollisionRegistration(C* c)
	{
		CollidableGroup<C>::Register(c);
	}

	template <typename C>
	void CollisionDeregistration(C* c)
	{
		CollidableGroup<C>::Deregister(c);
	}

	enum class RegistrationState
	{
		CURRENTLY_DEREGISTERED,
		PENDING_REGISTRATION,
		CURRENTLY_REGISTERED,
		PENDING_DEREGISTRATION
	};

	RegistrationState currState;

	CollisionVolumeBSphere* defaultBSphere;
	CollisionVolume* colVolume;
	Model* pColModel;

};

#endif // !_Collidable
