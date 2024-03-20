#pragma once
#include "BaseComponent.h"
#include <memory>
#include <glm/vec2.hpp>

namespace rift2d
{
	class Texture2D;
	class GameObject;
	class SpriteComponent final : public BaseComponent, public IRenderable
	{
	public:
		virtual void render() const override;

		void setTexture(const std::string& filename, const glm::vec2& offset = {0.f,0.f});
		void setTexture(Texture2D* texture, const glm::vec2& offset = { 0.f,0.f });
		void shouldRender(bool shouldRender) { m_shouldRender = shouldRender; }

		SpriteComponent(GameObject* owner);
		virtual ~SpriteComponent() override = default;
		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;
	private:
		Texture2D* m_texture{};
		glm::vec2 m_offest{};
		bool m_shouldRender{true};
	};
		
}
