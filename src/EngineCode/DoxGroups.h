///
///\file	Doxygen Group\DoxyGroups.h
///
///\brief	Doxygen groups for Mithril Engine
///



///\mainpage Mithril Engine Documentation
///\section intro_sec Introduction
///         Welcome to the MithrilEngine documentation!
///\section asset_sec Placing Asset Files
///         All custom assets (models, textures, shaders,...) should be put in the ../Assets/ folder.
///         Models go inside of ../Assets/ModelsAndTextures.
///         Shaders go inside of ../Assets/Shaders.
///			Setting up the game: \ref Setup
///\section assetload_sec Loading Asset Files
///         The LoadAllResources.cpp source file is where all custom assets are loaded in.
///         Some examples are already written in the file for models and textures.
///\par Example:
///\code
///void MithrilEngine::LoadResources()
///{
///
///	ModelManager::LoadDefaultModels();
///	TextureManager::LoadDefaultTextures();
///	ShaderManager::LoadDefaultShaders();
///
///	TextureManager::LoadTexture("GrassTex", "../Assets/ModelsAndTextures/grass.tga");
///	ModelManager::LoadModel("Ship", "../Assets/ModelsAndTextures/ship.azul");
///
///	ImageManager::CreateImage("UI", TextureManager::GetTexture("UITex"), new Rect(0.0f, 0.0f, (float)TextureManager::GetTexture("UITex")->getWidth(), (float)TextureManager::GetTexture("UITex")->getHeight()));
///
///	SoundManager::LoadSound("StartMusic", "../Assets/Sounds/startmusic.ogg");
///
///	TerrainObjectManager::LoadTerrainObject("MainTerrain", "../Assets/ModelsAndTextures/finalHM.tga", "PlaneTex", 6, 6, 597, 225, 5, 2.0f, -10.0f, 2.0f);
///
///}
///\endcode
///\section game_sec Initializing Game Parameters
///         The GameInitialize.cpp source file is where you can set the window width, height, and name.
///\par Example:
///\code
///void MithrilEngine::GameInitialize()
///{
///	// Game Window Device setup
///	this->setWindowName("Mithril Engine");
///	this->setWidthHeight(800, 600);
///	this->SetClearColor(0.4f, 0.4f, 0.8f, 1.0f);
///}
///\endcode
///\section time_sec Debug Tools (Freeze Time)
///         By default, F10 freeze game time. F9 steps through one frame at a time.
///\section scene_sec Setting Up A Scene
///			The following code snippet shows how to set up a start scene.
///\par Example:
///\code
///	void MithrilEngine::LoadResources()
///	{
///	Scene* firstScene = new FirstScene();
///	SceneManager::SetCurrentScene(firstScene);
///	SceneManager::InitializeCurrentScene();
///	}
///\endcode
///\section col_sec Setting Up A Scene & Collision
///			The following code snippet shows how to set a scene and collisions with self and pairs
///\par Example:
///\code
///	void MyFirstScene::Initialize()
///	{
///
///	SetTerrain("MainTerrain");
///
///	myShip = new Ship();
///	myPlane = new Plane();
///
///	//NOTE: ColMgr is the Collision Manager name
///	ColMgr->SetCollisionSelf<Ship>();
///	ColMgr->SetCollisionPair<Ship, Plane>();
/// ColMgr->SetCollisionTerrain<Ship>();
///	}
///\endcode
///\section sound_sec Playing Sound
///			The following code snippet shows how to play sounds in the engine
///\par 2D Sound:
///\code
///void Bullet::SceneEntry()
///{
///	SoundManager::PlaySound2D("TankShot", false);
///}
///\endcode
///\section part_sec Loading Particles
///			The following code snippet shows how to load particle effects
///\par Particle Effects:
///\code
///	ParticleEffectStream* pe = new ParticleEffectStream();
///	pe->SetBurstCount(200);
///	pe->SetBurstIntervalAndLife(0.5f, 3.0f);
///	pe->SetGraphicObject("Square", "Water1");
///	pe->SetSpeed(1.0f);
///	pe->SetScale(6.0f);
///	pe->SetTightness(0.9f);
///
///	ParticleEffectManager::LoadParticleEffect("Water1", pe);
///\endcode

///
/// \defgroup     MithrilEngine
///
/// \brief        A group for all Engine code.
///

///
/// \defgroup     GameObject
/// \ingroup      MithrilEngine
/// \brief        GameObject group, and all associated "-able" classes.
///

///
/// \defgroup     Update
/// \ingroup      GameObject
/// \brief        GameObject update group, everything relating to Updatable.
///

///
/// \defgroup     Draw
/// \ingroup      GameObject
/// \brief        GameObject draw group, everything relating to Drawable.
///

///
/// \defgroup     Alarms
/// \ingroup      GameObject
/// \brief        GameObject alarm group, everything relating to Alarmable.
///

///
/// \defgroup     Input
/// \ingroup      GameObject
/// \brief        GameObject input group, everything relating to Inputable.
///


///
/// \defgroup     Collisions
/// \ingroup      GameObject
/// \brief        GameObject collision group, everything relating to Collidable.
///

///
/// \defgroup     Scene
/// \ingroup      MithrilEngine
/// \brief        Scene group, everything relating to Scene.
///

///
/// \defgroup     Resources
/// \ingroup      MithrilEngine
/// \brief        Resource group, everything relating to resources (models, shaders, textures,...).
///

///
/// \defgroup     Particles
/// \ingroup      MithrilEngine
/// \brief        Particles group, everything relating to particles (effects, emitters, bursts,...).
///

///
/// \defgroup     Font
/// \ingroup      MithrilEngine
/// \brief        Font group, everything relating to sprite fonts (SpriteFont, SpriteString,...).
///

///
/// \defgroup     Sound
/// \ingroup      MithrilEngine
/// \brief        Sound group, everything relating to sound (playing, stopping,...).
///

///
/// \defgroup     Time
/// \ingroup      MithrilEngine
/// \brief        Time group, everything relating to time (TimeManager, FreezeTime,...).
///

///
/// \defgroup     MathTools
/// \ingroup      MithrilEngine
/// \brief        Math tool group, everything relating computing various common math functions.
///