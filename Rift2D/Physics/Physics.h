#pragma once
#include "Singleton.h"
#include "RigidBody2D.h"
#include <memory>

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

		void update();
		void* createRigidBody(const RigidBodyDef& bodyDef) const;

	private:
		friend class Singleton;
		Physics();

		class Impl;
		std::unique_ptr<Impl> m_pImpl;

		
	};

}
