#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

bool rift2d::GameObject::m_GameStarted{ false };
void rift2d::GameObject::Init()
{
	for (auto& comp : m_Components)
	{
		comp->Init();
	}
	m_GameStarted = true;
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

void rift2d::GameObject::End()
{
	for (auto& comp : m_Components)
	{
		comp->End();
	}
}

