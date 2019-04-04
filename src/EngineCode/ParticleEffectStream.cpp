#include "ParticleEffectStream.h"

ParticleEffectStream::ParticleEffectStream()
{
	currentPattern = BurstPattern::Stream;
	burstTightness = 0.9f;
}

void ParticleEffectStream::SetBurstIntervalAndLife(float interval, float life)
{
	burstInterval = interval;
	burstLife = life;
}

void ParticleEffectStream::SetBurstCount(int count)
{
	burstCount = count;
}

void ParticleEffectStream::SetSpeed(float s)
{
	burstSpeed = s;
}

void ParticleEffectStream::SetScale(float s)
{
	burstScale = s;
}

void ParticleEffectStream::SetTightness(float t)
{
	burstTightness = t;
}
