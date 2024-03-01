#include "FPSComponent.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "TextComponent.h"
#include <format>

rift2d::FPSComponent::FPSComponent(GameObject* owner) :
	BaseComponent(owner)
{

}

void rift2d::FPSComponent::Init()
{
	auto owner = GetParent();
	if (owner)
	{
		m_pText= owner->GetComponent<TextComponent>();
		if (m_pText)
		{
			m_pText->RegisterWatcher(this);
		}
	}
}

void rift2d::FPSComponent::Update()
{
	if (!m_pText)
	{
		return;
	}

	m_AccumulatedSeconds += TimeManager::GetInstance().GetDeltaTime();
	++m_FrameCount;

	if (m_AccumulatedSeconds < m_UpdateInterval)
	{
		return;
	}

	auto textComp = m_pText;
	textComp->SetText(std::format("FPS: {:.1f}", m_FrameCount / m_AccumulatedSeconds));
	m_FrameCount = 0;
	m_AccumulatedSeconds = 0;

}

void rift2d::FPSComponent::End()
{
	m_pText->UnregisterWatcher(this);
	m_pText = nullptr;
}

void rift2d::FPSComponent::OnComponentRemoved(BaseComponent* component)
{
	if (component == static_cast<BaseComponent*>(m_pText))
	{
		m_pText = nullptr;
	}
}