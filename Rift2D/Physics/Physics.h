#pragma once
#include "Singleton.h"
#include <cstdint>
class b2World;

namespace rift2d
{
	class Physics final : public Singleton<Physics>
	{
	public:
		~Physics() override;
		Physics(const Physics& other) = delete;
		Physics(Physics&& other) noexcept = delete;
		Physics& operator=(const Physics& other) = delete;
		Physics& operator=(Physics&& other) noexcept = delete;

		void init();
		void destroy();
		void update();

		b2World& getWorld() const { return *m_physicsWorld; }
	private:
		friend class Singleton;
		Physics() = default;

		b2World* m_physicsWorld;
		int32_t m_velocityIterations;
		int32_t m_positionIterations;
	};

}
