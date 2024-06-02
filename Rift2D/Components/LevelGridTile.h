#pragma once
#include "BaseComponent.h"

namespace rift2d
{
	class LevelGridTile final : public BaseComponent, public IComponentWatcher
	{
	public:
		LevelGridTile(GameObject* owner);
		virtual ~LevelGridTile() override = default;
		LevelGridTile(const LevelGridTile& other) = delete;
		LevelGridTile(LevelGridTile&& other) = delete;
		LevelGridTile& operator=(const LevelGridTile& other) = delete;
		LevelGridTile& operator=(LevelGridTile&& other) = delete;

		virtual void init() override;

		virtual void onComponentRemoved(BaseComponent* component) override;
	};



}
