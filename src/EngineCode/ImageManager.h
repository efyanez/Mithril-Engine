#ifndef _ImageManager
#define _ImageManager

#include <map>
#include "AzulCore.h"

class ImageManager
{
private:
	static ImageManager* self;
	ImageManager() {};
	ImageManager(const ImageManager&) {};
	ImageManager& operator= (const ImageManager) {};
	~ImageManager() {};

	static ImageManager& Instance()
	{
		if (!self)
		{
			self = new ImageManager();
		}
		return *self;
	};

	std::map<std::string, Image*> ImageList;

	void privLoadImage(std::string key, Texture* tex, Rect* imageRect);

	Image* privGetImage(std::string key);

	void privUnloadImages();


public:

	//! Public static function. Loads an image from a texture into the map of Model pointers.
	/*!
	\param key A string name for the Model.
	\param tex A texture pointer for the image.
	\param imageRect A rectangle pointer for the image sample.
	*/
	static void CreateImage(std::string key, Texture* tex, Rect* imageRect) { Instance().privLoadImage(key, tex, imageRect); };

	//! Returns a Model pointer by taking a key and searching the key in the map.
	/*!
	\param key A string name for the Model.
	\return Returns a Model pointer
	*/
	static Image* GetImage(std::string key) { return Instance().privGetImage(key); };

	//! Unload images, deletes them from the map.

	static void UnloadImages() { Instance().privUnloadImages(); };
};

#endif _ImageManager