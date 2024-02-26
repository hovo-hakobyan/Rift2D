#include <stdexcept>
#include <SDL_ttf.h>
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"


rift2d::TextComponent::TextComponent(std::shared_ptr<GameObject> owner, const std::string& text, std::shared_ptr<Font> font)
	: BaseComponent(owner), m_needsUpdate(true), m_text(text), m_font(std::move(font)), m_textTexture(nullptr)
{ }


void rift2d::TextComponent::Update()
{
	if (m_needsUpdate)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_textTexture = std::make_shared<Texture2D>(texture);
		m_needsUpdate = false;
	}
}

void rift2d::TextComponent::Render() const
{
	if (m_textTexture != nullptr)
	{
		auto owner = m_Owner.lock();
		if (owner)
		{
			auto& pos = owner->GetTransform().GetPosition();
			Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
		}
		
	}
}

// This implementation uses the "dirty flag" pattern
void rift2d::TextComponent::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}

void rift2d::TextComponent::SetPosition(const float x, const float y)
{
	auto owner = m_Owner.lock();
	if (owner)
	{
		auto& transform = owner->GetTransform();
		transform.SetPosition(x, y, 0.0f);
	}

	
}


