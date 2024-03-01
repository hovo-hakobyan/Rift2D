#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

bool rift2d::GameObject::m_gameStarted{ false };
void rift2d::GameObject::init()
{
	for (auto& comp : m_components)
	{
		comp->init();
	}
	m_gameStarted = true;
}

void rift2d::GameObject::update()
{
	for (auto& comp : m_components) 
	{
		comp->update();
	}

}

void rift2d::GameObject::lateUpdate()
{
	for (auto& comp : m_components)
	{
		comp->lateUpdate();
	}
}

void rift2d::GameObject::end()
{
	for (auto& comp : m_components)
	{
		comp->end();
	}
}

