#ifndef _ParticleEffectManager
#define _ParticleEffectManager

#include <map>
#include <string>

class ParticleEffect;

class ParticleEffectManager
{
private:
	static ParticleEffectManager* self;
	ParticleEffectManager() {};
	ParticleEffectManager(const ParticleEffectManager&) {};
	ParticleEffectManager& operator= (const ParticleEffectManager) {};
	~ParticleEffectManager() {};

	static ParticleEffectManager& Instance()
	{
		if (!self)
		{
			self = new ParticleEffectManager();
		}
		return *self;
	};

	std::map<std::string, ParticleEffect*> ParticleEffectList;

	void privLoadParticleEffect(std::string key, ParticleEffect* pe);
	ParticleEffect* privGetParticleEffect(std::string key);

	void privUnloadParticleEffects();


public:

	//! Public static function. Loads a model from a filepath into the map of ParticleEffect pointers.
	/*!
	\param key A string name for the ParticleEffect.
	\param filepath A string filepath for the Azul model location.
	*/
	static void LoadParticleEffect(std::string key, ParticleEffect* pe) { Instance().privLoadParticleEffect(key, pe); };

	//! Returns a ParticleEffect pointer by taking a key and searching the key in the map.
	/*!
	\param key A string name for the ParticleEffect.
	\return Returns a ParticleEffect pointer
	*/
	static ParticleEffect* GetParticleEffect(std::string key) { return Instance().privGetParticleEffect(key); };

	//! Unloaded ParticleEffects, deletes them from the map.
	static void UnloadParticleEffects() { Instance().privUnloadParticleEffects(); };
};

#endif _ParticleEffectManager