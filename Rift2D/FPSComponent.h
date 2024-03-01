#pragma once
#include "BaseComponent.h"

namespace rift2d
{
	class TextComponent;
	class FPSComponent final : public BaseComponent, public IComponentWatcher
	{
	public:
		virtual void Init() override;
		virtual void Update() override;
		virtual void End() override;

		FPSComponent(GameObject* owner);
		virtual ~FPSComponent() = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		virtual void OnComponentRemoved(BaseComponent* component);

	private:
		TextComponent* m_pText{};
		float m_AccumulatedSeconds{0.0f};
		int m_FrameCount{};
		float m_UpdateInterval{ .1f };
	};

}

