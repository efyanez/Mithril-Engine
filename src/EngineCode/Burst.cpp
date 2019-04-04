#include "Burst.h"
#include "SceneManager.h"
#include "CameraManager.h"
#include "MathTools.h"
#include "GraphicsObject_TextureFlat.h"
#include "TimeManager.h"
#include "BurstTypeSpherical.h"
#include "BurstTypePulse.h"
#include "BurstTypeStream.h"

Burst::Burst(BurstPattern pattern, int particleCount, Vect & position, float particleSpeed, float tightness, float scale, float lifetime, GraphicsObject_TextureFlat* obj)
{
	grObj = obj;
	myParticleCount = particleCount;
	myScale = scale;
	timeLeft = lifetime;
	mySpeed = particleSpeed;
	myTightness = tightness;
	particleArray = new Particle[particleCount]();
	for (int i = 0; i < particleCount; i++)
	{
		particleArray[i].pos = position;
		particleArray[i].speed = particleSpeed;
		particleArray[i].direction = Vect(MathTools::GetRandomFloat(-1.0f, 1.0f), MathTools::GetRandomFloat(-1.0f, 1.0f), MathTools::GetRandomFloat(-1.0f, 1.0f));
	}
	isDone = false;
	SubmitAlarmRegistration(timeLeft, AlarmEnum::AlarmID::Alarm_0);

	switch (pattern)
	{
	case(BurstPattern::Spherical):
		currentBurstType = new BurstTypeSpherical();
		break;
	case(BurstPattern::Pulse):
		currentBurstType = new BurstTypePulse();
		break;
	case(BurstPattern::Stream):
		currentBurstType = new BurstTypeStream();
		break;
	default:
		currentBurstType = new BurstTypeSpherical();
		break;
	}
}

Burst::~Burst()
{
	delete currentBurstType;
}

void Burst::ComputeNewBurst(Vect & position)
{
	particleArray = new Particle[myParticleCount]();
	for (int i = 0; i < myParticleCount; i++)
	{
		particleArray[i].pos = position;
		particleArray[i].speed = mySpeed;
		particleArray[i].direction = Vect(MathTools::GetRandomFloat(-1.0f, 1.0f), MathTools::GetRandomFloat(-1.0f, 1.0f), MathTools::GetRandomFloat(-1.0f, 1.0f));
	}
	isDone = false;
	SubmitAlarmRegistration(timeLeft, AlarmEnum::AlarmID::Alarm_0);
}

void Burst::Alarm0()
{
	isDone = true;
}

void Burst::DrawParticles()
{
	Vect camPos;

	for (int i = 0; i < myParticleCount; i++)
	{
		SceneManager::GetCurrent3DCamera()->getPos(camPos);

		float newX = camPos.X() - particleArray[i].pos.X();
		float newZ = camPos.Z() - particleArray[i].pos.Z();

		float ang = atan2(newX, newZ);

		Matrix world = Matrix(SCALE, myScale, myScale, myScale) * Matrix(ROT_Y, ang) * Matrix(TRANS, particleArray[i].pos);

		grObj->SetWorld(world);
		grObj->Render(SceneManager::GetCurrent3DCamera());
	}
}

void Burst::UpdateParticles()
{
	for (int i = 0; i < myParticleCount; i++)
	{
		//particleArray[i].pos += particleArray[i].direction * particleArray[i].speed * (sinf(TimeManager::GetTimeSeconds()) * cosf(TimeManager::GetTimeSeconds()));
		currentBurstType->CalculatePosition(particleArray[i].pos, particleArray[i].direction, particleArray[i].speed, myTightness);
	}
}

bool Burst::GetStatus()
{
	return isDone;
}
