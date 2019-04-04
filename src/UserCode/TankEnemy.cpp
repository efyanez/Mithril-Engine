#include "../EngineCode/SceneManager.h"
#include "../EngineCode/MithrilEngine.h"
#include "../EngineCode/AlarmEnum.h"
#include <string>
#include "TankEnemy.h"
#include "EnemyFactory.h"
#include "Frigate.h"
#include "../EngineCode/Visualizer.h"
#include "../EngineCode/ColorLibrary.h"
#include "EnemyBulletFactory.h"
#include "LVL1Manager.h"
#include <ctime>
#include "FinalScene.h"

TankEnemy::TankEnemy(const Matrix& mscale, const Matrix& mrot, const Vect& mpos, Frigate* p)
{
	Vect LightColor(1.0f, 1.0f, 1.0f, 1.0f);
	Vect LightPos(1.0f, 100.0f, 100.0f, 1.0f);
	pGObj_TankEnemy = new GraphicsObject_TextureLight(ModelManager::GetModel("EnemyTank"), ShaderManager::GetShader(ShaderManager::DefaultShader::LightRender), TextureManager::GetTexture("EnemyTankTex"), TextureManager::GetTexture("EnemyTankTex"), TextureManager::GetTexture("EnemyTankTex"), TextureManager::GetTexture("EnemyTankTex"), LightColor, LightPos);
	Scale.set(SCALE, 0.8f, 0.8f, 0.8f);

	SetColliderModel(pGObj_TankEnemy->getModel(), CollisionType::OBB);
	//SetColliderModel(pGObj_SpaceFrigateLight->getModel(), CollisionType::AABB);
	state = &TankEnemy::state_Idle;

	//Scale = mscale;
	(void)mscale;
	Rot = mrot;
	Pos = mpos;
	world = Scale * Rot * Matrix(TRANS, Pos);
	pGObj_TankEnemy->SetWorld(world);
	std::srand((unsigned int)time(0));
	player = p;
	state = &TankEnemy::state_Idle;

	this->GameObject::SubmitEntry();
}

TankEnemy::~TankEnemy()
{
	delete pGObj_TankEnemy;
}

void TankEnemy::Update()
{
	(this->*state)();

	UpdateCollisionData(world);
}

void TankEnemy::state_Idle()
{
	float newX = player->GetTranslation().X() - Pos.X();
	float newZ = player->GetTranslation().Z() - Pos.Z();

	float ang = atan2(newX, newZ);
	Pos.Y() = 10.0f;
	Pos += Vect(0, 0, 1) * Rot * TransSpeed;
	Rot = Matrix(ROT_Y, ang);
	world = Scale * Rot * Matrix(TRANS, Pos);
	pGObj_TankEnemy->SetWorld(world);

	if ((Vect(player->GetTranslation() - Pos).mag()) <= 550)
	{
		state = &TankEnemy::state_FollowPlayer;
	}

}

void TankEnemy::state_FollowPlayer()
{

	float newX = player->GetTranslation().X() - Pos.X();
	float newZ = player->GetTranslation().Z() - Pos.Z();

	float ang = atan2(newX, newZ);

	Pos += Vect(0, 1 * upSpeed, 2) * Rot * TransSpeed;
	Rot = Matrix(ROT_Y, ang);
	world = Scale * Rot * Matrix(TRANS, Pos);
	pGObj_TankEnemy->SetWorld(world);

	if ((Vect(player->GetTranslation() - Pos).mag()) > 550)
	{
		state = &TankEnemy::state_Idle;
	}
}

void TankEnemy::Draw()
{
	pGObj_TankEnemy->Render(SceneManager::GetCurrent3DCamera());
	//pGObj_SpaceshipBSphere->Render(SceneManager::GetCurrentScene()->GetCamManager()->GetCurrentCamera());
	if (bDebugCol)
	{
		//Visualizer::ShowSphere(GetBSphere(), Colors::Red);
		//Visualizer::ShowCollisionVolume(this, Colors::Red);
		Visualizer::VisualizeMe(this, Colors::Red);
	}
	else
	{
		//Visualizer::ShowSphere(GetBSphere(), Colors::Blue);
		//Visualizer::ShowCollisionVolume(this, Colors::Blue);
		Visualizer::VisualizeMe(this, Colors::Blue);
	}
	bDebugCol = false;
}


void TankEnemy::Collision(Collidable *)
{
	//DebugMsg::out("Colliding with Collidable!\n");
}

void TankEnemy::Collision(Frigate *)
{
	LVL1Manager::UpdateScore();
	GameObject::SubmitExit();
	//DebugMsg::out("Colliding with Frigate!\n");
}

void TankEnemy::Collision(Bullet *)
{
	LVL1Manager::UpdateScore();
	bDebugCol = true;
	totalHealth--;
	if (totalHealth <= 0) 
	{
		GameObject::SubmitExit();
	}
	//DebugMsg::out("Colliding with Bullet!\n");
}

void TankEnemy::SceneEntry()
{
	SubmitUpdateRegistration();
	SubmitDrawRegistration();
	SubmitCollisionRegistration<TankEnemy>(this);
	SubmitAlarmRegistration(1.0f, AlarmEnum::AlarmID::Alarm_1);
}

void TankEnemy::SceneExit()
{
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration<TankEnemy>(this);
	SubmitAlarmDeregistration(AlarmEnum::AlarmID::Alarm_1);
	SceneManager::SubmitSceneChange(new FinalScene());
}

void TankEnemy::Alarm1()
{
	upSpeed *= -1;
	EnemyBulletFactory::CreateBullet(this);
	EnemyBulletFactory::CreateBullet(this, -15.0f, 5.0f, 0.0f);
	EnemyBulletFactory::CreateBullet(this, 15.0f, 5.0f, 0.0f);
	SubmitAlarmRegistration(1.0f, AlarmEnum::AlarmID::Alarm_1);
}
