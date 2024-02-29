#include "SpriteComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"


rift2d::SpriteComponent::SpriteComponent(GameObject* owner) :
	BaseComponent(owner), m_texture(nullptr)
{
}


void rift2d::SpriteComponent::Update()
{
}

void rift2d::SpriteComponent::Render() const
{
	if (m_texture)
	{
		auto owner = GetParent();
		if (owner)
		{
			auto& pos = owner->GetTransform().GetPosition();
			Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
		}

	}
}

void rift2d::SpriteComponent::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void rift2d::SpriteComponent::SetPosition(float x, float y)
{
	auto owner = GetParent();
	if (owner)
	{
		auto& transform = owner->GetTransform();
		transform.SetPosition(x, y, 0.0f);
	}
}

