#include "AlarmableManager.h"
#include "Alarmable.h"
#include "TimeManager.h"

AlarmableManager::~AlarmableManager()
{
	//TimelineMap.clear();
	DebugMsg::out("ALARMABLE MANAGER TERMINATED\n");
}

void AlarmableManager::Register(float t, Alarmable * al, AlarmEnum::AlarmID ID)
{
	AlarmEvent newEvent;
	newEvent.first = ID;
	newEvent.second = al;
	TimelineMapPair tmPair;
	tmPair.first = TimeManager::GetFrameTime() + t;
	tmPair.second = newEvent;
	ref = TimelineMap.insert(tmPair);
	al->SetIterator(ref, ID);
	al->AddTime(ID, TimeManager::GetFrameTime() + t);
}

void AlarmableManager::Deregister(Alarmable * al, AlarmEnum::AlarmID ID)
{
	TimelineMap.erase(al->GetIterator(ID));
}

void AlarmableManager::AddTime(float time, Alarmable * al, AlarmEnum::AlarmID ID)
{
	std::multimap<float, AlarmEvent>::iterator temp = TimelineMap.begin();

	std::multimap<float, AlarmEvent>::iterator it = TimelineMap.begin();

	while (it != TimelineMap.end())
	{
		if ((it->second).second == al && (it->second).first == ID)
		{
			(it->second).second->AddTime(ID, (it->second).second->GetRemainingTime(ID) + time);
		}
		it++;
	}
}

float AlarmableManager::GetRemainingTime(Alarmable * al, AlarmEnum::AlarmID ID)
{
	std::multimap<float, AlarmEvent>::iterator temp = TimelineMap.begin();

	std::multimap<float, AlarmEvent>::iterator it = TimelineMap.begin();

	while (it != TimelineMap.end())
	{
		if ((it->second).second == al && (it->second).first == ID)
		{
			return it->first - TimeManager::GetTimeSeconds();
		}
		it++;
	}
	return 0.0f;
}

void AlarmableManager::ProcessElements()
{
	std::multimap<float, AlarmEvent>::iterator temp = TimelineMap.begin();

	std::multimap<float, AlarmEvent>::iterator it = TimelineMap.begin();

	//Compare to "soonest" alarm, then called TriggerAlarm();
	while (it != TimelineMap.end() && it->first <= TimeManager::GetFrameTime())
	{
		temp = it;
		++temp;
		(it->second).second->TriggerAlarm((it->second).first);
		TimelineMap.erase(it);
		it = temp;
	}
}
