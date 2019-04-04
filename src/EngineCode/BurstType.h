#ifndef _BurstType_H
#define _BurstType_H

#include "Vect.h"

class BurstType
{

	friend class Burst;
	friend class ParticleEmitter;

protected:
	BurstType() = default;
	virtual ~BurstType() = default;
	BurstType & operator=(BurstType&other) = delete;
	BurstType(BurstType&other) = delete;

	virtual void CalculatePosition(Vect& pos, Vect& direction, float speed, float tightness) 
	{
		(void)pos;
		(void)direction;
		(void)speed;
		(void)tightness;
	};
};

#endif // !_BurstType_H
