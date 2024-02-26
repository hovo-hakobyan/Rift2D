#include "FPSComponent.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "TextComponent.h"
#include <format>

rift2d::FPSComponent::FPSComponent(std::shared_ptr<GameObject> owner) :
	BaseComponent(owner)
{

}
void rift2d::FPSComponent::Init()
{
	auto owner = m_Owner.lock();
	if (owner)
	{
		m_pText= owner->GetComponent<TextComponent>();
	}
}

void rift2d::FPSComponent::Update()
{
	if (m_pText.expired())
	{
		return;
	}

	m_AccumulatedSeconds += TimeManager::GetInstance().GetDeltaTime();
	++m_FrameCount;

	if (m_AccumulatedSeconds < m_UpdateInterval)
	{
		return;
	}

	auto textComp = m_pText.lock();
	textComp->SetText(std::format("{:.1f}", m_FrameCount / m_AccumulatedSeconds));
	m_FrameCount = 0;
	m_AccumulatedSeconds = 0;

}
