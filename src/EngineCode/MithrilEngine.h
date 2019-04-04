#ifndef GAME_H
#define GAME_H

#include "AzulCore.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "CameraManager.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "SoundManager.h"
#include "SpriteFontManager.h"
#include "TerrainObjectManager.h"
#include "ParticleEffectManager.h"
#include "ParticleEffectGroups.h"
#include "../UserCode/FirstScene.h"
#include "../UserCode/SecondScene.h"
#include "../UserCode/StartScene.h"
#include "../UserCode/FinalScene.h"

class MithrilEngine: public Engine
{
private:

	static MithrilEngine* self;

	//! MithrilEngine constructor
	/*!
	\ingroup MithrilEngine
	*/
	MithrilEngine() {};

	MithrilEngine(const MithrilEngine&) {};
	MithrilEngine& operator= (const MithrilEngine) {};
	~MithrilEngine() {};

	static MithrilEngine& Instance()
	{
		if (!self)
		{
			self = new MithrilEngine();
		}
		return *self;
	};

	virtual void Initialize();
	virtual void LoadContent();
	virtual void Update();
	virtual void Draw();
	virtual void UnLoadContent();

	void LoadResources();
	void GameInitialize();

public:

	//! Calls Run() on the engine class.
	static void Run();

	//! Returns the time elapsed in seconds.
	static float GetTimeSeconds();

	//! Returns the width of the current window.
	static int GetWidth();

	//! Returns the height of the current window.
	static int GetHeight();
};

#endif