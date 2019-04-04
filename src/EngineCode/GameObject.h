#ifndef _GameObject
#define _GameObject

class GameObjectEntryCommand;
class GameObjectExitCommand;

class GameObject
{
public:
	//! Called once per frame on each GameObject
	/// \ingroup DEFAULT EVENTS
	/// All Game Objects are automatically registered to the current scene when they are created
	GameObject();

	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;
	~GameObject();

	//! Submits the GameObject for Scene Entry
	/*!
	\par Example:
	\code
	void Ship::Ship()
	{
		//If the object can leave the scene, it should submit for entry
		SubmitEntry();
	}
	\endcode
	*/
	void SubmitEntry();

	//! Submits the GameObject for Scene Exit
	/*!
	\par Example:
	\code
	void Ship::Alarm0()
	{
		//When the object can leave the scene, it should submit for exit
		SubmitExit();
	}
	\endcode
	*/
	void SubmitExit();

	friend class GameObjectEntryCommand;
	friend class GameObjectExitCommand;
	friend class Scene;

private:

	GameObjectEntryCommand* pRegCmd;
	GameObjectExitCommand* pDeregCmd;

	//virtual void Initialize();
	//virtual void Update();
	//virtual void Draw();

	enum class RegistrationState
	{
		CURRENTLY_DEREGISTERED,
		PENDING_REGISTRATION,
		CURRENTLY_REGISTERED,
		PENDING_DEREGISTRATION
	};


	RegistrationState currState;

	void ConnectToScene();
	void DisconnectFromScene();

	virtual void SceneEntry();
	virtual void SceneExit();

};

#endif // !_GameObject
