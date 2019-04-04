#include "StartSceneFrigate.h"
#include "../EngineCode/SceneManager.h"
#include "DebugOut.h"
#include "../EngineCode/MithrilEngine.h"
#include "BulletFactory.h"
#include "EnemySpawner.h"
#include "../EngineCode/AlarmEnum.h"
#include "SecondScene.h"
#include "Axis.h"
#include "../EngineCode/Sprite.h"
#include <string>
#include "DebugOut.h"
#include "../EngineCode/MathTools.h"
#include "../EngineCode/TimeManager.h"
#include "../EngineCode/SoundManager.h"
#include "Mouse.h"


StartSceneFrigate::StartSceneFrigate()
{
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGObj_SpaceStartSceneFrigateLight = new GraphicsObject_TextureLight(ModelManager::GetModel("TankBottom"), ShaderManager::GetShader(ShaderManager::DefaultShader::LightRender), TextureManager::GetTexture("SpaceFrigateTex"), LightColor, LightPos);
	pGObj_TankTop = new GraphicsObject_TextureLight(ModelManager::GetModel("TankTop"), ShaderManager::GetShader(ShaderManager::DefaultShader::LightRender), TextureManager::GetTexture("SpaceFrigateTex"), LightColor, LightPos);

	ShipScale.set(SCALE, 6.5f, 6.5f, 6.5f);
	ShipRot.set(IDENTITY);
	ShipPos.set(0, 0, 0);
	GunRot = ShipRot;
	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_SpaceStartSceneFrigateLight->SetWorld(world);
	pGObj_TankTop->SetWorld(world);

	CamRot.set(IDENTITY);

	SubmitUpdateRegistration();
	SubmitDrawRegistration();
	SubmitKeyEventRegistration(AZUL_KEY::KEY_SPACE, Inputable::EVENT_TYPE::KEY_RELEASE);

	UI = new Sprite("StartUI");
	UI->SetPos(MithrilEngine::GetWidth() / 2.0f, MithrilEngine::GetHeight() / 2.0f);
	UI->SetCenter(0, 0);

	currentCamera = SceneManager::GetCurrent3DCamera();
	current2DCamera = SceneManager::GetCurrent2DCamera();

	SoundManager::PlaySound2D("StartMusic", true);
}

StartSceneFrigate::~StartSceneFrigate()
{
	delete pGObj_SpaceStartSceneFrigateLight;

	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitKeyEventDeregistration(AZUL_KEY::KEY_SPACE, EVENT_TYPE::KEY_RELEASE);

	delete UI;
}

void StartSceneFrigate::Update()
{
	// Spaceship adjust matrix
	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_SpaceStartSceneFrigateLight->SetWorld(world);

	gunWorld = ShipScale * GunRot * ShipRot * Matrix(TRANS, ShipPos);
	//DebugMsg::out("%4f, %4f, %4f\n", ShipPos.X(), ShipPos.Y(), ShipPos.Z());
	pGObj_TankTop->SetWorld(gunWorld);

	CamRot *= Matrix(ROT_Y, 0.01f);

	currentCamera->setOrientAndPosition(Vect(0, 1, 0), ShipPos + Vect(0, 25, 0), Vect(0, 80, -210) * CamRot * Matrix(TRANS, ShipPos));
	//currentCamera->setOrientAndPosition(Vect(0, 1, 0), ShipPos + Vect(0, 25, 0), Vect(0, 350, -550) * ShipRot * Matrix(TRANS, ShipPos));
	currentCamera->updateCamera();
	current2DCamera->updateCamera();
	//DebugMsg::out("Tank Point: %2f, %2f, %2f\n", ShipPos.X(), ShipPos.Y(), ShipPos.Z());
}

void StartSceneFrigate::Draw()
{
	pGObj_SpaceStartSceneFrigateLight->Render(SceneManager::GetCurrentScene()->GetCamManager()->GetCurrentCamera());
	pGObj_TankTop->Render(SceneManager::GetCurrentScene()->GetCamManager()->GetCurrentCamera());
}

void StartSceneFrigate::Draw2D()
{
	UI->Render();
}

void StartSceneFrigate::OnKeyRelease(AZUL_KEY k)
{
	if (k == AZUL_KEY::KEY_SPACE)
	{
		SoundManager::StopSound("StartMusic");
		SceneManager::SubmitSceneChange(new FirstScene());
	}
}
