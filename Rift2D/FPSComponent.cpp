#include "FPSComponent.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "TextComponent.h"
#include <sstream>
#include <iomanip>

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

	const float deltaTime = TimeManager::GetInstance().GetDeltaTime();

	m_AccumulatedSeconds += deltaTime;
	++m_FrameCount;

	if (m_AccumulatedSeconds < m_UpdateInterval)
	{
		return;
	}

	std::stringstream fpsText{};
	float fps = m_FrameCount / m_AccumulatedSeconds;
	fps = std::round(fps * 10) / 10;
	fpsText << std::fixed << std::setprecision(1) << fps;
	fpsText << " FPS";

	m_FrameCount = 0;
	m_AccumulatedSeconds -= m_UpdateInterval;
	
	auto textComp = m_pText.lock();
	textComp->SetText(fpsText.str());

}
