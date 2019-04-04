#ifndef _AlarmableManager
#define _AlarmableManager

#include <map>
#include "AlarmEnum.h"

class Alarmable;

class AlarmableManager
{
public:
	AlarmableManager() = default;
	~AlarmableManager();
	AlarmableManager(const AlarmableManager&) = delete;
	AlarmableManager& operator=(const AlarmableManager&) = delete;

	using AlarmEvent = std::pair<AlarmEnum::AlarmID, Alarmable*>;
	using StorageListRef = std::multimap<float, AlarmEvent>::iterator;
	using TimelineMapPair = std::pair<float, AlarmEvent>;

	//! Registers the alarmable with the given time and ID
	/*!
	\ingroup Alarms
	\param t A float for time
	\param al An Alarmable pointer
	\param ID An AlarmEnum AlarmID
	*/
	void Register(float t, Alarmable* al, AlarmEnum::AlarmID ID);

	//! Deregisters the alarmable with the given ID
	/*!
	\ingroup Alarms
	\param al An Alarmable pointer
	\param ID An AlarmEnum AlarmID
	*/
	void Deregister(Alarmable* al, AlarmEnum::AlarmID ID);

	//! Adds time to an alarmable with ID
	/*!
	\ingroup Alarms
	\param al An Alarmable pointer
	\param ID An AlarmEnum AlarmID
	\param time A float for time
	*/
	void AddTime(float time, Alarmable* al, AlarmEnum::AlarmID ID);

	float GetRemainingTime(Alarmable* al, AlarmEnum::AlarmID ID);

private:
	//std::list<Alarmable*> StorageList;
	std::multimap<float, AlarmEvent> TimelineMap;
	StorageListRef ref;

	friend class Scene;

	void ProcessElements();
};

#endif // !_AlarmableManager
