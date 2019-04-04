#ifndef _FirstScene
#define _FirstScene

#include "../EngineCode/Scene.h"

class Frigate;
class Plane;
class Axis;
class TimedEnemySpawner;
class GodCamera;
class SkySphere;

class FirstScene : public Scene
{
public:
	FirstScene();
	~FirstScene();

private:

	void Initialize() override;
	void Terminate();

	Frigate* testFrigate;
	//Frigate* testFrigate2;
	//Plane* testPlane;
	Axis* testAxis;
	TimedEnemySpawner* spawner;
	//GodCamera* godCam;
	SkySphere* testSky;
};

#endif // !_FirstScene
