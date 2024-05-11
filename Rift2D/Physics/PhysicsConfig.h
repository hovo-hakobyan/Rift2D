#pragma once
#include <cstdint>
#include <functional>

#include "GameObject.h"

namespace rift2d
{
	class RigidBody2D;
}

//class rift2d::RigidBody2D;
namespace physics
{
	enum class CollisionGroup : uint16_t
	{
		Default	=	0x0001,
		Group1	=	0x0002,
		Group2	=	0x0004,
		Group3	=	0x0008,
		Group4	=	0x0010,
		Group5	=	0x0020,
		Group6	=	0x0040,
		Group7	=	0x0080,
		Group8	=	0x0100,
		Group9	=	0x0200,
		Group10	=	0x0400,
		Group11	=	0x0800,
		Group12	=	0x1000,
		Group13	=	0x2000,
		Group14	=	0x4000,
		Group15	=	0x8000,
		All		=	0xFFFF

	};

	constexpr float			DEFAULT_GRAVITY = 0.f;
	constexpr uint32_t		VELOCITY_ITERATIONS = 6;
	constexpr uint32_t		POSITION_ITERATIONS = 2;

	using OverlapEventCallback = std::function<void(rift2d::RigidBody2D* body, rift2d::RigidBody2D* otherBody, rift2d::GameObject* gameObject, rift2d::GameObject* otherGameObject )>;

}
