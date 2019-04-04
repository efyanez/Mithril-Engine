#include "Pyramid.h"
#include "DebugOut.h"
#include "../EngineCode/SceneManager.h"

Pyramid::Pyramid()
{
	pGObj_Pyramid = new GraphicsObject_TextureFlat(ModelManager::GetModel("Pyramid"), ShaderManager::GetShader(ShaderManager::DefaultShader::FlatRender), TextureManager::GetTexture("BrickWall"), TextureManager::GetTexture("RoofTexture"), TextureManager::GetTexture("RedBrick"), TextureManager::GetTexture("ChimneyTexture"));
	world = Matrix(SCALE, 8, 8, 8) * Matrix(TRANS, 120, 5, 0);
	pGObj_Pyramid->SetWorld(world);
	SubmitUpdateRegistration();
	SubmitDrawRegistration();
	SubmitCollisionRegistration<Pyramid>(this);
	SetColliderModel(pGObj_Pyramid->getModel(), CollisionType::AABB);
}

Pyramid::Pyramid(Vect & pos)
{
	pGObj_Pyramid = new GraphicsObject_TextureFlat(ModelManager::GetModel("Pyramid"), ShaderManager::GetShader(ShaderManager::DefaultShader::FlatRender), TextureManager::GetTexture("BrickWall"), TextureManager::GetTexture("RoofTexture"), TextureManager::GetTexture("RedBrick"), TextureManager::GetTexture("ChimneyTexture"));
	world = Matrix(SCALE, 8, 8, 8) * Matrix(TRANS, pos);
	pGObj_Pyramid->SetWorld(world);
	SubmitUpdateRegistration();
	SubmitDrawRegistration();
	SubmitCollisionRegistration<Pyramid>(this);
	SetColliderModel(pGObj_Pyramid->getModel(), CollisionType::AABB);
}

Pyramid::~Pyramid()
{
	delete pGObj_Pyramid;
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration<Pyramid>(this);
	DebugMsg::out("PLANE DESTROYED\n");
}

void Pyramid::Collision(Collidable *)
{
}

void Pyramid::Collision(Frigate *)
{
	bDebugCol = true;
}

void Pyramid::Update()
{
	UpdateCollisionData(world);
}

void Pyramid::Draw()
{
	pGObj_Pyramid->Render(SceneManager::GetCurrentScene()->GetCamManager()->GetCurrentCamera());
	if (bDebugCol)
	{
		//Visualizer::ShowSphere(GetBSphere(), Colors::Red);
		//Visualizer::VisualizeMe(this, Colors::Red);
	}
	else
	{
		//Visualizer::ShowSphere(GetBSphere(), Colors::Blue);
		//Visualizer::VisualizeMe(this, Colors::Blue);
	}
	bDebugCol = false;
}
