#pragma once
#include "Prefab.h"

namespace digger
{
	class DiggerUI final : public rift2d::Prefab
	{
	public:
		DiggerUI() = default;
		~DiggerUI() override = default;
		DiggerUI(const DiggerUI& other) = delete;
		DiggerUI(DiggerUI&& other) = delete;
		DiggerUI& operator=(const DiggerUI& other) = delete;
		DiggerUI& operator=(DiggerUI&& other) = delete;

		void setup(rift2d::GameObject* rootObj, rift2d::Scene* pScene) override;
	};


}
