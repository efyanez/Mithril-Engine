#include "LVL1Manager.h"
#include "../EngineCode/SceneManager.h"
#include "SecondScene.h"

LVL1Manager* LVL1Manager::self = NULL;

void LVL1Manager::privSetGoal(int num)
{
	levelGoal = num;
}

void LVL1Manager::privUpdateScore()
{
	currentScore++;
	if (currentScore >= levelGoal)
	{
		SceneManager::SubmitSceneChange(new SecondScene());
	}
}
