#ifndef _Pyramid
#define _Pyramid

#include "AzulCore.h"
#include "../EngineCode/Drawable.h"
#include "../EngineCode/Collidable.h"
#include "../EngineCode/Updatable.h"
#include "Align16.h"
#include "../EngineCode/ModelManager.h"
#include "../EngineCode/ShaderManager.h"
#include "../EngineCode/TextureManager.h"
#include "../EngineCode/CameraManager.h"

class Collidable;
class Frigate;

class Pyramid : public Drawable, public Collidable, public Updatable, public Align16
{
private:
	GraphicsObject_TextureFlat *pGObj_Pyramid;
	Matrix world;
	bool bDebugCol;
public:
	Pyramid();
	Pyramid(Vect & pos);
	virtual ~Pyramid();

	virtual void Collision(Collidable*);
	virtual void Collision(Frigate*);

	void Update() override;
	void Draw() override;
};

#endif // !_Pyramid
