#ifndef _SceneManager
#define _SceneManager

#include "AzulCore.h"
#include "SceneChangeCommand.h"

class Scene;

class SceneManager
{
	friend class Scene;
	friend class MithrilEngine;
	friend class SceneChangeCommand;
private:
	static SceneManager* self;
	SceneManager() {};
	SceneManager(const SceneManager&) {};
	SceneManager& operator= (const SceneManager) {};
	~SceneManager() {};

	static SceneManager& Instance()
	{
		if (!self)
		{
			self = new SceneManager();
		}
		return *self;
	};

	Scene* currentScene = nullptr;
	Scene* nextScene = nullptr;

	void privInitializeCurrentScene();
	void privSetCurrentScene(Scene* sc);
	Scene* privGetCurrentScene();
	void privTerminate();

	void privUpdateUpdatables();
	void privDrawDrawables();

	void privChangeScene();
	void privSetNextScene(Scene* pnextScene);

	void privSubmitSceneChange(Scene* newScene);

	Camera* privGetCurrent3DCamera();
	Camera* privGetCurrent2DCamera();

	//! Calls Scene::Terminate() on the current scene.
	/*!
	\sa Scene::Initialize()
	*/
	static void Terminate() { Instance().privTerminate(); }

	//! Calls Scene::Update() on the current scene.
	/*!
	\sa Scene::Update()
	*/
	static void UpdateUpdatables() { Instance().privUpdateUpdatables(); }

	//! Calls Scene::Draw() on the current scene.
	/*!
	\sa Scene::Draw()
	*/
	static void DrawDrawables() { Instance().privDrawDrawables(); }

	//! Sets the next scene.
	/*!
	\param pnextScene A Scene pointer
	*/
	static void SetNextScene(Scene* pnextScene) { Instance().privSetNextScene(pnextScene); }

	//! Terminates the current scene and sets the current scene to the next scene. Then calls initialize on the current scene.
	/*!
	\sa Scene::Initialize()
	*/
	static void ChangeScene() { Instance().privChangeScene(); }

public:
	//! Public static function. Sets the current scene.
	/*!
	\param sc A Scene pointer.
	*/
	static void SetCurrentScene(Scene* sc) { Instance().privSetCurrentScene(sc); }

	//! Public static function. Returns the current scene.
	/*!
	\return Returns a Scene pointer.
	*/
	static Scene* GetCurrentScene() { return Instance().privGetCurrentScene(); }

	//! Calls Scene::Initialize() on the current scene.
	/*!
	\sa Scene::Initialize()
	*/
	static void InitializeCurrentScene() { Instance().privInitializeCurrentScene(); }

	static void SubmitSceneChange(Scene* newScene) { Instance().privSubmitSceneChange(newScene); }

	//! Returns the current scene 3D camera
	/*!
	\return Returns the current scene 3D camera as a Camera* pointer
	*/
	static Camera* GetCurrent3DCamera() { return Instance().privGetCurrent3DCamera(); }

	//! Returns the current scene 2D camera
	/*!
	\return Returns the current scene 2D camera as a Camera* pointer
	*/
	static Camera* GetCurrent2DCamera() { return Instance().privGetCurrent2DCamera(); }
};

#endif _CameraManager