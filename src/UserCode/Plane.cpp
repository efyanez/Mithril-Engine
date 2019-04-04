#include "Plane.h"
#include "DebugOut.h"
#include "Grass.h"
#include "../EngineCode/SceneManager.h"
#include <ctime>
#include <stdlib.h>

Plane::Plane()
{
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 50.0f, 1.0f, -1.0f);
	pGObj_Plane = new GraphicsObject_TextureLight(ModelManager::GetModel("Terrain"), ShaderManager::GetShader(ShaderManager::DefaultShader::LightRender), TextureManager::GetTexture("PlaneTex"), LightColor, LightPos);
	world = Matrix(SCALE, 15, 15, 15);
	pGObj_Plane->SetWorld(world);
	int randX;
	int randZ;
	std::srand((unsigned int)time(0));
	for (int i = 0; i < 25; i++)
	{
		randX = rand() % 500 + (-40);
		randZ = rand() % 300 + (-150);
		new Grass(Matrix(TRANS, (float)randX, 0, (float)randZ));
	}

	//Drawable::SceneRegistration();
	SubmitDrawRegistration();
}

Plane::~Plane()
{
	delete pGObj_Plane;
	SubmitDrawDeregistration();
	DebugMsg::out("PLANE DESTROYED\n");
}

void Plane::Draw()
{
	pGObj_Plane->Render(SceneManager::GetCurrentScene()->GetCamManager()->GetCurrentCamera());
}
