#include "TerrainObjectManager.h"
#include "TerrainObject.h"
#include <assert.h>

TerrainObjectManager* TerrainObjectManager::self = NULL;

void TerrainObjectManager::privLoadTerrainObject(std::string key, std::string filepath, std::string textureKey, int RepeatU, int RepeatV, int width, int height, int scale, float offsetX, float offsetY, float offsetZ, int channelFix)
{
	assert((key != "" || filepath != "") && "Key or filepath invalid");
	assert(Instance().TerrainObjectList[key] == NULL && "Duplicate key found!");

	Instance().TerrainObjectList[key] = new TerrainObject(filepath.c_str(), textureKey, RepeatU, RepeatV, width, height, scale, offsetX, offsetY, offsetZ, channelFix);
}

TerrainObject * TerrainObjectManager::privGetTerrainObject(std::string key)
{
	assert(Instance().TerrainObjectList[key] != NULL && "Texture not found!");
	return Instance().TerrainObjectList[key];
}

void TerrainObjectManager::privUnloadTerrainObjects()
{
	std::map<std::string, TerrainObject*>::iterator textureIt = Instance().TerrainObjectList.begin();
	while (textureIt != Instance().TerrainObjectList.end())
	{
		delete textureIt->second;
		textureIt->second = nullptr;
		textureIt++;
	}
	DebugMsg::out("TERRAIN OBJECTS UNLOADED\n");
	delete self;
}
