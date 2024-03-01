#pragma once
#include "BaseComponent.h"

namespace rift2d
{
	class TextComponent;
	class FPSComponent final : public BaseComponent, public IComponentWatcher
	{
	public:
		virtual void init() override;
		virtual void update() override;
		virtual void end() override;

		FPSComponent(GameObject* owner);
		virtual ~FPSComponent() override = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		virtual void onComponentRemoved(BaseComponent* component);

	private:
		TextComponent* m_pText{};
		float m_accumulatedSeconds{0.0f};
		int m_frameCount{};
		float m_updateInterval{ .1f };
	};

}

