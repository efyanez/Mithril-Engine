#ifndef _SpriteFont_H
#define _SpriteFont_H

#include "../../RapidXML/rapidxml.hpp"
#include "Sprite.h"
#include <map>
#include <string>
#include "Vect.h"

class SpriteFont
{
public:
	using Key = int;
	using Glyph = Sprite;

	Texture* FontTexture;
	using FontMap = std::map< Key, Glyph* >;
	FontMap fontmap;

	//! Constructor for a Sprite Font. Takes the name of the font (must match name of font texture) and the xml filepath.
	/*!
	\ingroup Font
	\param string an std::string name.
	\param path an std::string filepath.
	*/
	SpriteFont(std::string name, std::string path);

	//! Constructor for a Sprite Font. Takes the name of the font (must match name of font texture) and the xml filepath.
	/*!
	\param c a char to map to the input character.
	\return Glyph* a glyph pointer
	*/
	Glyph* GetGlyph(char c);

	virtual ~SpriteFont();

private:

	void CreateGlyph(rapidxml::xml_node<char>* node);
	void XMLtoCollection(std::string path);

	std::string myName;
};

#endif // !_SpriteFont_H
