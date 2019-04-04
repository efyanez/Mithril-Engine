#ifndef _Drawable
#define _Drawable

#include "GameObject.h"
#include "DrawableManager.h"

class DrawRegistrationCommand;
class DrawDeregistrationCommand;

class Drawable : public GameObject
{
public:
	Drawable();
	virtual ~Drawable();
	Drawable(const Drawable&) = delete;
	Drawable& operator=(const Drawable&) = delete;

	//! Submit the object for Draw registration
	/*!
	\par Example:
	\code
	void Ship::Ship()
	{
		//In order to be drawn, it needs to be submitted
		SubmitDrawRegistration();
	}
	\endcode
	*/
	void SubmitDrawRegistration();

	//! Submit the object for Draw deregistration
	/*!
	\par Example:
	\code
	void Ship::~Ship()
	{
		//Needs to be submitted for deregistration upon destruction
		SubmitDrawRegistration();
	}
	\endcode
	*/
	void SubmitDrawDeregistration();

	DrawableManager::StorageListRef myRef;

	friend class DrawableManager;
	friend class DrawRegistrationCommand;
	friend class DrawDeregistrationCommand;

private:
	DrawRegistrationCommand* regCmd;
	DrawDeregistrationCommand* dregCmd;

	void SetIterator(DrawableManager::StorageListRef ref);
	DrawableManager::StorageListRef GetIterator();

	//! Everything in Draw() happens once per frame, after Updatable::Update()
	/*!
	\ingroup Draw
	\par Example:
	\code
	void Ship::Draw()
	{
	pGObj_ShipLight->Render(SceneManager::GetCurrentScene()->GetCamManager()->GetCurrentCamera());
	}
	\endcode
	*/
	virtual void Draw() {};
	virtual void Draw2D() {};

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

#endif // !_Drawable
