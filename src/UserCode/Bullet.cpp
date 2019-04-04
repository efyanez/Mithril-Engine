#include "Bullet.h"
#include "../EngineCode/SceneManager.h"
#include "../EngineCode/Updatable.h"
#include "../EngineCode/Drawable.h"
#include "DebugOut.h"
#include "../EngineCode/MithrilEngine.h"
#include "BulletFactory.h"
#include "Frigate.h"
#include "Enemy.h"
#include "../EngineCode/AlarmEnum.h"
#include <string>
#include "../EngineCode/Visualizer.h"
#include "../EngineCode/SoundManager.h"
#include "../EngineCode/ParticleEffectManager.h"

Bullet::Bullet()
{
	bulletModel = new GraphicsObject_TextureFlat(ModelManager::GetModel("UnitSphere"), ShaderManager::GetShader(ShaderManager::DefaultShader::FlatRender), TextureManager::GetTexture("SpaceFrigateTex"));
	Vect pos(0.0f, 60.0f, 0.0f);
	Matrix rot(IDENTITY);

	pe = ParticleEffectManager::GetParticleEffect("Explosion");
}

Bullet::~Bullet()
{
	delete bulletModel;
}

void Bullet::SceneEntry()
{
	SubmitUpdateRegistration();
	SubmitDrawRegistration();
	SubmitAlarmRegistration(1.0f, AlarmEnum::AlarmID::Alarm_0);
	SubmitCollisionRegistration<Bullet>(this);
	SetColliderModel(bulletModel->getModel(), CollisionType::BSphere);
	SoundManager::PlaySound2D("TankShot", false);
}

void Bullet::SceneExit()
{
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration<Bullet>(this);
	BulletFactory::RecycleBullet(this);
}

void Bullet::Collision(Collidable *)
{
}

void Bullet::Collision(Enemy *)
{
	pe->SpawnParticleEmitter(bPos, bRot, false);
	GameObject::SubmitExit();
	SubmitAlarmDeregistration(AlarmEnum::AlarmID::Alarm_0);
}

void Bullet::Initialize(Frigate* rotation)
{
	bScale.set(SCALE, 6.0f, 6.0f, 6.0f);
	bRot = rotation->GetRotation();
	bPos = Vect(0, 0, 0) + rotation->GetTranslation();
	world = bScale * bRot * Matrix(TRANS, bPos);
	bulletModel->SetWorld(world);
}

void Bullet::Update()
{
	bPos += Vect(0, 0.3f, 3) * bRot * bSpeed;
	world = bScale * bRot * Matrix(TRANS, bPos);
	bulletModel->SetWorld(world);
	UpdateCollisionData(world);
}

void Bullet::Draw()
{
	bulletModel->Render(SceneManager::GetCurrentScene()->GetCamManager()->GetCurrentCamera());
	//Visualizer::ShowSphere(GetBSphere(), Colors::Blue);
}

void Bullet::Alarm0()
{
	GameObject::SubmitExit();
}
