#ifndef _Enemy
#define _Enemy

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

class Frigate;
class Bullet;

class Enemy : public Updatable, public Drawable, public Alarmable, public Collidable, public Align16
{
private:

	GraphicsObject_TextureLight *pGObj_SpaceFrigateLight;

	Matrix world;
	Matrix Scale;
	Vect Pos;
	Matrix Rot;
	float TransSpeed = 1;
	float RotAng = .05f;
	int mynum = 2;
	bool bDebugCol = false;

	//void(*state)();
	void(Enemy::*state)();
	void state_Idle();
	void state_FollowPlayer();

	Frigate* player;

public:
	Enemy();
	virtual ~Enemy();

	void Initialize(const Matrix& mscale, const Matrix& mrot, const Vect& mpos, Frigate* p);
	void Update() override;
	void Draw() override;

	void SceneEntry() override;
	void SceneExit() override;

	void Alarm0() override;
	void Alarm1() override;

	virtual void Collision(Collidable*);
	virtual void Collision(Frigate*);
	virtual void Collision(Bullet*);
	virtual void Collision(Enemy*);

	virtual Matrix GetRotation() { return Rot; };
	virtual Vect GetTranslation() { return Pos; }
};

#endif // !_Enemy
