#ifndef _Burst_H
#define _Burst_H

#include "Vect.h"
#include "Align16.h"
#include "Alarmable.h"
#include "BurstPattern.h"

class GraphicsObject_TextureFlat;
class BurstType;

class Burst : public Alarmable, public Align16
{

	friend class ParticleEmitter;

protected:

	//! Particle represented as a struct
	struct Particle : public Align16
	{
		Vect pos;
		Vect direction;
		float speed;
	};

	Particle* particleArray;
	Vect currentColor;
	Vect currentScale;
	int myParticleCount;
	float mySpeed;
	float timeLeft;
	float myScale;
	float myTightness;
	bool isDone;

	GraphicsObject_TextureFlat* grObj;

	virtual void Alarm0();

	BurstType* currentBurstType;


protected:

	Burst() = default;

	//! Constructor for a Burst. Should never be called outside of emitter
	/*!
	\ingroup Particles
	*/
	Burst(BurstPattern pattern, int particleCount, Vect & position, float particleSpeed, float tightness, float scale, float lifetime, GraphicsObject_TextureFlat* obj);


	Burst(const Burst& other) = delete;
	Burst & operator=(const Burst& other) = delete;
	~Burst();

	//! Recomputes new burst with position reset
	/*!
	\param position A Vect reference
	*/
	void ComputeNewBurst(Vect & position);

	void DrawParticles();
	void UpdateParticles();
	bool GetStatus();


};

#endif // !_Burst_H
