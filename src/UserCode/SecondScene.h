#ifndef _SecondScene
#define _SecondScene

#include "../EngineCode/Scene.h"

class Frigate;
class Field;
class Axis;
class Pyramid;
class GodCamera;
class Terrain;
class TankEnemy;

class SecondScene : public Scene
{
public:
	SecondScene();
	~SecondScene();

private:

	void Initialize() override;
	void Terminate();

	Frigate* testFrigate;
	Field* testField;
	Axis* testAxis;
	Pyramid* testPyramid;
	Pyramid* testPyramid2;
	Terrain* testTerrain;

	TankEnemy* enemy1;

	GodCamera* godCam;
};

#endif // !_SecondScene
