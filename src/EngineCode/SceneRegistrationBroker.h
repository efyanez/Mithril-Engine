#ifndef _SceneRegistrationBroker
#define _SceneRegistrationBroker

#include <list>

class CommandBase;

class SceneRegistrationBroker
{
public:
	SceneRegistrationBroker();
	~SceneRegistrationBroker();
	SceneRegistrationBroker(const SceneRegistrationBroker&) = delete;
	SceneRegistrationBroker& operator=(const SceneRegistrationBroker&) = delete;

	//! Adds a command of type CommandBase to a list.
	void AddCommand(CommandBase* cmd);

	void AddSceneCommand(CommandBase* cmd);

	//! Goes through all the CommandBase pointers in command list and calls Execute() on them.
	void ExecuteCommands();

	void ExecuteSceneCommands();

private:
	std::list<CommandBase*> commandList;
	std::list<CommandBase*> sceneCommandList;
};

#endif // !_SceneRegistrationBroker
