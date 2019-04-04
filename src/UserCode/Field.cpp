#include "Field.h"
#include "DebugOut.h"
#include "../EngineCode/SceneManager.h"

Field::Field()
{
	pGObj_Field = new GraphicsObject_TextureFlat(ModelManager::GetModel("Plane"), ShaderManager::GetShader(ShaderManager::DefaultShader::FlatRender), TextureManager::GetTexture("WeedTex"));
	world = Matrix(SCALE, 400, 400, 400);
	pGObj_Field->SetWorld(world);

	SubmitDrawRegistration();
}

Field::~Field()
{
	delete pGObj_Field;
	SubmitDrawDeregistration();
	DebugMsg::out("PLANE DESTROYED\n");
}

void Field::Draw()
{
	pGObj_Field->Render(SceneManager::GetCurrentScene()->GetCamManager()->GetCurrentCamera());
}
