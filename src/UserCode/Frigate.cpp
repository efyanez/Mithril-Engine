#include "Frigate.h"
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
#include "../EngineCode/SpriteFont.h"
#include "../EngineCode/SpriteString.h"


Frigate::Frigate()
{
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGObj_SpaceFrigateLight = new GraphicsObject_TextureLight(ModelManager::GetModel("TankBottom"), ShaderManager::GetShader(ShaderManager::DefaultShader::LightRender), TextureManager::GetTexture("SpaceFrigateTex"), LightColor, LightPos);
	pGObj_TankTop = new GraphicsObject_TextureLight(ModelManager::GetModel("TankTop"), ShaderManager::GetShader(ShaderManager::DefaultShader::LightRender), TextureManager::GetTexture("SpaceFrigateTex"), LightColor, LightPos);

	Vect Blue(0.0f, 0.0f, 1.0f, 1.0f);
	pGObj_SpaceshipBSphere = new GraphicsObject_WireframeConstantColor(ModelManager::GetModel("UnitSphere"), ShaderManager::GetShader("ColorConstantRender"), Blue);
	health = 3;

	ShipScale.set(SCALE, 6.5f, 6.5f, 6.5f);
	ShipRot.set(IDENTITY);
	ShipPos.set(0, 0, 0);
	GunRot = ShipRot;
	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_SpaceFrigateLight->SetWorld(world);
	pGObj_TankTop->SetWorld(world);

	//SetColliderModel(pGObj_SpaceFrigateLight->getModel(), CollisionType::BSphere);
	SetColliderModel(pGObj_SpaceFrigateLight->getModel(), CollisionType::OBB);

	UI = new Sprite("UI");
	UI->SetPos(MithrilEngine::GetWidth() / 2.0f, MithrilEngine::GetHeight() / 2.0f);
	UI->SetCenter(0, 0);

	Hearts3 = new Sprite("Hearts3");
	Hearts3->SetPos(MithrilEngine::GetWidth() / 2.0f, MithrilEngine::GetHeight() / 2.0f);
	Hearts2 = new Sprite("Hearts2");
	Hearts2->SetPos(MithrilEngine::GetWidth() / 2.0f, MithrilEngine::GetHeight() / 2.0f);
	Hearts1 = new Sprite("Hearts1");
	Hearts1->SetPos(MithrilEngine::GetWidth() / 2.0f, MithrilEngine::GetHeight() / 2.0f);

	currentCamera = SceneManager::GetCurrent3DCamera();
	current2DCamera = SceneManager::GetCurrent2DCamera();

	endPos = (ShipPos + Vect(250, 0, 125));
	startTime = TimeManager::GetFrameTime();
	distance = (ShipPos - endPos).mag();

	myString = new SpriteString("BerlinSans", "My pos: 0.0f, 2.0f", 520.0f, 20.0f);

	GameObject::SubmitEntry();

}

Frigate::~Frigate()
{
	delete pGObj_SpaceFrigateLight;
	delete pGObj_SpaceshipBSphere;

	delete UI;
	delete Hearts1;
	delete Hearts2;
	delete Hearts3;
}

void Frigate::SceneEntry()
{

	SubmitUpdateRegistration();
	SubmitDrawRegistration();

	//SubmitAlarmRegistration(2.0f, AlarmEnum::AlarmID::Alarm_0);
	SubmitAlarmRegistration(4.0f, AlarmEnum::AlarmID::Alarm_1);

	SubmitKeyEventRegistration(AZUL_KEY::KEY_SPACE, Inputable::EVENT_TYPE::KEY_PRESS);
	SubmitKeyEventRegistration(AZUL_KEY::KEY_R, Inputable::EVENT_TYPE::KEY_RELEASE);

	SubmitCollisionRegistration<Frigate>(this);
}

