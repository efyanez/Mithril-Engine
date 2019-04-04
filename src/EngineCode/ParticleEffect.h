#ifndef _ParticleEffect_H
#define _ParticleEffect_H

#include <string>
#include "BurstPattern.h"
#include "Vect.h"
#include "Matrix.h"

class Model;
class ShaderObject;
class Texture;
class GraphicsObject_TextureFlat;
class ParticleEmitter;

class ParticleEffect
{
protected:
	float burstInterval;
	float burstLife;
	int burstCount;
	float burstSpeed;
	float burstScale;
	float burstTightness;

	Model* pModel;
	ShaderObject* pShader;
	Texture* pTexture;

	GraphicsObject_TextureFlat* grObj;

	BurstPattern currentPattern;

	ParticleEmitter* currentEmitter;

public:

	ParticleEffect();
	virtual ~ParticleEffect();

	//! Sets the graphics object of the particle by taking string keys for the model and the texture
	/*!
	\ingroup Particles
	\param modelKey a string.
	\param texKey a string.
	*/
	void SetGraphicObject(std::string modelKey, std::string texKey);

	//! Gets the burst interval of the effect
	/*!
	\ingroup Particles
	\return float The burst interval
	*/
	float GetBurstInterval();

	//! Gets the burst life of the effect
	/*!
	\ingroup Particles
	\return float The burst life
	*/
	float GetBurstLife();

	//! Gets the burst count of the effect
	/*!
	\ingroup Particles
	\return int The burst count
	*/
	int GetBurstCount();

	//! Gets the burst speed of the effect
	/*!
	\ingroup Particles
	\return float The burst speed
	*/
	float GetBurstSpeed();

	//! Gets the burst scale of the effect
	/*!
	\ingroup Particles
	\return float The burst scale
	*/
	float GetScale();

	//! Gets the burst tightness of the effect
	/*!
	\ingroup Particles
	\return float The burst tightness
	*/
	float GetBurstTightness();

	GraphicsObject_TextureFlat* GetGraphicsObject();


	//! Spawns a particle emitter for the given effect
	/*!
	\ingroup Particles
	\param pos A Vect reference for position of the emitter
	\param rot A Matrix reference for rotation of the emitter
	\param loop A bool for whether or not the emitter should loop
	*/
	void SpawnParticleEmitter(Vect& pos, Matrix& rot, bool loop);

	BurstPattern GetBurstPattern();
};

#endif // !_ParticleEffect_H
