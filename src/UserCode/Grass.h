#ifndef _Grass
#define _Grass

#include "AzulCore.h"
#include "../EngineCode/Drawable.h"
#include "Align16.h"
#include "../EngineCode/ModelManager.h"
#include "../EngineCode/ShaderManager.h"
#include "../EngineCode/TextureManager.h"
#include "../EngineCode/CameraManager.h"

class Grass : public Drawable, public Align16
{
private:
	GraphicsObject_TextureLight *pGObj_Grass;
	Matrix world;
public:
	Grass(const Matrix& trans);
	virtual ~Grass();

	void Draw() override;
};

#endif // !_Grass
