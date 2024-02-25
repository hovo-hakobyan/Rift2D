#pragma once
#include "BaseComponent.h"
#include <string>
#include <memory>

namespace rift2d
{
	class Texture2D;
	class SpriteRenderer final : public BaseComponent, public IRenderable
	{
	public:
		virtual void Update() override;
		virtual void FixedUpdate() {}
		virtual void Render() const override;

		void SetTexture(const std::string& filename);

		void SetPosition(float x, float y);

		SpriteRenderer(std::shared_ptr<Texture2D> texture);
		virtual ~SpriteRenderer() = default;
		SpriteRenderer(const SpriteRenderer& other) = delete;
		SpriteRenderer(SpriteRenderer&& other) = delete;
		SpriteRenderer& operator=(const SpriteRenderer& other) = delete;
		SpriteRenderer& operator=(SpriteRenderer&& other) = delete;
	private:
		std::shared_ptr<Texture2D> m_texture{};
	};
		
}