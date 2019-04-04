#ifndef _GameObjectExitCommand
#define _GameObjectExitCommand

#include "CommandBase.h"

class GameObject;

class GameObjectExitCommand : public CommandBase
{

	friend class GameObject;
public:
	GameObjectExitCommand(GameObject* go);
	~GameObjectExitCommand();
	GameObjectExitCommand(const GameObjectExitCommand&) = delete;
	GameObjectExitCommand& operator=(const GameObjectExitCommand&) = delete;

	//! Execute override. Calls SceneExit() on GameObject pointer.
	void Execute() override;
private:
	GameObject* ptrGO;
};

#endif // !_GameObjectExitCommand
