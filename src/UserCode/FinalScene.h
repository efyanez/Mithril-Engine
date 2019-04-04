#ifndef _FinalScene
#define _FinalScene

#include "../EngineCode/Scene.h"

class Frigate;
class GodCamera;

class FinalScene : public Scene
{
public:
	FinalScene();
	~FinalScene();

private:

	void Initialize() override;
	void Terminate();

	Frigate* testFrigate;
	GodCamera* testGodCamera;

};

#endif // !_FinalScene
