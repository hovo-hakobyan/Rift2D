#pragma once
#include <memory>

#include "Singleton.h"

namespace rift2d
{
	class GameObject;

	class RiftUI final : public Singleton<RiftUI>
	{
	public:
		~RiftUI() override;
		RiftUI(const RiftUI& other) = delete;
		RiftUI(RiftUI&& other) noexcept = delete;
		RiftUI& operator=(const RiftUI& other) = delete;
		RiftUI& operator=(RiftUI&& other) noexcept = delete;

		void init(GameObject* pCanvas) { m_pCanvas = pCanvas; }
		GameObject* getCanvas() const { return m_pCanvas; }
		void disable();
		void enable();
		void reset() { m_pCanvas = nullptr; }
	private:
		friend class Singleton;
		RiftUI() = default;

		GameObject* m_pCanvas;
	};


}
