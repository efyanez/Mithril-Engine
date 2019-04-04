#include "ImageManager.h"
#include <iostream>

ImageManager* ImageManager::self = NULL;

void ImageManager::privLoadImage(std::string key, Texture* tex, Rect* imageRect)
{
	assert((key != "" || tex != nullptr) && "Key or Texture invalid");
	assert(Instance().ImageList[key] == NULL && "Duplicate key found!");

	Instance().ImageList[key] = new Image(tex, imageRect);
}

Image * ImageManager::privGetImage(std::string key)
{

	assert(Instance().ImageList[key] != NULL && "Image not found!");
	return Instance().ImageList[key];
}

void ImageManager::privUnloadImages()
{
	std::map<std::string, Image*>::iterator imageIt = Instance().ImageList.begin();
	while (imageIt != Instance().ImageList.end())
	{
		delete imageIt->second;
		imageIt->second = nullptr;
		imageIt++;
	}
	DebugMsg::out("IMAGES UNLOADED\n");
	delete self;
}
