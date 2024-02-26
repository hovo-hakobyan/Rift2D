#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

rift2d::GameObject::~GameObject() = default;

void rift2d::GameObject::Init()
{
	for (auto& comp : m_Components)
	{
		comp->Init();
	}
}

void rift2d::GameObject::Update()
{
	for (auto& comp : m_Components) 
	{
		comp->Update();
	}

}

void rift2d::GameObject::LateUpdate()
{
	for (auto& comp : m_Components)
	{
		comp->LateUpdate();
	}
}

