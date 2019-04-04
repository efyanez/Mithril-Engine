#ifndef _BurstTypePulse_H
#define _BurstTypePulse_H

#include "BurstType.h"

class BurstTypePulse : public BurstType
{

	friend class Burst;
	friend class ParticleEmitter;

protected:
	BurstTypePulse();
	~BurstTypePulse() override;
	BurstTypePulse & operator=(BurstTypePulse&other) = delete;
	BurstTypePulse(BurstTypePulse&other) = delete;

	virtual void CalculatePosition(Vect& pos, Vect& direction, float speed, float tightness) override;
};

#endif // !_BurstTypePulse_H
