#pragma once
#include "BaseComponent.h"
#include <memory>

namespace rift2d
{
	class Texture2D;
	class GameObject;
	class SpriteComponent final : public BaseComponent, public IRenderable
	{
	public:
		virtual void update() override;
		virtual void render() const override;

		void setTexture(const std::string& filename);
		void setTexture(std::shared_ptr<Texture2D> texture);

		SpriteComponent(GameObject* owner);
		virtual ~SpriteComponent() override = default;
		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;
	private:
		std::shared_ptr<Texture2D> m_texture{};
	};
		
}