#include "LevelGridTile.h"

#include "GameObject.h"
#include "LevelGrid.h"
#include "Settings.h"
#include "Transform.h"

rift2d::LevelGridTile::LevelGridTile(GameObject* owner):
BaseComponent(owner)
{
}

void rift2d::LevelGridTile::init()
{
	BaseComponent::init();

	const auto transform = getOwner()->getTransform();
	transform->registerWatcher(this);

	auto pos = transform->getWorldPosition();
	pos.x += riftSettings::TILE_WIDTH / 2;
	pos.y += riftSettings::TILE_HEIGHT / 2;
	LevelGrid::GetInstance().setTile(static_cast<int>(pos.x), static_cast<int>(pos.y),false, getOwner());
}



void rift2d::LevelGridTile::onComponentRemoved(BaseComponent*)
{
	auto pos = getOwner()->getTransform()->getWorldPosition();
	pos.x += riftSettings::TILE_WIDTH / 2;
	pos.y += riftSettings::TILE_HEIGHT / 2;
	LevelGrid::GetInstance().setTile(static_cast<int>(pos.x), static_cast<int>(pos.y), true, getOwner());
}
