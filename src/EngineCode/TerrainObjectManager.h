#ifndef _TerrainObjectManager
#define _TerrainObjectManager

#include <map>

class TerrainObject;

class TerrainObjectManager
{
private:
	static TerrainObjectManager* self;
	TerrainObjectManager() {};
	TerrainObjectManager(const TerrainObjectManager&) {};
	TerrainObjectManager& operator= (const TerrainObjectManager) {};
	~TerrainObjectManager() {};

	static TerrainObjectManager& Instance()
	{
		if (!self)
		{
			self = new TerrainObjectManager();
		}
		return *self;
	};

	std::map<std::string, TerrainObject*> TerrainObjectList;

	void privLoadTerrainObject(std::string key, std::string filepath, std::string textureKey, int RepeatU, int RepeatV, int width, int height, int scale = 1, float offsetX = 0.5f, float offsetY = 0.0f, float offsetZ = 0.5f, int channelFix = 4);
	TerrainObject* privGetTerrainObject(std::string key);

	void privUnloadTerrainObjects();

public:
	//! Public static function. Loads a texture from a filepath into the map of Texture pointers.
	/*!
	\param key A string name for the Texture.
	\param filepath A string filepath for the texture location.
	*/
	static void LoadTerrainObject(std::string key, std::string filepath, std::string textureKey, int RepeatU, int RepeatV, int width, int height, int scale = 1, float offsetX = 0.5f, float offsetY = 0.0f, float offsetZ = 0.5f, int channelFix = 4) { Instance().privLoadTerrainObject(key, filepath, textureKey, RepeatU, RepeatV, width, height, scale, offsetX, offsetY, offsetZ, channelFix); };

	//! Returns a Texture pointer by taking a key and searching the key in the map.
	/*!
	\param key A string name for the Texture.
	\return Returns a Texture pointer.
	*/
	static TerrainObject* GetTerrainObject(std::string key) { return Instance().privGetTerrainObject(key); };

	//! Unloads the textures from the map and deletes their associated pointers.
	static void UnloadTerrainObjects() { Instance().privUnloadTerrainObjects(); };
};

#endif _TextureManager