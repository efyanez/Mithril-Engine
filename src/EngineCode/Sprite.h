#ifndef _Sprite
#define _Sprite

#include <string>

#include "AzulCore.h"
#include "Align16.h"

class Model;
class Shader;
class Image;
class GraphicsObject_Sprite;

class Sprite : public Align16
{
public:
	Sprite() = delete;
	Sprite(std::string key);
	Sprite(const Sprite&) {};
	Sprite& operator= (const Sprite) {};
	~Sprite() = default;

	//! Sets the center for a sprite
	/*!
	\param x Float x-value
	\param y Float y-value
	*/
	void SetCenter(float x, float y);

	//! Sets the position for a sprite
	/*!
	\param x Float x-value
	\param y Float y-value
	*/
	void SetPos(float x, float y);

	//! Sets the angle for a sprite
	/*!
	\param angle A float angle
	*/
	void SetAngle(float angle);

	//! Returns the angle of a sprite
	/*!
	\return Angle as float
	*/
	float GetAngle();

	//! Returns the position of a sprite
	/*!
	\return Position as vector
	*/
	Vect GetPos();

	//! Sets the scale factor for a sprite
	/*!
	\param x Float x-value
	\param y Float y-value
	*/
	void SetScaleFactor(float x, float y);

	//! Sets the pixel scale for a sprite
	/*!
	\param x Float x-value
	\param y Float y-value
	*/
	void SetScalePixel(float x, float y);

	void SetGlyphWidth(float w);

	float GetGlyphWidth();

	//! Renders sprite to current 2D camera
	void Render();

	float GetWidth();

private:

	Model* pSpriteModel;
	ShaderObject* pSpriteShader;
	Image* pSpriteImage;

	GraphicsObject_Sprite* pSpriteObject;

	float centerX;
	float centerY;
	float scaleX;
	float scaleY;
	float posX;
	float posY;
	float spriteAngle;
	float glyphWidth;

	Matrix world;
	Matrix Scale;
	Matrix RotZ;
	Matrix Trans;
};

#endif _Sprite