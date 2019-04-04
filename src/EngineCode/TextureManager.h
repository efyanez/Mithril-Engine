#ifndef _TextureManager
#define _TextureManager

#include <map>
#include "AzulCore.h"

class TextureManager
{
private:
	static TextureManager* self;
	TextureManager() {};
	TextureManager(const TextureManager&) {};
	TextureManager& operator= (const TextureManager) {};
	~TextureManager() {};

	static TextureManager& Instance()
	{
		if (!self)
		{
			self = new TextureManager();
		}
		return *self;
	};

	std::map<std::string, Texture*> TextureList;

	void privLoadTexture(std::string key, std::string filepath);
	Texture* privGetTexture(std::string key);

	void privLoadDefaultTextures();
	void privUnloadTextures();

public:
	//! Public static function. Loads a texture from a filepath into the map of Texture pointers.
	/*!
	\param key A string name for the Texture.
	\param filepath A string filepath for the texture location.
	*/
	static void LoadTexture(std::string key, std::string filepath) { Instance().privLoadTexture(key, filepath); };

	//! Returns a Texture pointer by taking a key and searching the key in the map.
	/*!
	\param key A string name for the Texture.
	\return Returns a Texture pointer.
	*/
	static Texture* GetTexture(std::string key) { return Instance().privGetTexture(key); };

	//! Loads the default textures.
	static void LoadDefaultTextures() { Instance().privLoadDefaultTextures(); };

	//! Unloads the textures from the map and deletes their associated pointers.
	static void UnloadTextures() { Instance().privUnloadTextures(); };
};

#endif _TextureManager