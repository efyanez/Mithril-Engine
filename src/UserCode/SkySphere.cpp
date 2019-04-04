#include "SkySphere.h"
#include "DebugOut.h"
#include "Grass.h"
#include "../EngineCode/SceneManager.h"

SkySphere::SkySphere()
{
	pGObj_Sky = new GraphicsObject_TextureFlat(ModelManager::GetModel("Sky"), ShaderManager::GetShader(ShaderManager::DefaultShader::FlatRender), TextureManager::GetTexture("Sunset"));
	world = Matrix(SCALE, 15, 15, 15);
	pGObj_Sky->SetWorld(world);

	//Drawable::SceneRegistration();
	SubmitDrawRegistration();
}

SkySphere::~SkySphere()
{
	delete pGObj_Sky;
	SubmitDrawDeregistration();
	DebugMsg::out("PLANE DESTROYED\n");
}

void SkySphere::Draw()
{
	pGObj_Sky->Render(SceneManager::GetCurrentScene()->GetCamManager()->GetCurrentCamera());
}
