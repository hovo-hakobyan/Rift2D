#include "SpriteComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Transform.h"


rift2d::SpriteComponent::SpriteComponent(GameObject* owner, bool isUI) :
	BaseComponent(owner), m_texture(nullptr),m_isUI(isUI)
{
}

void rift2d::SpriteComponent::render() const
{
	if (isDisabled()) return;
	if (!m_shouldRender) return;
	if (m_texture)
	{
		auto owner = getOwner();
		if (owner)
		{
			const glm::vec2 pos = m_isUI ? owner->getTransform()->getWorldPosition() : owner->getTransform()->getWorldPosition();
			const auto rot = owner->getTransform()->getWorldRotation(true);

			Renderer::GetInstance().renderTexture(*m_texture, pos.x + m_offest.x, pos.y + m_offest.y, rot);
		
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

