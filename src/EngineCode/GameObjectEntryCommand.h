#ifndef _GameObjectEntryCommand
#define _GameObjectEntryCommand

#include "CommandBase.h"

class GameObject;

class GameObjectEntryCommand : public CommandBase
{

	friend class GameObject;
public:
	GameObjectEntryCommand(GameObject* go);
	~GameObjectEntryCommand();
	GameObjectEntryCommand(const GameObjectEntryCommand&) = delete;
	GameObjectEntryCommand& operator=(const GameObjectEntryCommand&) = delete;

	//! Execute override. Calls SceneEntry() on GameObject pointer.
	void Execute() override;
private:
	GameObject* ptrGO;
};

#endif // !_GameObjectEntryCommand
