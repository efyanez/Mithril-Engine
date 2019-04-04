#include "SoundManager.h"

SoundManager* SoundManager::self = NULL;

void SoundManager::privCreateSoundEngine()
{
	engine = createIrrKlangDevice();
}

void SoundManager::privPlaySound2D(std::string key, bool loop)
{
	engine->play2D(Instance().SoundList[key], loop, false, false, irrklang::E_STREAM_MODE::ESM_AUTO_DETECT, true);
}

void SoundManager::privPlaySound3D(std::string key, bool loop, Vect & pos)
{
	ik_f32 x = pos.X();
	ik_f32 y = pos.Y();
	ik_f32 z = pos.Z();
	vec3df newPos = vec3df(x, y, z);
	engine->play3D(Instance().SoundList[key], newPos, loop, false, true);
}

void SoundManager::privPlayWithDistortionEffect(std::string key, float gain, float edge, float frequency)
{
	ISound* music = engine->play2D(Instance().SoundList[key], true, false, false, ESM_AUTO_DETECT, true);
	ISoundEffectControl* fx = music->getSoundEffectControl();
	assert(music && fx);
	fx->enableDistortionSoundEffect(gain, edge, frequency);
}

void SoundManager::privPlayWithChorusEffect(std::string key, float wetDryMix, float depth, float feedback, float frequency)
{
	ISound* music = engine->play2D(Instance().SoundList[key], true, false, false, ESM_AUTO_DETECT, true);
	ISoundEffectControl* fx = music->getSoundEffectControl();
	assert(music && fx);
	fx->enableChorusSoundEffect(wetDryMix, depth, feedback, frequency);
}

void SoundManager::privLoadSound(std::string key, const char * filepath)
{
	assert((key != "") && "Key or filepath invalid");
	assert(Instance().SoundList[key] == NULL && "Duplicate key found!");

	Instance().SoundList[key] = filepath;
}

void SoundManager::privSetListenerPosition(Vect & pos, Vect & forward)
{
	ik_f32 x = pos.X();
	ik_f32 y = pos.Y();
	ik_f32 z = pos.Z();
	vec3df newPos = vec3df(x, y, z);
	ik_f32 x1 = forward.X();
	ik_f32 y1 = forward.Y();
	ik_f32 z1 = forward.Z();
	vec3df newPos2 = vec3df(x1, y1, z1);
	engine->setListenerPosition(newPos, newPos2);
}

bool SoundManager::privIsSoundPlaying(std::string key)
{
	return engine->isCurrentlyPlaying(Instance().SoundList[key]);
}

void SoundManager::privStopSound(std::string key)
{
	if (privIsSoundPlaying(key)) 
	{
		engine->removeSoundSource(Instance().SoundList[key]);
	}
}

void SoundManager::privStopAllSounds()
{
	engine->stopAllSounds();
}

void SoundManager::privUpdate()
{
	engine->update();
}

void SoundManager::privTerminate()
{
	SoundList.clear();
	//Instance().engine->stopAllSounds();
	//Instance().engine->removeAllSoundSources();
	//Instance().engine->drop();
}

void SoundManager::privSetVolume(float vol)
{
	engine->setSoundVolume(vol);
}