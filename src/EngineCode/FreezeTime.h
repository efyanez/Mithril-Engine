// FreezeTime
// Andre Berthiaume, Jan 2016

#ifndef _FreezeTime
#define _FreezeTime

#include "AzulCore.h"

class FreezeTime
{
private:
	static const AZUL_KEY FREEZE_KEY = AZUL_KEY::KEY_F10;
	static const AZUL_KEY SINGLE_FRAME_KEY = AZUL_KEY::KEY_F9;

	float totalFrozenTime;
	bool freeze_mode_active;

	//! Hack to suspend program in infinite loop and calculate the time spent frozen.
	/*!
		\param activeTime A float (active time of engine).
		\return Returns a float that indicates the amount of time spent frozen.
	*/
	float WaitAndReturnFrozenTime(float activetime);

	//! Hack to release the freeze time from the infinite loop.
	/*!
	\param k An AZUL_KEY key.
	\return True or false, whether or not the key was pressed.
	*/
	bool HackedKeyRelease(AZUL_KEY k);

public:

	//! FreezeTime constructor
	/*!
	\ingroup MithrilEngine
	*/
	FreezeTime();

	~FreezeTime(){};
	FreezeTime(const FreezeTime&) = delete;
	FreezeTime& operator=(const FreezeTime&) = delete;

	//! Return the frozen time in seconds
	/*!
	\param sys_time A float (active time of engine).
	\return Returns the frozen time in seconds
	*/
	float GetTimeInSeconds(float sys_time);
};

#endif _FreezeTime