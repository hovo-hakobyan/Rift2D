#pragma once
#include "Singleton.h"

namespace rift2d
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool processInput();
	};

}
