#include "ContactListener.h"

#include <iostream>
#include <box2d/b2_contact.h>
#include "RigidBody2D.h"

namespace rift2d
{
	void ContactListener::BeginContact(b2Contact* contact)
	{

		auto* bodyA = static_cast<RigidBody2D*>(contact->GetFixtureA()->GetBody()->GetUserData());
		if (!bodyA) return;

		auto* bodyB = static_cast<RigidBody2D*>(contact->GetFixtureB()->GetBody()->GetUserData());
		if (!bodyB) return;
		bodyA->evaluateBeginOverlap(bodyB);
		bodyB->evaluateBeginOverlap(bodyA);
	}

	void ContactListener::EndContact(b2Contact* contact)
	{
		auto* bodyA = static_cast<RigidBody2D*>(contact->GetFixtureA()->GetBody()->GetUserData());
		if (!bodyA) return;

		auto* bodyB = static_cast<RigidBody2D*>(contact->GetFixtureB()->GetBody()->GetUserData());
		if (!bodyB) return;

		bodyA->evaluateEndOverlap(bodyB);
		bodyB->evaluateEndOverlap(bodyA);
	}
}
