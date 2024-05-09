#pragma once
#include <memory>
#include <box2d/b2_world_callbacks.h>
#include "Interfaces.h"

namespace rift2d
{
	class ContactListener : public b2ContactListener
	{

	public:
		ContactListener() = default;
		~ContactListener() = default;
		ContactListener(const ContactListener& other) = delete;
		ContactListener(ContactListener&& other) = delete;
		ContactListener& operator=(const ContactListener& other) = delete;
		ContactListener& operator=(ContactListener&& other) = delete;

		void BeginContact(b2Contact* contact) override;
		void EndContact(b2Contact* contact) override;
	};


}
