#include "SpriteFontManager.h"
#include "SpriteFont.h"
#include <assert.h>

SpriteFontManager* SpriteFontManager::self = NULL;

void SpriteFontManager::privLoadSpriteFont(std::string key, std::string filepath)
{
	assert((key != "" || filepath != "") && "Key or filepath invalid");
	assert(Instance().SpriteFontList[key] == NULL && "Duplicate key found!");

	Instance().SpriteFontList[key] = new SpriteFont(key, filepath.c_str());
}


SpriteFont * SpriteFontManager::privGetSpriteFont(std::string key)
{
	assert(Instance().SpriteFontList[key] != NULL && "SpriteFont not found!");
	return Instance().SpriteFontList[key];
}

void SpriteFontManager::privUnloadSpriteFonts()
{
	std::map<std::string, SpriteFont*>::iterator fontIt = Instance().SpriteFontList.begin();
	while (fontIt != Instance().SpriteFontList.end())
	{
		delete fontIt->second;
		fontIt->second = nullptr;
		fontIt++;
	}
	DebugMsg::out("SPRITE FONTS UNLOADED\n");
	delete self;
}
