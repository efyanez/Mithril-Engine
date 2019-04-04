#ifndef _Alarmable
#define _Alarmable

#include "GameObject.h"
#include "AlarmableManager.h"
#include "AlarmEnum.h"

class AlarmRegistrationCommand;
class AlarmDeregistrationCommand;

class Alarmable : public GameObject
{
public:
	Alarmable();
	virtual ~Alarmable() {};
	Alarmable(const Alarmable&) = delete;
	Alarmable& operator=(const Alarmable&) = delete;

	//! Submit the object for Alarm registration
	/*!
	\ingroup Alarms
	\par Example:
	\code
	void Ship::Ship()
	{
	//Needs to be submitted for alarm with time and alarm ID
	SubmitAlarmRegistration(2.0f, AlarmEnum::AlarmID::ALARM_0);
	}
	\endcode
	*/
	void SubmitAlarmRegistration(float t, AlarmEnum::AlarmID alID);

	//! Submit the object for Alarm deregistration
	/*!
	\ingroup Alarms
	\par Example:
	\code
	void Ship::~Ship()
	{
	//NOTE: ALARMS ARE ALREADY DEREGISTERED AFTER THEY ARE TRIGGERED.
	//Needs to be submitted for alarm with alarm ID
	SubmitAlarmDeregistration(AlarmEnum::AlarmID::ALARM_0);
	}
	\endcode
	*/
	void SubmitAlarmDeregistration(AlarmEnum::AlarmID alID);

	//! Return the specified alarm's time (in seconds).
	/*!
	\ingroup Alarms
	\param alID An AlarmEnum::AlarmID type.
	*/
	float GetTime(AlarmEnum::AlarmID alID) { return RegData[alID].time; }

	//! Return the specified alarm's remaining time (in seconds).
	/*!
	\ingroup Alarms
	\param alID An AlarmEnum::AlarmID type.
	*/
	float GetRemainingTime(AlarmEnum::AlarmID alID) { return RegData[alID].remainingTime; }

	void SetTime(AlarmEnum::AlarmID alID, float newTime);

	//AlarmableManager::StorageListRef myRef;

	friend class AlarmableManager;
	friend class AlarmRegistrationCommand;
	friend class AlarmDeregistrationCommand;

private:
	//! Defines what happens when Alarm 0 is triggered
	/*!
	\ingroup Alarms
	\par Example:
	\code
	void Ship::Alarm0()
	{
	ShipPos += Vect(0, 0, 2) * ShipRot * ShipTransSpeed;
	SubmitAlarmRegistration(2.0f, AlarmEnum::AlarmID::Alarm_0);
	}
	\endcode
	*/
	virtual void Alarm0() {};

	//! Defines what happens when Alarm 1 is triggered
	/*!
	\ingroup Alarms
	\par Example:
	\code
	void Ship::Alarm1()
	{
	BulletFactory::CreateBullet(this);
	}
	\endcode
	*/
	virtual void Alarm1() {};

	//! Defines what happens when Alarm 2 is triggered
	/*!
	\ingroup Alarms
	\par Example:
	\code
	void Ship::Alarm2()
	{
	KeyEventDeregistration(AZUL_KEY::KEY_T, EVENT_TYPE::KEY_PRESS);
	}
	\endcode
	*/
	virtual void Alarm2() {};

	virtual void TriggerAlarm(AlarmEnum::AlarmID ID);

	float remainingTime;
	void AddTime(AlarmEnum::AlarmID ID, float time);

	const int numAlarms = 3;

	void SceneRegistration(float t, AlarmEnum::AlarmID alID);
	void SceneDeregistration(AlarmEnum::AlarmID alID);


	void SetIterator(AlarmableManager::StorageListRef ref, AlarmEnum::AlarmID alID);
	AlarmableManager::StorageListRef GetIterator(AlarmEnum::AlarmID alID);

	enum class RegistrationState
	{
		CURRENTLY_DEREGISTERED,
		PENDING_REGISTRATION,
		CURRENTLY_REGISTERED,
		PENDING_DEREGISTRATION
	};

	
	struct RegistrationData
	{
		AlarmableManager::StorageListRef myRef;
		RegistrationState currState;
		AlarmRegistrationCommand* regCmd;
		AlarmDeregistrationCommand* dregCmd;
		AlarmEnum::AlarmID myID;
		float time;
		float remainingTime;
	};

	RegistrationData RegData[3];
	
};

#endif // !_Alarmable
