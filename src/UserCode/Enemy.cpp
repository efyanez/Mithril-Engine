#include "../EngineCode/SceneManager.h"
#include "../EngineCode/MithrilEngine.h"
#include "../EngineCode/AlarmEnum.h"
#include <string>
#include "Enemy.h"
#include "EnemyFactory.h"
#include "Frigate.h"
#include "../EngineCode/Visualizer.h"
#include "../EngineCode/ColorLibrary.h"
#include "EnemyBulletFactory.h"
#include "LVL1Manager.h"
#include <ctime>

Enemy::Enemy()
{
	Vect LightColor(1.0f, 1.0f, 1.0f, 1.0f);
	Vect LightPos(1.0f, 100.0f, 100.0f, 1.0f);
	pGObj_SpaceFrigateLight = new GraphicsObject_TextureLight(ModelManager::GetModel("Frigate"), ShaderManager::GetShader(ShaderManager::DefaultShader::LightRender), TextureManager::GetTexture("SpaceFrigateTex"), LightColor, LightPos);
	Scale.set(SCALE, 1.0f, 1.0f, 1.0f);

	SetColliderModel(pGObj_SpaceFrigateLight->getModel(), CollisionType::AABB);
	//SetColliderModel(pGObj_SpaceFrigateLight->getModel(), CollisionType::AABB);
	state = &Enemy::state_Idle;
}

Enemy::~Enemy()
{
	delete pGObj_SpaceFrigateLight;
}

void Enemy::Initialize(const Matrix& mscale, const Matrix& mrot, const Vect& mpos, Frigate* p)
{

	//Scale = mscale;
	(void)mscale;
	Rot = mrot;
	Pos = mpos;
	world = Scale * Rot * Matrix(TRANS, Pos);
	pGObj_SpaceFrigateLight->SetWorld(world);
	SubmitCollisionRegistration<Enemy>(this);
	std::srand((unsigned int)time(0));
	player = p;
	state = &Enemy::state_Idle;
}

void Enemy::Update()
{
	(this->*state)();

	UpdateCollisionData(world);
}

void Enemy::state_Idle()
{
	int rotationFactor = rand() % (50) + (0);
	Pos += Vect(0, 0, 1) * Rot * TransSpeed;
	Rot *= Matrix(ROT_Y, (float)rotationFactor / 10000.0f);
	world = Scale * Rot * Matrix(TRANS, Pos);
	pGObj_SpaceFrigateLight->SetWorld(world);

	if ((Vect(player->GetTranslation() - Pos).mag()) <= 250)
	{
		state = &Enemy::state_FollowPlayer;
	}

}

void Enemy::state_FollowPlayer()
{

	float newX = player->GetTranslation().X() - Pos.X();
	float newZ = player->GetTranslation().Z() - Pos.Z();

	float ang = atan2(newX, newZ);

	Pos += Vect(0, 0, 1) * Rot * TransSpeed;
	Rot = Matrix(ROT_Y, ang);
	world = Scale * Rot * Matrix(TRANS, Pos);
	pGObj_SpaceFrigateLight->SetWorld(world);

	if ((Vect(player->GetTranslation() - Pos).mag()) > 250)
	{
		state = &Enemy::state_Idle;
	}
}

void Enemy::Draw()
{
	pGObj_SpaceFrigateLight->Render(SceneManager::GetCurrent3DCamera());
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


void Enemy::Collision(Collidable *)
{
	//DebugMsg::out("Colliding with Collidable!\n");
}

void Enemy::Collision(Frigate *)
{
	LVL1Manager::UpdateScore();
	GameObject::SubmitExit();
	//DebugMsg::out("Colliding with Frigate!\n");
}

void Enemy::Collision(Bullet *)
{
	LVL1Manager::UpdateScore();
	bDebugCol = true;
	GameObject::SubmitExit();
	//DebugMsg::out("Colliding with Bullet!\n");
}

void Enemy::Collision(Enemy *)
{
	bDebugCol = true;
	//DebugMsg::out("Colliding with Enemy!\n");
}

void Enemy::SceneEntry()
{
	SubmitUpdateRegistration();
	SubmitDrawRegistration();
	SubmitAlarmRegistration(10.0f, AlarmEnum::AlarmID::Alarm_0);
	SubmitAlarmRegistration(1.0f, AlarmEnum::AlarmID::Alarm_1);
}

void Enemy::SceneExit()
{
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration<Enemy>(this);
	SubmitAlarmDeregistration(AlarmEnum::AlarmID::Alarm_0);
	SubmitAlarmDeregistration(AlarmEnum::AlarmID::Alarm_1);
	EnemyFactory::RecycleEnemy(this);
}

void Enemy::Alarm0()
{
	GameObject::SubmitExit();
}

void Enemy::Alarm1()
{
	EnemyBulletFactory::CreateBullet(this);
	SubmitAlarmRegistration(1.0f, AlarmEnum::AlarmID::Alarm_1);
}
