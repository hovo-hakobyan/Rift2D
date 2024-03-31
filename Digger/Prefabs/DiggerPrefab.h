#pragma once
#include "Prefab.h"

namespace digger
{
	class GameObject;
	class Scene;
	class DiggerPrefab final : public rift2d::Prefab
	{
	public:

		DiggerPrefab() = default;
		~DiggerPrefab() override = default;
		DiggerPrefab(const DiggerPrefab& other) = delete;
		DiggerPrefab(DiggerPrefab&& other) = delete;
		DiggerPrefab& operator=(const DiggerPrefab& other) = delete;
		DiggerPrefab& operator=(DiggerPrefab&& other) = delete;

		void setup(rift2d::GameObject* rootObj, rift2d::Scene* pScene) override;
	};
}
