#ifndef _Plane
#define _Plane

#include "AzulCore.h"
#include "../EngineCode/Drawable.h"
#include "Align16.h"
#include "../EngineCode/ModelManager.h"
#include "../EngineCode/ShaderManager.h"
#include "../EngineCode/TextureManager.h"
#include "../EngineCode/CameraManager.h"

class Plane : public Drawable, public Align16
{
private:
	GraphicsObject_TextureLight *pGObj_Plane;
	Matrix world;
public:
	Plane();
	virtual ~Plane();
	
	void Draw() override;
};

#endif // !_Plane
