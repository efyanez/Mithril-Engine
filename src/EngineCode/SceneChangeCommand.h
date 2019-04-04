#ifndef _SceneChangeCommand
#define _SceneChangeCommand

#include "CommandBase.h"

class Scene;

class SceneChangeCommand : public CommandBase
{
public:
	SceneChangeCommand(Scene* s);
	~SceneChangeCommand();
	SceneChangeCommand(const SceneChangeCommand&) = delete;
	SceneChangeCommand& operator=(const SceneChangeCommand&) = delete;

	//! Execute override. Calls SetNextScene() and ChangeScene() on SceneManager.
	void Execute() override;
private:
	Scene* ptrScene;
};

#endif // !_SceneChangeCommand
