#pragma once
#include <memory>
#include "Transform.h"
#include "BaseComponent.h"

namespace rift2d
{
	class Font;
	class Texture2D;
	class GameObject;
	class SpriteComponent;
	class TextComponent final : public BaseComponent, public IComponentWatcher
	{
	public:
		virtual void init() override;
		virtual void update() override;
		virtual void end() override;

		void setText(const std::string& text);
		void setPosition(float x, float y) const;

		TextComponent(GameObject* owner, const std::string& text, std::shared_ptr<Font> font);
		virtual ~TextComponent() override = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		virtual void onComponentRemoved(BaseComponent* component) override;
	private:
		bool m_needsUpdate;
		std::string m_text;
		std::shared_ptr<Font> m_font;
		SpriteComponent* m_pSpriteComponent;
	};
}
