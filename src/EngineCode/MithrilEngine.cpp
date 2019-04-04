#include "AzulCore.h"
#include "MithrilEngine.h"
#include "TimeManager.h"
#include "Visualizer.h"

MithrilEngine* MithrilEngine::self = NULL;

// Global varables just for the demo:
// Note: Don't do this!
// Global vars should always be avoided in a finished product!

//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void MithrilEngine::Initialize()
{
	Instance().GameInitialize();
	SoundManager::CreateSoundEngine();
	SoundManager::SetVolume(0.5f);
}

//-----------------------------------------------------------------------------
// Game::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void MithrilEngine::LoadContent()
{
	Instance().LoadResources();
	Visualizer::CreateSphere();
}

//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void MithrilEngine::Update()
{
	SoundManager::Update();
	SceneManager::UpdateUpdatables();
	TimeManager::ProcessTime(this->GetTimeSeconds());
}

//-----------------------------------------------------------------------------
// Game::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void MithrilEngine::Draw()
{
	SceneManager::DrawDrawables();
}



//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void MithrilEngine::UnLoadContent()
{
	SceneManager::Terminate();
	ShaderManager::UnloadShaders();
	ModelManager::UnloadModels();
	TextureManager::UnloadTextures();
	ImageManager::UnloadImages();
	TerrainObjectManager::UnloadTerrainObjects();
	SpriteFontManager::UnloadSpriteFonts();
	SoundManager::Terminate();
	Visualizer::Terminate();
	SoundManager::Terminate();
}

void MithrilEngine::Run()
{
	Instance().run();
}

float MithrilEngine::GetTimeSeconds()
{
	return Instance().GetTimeInSeconds();
}

int MithrilEngine::GetWidth()
{
	return Instance().getWidth();
}

int MithrilEngine::GetHeight()
{
	return Instance().getHeight();
}