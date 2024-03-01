#include "SpriteComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"


rift2d::SpriteComponent::SpriteComponent(GameObject* owner) :
	BaseComponent(owner), m_texture(nullptr)
{
}


void rift2d::SpriteComponent::update()
{
}

void rift2d::SpriteComponent::render() const
{
	if (m_texture)
	{
		auto owner = getParent();
		if (owner)
		{
			auto& pos = owner->getTransform().getPosition();
			Renderer::GetInstance().renderTexture(*m_texture, pos.x, pos.y);
		}

	}
}

void rift2d::SpriteComponent::setTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().loadTexture(filename);
}

void rift2d::SpriteComponent::setTexture(std::shared_ptr<Texture2D> texture)
{
	m_texture = texture;
}

void rift2d::SpriteComponent::setPosition(float x, float y)
{
	auto owner = getParent();
	if (owner)
	{
		auto& transform = owner->getTransform();
		transform.setPosition(x, y, 0.0f);
	}
}

