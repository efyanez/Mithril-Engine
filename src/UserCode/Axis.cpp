#include "Axis.h"
#include "DebugOut.h"
#include "../EngineCode/SceneManager.h"
#include "Frigate.h"

Axis::Axis()
{
	pGObj_Axis = new GraphicsObject_ColorNoTexture(ModelManager::GetModel("Axis"), ShaderManager::GetShader(ShaderManager::DefaultShader::ColorNoTextureRender));
	world = Matrix(IDENTITY);
	pGObj_Axis->SetWorld(world);


	//Drawable::SceneRegistration();
	//CollisionRegistration<Axis>(this);
	SubmitDrawRegistration();
}

Axis::~Axis()
{
	delete pGObj_Axis;
	SubmitDrawDeregistration();
	DebugMsg::out("AXIS DESTROYED\n");
}

void Axis::Draw()
{
	pGObj_Axis->Render(SceneManager::GetCurrentScene()->GetCamManager()->GetCurrentCamera());

}