void Frigate::SceneExit()
{
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration<Frigate>(this);
	//SubmitAlarmDeregistration(AlarmEnum::AlarmID::Alarm_0);
	//SubmitAlarmDeregistration(AlarmEnum::AlarmID::Alarm_1);

	SubmitKeyEventDeregistration(AZUL_KEY::KEY_T, Inputable::EVENT_TYPE::KEY_PRESS);
	SubmitKeyEventDeregistration(AZUL_KEY::KEY_R, Inputable::EVENT_TYPE::KEY_RELEASE);
	BulletFactory::Terminate();
}

void Frigate::Update()
{
	//float distanceCovered = (TimeManager::GetFrameTime() - startTime) * ShipTransSpeed;
	//float fracJourney = distanceCovered / distance;
	//ShipPos = MathTools::Lerp(ShipPos, endPos, fracJourney);

	float x;
	float y;
	Mouse* m = Mouse::GetInstance();
	m->GetCursor(x, y);
	//DebugMsg::out("%2f, %2f\n", x, y);
	Matrix viewProjectionInverse = (currentCamera->getProjMatrix() * currentCamera->getViewMatrix());
	viewProjectionInverse = viewProjectionInverse.getInv();
	Vect point3D = Vect(MithrilEngine::GetWidth() - x, MithrilEngine::GetHeight() - y, -1, 1);
	point3D = point3D * viewProjectionInverse;
	//DebugMsg::out("3D Point: %2f, %2f, %2f\n", point3D.X(), point3D.Y(), point3D.Z());


	// Ship translation movement (not using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
	{
		ShipPos += Vect(0, 0, 2) * ShipRot * ShipTransSpeed;
		
		if(!SoundManager::IsSoundPlaying("TankMove")) SoundManager::PlaySound2D("TankMove", true);
		//if (!SoundManager::IsSoundPlaying("TankMove")) SoundManager::PlayWithDistortionEffect("TankMove");
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
	{
		ShipPos += Vect(0, 0, 2) * ShipRot * -ShipTransSpeed;
		if (!SoundManager::IsSoundPlaying("TankMove")) SoundManager::PlaySound2D("TankMove", true);
		//if (!SoundManager::IsSoundPlaying("TankMove")) SoundManager::PlayWithChorusEffect("TankMove", 80.0f, 50.0f, 50.0f);
	}
	else
	{
		SoundManager::StopSound("TankMove");
	}

	// Ship Rotation movement (not using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_A))
	{
		ShipRot *= Matrix(ROT_Y, ShipRotAng);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_D))
	{
		ShipRot *= Matrix(ROT_Y, -ShipRotAng);
	}

	if (Keyboard::GetKeyState(AZUL_KEY::KEY_Q))
	{
		GunRot *= Matrix(ROT_Y, ShipRotAng);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_E))
	{
		GunRot *= Matrix(ROT_Y, -ShipRotAng);
	}

	// Spaceship adjust matrix
	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_SpaceFrigateLight->SetWorld(world);

	myString->SetText("Pos: " + std::to_string(ShipPos.X()) + ", " + std::to_string(ShipPos.Z()));

	//*
	// Adjusting the spaceship's bounding sphere
	Vect vBSSize = pGObj_SpaceFrigateLight->getModel()->getRadius() * Vect(1, 1, 1);
	Vect vBSPos = pGObj_SpaceFrigateLight->getModel()->getCenter();

	// Adjust the Bounding Sphere's position and scale to fit the Ship's center and scale
	Matrix worldBS = Matrix(SCALE, vBSSize) * Matrix(TRANS, vBSPos) * world;

	// Toggle the bounding sphere's visibility
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_SPACE))
	{
		BsphereToggle = true;
	}
	else
	{
		BsphereToggle = false;
	}

	gunWorld = ShipScale * GunRot * ShipRot * Matrix(TRANS, ShipPos);
	//DebugMsg::out("%4f, %4f, %4f\n", ShipPos.X(), ShipPos.Y(), ShipPos.Z());
	pGObj_TankTop->SetWorld(gunWorld);

	UpdateCollisionData(world);

	currentCamera->setOrientAndPosition(Vect(0, 1, 0), ShipPos + Vect(0, 25, 0), Vect(0, 50, -150) * ShipRot * Matrix(TRANS, ShipPos));
	//currentCamera->setOrientAndPosition(Vect(0, 1, 0), ShipPos + Vect(0, 25, 0), Vect(0, 350, -550) * ShipRot * Matrix(TRANS, ShipPos));
	currentCamera->updateCamera();
	current2DCamera->updateCamera();
	//DebugMsg::out("Tank Point: %2f, %2f, %2f\n", ShipPos.X(), ShipPos.Y(), ShipPos.Z());
}

