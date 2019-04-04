#ifndef _SpriteString_H
#define _SpriteString_H

#include "SpriteFont.h"
#include <list>

class SpriteString : public Align16
{
protected:

	using GlyphCollection = std::list<SpriteFont::Glyph*>;
	GlyphCollection glyphs;
	int height;
	int width;
	float posx;
	float posy;

	SpriteFont* currentFont;

public:
	//! Constructor for a Sprite String. Takes the name of the SpriteFont, the string of text, and two floats (x and y) for position.
	/*!
	\ingroup Font
	\param c a char to map to the input character.
	\return Glyph* a glyph pointer
	*/
	SpriteString() = default;
	virtual ~SpriteString() {};
	SpriteString(std::string font, std::string s, float x, float y);
	void SetText(std::string s);
	void Render();
};

#endif // !_SpriteString_H
