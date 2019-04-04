#ifndef _SoundManager
#define _SoundManager

#include <map>
#include "AzulCore.h"
#include "irrKlang.h"

using namespace irrklang;

class SoundManager
{
private:
	static SoundManager* self;
	SoundManager() {};
	SoundManager(const SoundManager&) {};
	SoundManager& operator= (const SoundManager) {};
	~SoundManager() {};

	static SoundManager& Instance()
	{
		if (!self)
		{
			self = new SoundManager();
		}
		return *self;
	};

	std::map<std::string, const char*> SoundList;

	ISoundEngine* engine;

	void privSetVolume(float vol);

	void privCreateSoundEngine();

	void privPlaySound2D(std::string key, bool loop);

	void privPlaySound3D(std::string key, bool loop, Vect & pos);

	void privPlayWithDistortionEffect(std::string key, float gain = -18.0f, float edge = 15.0f, float frequency = 2400.0f);

	void privPlayWithChorusEffect(std::string key, float wetDryMix = 50.0f, float depth = 10.0f, float feedback = 25.0f, float frequency = 1.1f);

	void privLoadSound(std::string key, const char* filepath);

	void privSetListenerPosition(Vect & pos, Vect & forward);

	bool privIsSoundPlaying(std::string key);

	void privStopSound(std::string key);

	void privStopAllSounds();

	void privUpdate();

	void privTerminate();

	//! Creates the sound engine
	static void CreateSoundEngine() { Instance().privCreateSoundEngine(); }

public:

	friend class MithrilEngine;

	//! Public static function. Sets the volume of the sound engine.
	/*!
	\param vol A float for volume level (0.0f to 1.0f)
	*/
	static void SetVolume(float vol) { Instance().privSetVolume(vol); }

	//! Public static function. Plays a 2D sound from a string key, looped or unlooped.
	/*!
	\param key A string for the sound key
	\param loop A bool for looping the sound
	*/
	static void PlaySound2D(std::string key, bool loop) { Instance().privPlaySound2D(key, loop); }

	//! Public static function. Plays a 3D sound from a string key, looped or unlooped, with a given position
	/*!
	\param key A string for the sound key
	\param loop A bool for looping the sound
	\param pos The position of the sound in 3D space as a Vect
	*/
	static void PlaySound3D(std::string key, bool loop, Vect & pos) { Instance().privPlaySound3D(key, loop, pos); }

	//! Public static function. Plays a 2D sound with a distortion effect
	/*!
	\param key A string for the sound key
	\param various Various controls for the effect
	*/
	static void PlayWithDistortionEffect(std::string key, float gain = -18.0f, float edge = 15.0f, float frequency = 2400.0f) { Instance().privPlayWithDistortionEffect(key, gain, edge, frequency); }

	//! Public static function. Plays a 2D sound with a chorus effect
	/*!
	\param key A string for the sound key
	\param various Various controls for the effect
	*/
	static void PlayWithChorusEffect(std::string key, float wetDryMix = 50.0f, float depth = 10.0f, float feedback = 25.0f, float frequency = 1.1f) { Instance().privPlayWithChorusEffect(key, wetDryMix, depth, feedback, frequency); }

	//! Public static function. Loads a sound into the sound map
	/*!
	\param key A string for the sound key
	\param filepath The filepath to the sound
	*/
	static void LoadSound(std::string key, const char* filepath) { Instance().privLoadSound(key, filepath); }

	//! Public static function. Sets the listener position for 3D sound
	/*!
	\param pos The listener position as a Vect
	\param forward The listener's forward vector as a Vect
	*/
	static void SetListenerPosition(Vect & pos, Vect & forward) { Instance().privSetListenerPosition(pos, forward); }

	//! Public static function. Returns true if a sound is playing, false otherwise
	/*!
	\param key The key to the sound in the sound map
	\return bool True or false, whether or not the given sound is playing
	*/
	static bool IsSoundPlaying(std::string key) { return Instance().privIsSoundPlaying(key); }


	//! Public static function. Stops a given sound
	/*!
	\param key The key to the sound in the sound map
	*/
	static void StopSound(std::string key) { Instance().privStopSound(key); }

	//! Public static function. Stops all sounds
	static void StopAllSounds() { Instance().privStopAllSounds(); }

	//! Public static function. Updates the sound engine
	static void Update() { Instance().privUpdate(); }

	//! Public static function. Terminates the sound engine
	static void Terminate() { Instance().privTerminate(); }
};

#endif _SoundManager