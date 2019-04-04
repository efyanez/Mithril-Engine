#include "BurstTypeStream.h"
#include "TimeManager.h"

BurstTypeStream::BurstTypeStream()
{
}

BurstTypeStream::~BurstTypeStream()
{
}

void BurstTypeStream::CalculatePosition(Vect & pos, Vect & direction, float speed, float tightness)
{
	direction = Vect(direction.X() * tightness, direction.Y() * speed, direction.Z() * tightness);
	direction += Vect(0, -0.05f, 0);
	pos += direction;
}
