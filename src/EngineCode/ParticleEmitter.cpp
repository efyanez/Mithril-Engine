#include "ParticleEmitter.h"
#include "ParticleEffect.h"
#include "AlarmEnum.h"
#include "Burst.h"
#include "GraphicsObject_TextureFlat.h"

ParticleEmitter::ParticleEmitter()
{
}

ParticleEmitter::ParticleEmitter(ParticleEffect * pe, const Vect & pos, const Matrix & rot, bool loop)
{
	pParticleEffect = pe;
	loopEffect = loop;
	Position = pos;
	Rotation = rot;
	WorldMat = Rotation * Matrix(TRANS, Position);

	BurstInterval = pParticleEffect->GetBurstInterval();

}

ParticleEmitter::~ParticleEmitter()
{
	for (auto it = burstCollection.begin(); it != burstCollection.end(); it++)
	{
		delete (*it);
	}
	while (!recycledBursts.empty())
	{
		delete recycledBursts.top();
		recycledBursts.pop();
	}
}

void ParticleEmitter::SceneEntry()
{
	if (!loopEffect) 
	{
		NewBurst();
	}
	SubmitDrawRegistration();
	if (loopEffect)
	{
		SubmitAlarmRegistration(BurstInterval, AlarmEnum::AlarmID::Alarm_0);
	}
}

void ParticleEmitter::SceneExit()
{
	SubmitAlarmDeregistration(AlarmEnum::AlarmID::Alarm_0);
	SubmitDrawDeregistration();
}

void ParticleEmitter::Draw()
{
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (auto it = burstCollection.begin(); it != burstCollection.end(); it++)
	{
		(*it)->UpdateParticles();
		(*it)->DrawParticles();
	}
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);

	if (!burstCollection.empty() && burstCollection.front()->GetStatus())
	{
		recycledBursts.push(burstCollection.front());
		burstCollection.pop_front();
	}

}

void ParticleEmitter::Alarm0()
{
	NewBurst();
	SubmitAlarmRegistration(BurstInterval, AlarmEnum::AlarmID::Alarm_0);
}

void ParticleEmitter::NewBurst()
{
	Burst* newBurst;

	if (!recycledBursts.empty())
	{
		newBurst = recycledBursts.top();
		recycledBursts.pop();
		newBurst->ComputeNewBurst(Position);
	}
	else
	{
		newBurst = new Burst(pParticleEffect->GetBurstPattern(), pParticleEffect->GetBurstCount(), Position, pParticleEffect->GetBurstSpeed(), pParticleEffect->GetBurstTightness(), pParticleEffect->GetScale(), pParticleEffect->GetBurstLife(), pParticleEffect->GetGraphicsObject());
	}
	burstCollection.push_back(newBurst);
}
