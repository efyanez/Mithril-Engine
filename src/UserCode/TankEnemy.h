#ifndef _TankEnemy
#define _TankEnemy

#include "AzulCore.h"
#include "../EngineCode/Updatable.h"
#include "../EngineCode/Drawable.h"
#include "../EngineCode/Alarmable.h"
#include "../EngineCode/Collidable.h"
#include "Align16.h"
#include "../EngineCode/ModelManager.h"
#include "../EngineCode/ShaderManager.h"
#include "../EngineCode/TextureManager.h"
#include "../EngineCode/CameraManager.h"
#include "Enemy.h"

class Frigate;
class Bullet;

class TankEnemy : public Enemy
{
private:

	GraphicsObject_TextureLight *pGObj_TankEnemy;

	Matrix world;
	Matrix Scale;
	Vect Pos;
	Matrix Rot;
	float TransSpeed = 1;
	float RotAng = .05f;
	float upSpeed = 1.0f;
	bool bDebugCol = false;
	int totalHealth = 3;

	//void(*state)();
	void(TankEnemy::*state)();
	void state_Idle();
	void state_FollowPlayer();

	Frigate* player;

public:
	TankEnemy(const Matrix& mscale, const Matrix& mrot, const Vect& mpos, Frigate* p);
	virtual ~TankEnemy();

	void Update() override;
	void Draw() override;

	void SceneEntry() override;
	void SceneExit() override;

	void Alarm1() override;

	virtual void Collision(Collidable*);
	virtual void Collision(Frigate*);
	virtual void Collision(Bullet*);

	Matrix GetRotation() override { return Rot; };
	Vect GetTranslation() override { return Pos; }
};

#endif // !_TankEnemy
