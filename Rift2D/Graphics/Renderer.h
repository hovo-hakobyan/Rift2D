#pragma once
#include <SDL.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Color.h"
#include "Singleton.h"
#include "vector"

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
		RiftColor m_clearColor{};
		std::vector<IRenderable*> m_renderables;


	public:
		void init(SDL_Window* window);
		void render() const;
		void destroy();
		void reset();

		void renderTexture(const Texture2D& texture, float x, float y, float angle = 0.0f) const;
		void renderTexture(const Texture2D& texture, float x, float y, float width, float height, float angle = 0.0f) const;
		void renderBox(const float x, const float y, const float width, const float height, RiftColor color) const;

		SDL_Renderer* getSDLRenderer() const;

		const RiftColor& getBackgroundColor() const { return m_clearColor; }
		void setBackgroundColor(const RiftColor& color) { m_clearColor = color; }

		void registerComponent(IRenderable* component);
		void unregisterComponent(IRenderable* component);
	};
}

