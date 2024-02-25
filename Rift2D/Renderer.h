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
		std::vector<std::shared_ptr<IRenderable>> m_Renderables;
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }

		void RegisterComponent(std::shared_ptr<IRenderable> component);
		void UnregisterComponent(const std::shared_ptr<IRenderable>& component);
	};
}

