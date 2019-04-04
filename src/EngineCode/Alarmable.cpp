#include "Alarmable.h"
#include "Scene.h"
#include "SceneManager.h"
#include "AlarmRegistrationCommand.h"
#include "AlarmDeregistrationCommand.h"

Alarmable::Alarmable()
{
	for (int i = 0; i < numAlarms; i++)
	{
		RegData[i].regCmd = new AlarmRegistrationCommand(this, (AlarmEnum::AlarmID)i);
		RegData[i].dregCmd = new AlarmDeregistrationCommand(this, (AlarmEnum::AlarmID)i);
		RegData[i].currState = RegistrationState::CURRENTLY_DEREGISTERED;
		RegData[i].myID = (AlarmEnum::AlarmID)i;
		RegData[i].remainingTime = 0.0f;
	}
}

void Alarmable::SceneRegistration(float t, AlarmEnum::AlarmID alID)
{
	assert(RegData[alID].currState == RegistrationState::PENDING_REGISTRATION);
	SceneManager::GetCurrentScene()->Register(t, this, alID);
	RegData[alID].currState = RegistrationState::CURRENTLY_REGISTERED;
}

void Alarmable::SceneDeregistration(AlarmEnum::AlarmID alID)
{
	assert(RegData[alID].currState == RegistrationState::PENDING_DEREGISTRATION);
	SceneManager::GetCurrentScene()->Deregister(this, alID);
	RegData[alID].currState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Alarmable::SubmitAlarmRegistration(float t, AlarmEnum::AlarmID alID)
{
	assert(RegData[alID].currState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneManager::GetCurrentScene()->SubmitCommand(RegData[alID].regCmd);
	RegData[alID].time = t;
	RegData[alID].remainingTime = t;
	RegData[alID].currState = RegistrationState::PENDING_REGISTRATION;
}

void Alarmable::SubmitAlarmDeregistration(AlarmEnum::AlarmID alID)
{
	if (RegData[alID].currState == RegistrationState::CURRENTLY_DEREGISTERED) return;
	assert(RegData[alID].currState == RegistrationState::CURRENTLY_REGISTERED);
	SceneManager::GetCurrentScene()->SubmitCommand(RegData[alID].dregCmd);
	RegData[alID].currState = RegistrationState::PENDING_DEREGISTRATION;
}

void Alarmable::SetTime(AlarmEnum::AlarmID alID, float newTime)
{
	RegData[alID].time = newTime;
}

void Alarmable::TriggerAlarm(AlarmEnum::AlarmID alID)
{
	switch (alID) {
		case(0):
			RegData[alID].currState = RegistrationState::CURRENTLY_DEREGISTERED;
			this->Alarm0();
			break;
		case(1):
			RegData[alID].currState = RegistrationState::CURRENTLY_DEREGISTERED;
			this->Alarm1();
			break;
		case(2):
			RegData[alID].currState = RegistrationState::CURRENTLY_DEREGISTERED;
			this->Alarm2();
			break;
		default:
			break;
	}
}

void Alarmable::AddTime(AlarmEnum::AlarmID ID, float time)
{
	RegData[ID].time = time;
}

void Alarmable::SetIterator(AlarmableManager::StorageListRef ref, AlarmEnum::AlarmID alID)
{
	RegData[alID].myRef = ref;
}

AlarmableManager::StorageListRef Alarmable::GetIterator(AlarmEnum::AlarmID alID)
{
	return RegData[alID].myRef;
}
