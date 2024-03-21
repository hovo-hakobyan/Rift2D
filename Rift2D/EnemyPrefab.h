#pragma once
#include "Prefab.h"

namespace rift2d
{
	class GameObject;
	class Scene;
	class EnemyPrefab final : public Prefab
	{
	public:

		EnemyPrefab() = default;
		~EnemyPrefab() override = default;
		EnemyPrefab(const EnemyPrefab& other) = delete;
		EnemyPrefab(EnemyPrefab&& other) = delete;
		EnemyPrefab& operator=(const EnemyPrefab& other) = delete;
		EnemyPrefab& operator=(EnemyPrefab&& other) = delete;

		void setup(GameObject* rootObj, Scene* pScene) override;
	};
}
