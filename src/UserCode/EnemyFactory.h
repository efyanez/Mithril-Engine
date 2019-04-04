#ifndef _EnemyFactory
#define _EnemyFactory

#include <stack>
#include "Enemy.h"

class Frigate;

class EnemyFactory
{
private:

	static EnemyFactory* ptrInstance;			// Game set up as a singleton

	EnemyFactory() = default;												// Private constructor
	EnemyFactory(const EnemyFactory&) = delete;				// Prevent copy-construction
	EnemyFactory& operator=(const EnemyFactory&) = delete;	// Prevent assignment
	~EnemyFactory();														// Only this class can delete

	static EnemyFactory& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new EnemyFactory;
		return *ptrInstance;
	};

	std::stack<Enemy*> recycledItems;  // Back to be a non-static member
	std::stack<Enemy*> activeItems;

										// Note: Some facctory designs also keep a list of 'currently active' objects
										// Often useful at cleanup time. Not needed for this demo however

										// Private methods to perform actual work on member var
	void privCreateEnemy(const Matrix& mscale, const Matrix& mrot, const Vect& mpos, Frigate* p);
	void privRecycleEnemy(Enemy* e);
	void privTerminate();

public:

	// Services/API
	static void CreateEnemy(const Matrix& mscale, const Matrix& mrot, const Vect& mpos, Frigate* p) { Instance().privCreateEnemy(mscale, mrot, mpos, p); };
	static void RecycleEnemy(Enemy* e) { Instance().privRecycleEnemy(e); };

	static void Terminate() { Instance().privTerminate(); };
};


#endif _EnemyFactory