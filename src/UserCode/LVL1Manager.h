#ifndef _LVL1Manager
#define _LVL1Manager

#include <map>
#include "AzulCore.h"

class LVL1Manager
{
private:
	static LVL1Manager* self;
	LVL1Manager() {};
	LVL1Manager(const LVL1Manager&) {};
	LVL1Manager& operator= (const LVL1Manager&) {};
	~LVL1Manager() {};

	static LVL1Manager& Instance()
	{
		if (!self)
		{
			self = new LVL1Manager();
		}
		return *self;
	};

	int levelGoal = 6;

	int currentScore = 0;


	void privSetGoal(int num);

	void privUpdateScore();

public:

	static void SetGoal(int num) { Instance().privSetGoal(num); }

	static void UpdateScore() { Instance().privUpdateScore(); }


};

#endif _LVL1Manager