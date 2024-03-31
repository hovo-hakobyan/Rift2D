#pragma once
#include "Prefab.h"

namespace digger
{
	class EnemyPrefab final : public rift2d::Prefab
	{
	public:

		EnemyPrefab() = default;
		~EnemyPrefab() override = default;
		EnemyPrefab(const EnemyPrefab& other) = delete;
		EnemyPrefab(EnemyPrefab&& other) = delete;
		EnemyPrefab& operator=(const EnemyPrefab& other) = delete;
		EnemyPrefab& operator=(EnemyPrefab&& other) = delete;

		void setup(rift2d::GameObject* rootObj, rift2d::Scene* pScene) override;
	};
}
