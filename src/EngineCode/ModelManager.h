#ifndef _ModelManager
#define _ModelManager

#include <map>
#include "AzulCore.h"

class ModelManager
{
private:
	static ModelManager* self;
	ModelManager() {};
	ModelManager(const ModelManager&) {};
	ModelManager& operator= (const ModelManager) {};
	~ModelManager() {};

	static ModelManager& Instance()
	{
		if (!self)
		{
			self = new ModelManager();
		}
		return *self;
	};

	std::map<std::string, Model*> ModelList;

	void privLoadModel(std::string key, std::string filepath);
	void privLoadModel(std::string key, Model::PreMadedeModels model);
	Model* privGetModel(std::string key);

	void privLoadDefaultModels();
	void privUnloadModels();


public:

	//! Public static function. Loads a model from a filepath into the map of Model pointers.
	/*!
		\param key A string name for the Model.
		\param filepath A string filepath for the Azul model location.
	*/
	static void LoadModel(std::string key, std::string filepath) { Instance().privLoadModel(key, filepath); };

	//! Public static function. Loads a model from premade models enum.
	/*!
		\param key A string name for the Model.
		\param model A premade model from Model::PreMadedeModels enum.
	*/
	static void LoadModel(std::string key, Model::PreMadedeModels model) { Instance().privLoadModel(key, model); };

	//! Returns a Model pointer by taking a key and searching the key in the map.
	/*!
		\param key A string name for the Model.
		\return Returns a Model pointer
	*/
	static Model* GetModel(std::string key) { return Instance().privGetModel(key); };

	//! Loads default models (Premade models).
	static void LoadDefaultModels() { Instance().privLoadDefaultModels(); };
	//! Unloaded models, deletes them from the map.

	static void UnloadModels() { Instance().privUnloadModels(); };
};

#endif _ModelManager