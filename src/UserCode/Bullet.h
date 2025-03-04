#ifndef _Bullet
#define _Bullet

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
class Enemy;
class ParticleEffect;

class Bullet : public Updatable, public Drawable, public Alarmable, public Collidable, public Align16
{
private:

	GraphicsObject_TextureFlat* bulletModel;

	Matrix world;
	Matrix tankWorld;
	Matrix bScale;
	Vect bPos;
	Matrix bRot;
	float bSpeed = 1;
	float ShipRotAng = .05f;
	bool BsphereToggle = false;

	ParticleEffect* pe;

public:
	Bullet();
	virtual ~Bullet();

	void SceneEntry() override;
	void SceneExit() override;

	virtual void Collision(Collidable*);
	virtual void Collision(Enemy*);

	void Initialize(Frigate* rotation);
	void Update() override;
	void Draw() override;
	void Alarm0() override;
};

#endif // _!Bullet
