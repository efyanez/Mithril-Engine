#ifndef _Updatable
#define _Updatable

#include "GameObject.h"
#include "UpdatableManager.h"

class UpdateRegistrationCommand;
class UpdateDeregistrationCommand;

class Updatable : public GameObject
{
public:
	Updatable();
	~Updatable();
	Updatable(const Updatable&) = delete;
	Updatable& operator=(const Updatable&) = delete;


	//! Submit the object for Update registration
	/*!
	\ingroup Update
	\par Example:
	\code
	void Ship::Ship()
	{
		//In order to be updated, it needs to be submitted
		SubmitUpdateRegistration();
	}
	\endcode
	*/
	void SubmitUpdateRegistration();

	//! Submit the object for Draw registration
	/*!
	\ingroup Update
	\par Example:
	\code
	void Ship::~Ship()
	{
		//Must deregister update upon destruction
		SubmitUpdateDeregistration();
	}
	\endcode
	*/
	void SubmitUpdateDeregistration();

	UpdatableManager::StorageListRef myRef;

	friend class UpdatableManager;
	friend class UpdateRegistrationCommand;
	friend class UpdateDeregistrationCommand;

private:
	UpdateRegistrationCommand* regCmd;
	UpdateDeregistrationCommand* dregCmd;

	void SetIterator(UpdatableManager::StorageListRef ref);
	UpdatableManager::StorageListRef GetIterator();

	//! Everything in Update() happens once per frame
	/*!
	\ingroup Update
	\par Example:
	\code
	void Ship::Update()
	{
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
	{
	ShipPos += Vect(0, 0, 1) * ShipRot * ShipTransSpeed;
	}
	}
	\endcode
	*/
	virtual void Update() {};

	void SceneRegistration();
	void SceneDeregistration();

	enum class RegistrationState
	{
		CURRENTLY_DEREGISTERED,
		PENDING_REGISTRATION,
		CURRENTLY_REGISTERED,
		PENDING_DEREGISTRATION
	};

	RegistrationState currState;
};

#endif // !_Updatable
