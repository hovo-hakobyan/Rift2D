#pragma once
#include <memory>
#include "BaseComponent.h"


namespace rift2d
{
	class Texture2D;
	class Font;
	class GameObject;
	class SpriteComponent;
	class TextComponent final : public BaseComponent, public IComponentWatcher
	{
	public:
		virtual void init() override;
		virtual void update() override;
		virtual void end() override;

		void setText(const std::string& text);

		TextComponent(GameObject* owner, const std::string& text, Font* pFont);
		virtual ~TextComponent() override;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		virtual void onComponentRemoved(BaseComponent* component) override;
	private:
		bool m_needsUpdate;
		std::string m_text;
		Font* m_font;
		SpriteComponent* m_pSpriteComponent;
		std::unique_ptr<Texture2D> m_fontTexture{};
	};
}
