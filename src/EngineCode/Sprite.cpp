#include "Sprite.h"

#include "ModelManager.h"
#include "ShaderManager.h"
#include "ImageManager.h"
#include "GraphicsObject_Sprite.h"
#include "SceneManager.h"
#include "CameraManager.h"

Sprite::Sprite(std::string key)
{
	pSpriteModel = ModelManager::GetModel("UnitSquare");
	pSpriteShader = ShaderManager::GetShader(ShaderManager::DefaultShader::SpriteRender);
	pSpriteImage = ImageManager::GetImage(key);

	pSpriteObject = new GraphicsObject_Sprite(pSpriteModel, pSpriteShader, pSpriteImage, new Rect(0.0f, 0.0f, pSpriteImage->pImageRect->width, pSpriteImage->pImageRect->height));

	Scale.set(SCALE, 1.0f, 1.0f, 1.0f);
	RotZ.set(ROT_Z, 0.0f);
	Trans.set(TRANS, pSpriteObject->origPosX, pSpriteObject->origPosY, 0.0f);
	centerX = 0.0f;
	centerY = 0.0f;

	world = Scale * RotZ * Trans;
	pSpriteObject->SetWorld(world);
}

void Sprite::SetCenter(float x, float y)
{
	centerX = x;
	centerY = y;
}

void Sprite::SetPos(float x, float y)
{
	Trans.set(TRANS, x, y, 1);
	world = Scale * RotZ * Trans;
	posX = x;
	posY = y;
	pSpriteObject->SetWorld(world);
}

void Sprite::SetAngle(float angle)
{
	spriteAngle = angle;
	RotZ.set(ROT_Z, spriteAngle);
	RotZ = Matrix(TRANS, -centerX, -centerY, 1) * RotZ * Matrix(TRANS, centerX, centerY, 1);
	world = Scale * RotZ * Trans;
	pSpriteObject->SetWorld(world);
}

float Sprite::GetAngle()
{
	return spriteAngle;
}

Vect Sprite::GetPos()
{
	return Vect(posX, posY, 0.0f);
}

void Sprite::SetScaleFactor(float x, float y)
{
	scaleX = x;
	scaleY = y;
	Scale.set(SCALE, scaleX, scaleY, 1.0f);
	world = Scale * RotZ * Trans;
	pSpriteObject->SetWorld(world);
}

void Sprite::SetScalePixel(float x, float y)
{
	float scaleFactorX = x / pSpriteObject->origWidth;
	float scaleFactorY = y / pSpriteObject->origHeight;
	SetScaleFactor(scaleFactorX, scaleFactorY);
}

void Sprite::SetGlyphWidth(float w)
{
	glyphWidth = w;
}

float Sprite::GetGlyphWidth()
{
	return glyphWidth;
}

void Sprite::Render()
{
	pSpriteObject->Render(SceneManager::GetCurrentScene()->GetCamManager()->GetCurrent2DCamera());
}

float Sprite::GetWidth()
{
	return pSpriteImage->pImageRect->width;
}
