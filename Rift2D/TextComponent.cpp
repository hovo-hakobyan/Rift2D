#include <stdexcept>
#include <SDL_ttf.h>
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "SpriteComponent.h"


rift2d::TextComponent::TextComponent(GameObject* owner, const std::string& text, std::shared_ptr<Font> font)
	: BaseComponent(owner), m_needsUpdate(true), m_text(text), m_font(std::move(font)), m_pSpriteComponent(nullptr)
{ }




void rift2d::TextComponent::init()
{
	BaseComponent::init();
	m_pSpriteComponent = getOwner()->getComponent<SpriteComponent>();
	//if there is no sprite component, add one automatically
	if (!m_pSpriteComponent)
	{
		m_pSpriteComponent = getOwner()->addComponent<SpriteComponent>();
		
	}

	m_pSpriteComponent->registerWatcher(this);
}

void rift2d::TextComponent::update()
{
	if (m_needsUpdate and m_pSpriteComponent)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_font->getFont(), m_text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().getSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		
		auto texture2d = std::make_shared<Texture2D>(texture);
		m_pSpriteComponent->setTexture(texture2d);
		
		m_needsUpdate = false;
	}
}

void rift2d::TextComponent::end()
{
	if (m_pSpriteComponent)
	{
		m_pSpriteComponent->unregisterWatcher(this);
		m_pSpriteComponent = nullptr;
	}
	
}


// This implementation uses the "dirty flag" pattern
void rift2d::TextComponent::setText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}

void rift2d::TextComponent::setPosition(const float x, const float y) const
{
	auto owner = getOwner();
	if (owner)
	{
		auto transform = owner->getTransform();
		transform->setLocalPosition(x, y, 0.0f);
	}

	
}

void rift2d::TextComponent::onComponentRemoved(BaseComponent* component)
{
	if (component == static_cast<BaseComponent*>(m_pSpriteComponent)) 
	{
		m_pSpriteComponent = nullptr;
	}
}

