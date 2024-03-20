#pragma once
#include "Prefab.h"

namespace rift2d
{
	class GameObject;
	class Scene;
	class DiggerPrefab final : public Prefab
	{
	public:

		DiggerPrefab() = default;
		~DiggerPrefab() override = default;
		DiggerPrefab(const DiggerPrefab& other) = delete;
		DiggerPrefab(DiggerPrefab&& other) = delete;
		DiggerPrefab& operator=(const DiggerPrefab& other) = delete;
		DiggerPrefab& operator=(DiggerPrefab&& other) = delete;

		void setup(GameObject* rootObj, Scene* pScene) override;
	};
}
