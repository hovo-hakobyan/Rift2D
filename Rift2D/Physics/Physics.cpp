#include "Physics.h"
#include <box2d/b2_world.h>

#include "TimeManager.h"

rift2d::Physics::~Physics() = default;

void rift2d::Physics::init()
{
	m_physicsWorld = new b2World({0.f,-9.8f});
	m_positionIterations = 2;
	m_velocityIterations = 6;
}

void rift2d::Physics::destroy()
{
	delete m_physicsWorld;
	m_physicsWorld = nullptr;
}

void rift2d::Physics::update()
{
	m_physicsWorld->Step(TimeManager::GetInstance().getFixedTime(), m_velocityIterations, m_positionIterations);
}
