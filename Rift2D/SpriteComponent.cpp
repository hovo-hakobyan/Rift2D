#include "SpriteComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"


rift2d::SpriteComponent::SpriteComponent(GameObject* owner) :
	BaseComponent(owner), m_texture(nullptr)
{
}

void rift2d::SpriteComponent::render() const
{
	if (!m_shouldRender) return;
	if (m_texture)
	{
		auto owner = getOwner();
		if (owner)
		{
			glm::vec3 pos = owner->getTransform()->getWorldPosition();
			Renderer::GetInstance().renderTexture(*m_texture, pos.x + m_offest.x, pos.y + m_offest.y);
		}

	}
}

void rift2d::SpriteComponent::setTexture(const std::string& filename, const glm::vec2& offset)
{
	m_texture = ResourceManager::GetInstance().loadTexture(filename);
	m_offest = offset;
}

void rift2d::SpriteComponent::setTexture(Texture2D* texture, const glm::vec2& offset)
{
	m_texture = texture;
	m_offest = offset;
}

