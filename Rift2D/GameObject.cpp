#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

rift2d::GameObject::~GameObject() = default;

void rift2d::GameObject::Update()
{
	for (auto& comp : m_Components)
	{
		comp->Update();
	}
}

//void rift2d::GameObject::Render() const
//{
//	const auto& pos = m_transform.GetPosition();
//	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
//}


void rift2d::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
