#ifndef _StartScene
#define _StartScene

#include "../EngineCode/Scene.h"

class StartSceneFrigate;
class SkySphere;

class StartScene : public Scene
{
public:
	StartScene();
	~StartScene();

private:

	void Initialize() override;
	void Terminate();

	StartSceneFrigate* testFrigate;
	SkySphere* testSky;
};

#endif // !_StartScene
