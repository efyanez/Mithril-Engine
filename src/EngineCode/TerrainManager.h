#ifndef _TerrainManager
#define _TerrainManager

#include <string>

class TerrainObject;
class NullTerrainObject;

class TerrainManager
{
public:
	TerrainManager();
	~TerrainManager();
	TerrainManager(const TerrainManager& other) = delete;
	TerrainManager & operator=(const TerrainManager& other) = delete;

	void SetTerrain(std::string key);
	TerrainObject* GetTerrain();
private:
	TerrainObject* currentTerrain;
	NullTerrainObject* nullObject;
	friend class Scene;
	void RenderTerrain();
};

#endif // !_TerrainManager
