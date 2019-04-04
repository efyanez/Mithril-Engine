#ifndef _ParticleEffectSphericalBurst
#define _ParticleEffectSphericalBurst

#include <string>

#include "ParticleEffect.h"

class ParticleEffectSphericalBurst : public ParticleEffect
{
public:
	ParticleEffectSphericalBurst();

	//! Sets the burst interval and life of the effect
	/*!
	\ingroup Particles
	\param float The burst interval
	\param float The burst life
	*/
	void SetBurstIntervalAndLife(float interval = 0.1f, float life = 3.0f);

	//! Sets the burst count of the effect
	/*!
	\ingroup Particles
	\param int The burst count
	*/
	void SetBurstCount(int count = 100.0f);

	//! Sets the burst speed of the effect
	/*!
	\ingroup Particles
	\param float The burst speed
	*/
	void SetSpeed(float s = 1.0f);

	//! Sets the burst scale of the effect
	/*!
	\ingroup Particles
	\param float The burst scale
	*/
	void SetScale(float s = 6.0f);

	//! Sets the burst tightness of the effect
	/*!
	\ingroup Particles
	\param float The burst tightness
	*/
	void SetTightness(float t = 0.89f);


private:

};

#endif // !_ParticleEffectSphericalBurst
