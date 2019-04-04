#include "ParticleEffectSphericalBurst.h"

ParticleEffectSphericalBurst::ParticleEffectSphericalBurst()
{
	currentPattern = BurstPattern::Spherical;
}

void ParticleEffectSphericalBurst::SetBurstIntervalAndLife(float interval, float life)
{
	burstInterval = interval;
	burstLife = life;
}

void ParticleEffectSphericalBurst::SetBurstCount(int count)
{
	burstCount = count;
}

void ParticleEffectSphericalBurst::SetSpeed(float s)
{
	burstSpeed = s;
}

void ParticleEffectSphericalBurst::SetScale(float s)
{
	burstScale = s;
}

void ParticleEffectSphericalBurst::SetTightness(float t)
{
	burstTightness = t;
}
