#include "ParticleEffectManager.h"
#include "ParticleEffect.h"
#include <assert.h>
#include "DebugOut.h"

ParticleEffectManager* ParticleEffectManager::self = NULL;

void ParticleEffectManager::privLoadParticleEffect(std::string key, ParticleEffect * pe)
{
	assert((key != "" || pe != nullptr) && "Key or particle effect invalid");
	assert(Instance().ParticleEffectList[key] == nullptr && "Duplicate key found!");

	Instance().ParticleEffectList[key] = pe;
}

ParticleEffect * ParticleEffectManager::privGetParticleEffect(std::string key)
{
	assert(Instance().ParticleEffectList[key] != nullptr && "Particle Effect not found!");
	return Instance().ParticleEffectList[key];
}

void ParticleEffectManager::privUnloadParticleEffects()
{
	std::map<std::string, ParticleEffect*>::iterator peIt = Instance().ParticleEffectList.begin();
	while (peIt != Instance().ParticleEffectList.end())
	{
		delete peIt->second;
		peIt->second = nullptr;
		peIt++;
	}
	DebugMsg::out("PARTICLE EFFECTS UNLOADED\n");
	delete self;
}
