#ifndef _Inputable
#define _Inputable

#include "GameObject.h"
#include "AzulCore.h"

class KeyEventRegistrationCommand;
class KeyEventDeregistrationCommand;

class Inputable : public GameObject
{
public:
	Inputable();
	virtual ~Inputable() {};
	Inputable(const Inputable&) = delete;
	Inputable& operator=(const Inputable&) = delete;

	enum EVENT_TYPE
	{
		KEY_PRESS,
		KEY_RELEASE
	};

	//! Submit the object for Alarm registration
	/*!
	\ingroup Input
	\par Example:
	\code
	void Ship::Ship()
	{
	//Needs to be submitted for input with AZUL_KEY and event type
	SubmitKeyEventRegistration(AZUL_KEY::KEY_T, Inputable::EVENT_TYPE::KEY_PRESS);
	SubmitKeyEventRegistration(AZUL_KEY::KEY_R, Inputable::EVENT_TYPE::KEY_RELEASE);
	}
	\endcode
	*/
	virtual void SubmitKeyEventRegistration(AZUL_KEY k, EVENT_TYPE type);

	//! Submit the object for Alarm deregistration
	/*!
	\ingroup Input
	\par Example:
	\code
	void Ship::~Ship()
	{
	//Needs to be submitted for input deregistration with AZUL_KEY and event type
	SubmitKeyEventDeregistration(AZUL_KEY::KEY_T, Inputable::EVENT_TYPE::KEY_PRESS);
	SubmitKeyEventDeregistration(AZUL_KEY::KEY_R, Inputable::EVENT_TYPE::KEY_RELEASE);
	}
	\endcode
	*/
	virtual void SubmitKeyEventDeregistration(AZUL_KEY k, EVENT_TYPE type);

	//! DO NOT CALL DIRECTLY
	virtual void KeyEventRegistration(AZUL_KEY k, EVENT_TYPE type);

	//! DO NOT CALL DIRECTLY
	virtual void KeyEventDeregistration(AZUL_KEY k, EVENT_TYPE type);

	//! User defines what happens when a specific key is pressed
	/*!
	\ingroup Input
	\par Example:
	\code
	void Ship::OnKeyPress(AZUL_KEY k)
	{
		switch (k)
		{
			case(AZUL_KEY::KEY_T):
				DebugMsg::out("T key pressed!\n");
				BulletFactory::CreateBullet(this);
				break;
			default:
				break;
	}
	}
	\endcode
	*/
	virtual void OnKeyPress(AZUL_KEY k);

	//! User defines what happens when a specific key is released
	/*!
	\ingroup Input
	\par Example:
	\code
	void Ship::OnKeyRelease(AZUL_KEY k)
	{
		switch (k)
		{
			case(AZUL_KEY::KEY_R):
				DebugMsg::out("R key released!\n");
				SceneManager::SetNextScene(new SecondScene());
				break;
			default:
				break;
	}
	}
	\endcode
	*/
	virtual void OnKeyRelease(AZUL_KEY k);

private:
	KeyEventRegistrationCommand* regCmd;
	KeyEventDeregistrationCommand* deregCmd;
};

#endif // !_Inputable
