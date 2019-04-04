#ifndef _Scene
#define _Scene

class Updatable;
class UpdatableManager;
class Drawable;
class DrawableManager;
class Alarmable;
class AlarmableManager;
class Inputable;
class InputableManager;
class Collidable;
class CollisionManager;
class TerrainManager;
class TerrainObject;
class SceneRegistrationBroker;
class CommandBase;
class GameObject;
class CameraManager;
class Visualizer;

#include "AlarmEnum.h"
#include "Inputable.h"
#include <string>

class Scene
{
	friend class SceneManager;
	friend class Updatable;
	friend class Drawable;
	friend class Alarmable;
	friend class Inputable;
	friend class Collidable;
	friend class GameObject;
	friend class Visualizer;

public:
	Scene();
	virtual ~Scene();
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;

	//! Registers Updatable to current scene
	/*!
	\param up An Updatable pointer.
	*/
	void Register(Updatable* up);

	void Deregister(Updatable* up);

	//! Registers Drawable to current scene
	/*!
	\param dr A Drawable pointer.
	*/
	void Register(Drawable* dr);

	void Deregister(Drawable* dr);

	//! Registers Alarmable to current scene
	/*!
	\param t A float time for the alarm.
	\param al An Alarmable pointer.
	\param ID An Alarm ID enum from AlarmEnum::AlarmID
	*/
	void Register(float t, Alarmable* al, AlarmEnum::AlarmID ID);

	void Deregister(Alarmable* al, AlarmEnum::AlarmID ID);

	//! Adds time to alarm
	/*!
	\param t A float time for the alarm.
	\param al An Alarmable pointer.
	\param ID An Alarm ID enum from AlarmEnum::AlarmID
	*/
	void AddTime(float t, Alarmable* al, AlarmEnum::AlarmID ID);

	//! Gets remaining time for alarm
	/*!
	\param al An Alarmable pointer.
	\param ID An Alarm ID enum from AlarmEnum::AlarmID
	\return Returns remaining time as float
	*/
	float GetRemainingTime(Alarmable* al, AlarmEnum::AlarmID ID);

	//! Registers Inputable to current scene
	/*!
	\param in An Inputable pointer.
	\param k An AZUL_KEY key.
	\param type An EVENT_TYPE enum from Inputable::EVENT_TYPE
	*/
	void Register(Inputable* in, AZUL_KEY k, Inputable::EVENT_TYPE type);
	void Deregister(Inputable* in, AZUL_KEY k, Inputable::EVENT_TYPE type);

	//! Registers GameObject to current scene
	/*!
	\param go A GameObject pointer.
	*/
	void Register(GameObject* go);
	void Deregister(GameObject* go);

	//! Registers Collidable to current scene
	/*!
	\param co A Collidable pointer.
	*/
	void Register(Collidable* co);
	void Deregister(Collidable* co);

	//! Sets the current scene terrain
	/*!
	\param key A key to a terrain object.
	*/
	void SetTerrain(std::string key);

	TerrainObject* GetTerrain();

	//! Returns the scene's camera manager as a CameraManager pointer
	CameraManager* GetCamManager() { return camMgr; };

	//template<typename C1>
	//void Scene::SetCollisionSelf()
	//{
	//	CollisionManager->SetCollisionSelf<C1>();
	//}
	//
	//template<typename C1, typename C2>
	//void Scene::SetCollisionPair()
	//{
	//	CollisionManager->SetCollisionPair<C1, C2>();
	//}

	//! Virtual function, called when a scene is terminated
	/*!
	\par Example:
	\code
	void MyFirstScene::Initialize()
	{
		delete myShip;
		delete myPlane;
	}
	\endcode
	*/
	virtual void Terminate();

protected:
	UpdatableManager* UpdateMgr;
	DrawableManager* DrawMgr;
	AlarmableManager* AlarmMgr;
	InputableManager* InputMgr;
	CollisionManager* ColMgr;
	TerrainManager* TerrainMgr;
	SceneRegistrationBroker* sceneBroker;

	CameraManager* camMgr;

	//! User defines what happens when a scene is initialized
	/*!
	\par Example:
	\code
	void MyFirstScene::Initialize()
	{
		myShip = new Ship();
		myPlane = new Plane();

		//NOTE: ColMgr is the Collision Manager name
		ColMgr->SetCollisionSelf<Ship>();
		ColMgr->SetCollisionPair<Ship, Plane>();
	}
	\endcode
	*/
	virtual void Initialize() = 0;
	//virtual void Terminate();

	void Draw();
	void Update();

	void SubmitCommand(CommandBase* cmd);
	void SubmitSceneCommand(CommandBase* cmd);
};

#endif //#!_Scene
