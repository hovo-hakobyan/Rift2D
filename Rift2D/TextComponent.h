#pragma once
#include <string>
#include <memory>
#include "Transform.h"
#include "BaseComponent.h"

namespace rift2d
{
	class Font;
	class Texture2D;
	class GameObject;
	class TextComponent final : public BaseComponent, public IRenderable
	{
	public:
		virtual void Init() override;
		virtual void Update() override;
		virtual void FixedUpdate() {}
		virtual void Render() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);

		TextComponent(std::shared_ptr<GameObject> owner, const std::string& text, std::shared_ptr<Font> font);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;


	private:
		bool m_needsUpdate;
		std::string m_text;
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
	};
}
