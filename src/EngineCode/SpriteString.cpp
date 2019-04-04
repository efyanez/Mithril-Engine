#include "SpriteString.h"
#include "SpriteFontManager.h"

SpriteString::SpriteString(std::string font, std::string s, float x, float y)
{

	posx = x;
	posy = y;

	currentFont = SpriteFontManager::GetSpriteFont(font);

	for (size_t i = 0; i < s.length(); i++)
	{
		glyphs.push_back(currentFont->GetGlyph(s.at(i)));
	}
}

void SpriteString::SetText(std::string s)
{
	glyphs.clear();

	for (size_t i = 0; i < s.length(); i++)
	{
		glyphs.push_back(currentFont->GetGlyph(s.at(i)));
	}
}

void SpriteString::Render()
{
	float offset = 0;
	for (auto it = glyphs.begin(); it != glyphs.end(); it++)
	{
		Sprite* glyph = (*it);
		glyph->SetPos(posx + offset, posy);
		glyph->Render();

		float imgWidth = glyph->GetGlyphWidth();
		offset += imgWidth;
	}
}
