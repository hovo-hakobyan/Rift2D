#include "TextComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"


rift2d::TextComponent::TextComponent(GameObject* owner, const std::string& text, Font* pFont)
	: BaseComponent(owner), m_needsUpdate(true), m_text(text), m_font(pFont), m_pSpriteComponent(nullptr)
{ }

rift2d::TextComponent::~TextComponent() = default;



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
		if(auto texture = ResourceManager::GetInstance().createFontTexture(m_font,  RiftColor{ 255,255,255,255 }, m_text))
		{
			m_fontTexture = std::move(texture);
			m_pSpriteComponent->setTexture(m_fontTexture.get());
		}

		m_needsUpdate = false;
	}
}

void rift2d::TextComponent::end()
{
	BaseComponent::end();
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


void rift2d::TextComponent::onComponentRemoved(BaseComponent* component)
{
	if (component == static_cast<BaseComponent*>(m_pSpriteComponent)) 
	{
		m_pSpriteComponent = nullptr;
	}
}

