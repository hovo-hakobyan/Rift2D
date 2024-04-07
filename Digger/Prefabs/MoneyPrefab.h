#pragma once
#include <Prefab.h>
namespace digger
{
	class MoneyPrefab :public rift2d::Prefab
	{
	public:
		MoneyPrefab() = default;
		~MoneyPrefab() override = default;
		MoneyPrefab(const MoneyPrefab& other) = delete;
		MoneyPrefab(MoneyPrefab&& other) = delete;
		MoneyPrefab& operator=(const MoneyPrefab& other) = delete;
		MoneyPrefab& operator=(MoneyPrefab&& other) = delete;

		void setup(rift2d::GameObject* rootObj, rift2d::Scene* pScene) override;
	};


}
