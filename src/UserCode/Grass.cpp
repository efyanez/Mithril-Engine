#include "Grass.h"
#include "DebugOut.h"
#include "../EngineCode/SceneManager.h"

Grass::Grass(const Matrix& trans)
{
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(-1.0f, -1.0f, -1.0f, -1.0f);
	pGObj_Grass = new GraphicsObject_TextureLight(ModelManager::GetModel("Grass"), ShaderManager::GetShader(ShaderManager::DefaultShader::LightRender), TextureManager::GetTexture("WeedTex"), LightColor, LightPos);
	world = Matrix(SCALE, 0.5f, 0.5f, 0.5f) * trans;
	pGObj_Grass->SetWorld(world);

	//Drawable::SceneRegistration();
	SubmitDrawRegistration();
}

Grass::~Grass()
{
	delete pGObj_Grass;
	SubmitDrawDeregistration();
	DebugMsg::out("PLANE DESTROYED\n");
}

void Grass::Draw()
{
	pGObj_Grass->Render(SceneManager::GetCurrentScene()->GetCamManager()->GetCurrentCamera());
}
