#include "RigidBody2D.h"
#include "GameObject.h"
#include "Physics.h"
#include "Transform.h"
#include "Utils.h"
#include <box2d/b2_body.h>

namespace rift2d
{
	class RigidBody2D::Impl
	{
	public:
		Impl(GameObject* owner, const RigidBodyDef& bodyDef):
		m_bodyDef(bodyDef),
		m_pOwner(owner){}

		void init()
		{
			const auto transform = m_pOwner->getTransform();
			const auto pos = transform->getWorldPosition();
			m_bodyDef.pos = glm::vec2{ pos.x,pos.y };

			m_pBody = static_cast<b2Body*>(Physics::GetInstance().createRigidBody(m_bodyDef));
		}

		void update()
		{
			const auto newPos = m_pBody->GetPosition();
			const auto transform = m_pOwner->getTransform();
			transform->setWorldPosition(Utils::metersToPixels(glm::vec2{ newPos.x,newPos.y }));
		}

		void* getBody() const
		{
			return m_pBody;
		}
	private:
		RigidBodyDef m_bodyDef{};
		b2Body* m_pBody{};
		GameObject* m_pOwner{};
	};


	RigidBody2D::RigidBody2D(GameObject* owner, RigidBodyDef bodyDef) :
		BaseComponent(owner),
		m_pImpl(std::make_unique<Impl>(owner,bodyDef))
	{}

	RigidBody2D::~RigidBody2D() = default;

	void RigidBody2D::init()
	{
		BaseComponent::init();

		m_pImpl->init();
	}

	void RigidBody2D::update()
	{
		m_pImpl->update();
	}

	void* RigidBody2D::getBody() const
	{
		return m_pImpl->getBody();
	}

}
