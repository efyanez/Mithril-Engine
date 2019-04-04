#ifndef _TimedEnemySpawner
#define _TimedEnemySpawner

#include "AzulCore.h"
#include "../EngineCode/Updatable.h"
#include "../EngineCode/Alarmable.h"
#include "../EngineCode/Inputable.h"
#include "Align16.h"

class Frigate;

class TimedEnemySpawner : public Updatable, public Alarmable, public Inputable, public Align16
{
private:

	Matrix world;
	Matrix Scale;
	Vect Pos;
	Matrix Rot;

	Frigate* player;

	int numEnemies = 6;

public:
	TimedEnemySpawner() = default;
	TimedEnemySpawner(Frigate* p);
	virtual ~TimedEnemySpawner();

	void Update() override;

	void Alarm0() override;

	void OnKeyPress(AZUL_KEY k) override;

	Matrix GetRotation() { return Rot; };
	Vect GetTranslation() { return Pos; }
};

#endif // !_TimedEnemySpawner
