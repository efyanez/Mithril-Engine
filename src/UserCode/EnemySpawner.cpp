#include "EnemySpawner.h"
#include "EnemyFactory.h"
#include "Frigate.h"


EnemySpawner* EnemySpawner::self = NULL;

void EnemySpawner::privSpawnEnemies(Frigate * ship, int numEnemies)
{
	Matrix world;
	Matrix shipWorld = ship->GetWorld();
	float angle = 360.0f / numEnemies;
	assert(ship);
	assert(numEnemies > 0);
	for (int i = 0; i < numEnemies; i++)
	{
		//world = shipWorld * Matrix(ROT_Y, angle * i) * Matrix(TRANS, Vect(0, 0, 40));
		world = Matrix(TRANS, Vect(0, 0, 150)) * Matrix(ROT_Y, angle * i) * shipWorld;
		//EnemyFactory::CreateEnemy(world);
	}
}
