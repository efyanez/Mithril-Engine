#ifndef _Field
#define _Field

#include "AzulCore.h"
#include "../EngineCode/Drawable.h"
#include "Align16.h"
#include "../EngineCode/ModelManager.h"
#include "../EngineCode/ShaderManager.h"
#include "../EngineCode/TextureManager.h"
#include "../EngineCode/CameraManager.h"

class Field : public Drawable, public Align16
{
private:
	GraphicsObject_TextureFlat *pGObj_Field;
	Matrix world;
public:
	Field();
	virtual ~Field();

	void Draw() override;
};

#endif // !_Field
