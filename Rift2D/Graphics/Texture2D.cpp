#include <SDL.h>
#include "Texture2D.h"

rift2d::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_texture);
}

glm::ivec2 rift2d::Texture2D::getSize() const
{
	SDL_Rect dst;
	SDL_QueryTexture(getSdlTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}

SDL_Texture* rift2d::Texture2D::getSdlTexture() const
{
	return m_texture;
}

rift2d::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_texture = texture;
}
