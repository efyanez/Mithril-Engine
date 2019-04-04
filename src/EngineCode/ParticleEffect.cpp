#include "ParticleEffect.h"
#include "GraphicsObject_TextureFlat.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "ParticleEmitter.h"
#include <string>

ParticleEffect::ParticleEffect()
{
	currentEmitter = nullptr;
}

ParticleEffect::~ParticleEffect()
{
	delete currentEmitter;
}

void ParticleEffect::SetGraphicObject(std::string modelKey, std::string texKey)
{
	pModel = ModelManager::GetModel(modelKey);
	pShader = ShaderManager::GetShader(ShaderManager::DefaultShader::FlatRender);
	pTexture = TextureManager::GetTexture(texKey);

	grObj = new GraphicsObject_TextureFlat(pModel, pShader, pTexture);
}

float ParticleEffect::GetBurstInterval()
{
	return burstInterval;
}

float ParticleEffect::GetBurstLife()
{
	return burstLife;
}

int ParticleEffect::GetBurstCount()
{
	return burstCount;
}

float ParticleEffect::GetBurstSpeed()
{
	return burstSpeed;
}

float ParticleEffect::GetScale()
{
	return burstScale;
}

float ParticleEffect::GetBurstTightness()
{
	return burstTightness;
}

GraphicsObject_TextureFlat * ParticleEffect::GetGraphicsObject()
{
	return grObj;
}

void ParticleEffect::SpawnParticleEmitter(Vect & pos, Matrix & rot, bool loop)
{
	if (currentEmitter == nullptr)
	{
		currentEmitter = new ParticleEmitter(this, pos, rot, loop);
		currentEmitter->GameObject::SubmitEntry();
	}
	else
	{
		currentEmitter->GameObject::SubmitExit();
		currentEmitter = new ParticleEmitter(this, pos, rot, loop);
		currentEmitter->GameObject::SubmitEntry();
	}
}

BurstPattern ParticleEffect::GetBurstPattern()
{
	return currentPattern;
}
