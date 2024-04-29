#pragma once
#include <glm/glm.hpp>
#include "BaseComponent.h"

namespace rift2d
{
	class Transform final : public BaseComponent
	{
	public:
		Transform(GameObject* owner);
		virtual ~Transform() override = default;

		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;

		const glm::vec3& getLocalPosition() const { return m_localPosition; }
		const glm::vec3& getWorldPosition();

		void setLocalPosition(float x, float y, float z);
		void setLocalPosition(const glm::vec3& pos);
		void addLocalOffset(float x, float y);

		void setWorldPosition(float x, float y, float z = 1.f);

		void broadcastDirtyTransform();
	private:
		glm::vec3 m_localPosition{};
		glm::vec3 m_worldPosition{};

		bool m_isDirty{true};

		void updateWorldTransform();
	};
}
