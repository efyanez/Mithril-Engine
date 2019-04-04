#include "TimeManager.h"
#include "MithrilEngine.h"
#include "DebugOut.h"
#include "FreezeTime.h"

TimeManager* TimeManager::self = NULL;

TimeManager::TimeManager()
{
	FrzTime = new FreezeTime();
}

float TimeManager::privGetTimeSeconds()
{
	return MithrilEngine::GetTimeSeconds();
}

void TimeManager::privProcessTime(float sys_time)
{
	previousTime = currentTime;
	//currentTime = sys_time;
	currentTime = FrzTime->GetTimeInSeconds(sys_time);
	frameTime = currentTime - previousTime;
	//DebugMsg::out("Frame time: %2f\n", frameTime);
}

float TimeManager::privGetFrameTime()
{
	return currentTime;
}
