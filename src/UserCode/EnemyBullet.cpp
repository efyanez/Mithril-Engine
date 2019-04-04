#include "EnemyBullet.h"
#include "../EngineCode/SceneManager.h"
#include "../EngineCode/Updatable.h"
#include "../EngineCode/Drawable.h"
#include "DebugOut.h"
#include "../EngineCode/MithrilEngine.h"
#include "EnemyBulletFactory.h"
#include "Frigate.h"
#include "Enemy.h"
#include "../EngineCode/AlarmEnum.h"
#include <string>
#include "../EngineCode/Visualizer.h"

EnemyBullet::EnemyBullet()
{
	bulletModel = new GraphicsObject_TextureFlat(ModelManager::GetModel("UnitSphere"), ShaderManager::GetShader(ShaderManager::DefaultShader::FlatRender), TextureManager::GetTexture("Fire"));
	bSpeed = 3;
}

EnemyBullet::~EnemyBullet()
{
	delete bulletModel;
}

void EnemyBullet::SceneEntry()
{
	SubmitUpdateRegistration();
	SubmitDrawRegistration();
	SubmitAlarmRegistration(5.0f, AlarmEnum::AlarmID::Alarm_0);
	SubmitCollisionRegistration<EnemyBullet>(this);
	SetColliderModel(bulletModel->getModel(), CollisionType::BSphere);
}

void EnemyBullet::SceneExit()
{
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration<EnemyBullet>(this);
	SubmitAlarmDeregistration(AlarmEnum::AlarmID::Alarm_0);
	EnemyBulletFactory::RecycleBullet(this);
}

void EnemyBullet::Collision(Collidable *)
{
}

void EnemyBullet::Collision(Frigate *)
{
	GameObject::SubmitExit();
}

void EnemyBullet::Initialize(Enemy* rotation, float offX, float offY, float offZ)
{
	bScale.set(SCALE, 6.0f, 6.0f, 6.0f);
	bRot = rotation->GetRotation();
	bPos = Vect(0, 0, 0) + rotation->GetTranslation();
	bPos += Vect(offX, offY, offZ);
	world = bScale * bRot * Matrix(TRANS, bPos);
	bulletModel->SetWorld(world);
}

void EnemyBullet::Update()
{
	bPos += Vect(0, 0, 3) * bRot * bSpeed;
	world = bScale * bRot * Matrix(TRANS, bPos);
	bulletModel->SetWorld(world);
	UpdateCollisionData(world);
}

void EnemyBullet::Draw()
{
	bulletModel->Render(SceneManager::GetCurrentScene()->GetCamManager()->GetCurrentCamera());
	//Visualizer::ShowSphere(GetBSphere(), Colors::Blue);

}

void EnemyBullet::Alarm0()
{
	GameObject::SubmitExit();
}
