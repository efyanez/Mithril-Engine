#ifndef _TimeManager
#define _TimeManager

#include "AzulCore.h"

class FreezeTime;

class TimeManager
{
private:

	static TimeManager* self;
	TimeManager();
	TimeManager(const TimeManager&) {};
	TimeManager& operator= (const TimeManager) {};
	~TimeManager() {};

	static TimeManager& Instance()
	{
		if (!self)
		{
			self = new TimeManager();
		}
		return *self;
	};

	FreezeTime* FrzTime;

	float previousTime = 0;
	float currentTime = 0;
	float frameTime = 0;

	//! Returns the time in seconds (takes into account frozen time).
	/*!
		\return Returns a float that indicates the amount of time in seconds that has passed.
	*/
	float privGetTimeSeconds();

	//! Processes the amount of time spent frozen
	/*!
		\param sys_time A float (system time of engine).
	*/
	void privProcessTime(float sys_time);

	//! Returns the time it took (in seconds) to process a single frame
	/*!
		\return Returns a float that indicates the amount of time it took (in seconds) to process a single frame
	*/
	float privGetFrameTime();

public:

	static float GetTimeSeconds() { return Instance().privGetTimeSeconds(); }
	static void ProcessTime(float sys_time) {  Instance().privProcessTime(sys_time); }
	static float GetFrameTime() { return Instance().privGetFrameTime(); }
};

#endif // _!TimeManager