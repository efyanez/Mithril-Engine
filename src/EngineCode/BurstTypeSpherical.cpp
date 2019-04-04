#include "BurstTypeSpherical.h"

BurstTypeSpherical::BurstTypeSpherical()
{
}

BurstTypeSpherical::~BurstTypeSpherical()
{
}

void BurstTypeSpherical::CalculatePosition(Vect & pos, Vect& direction, float speed, float tightness)
{
	(void)tightness;
	pos += direction * speed;
}
