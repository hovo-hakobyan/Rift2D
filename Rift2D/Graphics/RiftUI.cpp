#include "RiftUI.h"
#include "GameObject.h"

namespace rift2d
{
	RiftUI::~RiftUI() = default;

	void RiftUI::disable()
	{
		m_pCanvas->disable();
	}

	void RiftUI::enable()
	{
		m_pCanvas->enable();
	}
}
