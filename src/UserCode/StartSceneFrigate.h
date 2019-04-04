#ifndef _StartSceneFrigate
#define _StartSceneFrigate

#include "AzulCore.h"
#include "../EngineCode/Updatable.h"
#include "../EngineCode/Drawable.h"
#include "../EngineCode/Inputable.h"
#include "Align16.h"
#include "../EngineCode/ModelManager.h"
#include "../EngineCode/ShaderManager.h"
#include "../EngineCode/TextureManager.h"
#include "../EngineCode/CameraManager.h"
#include "DebugOut.h"

class Sprite;

class StartSceneFrigate : public Updatable, public Drawable, public Inputable, public Align16
{
private:

	GraphicsObject_TextureLight *pGObj_SpaceStartSceneFrigateLight;
	GraphicsObject_TextureLight *pGObj_TankTop;

	GraphicsObject_Sprite	*pGObj_Sprite;

	Matrix world;
	Matrix gunWorld;
	Matrix ShipScale;
	Vect ShipPos;
	Matrix ShipRot;
	Matrix GunRot;

	Matrix CamRot;

	Camera* currentCamera;
	Camera* current2DCamera;

	Sprite* UI;

public:
	StartSceneFrigate();
	virtual ~StartSceneFrigate();

	void Update() override;
	void Draw() override;
	void Draw2D() override;

	void OnKeyRelease(AZUL_KEY k) override;

	Matrix GetRotation() { return GunRot * ShipRot; }
	Vect GetTranslation() { return ShipPos; }
	Matrix GetWorld() { return world; }
};

#endif // !_StartSceneFrigate
