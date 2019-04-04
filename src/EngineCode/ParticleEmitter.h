#ifndef _ParticleEmitter_H
#define _ParticleEmitter_H

#include "Vect.h"
#include "Matrix.h"
#include "Align16.h"
#include "Drawable.h"
#include "Alarmable.h"
#include "BurstPattern.h"
#include <stack>
#include <deque>

class ParticleEffect;
class Burst;

class ParticleEmitter : public Drawable, public Alarmable, public Align16
{

private:
	ParticleEffect* pParticleEffect;
	Vect Position;
	Matrix Rotation;
	Matrix WorldMat;
	float BurstInterval;
	bool loopEffect;

	std::stack<Burst*> recycledBursts;
	std::deque<Burst*> burstCollection;

	//! Specialized constructor for Particle Emitter, must not be called externally outside of Particle Effect
	/*!
	\ingroup Particles
	\param float The burst tightness
	*/
	ParticleEmitter(ParticleEffect* pe, const Vect & pos, const Matrix & rot, bool loop = true);

public:

	friend class ParticleEffect;

	ParticleEmitter();

	ParticleEmitter(const ParticleEmitter& other) = delete;

	ParticleEmitter & operator=(const ParticleEmitter& other) = delete;
	~ParticleEmitter();

	void SceneEntry() override;
	void SceneExit() override;

	void Draw() override;

	void Alarm0() override;

	void NewBurst();

};

#endif // !_ParticleEmitter_H
