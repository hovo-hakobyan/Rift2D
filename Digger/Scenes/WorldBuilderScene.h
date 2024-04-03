#pragma once
#include "Scene.h"
namespace digger
{
	class WorldBuilderScene : public rift2d::Scene
	{
	public:
		WorldBuilderScene();
		~WorldBuilderScene() override = default;
		WorldBuilderScene(const WorldBuilderScene& other) = delete;
		WorldBuilderScene(WorldBuilderScene&& other) noexcept = delete;
		WorldBuilderScene& operator=(const WorldBuilderScene& other) = delete;
		WorldBuilderScene& operator=(WorldBuilderScene&& other) noexcept = delete;

	protected:
		virtual void init() override;
	};

}
