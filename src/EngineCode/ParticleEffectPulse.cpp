#include "ParticleEffectPulse.h"

ParticleEffectPulse::ParticleEffectPulse()
{
	currentPattern = BurstPattern::Pulse;
}

void ParticleEffectPulse::SetBurstIntervalAndLife(float interval, float life)
{
	burstInterval = interval;
	burstLife = life;
}

void ParticleEffectPulse::SetBurstCount(int count)
{
	burstCount = count;
}

void ParticleEffectPulse::SetSpeed(float s)
{
	burstSpeed = s;
}

void ParticleEffectPulse::SetScale(float s)
{
	burstScale = s;
}

void ParticleEffectPulse::SetTightness(float t)
{
	burstTightness = t;
}

