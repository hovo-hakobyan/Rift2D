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

	auto pos = getOwner()->getTransform()->getWorldPosition();
	pos.x += settings::TILE_WIDTH / 2;
	pos.y += settings::TILE_HEIGHT / 2;
	LevelGrid::GetInstance().setTile(static_cast<int>(pos.x), static_cast<int>(pos.y),false, getOwner());
}

void rift2d::LevelGridTile::end()
{
	BaseComponent::end();
	auto pos = getOwner()->getTransform()->getWorldPosition();
	pos.x += settings::TILE_WIDTH / 2;
	pos.y += settings::TILE_HEIGHT / 2;
	LevelGrid::GetInstance().setTile(static_cast<int>(pos.x), static_cast<int>(pos.y), true, getOwner());
}
