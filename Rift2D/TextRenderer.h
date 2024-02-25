#pragma once
#include <string>
#include <memory>
#include "GameObject.h"
#include "Transform.h"
#include "BaseComponent.h"

namespace rift2d
{
	class Font;
	class Texture2D;
	class TextRenderer final : public BaseComponent, public IRenderable
	{
	public:
		virtual void Update() override;
		virtual void FixedUpdate() {}
		virtual void Render() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);

		TextRenderer(const std::string& text, std::shared_ptr<Font> font);
		virtual ~TextRenderer() = default;
		TextRenderer(const TextRenderer& other) = delete;
		TextRenderer(TextRenderer&& other) = delete;
		TextRenderer& operator=(const TextRenderer& other) = delete;
		TextRenderer& operator=(TextRenderer&& other) = delete;
	private:
		bool m_needsUpdate;
		std::string m_text;
		Transform m_transform{};
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
	};
}
