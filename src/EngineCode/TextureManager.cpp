#include "TextureManager.h"
#include <iostream>

TextureManager* TextureManager::self = NULL;

void TextureManager::privLoadTexture(std::string key, std::string filepath)
{
	assert((key != "" || filepath != "") && "Key or filepath invalid");
	assert(Instance().TextureList[key] == NULL && "Duplicate key found!");

	Instance().TextureList[key] = new Texture(filepath.c_str());
}

Texture * TextureManager::privGetTexture(std::string key)
{
	assert(Instance().TextureList[key] != NULL && "Texture not found!");
	return Instance().TextureList[key];
}

void TextureManager::privLoadDefaultTextures()
{

}

void TextureManager::privUnloadTextures()
{
	std::map<std::string, Texture*>::iterator textureIt = Instance().TextureList.begin();
	while (textureIt != Instance().TextureList.end())
	{
		delete textureIt->second;
		textureIt->second = nullptr;
		textureIt++;
	}
	DebugMsg::out("TEXTURES UNLOADED\n");
	delete self;
}
