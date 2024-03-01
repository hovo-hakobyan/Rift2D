#pragma once
#include <SDL.h>
#include "Singleton.h"
#include "vector"
#include "memory"

namespace rift2d
{
	class IRenderable;
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};	
		std::vector<IRenderable*> m_renderables;
	public:
		void init(SDL_Window* window);
		void render() const;
		void destroy();

		void renderTexture(const Texture2D& texture, float x, float y) const;
		void renderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* getSDLRenderer() const;

		const SDL_Color& getBackgroundColor() const { return m_clearColor; }
		void setBackgroundColor(const SDL_Color& color) { m_clearColor = color; }

		void registerComponent(IRenderable* component);
		void unregisterComponent(IRenderable* component);
	};
}

