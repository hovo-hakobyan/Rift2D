#pragma once
#include "BaseComponent.h"
#include <string>
#include <memory>

namespace rift2d
{
	class Texture2D;
	class GameObject;
	class SpriteComponent final : public BaseComponent, public IRenderable
	{
	public:
		virtual void Update() override;
		virtual void Render() const override;

		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<Texture2D> texture);
		void SetPosition(float x, float y);

		SpriteComponent(GameObject* owner);
		virtual ~SpriteComponent() = default;
		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;
	private:
		std::shared_ptr<Texture2D> m_texture{};
	};
		
}