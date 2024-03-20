#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Font.h"

rift2d::ResourceManager::~ResourceManager() = default;


void rift2d::ResourceManager::init(const std::filesystem::path& dataPath)
{
	m_dataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

rift2d::Texture2D* rift2d::ResourceManager::loadTexture(const std::string& file) const
{
	//If the texture is already loaded, don't load
	auto it = m_textureCache.find(file);
	if (it != m_textureCache.end()) return it->second.get();

	const auto fullPath = m_dataPath / file;
	//Load the texture
	auto texture = IMG_LoadTexture(Renderer::GetInstance().getSDLRenderer(), fullPath.string().c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}

	//Cache it
	auto texturePtr = std::make_unique<Texture2D>(texture);
	const auto rawPtr = texturePtr.get();
	m_textureCache[file] = std::move(texturePtr);
	return rawPtr;
}

std::unique_ptr<rift2d::Texture2D> rift2d::ResourceManager::createFontTexture(Font* font, const SDL_Color& color, const std::string& text)
{
	const auto surf = TTF_RenderText_Blended(font->getFont(), text.c_str(), color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().getSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);

	return std::make_unique<Texture2D>(texture);
}

rift2d::Font* rift2d::ResourceManager::loadFont(const std::string& file, unsigned int size) const
{
	//If the texture is already loaded, don't load
	auto it = m_fontCache.find(file);
	if (it != m_fontCache.end()) return it->second.get();

	const auto fullPath = m_dataPath/file;

	auto font = std::make_unique<Font>(fullPath.string(), size);
	const auto rawPtr = font.get();
	m_fontCache[file] = std::move(font);
	return rawPtr;

}
