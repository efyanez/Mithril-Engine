#ifndef _SkySphere
#define _SkySphere

#include "AzulCore.h"
#include "../EngineCode/Drawable.h"
#include "Align16.h"
#include "../EngineCode/ModelManager.h"
#include "../EngineCode/ShaderManager.h"
#include "../EngineCode/TextureManager.h"
#include "../EngineCode/CameraManager.h"

class SkySphere : public Drawable, public Align16
{
private:
	GraphicsObject_TextureFlat *pGObj_Sky;
	Matrix world;
public:
	SkySphere();
	virtual ~SkySphere();

	void Draw() override;
};

#endif // !_SkySphere
