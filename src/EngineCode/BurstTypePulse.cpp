#include "BurstTypePulse.h"
#include "TimeManager.h"

BurstTypePulse::BurstTypePulse()
{
}

BurstTypePulse::~BurstTypePulse()
{
}

void BurstTypePulse::CalculatePosition(Vect & pos, Vect & direction, float speed, float tightness)
{
	(void)tightness;
	pos += direction * speed * (sinf(TimeManager::GetTimeSeconds()) * cosf(TimeManager::GetTimeSeconds()));
}
