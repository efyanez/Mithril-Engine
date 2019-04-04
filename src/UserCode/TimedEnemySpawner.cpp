#include "TimedEnemySpawner.h"
#include "Enemy.h"
#include "EnemyFactory.h"
#include "Frigate.h"
#include "LVL1Manager.h"

TimedEnemySpawner::TimedEnemySpawner(Frigate* p)
{
	Scale.set(SCALE, 1.0f, 1.0f, 1.0f);
	Rot.set(IDENTITY);
	Pos.set(0, 20.0f, 0);
	world = Scale * Rot * Matrix(TRANS, Pos);
	SubmitAlarmRegistration(2.0f, AlarmEnum::AlarmID::Alarm_0);
	SubmitKeyEventRegistration(AZUL_KEY::KEY_K, Inputable::EVENT_TYPE::KEY_PRESS);
	SubmitUpdateRegistration();
	player = p;
	LVL1Manager::SetGoal(numEnemies);
}

TimedEnemySpawner::~TimedEnemySpawner()
{
}

void TimedEnemySpawner::Update()
{
	//DebugMsg::out("Remaining time on Alarm 0: %2f\n", SceneManager::GetCurrentScene()->GetRemainingTime(this, AlarmEnum::AlarmID::Alarm_0));
}

void TimedEnemySpawner::Alarm0()
{
	numEnemies--;
	if (numEnemies >= 0)
	{
		int randPosX = rand() % 150 + (-150);
		Pos.set((float)randPosX, 20.0f, 0);
		world = Scale * Rot * Matrix(TRANS, Pos);
		EnemyFactory::CreateEnemy(Scale, Rot, Pos, player);
		SubmitAlarmRegistration(1.5f, AlarmEnum::AlarmID::Alarm_0);
	}
	//SceneManager::GetCurrentScene()->AddTime(5.0f, this, AlarmEnum::AlarmID::Alarm_0);
}

void TimedEnemySpawner::OnKeyPress(AZUL_KEY k)
{
	if (k == AZUL_KEY::KEY_K)
	{
		SubmitAlarmDeregistration(AlarmEnum::AlarmID::Alarm_0);
	}
}
