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

		const glm::vec2& getLocalPosition() const { return m_localPosition; }
		const glm::vec2& getWorldPosition();

		void setLocalPosition(float x, float y);
		void setLocalPosition(const glm::vec2& pos);
		void addLocalOffset(float x, float y);
		void setWorldPosition(float x, float y);
		void setWorldPosition(const glm::vec2& pos);

		float getLocalRotation(bool inDegrees = false) const;
		float getWorldRotation(bool inDegrees = false);

		void setLocalRotation(float angle, bool isDegree = false);
		void setWorldRotation(float angle, bool isDegree = false);
		void rotate(float angle, bool isDegree = false);

		

		void broadcastDirtyTransform();
	private:
		glm::vec2 m_localPosition{};
		glm::vec2 m_worldPosition{};

		float m_localRotation{};
		float m_worldRotation{};

		bool m_isDirty{true};

		void updateWorldTransform();
	};
}
