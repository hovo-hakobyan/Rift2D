#pragma once
#include "Prefab.h"

namespace digger
{
	class Enemy final : public rift2d::Prefab
	{
	public:

		Enemy() = default;
		~Enemy() override = default;
		Enemy(const Enemy& other) = delete;
		Enemy(Enemy&& other) = delete;
		Enemy& operator=(const Enemy& other) = delete;
		Enemy& operator=(Enemy&& other) = delete;

		void setup(rift2d::GameObject* rootObj, rift2d::Scene* pScene) override;
	
	};


}
