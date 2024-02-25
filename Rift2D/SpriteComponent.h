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
		virtual void Init() override;
		virtual void Update() override;
		virtual void FixedUpdate() {}
		virtual void Render() const override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		SpriteComponent(std::shared_ptr<GameObject> owner);
		virtual ~SpriteComponent() = default;
		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;
	private:
		std::shared_ptr<Texture2D> m_texture{};
	};
		
}