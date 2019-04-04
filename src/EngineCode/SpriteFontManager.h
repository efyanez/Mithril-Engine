#ifndef _SpriteFontManager
#define _SpriteFontManager

#include <map>

class SpriteFont;

class SpriteFontManager
{
private:
	static SpriteFontManager* self;
	SpriteFontManager() {};
	SpriteFontManager(const SpriteFontManager&) {};
	SpriteFontManager& operator= (const SpriteFontManager) {};
	~SpriteFontManager() {};

	static SpriteFontManager& Instance()
	{
		if (!self)
		{
			self = new SpriteFontManager();
		}
		return *self;
	};

	std::map<std::string, SpriteFont*> SpriteFontList;

	void privLoadSpriteFont(std::string key, std::string filepath);
	SpriteFont* privGetSpriteFont(std::string key);

	void privUnloadSpriteFonts();


public:

	//! Public static function. Loads a SpriteFont from a filepath into the map of SpriteFont pointers.
	/*!
	\param key A string name for the SpriteFont.
	\param filepath A string filepath for the SpriteFont location.
	*/
	static void LoadSpriteFont(std::string key, std::string filepath) { Instance().privLoadSpriteFont(key, filepath); };

	//! Returns a SpriteFont pointer by taking a key and searching the key in the map.
	/*!
	\param key A string name for the SpriteFont.
	\return Returns a SpriteFont pointer
	*/
	static SpriteFont* GetSpriteFont(std::string key) { return Instance().privGetSpriteFont(key); };

	//! Unload SpriteFonts, deletes them from the map.

	static void UnloadSpriteFonts() { Instance().privUnloadSpriteFonts(); };
};

#endif _ModelManager