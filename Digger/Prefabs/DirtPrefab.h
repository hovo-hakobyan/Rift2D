#pragma once
#include <Prefab.h>
namespace digger
{
	class GameObject;
	class Scene;
	class DirtPrefab : public rift2d::Prefab
	{
		DirtPrefab() = default;
		~DirtPrefab() override = default;
		DirtPrefab(const DirtPrefab& other) = delete;
		DirtPrefab(DirtPrefab&& other) = delete;
		DirtPrefab& operator=(const DirtPrefab& other) = delete;
		DirtPrefab& operator=(DirtPrefab&& other) = delete;

		void setup(rift2d::GameObject* rootObj, rift2d::Scene* pScene) override;
	};
}


