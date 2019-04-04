#ifndef _BulletFactory
#define _BulletFactory

#include <stack>
#include "Matrix.h"
#include "Bullet.h"
class Frigate;
class BulletFactory
{
private:

	static BulletFactory* ptrInstance;			// Game set up as a singleton

	BulletFactory() = default;												// Private constructor
	BulletFactory(const BulletFactory&) = delete;				// Prevent copy-construction
	BulletFactory& operator=(const BulletFactory&) = delete;	// Prevent assignment
	~BulletFactory();														// Only this class can delete

	static BulletFactory& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new BulletFactory;
		return *ptrInstance;
	};

	std::stack<Bullet*> recycledItems;  // Back to be a non-static member
	std::stack<Bullet*> activeItems;

										// Note: Some facctory designs also keep a list of 'currently active' objects
										// Often useful at cleanup time. Not needed for this demo however

										// Private methods to perform actual work on member var
	void privCreateBullet(Frigate* rotation);
	void privRecycleBullet(Bullet* b);
	void privTerminate();

public:

	// Services/API
	static void CreateBullet(Frigate* rotation) { Instance().privCreateBullet(rotation); };
	static void RecycleBullet(Bullet* b) { Instance().privRecycleBullet(b); };

	static void Terminate() { Instance().privTerminate(); };
};


#endif _BulletFactory