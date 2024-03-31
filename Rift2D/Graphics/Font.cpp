#include <stdexcept>
#include <SDL_ttf.h>
#include "Font.h"

TTF_Font* rift2d::Font::getFont() const
{
	return m_font;
}

unsigned rift2d::Font::getFontSize() const
{
	return m_fontSize;
}

rift2d::Font::Font(const std::string& fullPath, unsigned int size) : m_font(nullptr), m_fontSize(size)
{
	m_font = TTF_OpenFont(fullPath.c_str(), size);
	if (m_font == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

rift2d::Font::~Font()
{
	TTF_CloseFont(m_font);
}
