#include "Visualizer.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CameraManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "ColorLibrary.h"
#include "Collidable.h"

Visualizer* Visualizer::self = NULL;

Visualizer::~Visualizer()
{

}

void Visualizer::privCreateBSphere()
{
	Vect white = Colors::White;
	Instance().WFUnitSphere = new GraphicsObject_WireframeConstantColor(ModelManager::GetModel("UnitSphere"), ShaderManager::GetShader("ColorConstantRender"), white);
	Instance().WFUnitBox = new GraphicsObject_WireframeConstantColor(ModelManager::GetModel("UnitBox"), ShaderManager::GetShader("ColorConstantRender"), white);
}

void Visualizer::privTerminate()
{
	delete Instance().WFUnitSphere;
	delete self;
	self = NULL;
	DebugMsg::out("VISUALIZER TERMINATED\n");
}

void Visualizer::privRenderBSphere(Matrix & S, const Vect & color)
{
	Matrix myWorld = S;
	Instance().WFUnitSphere->pWireColor->set(color);
	Instance().WFUnitSphere->SetWorld(myWorld);
	Instance().WFUnitSphere->Render(SceneManager::GetCurrentScene()->GetCamManager()->GetCurrentCamera());
}

void Visualizer::privRenderAABB(Matrix & S, const Vect & color)
{
	Matrix myWorld = S;
	Instance().WFUnitBox->pWireColor->set(color);
	Instance().WFUnitBox->SetWorld(myWorld);
	Instance().WFUnitBox->Render(SceneManager::GetCurrentScene()->GetCamManager()->GetCurrentCamera());
}

void Visualizer::privRenderOBB(Matrix & S, const Vect & color)
{
	Matrix myWorld = S;
	Instance().WFUnitBox->pWireColor->set(color);
	Instance().WFUnitBox->SetWorld(myWorld);
	Instance().WFUnitBox->Render(SceneManager::GetCurrentScene()->GetCamManager()->GetCurrentCamera());
}

void Visualizer::privRenderAll()
{
	for (auto it = visualizerList.begin(); it != visualizerList.end(); it++)
	{
		privRenderCollisionVolume((*it).myVolume, (*it).myColor);
	}
	visualizerList.clear();
	for (auto it = visualizerTerrainList.begin(); it != visualizerTerrainList.end(); it++)
	{
		privRenderAABB((*it).myWorld, (*it).myColor);
	}
	visualizerTerrainList.clear();
}

void Visualizer::privSubmitVisualize(Collidable * vol, const Vect & col)
{
	VisualizerData newData;
	newData.myColor = col;
	newData.myVolume = &vol->GetCollisionVolume();
	visualizerList.push_back(newData);
}

void Visualizer::privSubmitVisualize(Vect & min, Vect & max, const Vect & col)
{
	Vect cornerMin = min;
	Vect cornerMax = max;
	Vect center = MathTools::FindCenter(cornerMin, cornerMax);

	Matrix scale = Matrix(SCALE, (cornerMin - cornerMax));
	Matrix trans = Matrix(TRANS, center);
	Matrix world = scale * trans;

	VisualizerTerrainCell newCell;
	newCell.myColor = col;
	newCell.myWorld = world;
	visualizerTerrainList.push_back(newCell);
}

void Visualizer::privSubmitVisualize(CollisionVolume * vol, const Vect & col)
{
	VisualizerData newData;
	newData.myColor = col;
	newData.myVolume = vol;
	visualizerList.push_back(newData);
}

void Visualizer::privRenderCollisionVolume(Collidable * C, const Vect & color)
{
	C->GetCollisionVolume().DebugView(color);
}

void Visualizer::privRenderCollisionVolume(CollisionVolume * C, const Vect & color)
{
	C->DebugView(color);
}


