#pragma once
#include <Prefab.h>

namespace digger
{
	class EmeraldPrefab :public rift2d::Prefab
	{
	public:

		EmeraldPrefab() = default;
		~EmeraldPrefab() override = default;
		EmeraldPrefab(const EmeraldPrefab& other) = delete;
		EmeraldPrefab(EmeraldPrefab&& other) = delete;
		EmeraldPrefab& operator=(const EmeraldPrefab& other) = delete;
		EmeraldPrefab& operator=(EmeraldPrefab&& other) = delete;

		void setup(rift2d::GameObject* rootObj, rift2d::Scene* pScene) override;

	};


}
