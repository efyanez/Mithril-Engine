#ifndef _EnemySpawner
#define _EnemySpawner

#include "AzulCore.h"

class Frigate;

class EnemySpawner
{
private:

	static EnemySpawner* self;
	EnemySpawner() {};
	EnemySpawner(const EnemySpawner&) {};
	EnemySpawner& operator= (const EnemySpawner) {};
	~EnemySpawner() {};

	static EnemySpawner& Instance()
	{
		if (!self)
		{
			self = new EnemySpawner();
		}
		return *self;
	};

	void privSpawnEnemies(Frigate* ship, int numEnemies);

public:

	static void SpawnEnemies(Frigate* ship, int numEnemies) { Instance().privSpawnEnemies(ship, numEnemies); };
};

#endif // _!TimeManager