#ifndef _Axis
#define _Axis

#include "AzulCore.h"
#include "../EngineCode/Drawable.h"

#include "Align16.h"
#include "../EngineCode/ModelManager.h"
#include "../EngineCode/ShaderManager.h"
#include "../EngineCode/TextureManager.h"
#include "../EngineCode/CameraManager.h"

class Axis : public Drawable, public Align16
{
private:
	GraphicsObject_ColorNoTexture *pGObj_Axis;
	
	Matrix world;
public:
	Axis();
	virtual ~Axis();


	void Draw() override;
};

#endif // !_Frigate
