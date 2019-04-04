#include "SpriteFont.h"
#include "ImageManager.h"
#include "TextureManager.h"

#include "../../RapidXML/rapidxml_utils.hpp"

using namespace rapidxml;

SpriteFont::SpriteFont(std::string name, std::string path)
{
	myName = name;
	FontTexture = TextureManager::GetTexture(name);
	XMLtoCollection(path);
}

SpriteFont::Glyph* SpriteFont::GetGlyph(char c)
{
	return fontmap[c];
}

void SpriteFont::CreateGlyph(rapidxml::xml_node<char>* node)
{
	xml_node<char>* keynode = node;
	Key key = atoi(keynode->first_attribute()->value());

	keynode = keynode->first_node();
	float x = (float)atoi(keynode->value());
	keynode = keynode->next_sibling();
	float y = (float)atoi(keynode->value());
	keynode = keynode->next_sibling();
	float w = (float)atoi(keynode->value());
	keynode = keynode->next_sibling();
	float h = (float)atoi(keynode->value());

	ImageManager::CreateImage(myName + std::to_string(key),
		FontTexture, new Rect(x, y, w, h + 0.5f));
	fontmap[key] = new Glyph(myName + std::to_string(key));
	fontmap[key]->SetGlyphWidth(w);
}

void SpriteFont::XMLtoCollection(std::string path)
{
	rapidxml::file<char> FontData(path.c_str());

	using namespace rapidxml;
	xml_document<> doc;
	doc.parse<0>(FontData.data());

	xml_node<>* node = doc.first_node();
	while (node != nullptr)
	{
		if (strcmp(node->name(), "fontMetrics") == 0)
		{
			DebugMsg::out("SpriteFont: font data start\n");
			node = node->first_node();
		}
		else if (strcmp(node->name(), "character") == 0)
		{
			DebugMsg::out("SpriteFont: char data found\n");
			CreateGlyph(node);
			node = node->next_sibling();
		}
	}
}

SpriteFont::~SpriteFont()
{
	std::map<Key, Glyph*>::iterator it = fontmap.begin();
	while (it != fontmap.end())
	{
		delete it->second;
		it->second = nullptr;
		it++;
	}
}
