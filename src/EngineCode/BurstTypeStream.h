#ifndef _BurstTypeStream_H
#define _BurstTypeStream_H

#include "BurstType.h"

class BurstTypeStream : public BurstType
{

	friend class Burst;
	friend class ParticleEmitter;

protected:
	BurstTypeStream();
	~BurstTypeStream() override;
	BurstTypeStream & operator=(BurstTypeStream&other) = delete;
	BurstTypeStream(BurstTypeStream&other) = delete;

	virtual void CalculatePosition(Vect& pos, Vect& direction, float speed, float tightness) override;
};

#endif // !_BurstTypeStream_H
