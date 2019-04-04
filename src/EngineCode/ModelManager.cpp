#include "ModelManager.h"
#include <iostream>

ModelManager* ModelManager::self = NULL;

void ModelManager::privLoadModel(std::string key, std::string filepath)
{
	assert((key != "" || filepath != "") && "Key or filepath invalid");
	assert(Instance().ModelList[key] == NULL && "Duplicate key found!");

	Instance().ModelList[key] = new Model(filepath.c_str());
}

void ModelManager::privLoadModel(std::string key, Model::PreMadedeModels model)
{
	assert(key != "" && "Key or filepath invalid");
	assert(Instance().ModelList[key] == NULL && "Duplicate key found!");
	Instance().ModelList[key] = new Model(model);
}

Model * ModelManager::privGetModel(std::string key)
{
	assert(Instance().ModelList[key] != NULL && "Model not found!");
	return Instance().ModelList[key];
}

void ModelManager::privLoadDefaultModels()
{

	//Model *PModelSphere = new Model(Model::PreMadedeModels::UnitSphere);
	Instance().LoadModel("UnitSphere", Model::PreMadedeModels::UnitSphere);
	Instance().LoadModel("UnitBox", Model::PreMadedeModels::UnitBox_WF);
	Instance().LoadModel("UnitSquare", Model::PreMadedeModels::UnitSquareXY);
}

void ModelManager::privUnloadModels()
{
	std::map<std::string, Model*>::iterator modelIt = Instance().ModelList.begin();
	while (modelIt != Instance().ModelList.end())
	{
		delete modelIt->second;
		modelIt->second = nullptr;
		modelIt++;
	}
	DebugMsg::out("MODELS UNLOADED\n");
	delete self;
}