void Frigate::Draw()
{
	pGObj_SpaceFrigateLight->Render(SceneManager::GetCurrentScene()->GetCamManager()->GetCurrentCamera());
	pGObj_TankTop->Render(SceneManager::GetCurrentScene()->GetCamManager()->GetCurrentCamera());

	if (bDebugCol)
	{
		//Visualizer::VisualizeMe(this, Colors::Red);
	}
	else
	{
		//Visualizer::VisualizeMe(this, Colors::Blue);
	}
	bDebugCol = false;
}

void Frigate::Draw2D()
{
	UI->Render();
	myString->Render();
	switch (health)
	{
	case 3:
		Hearts3->Render();
		break;
	case 2:
		Hearts2->Render();
		break;
	case 1:
		Hearts1->Render();
		break;
	case 0:
		GameObject::SubmitExit();
		SceneManager::SubmitSceneChange(new FinalScene());
		break;
	default:
		Hearts1->Render();
		break;
	}
}

void Frigate::Alarm0()
{
	//ShipPos += Vect(0, 0, 2) * ShipRot * ShipTransSpeed;
	//SubmitAlarmRegistration(2.0f, AlarmEnum::AlarmID::Alarm_0);
}

void Frigate::Alarm1()
{
	//BulletFactory::CreateBullet(this);
	//SubmitAlarmRegistration(4.0f, AlarmEnum::AlarmID::Alarm_1);
	//KeyEventDeregistration(AZUL_KEY::KEY_T, EVENT_TYPE::KEY_PRESS);
}

void Frigate::Collision(Collidable*)
{
	//DebugMsg::out("Colliding with Collidable!\n");
}

void Frigate::Collision(Enemy *)
{
	//DebugMsg::out("Colliding with Enemy!\n");
	bDebugCol = true;
	health -= 1;
}

void Frigate::Collision(EnemyBullet *)
{
	//DebugMsg::out("Colliding with Enemy Bullet!\n");
	bDebugCol = true;
	health -= 1;
}

void Frigate::Collision(Pyramid *)
{
	bDebugCol = true;
}

void Frigate::TerrainCollision(CollisionVolumeAABB& cellAABB)
{
	Vect newPos = Vect(ShipPos.X(), cellAABB.GetCenterWorld().Y(), ShipPos.Z());
	ShipPos = newPos;

	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_SpaceFrigateLight->SetWorld(world);

	gunWorld = ShipScale * GunRot * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_TankTop->SetWorld(gunWorld);
}

void Frigate::OnKeyPress(AZUL_KEY k)
{
	switch (k)
	{
	case(AZUL_KEY::KEY_SPACE):
		BulletFactory::CreateBullet(this);
		//DebugMsg::out("T key pressed!\n");
		break;
	default:
		break;
	}
}

void Frigate::OnKeyRelease(AZUL_KEY k)
{
	switch (k)
	{
	case(AZUL_KEY::KEY_R):
		//DebugMsg::out("R key released!\n");
		this->GameObject::SubmitExit();
		SceneManager::SubmitSceneChange(new SecondScene());
		break;
	default:
		break;
	}
}