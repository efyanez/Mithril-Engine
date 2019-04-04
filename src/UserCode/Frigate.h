#ifndef _Frigate
#define _Frigate

#include "AzulCore.h"
#include "../EngineCode/Updatable.h"
#include "../EngineCode/Drawable.h"
#include "../EngineCode/Alarmable.h"
#include "../EngineCode/Inputable.h"
#include "../EngineCode/Collidable.h"
#include "Align16.h"
#include "../EngineCode/ModelManager.h"
#include "../EngineCode/ShaderManager.h"
#include "../EngineCode/TextureManager.h"
#include "../EngineCode/CameraManager.h"
#include "DebugOut.h"


class Bullet;
class Enemy;
class EnemyBullet;
class Sprite;
class Pyramid;
class SpriteString;

class Frigate : public Updatable, public Drawable, public Alarmable, public Inputable, public Collidable, public Align16
{
private:

	SpriteString* myString;

	GraphicsObject_TextureLight *pGObj_SpaceFrigateLight;
	GraphicsObject_TextureLight *pGObj_TankTop;
	GraphicsObject_WireframeConstantColor *pGObj_SpaceshipBSphere;

	GraphicsObject_Sprite	*pGObj_Sprite;

	Matrix world;
	Matrix gunWorld;
	Matrix ShipScale;
	Vect ShipPos;
	Matrix ShipRot;
	Matrix GunRot;
	float ShipTransSpeed = 3;
	float ShipRotAng = .05f;
	bool BsphereToggle = false;
	bool bDebugCol = false;

	Bullet* myBullet;
	Camera* currentCamera;
	Camera* current2DCamera;
	Sprite* UI;
	Sprite* Hearts3;
	Sprite* Hearts2;
	Sprite* Hearts1;

	int health;

	float startTime;
	float distance;
	Vect endPos;

public:
	Frigate();
	virtual ~Frigate();
	
	void SceneEntry() override;
	void SceneExit() override;

	void Update() override;
	void Draw() override;
	void Draw2D() override;

	void Alarm0() override;
	void Alarm1() override;

	virtual void Collision(Collidable*);
	virtual void Collision(Enemy*);
	virtual void Collision(EnemyBullet*);
	virtual void Collision(Pyramid*);
	void TerrainCollision(CollisionVolumeAABB& cellAABB) override;

	//void OnKeyRelease(AZUL_KEY k) override;
	void OnKeyPress(AZUL_KEY k) override;
	void OnKeyRelease(AZUL_KEY k) override;

	Matrix GetRotation() { return GunRot * ShipRot; }
	Vect GetTranslation() { return ShipPos;}
	Matrix GetWorld() { return world; }
};

#endif // !_Frigate
