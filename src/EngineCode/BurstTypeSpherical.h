#ifndef _BurstTypeSpherical_H
#define _BurstTypeSpherical_H

#include "BurstType.h"

class BurstTypeSpherical : public BurstType
{

	friend class Burst;
	friend class ParticleEmitter;

protected:
	BurstTypeSpherical();
	~BurstTypeSpherical() override;
	BurstTypeSpherical & operator=(BurstTypeSpherical&other) = delete;
	BurstTypeSpherical(BurstTypeSpherical&other) = delete;

	virtual void CalculatePosition(Vect& pos, Vect& direction, float speed, float tightness) override;
};

#endif // !_BurstTypeSpherical_H
