#include "TerrainManager.h"
#include "TerrainObjectManager.h"
#include "TerrainObject.h"
#include "NullTerrainObject.h"

TerrainManager::TerrainManager()
{
	nullObject = new NullTerrainObject();
	currentTerrain = nullObject;
}

TerrainManager::~TerrainManager()
{
	delete nullObject;
}

void TerrainManager::SetTerrain(std::string key)
{
	currentTerrain = TerrainObjectManager::GetTerrainObject(key);
}

TerrainObject * TerrainManager::GetTerrain()
{
	return currentTerrain;
}

void TerrainManager::RenderTerrain()
{
	currentTerrain->Render();
}
